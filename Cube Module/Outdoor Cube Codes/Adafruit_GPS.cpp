/***********************************
This is our GPS library

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
BSD license, check license.txt for more information
All text above must be included in any redistribution

20150125 Originally written to run with Arduino core, this has been
Ported to run with Raspberry Pi Linux (raspbian wheezy) by David Knight
(diemkae@gmail.com) and tested with SKM53 GPS receiver running at
9600 baud.

****************************************/

//#include <Adafruit_GPS.h>
#include "Adafruit_GPS.h"

FILE *fp;
int debug = 0;

// how long are max NMEA lines to parse?
#define MAXLINELENGTH 120

// we double buffer: read one line in and leave one for the main program
volatile char line1[MAXLINELENGTH];
volatile char line2[MAXLINELENGTH];
// our index into filling the current line
volatile uint8_t lineidx = 0;
// pointers to the double buffers
volatile char *currentline;
volatile char *lastline;
volatile boolean recvdflag;
volatile boolean inStandbyMode;

#ifdef COOKED
//  if the tty device is running in "cooked" more (as opposed to "raw" mode,
//  a lot of bogus traffic that gets "read" by fgetc( between valid nmea
//  sentences.
//
//  Since some Linux distros (e.g. debian and debian-based like
//  Ubuntu and raspbian) create /dev/ttyUSBx devices in cooked mode and some
//  other distros like Fedora (16, at least) create ttyUSBx devices in raw
//  mode, GPS.begin() sets the device into raw mode.  If for some reason the device 
//  cannot be set to or used in raw mode, used #define COOKED to enable this code,
//  which endeavors to ignore the bogus traffic.
//
//  chkHighTime - returns 0 if timestamp >= latest timestamp
//                        1 if timestamp is "older"
//
uint32_t highTime = 0;        // highest parsed timestamp value
static int chkHighTime(int newTime) {
  int rc = 0;
  // check for invalid timestamp in current sentence
  //
  if (newTime >= highTime)
    {
      highTime = newTime;
    }
  else
    {
      if (debug)
        fprintf (stderr,"bad timestamp (GPStime:%d < highTime:%d)\n", newTime,
            highTime);
      rc = 1;        // bad timestamp
    }

  return rc;
}
#endif

//
// GPS.parse() - returns true for good parses, false for NG
//

uint32_t GPStime = 0;;

boolean
Adafruit_GPS::parse (char *nmea)
{
  boolean rc = false;
  // do checksum check

#ifdef COOKED
  // nmea[] may or may not have a newline after the checksum
  // This occurs frequently with SMK53 GPS receivers
  //    dmk 20150128
  if (nmea[strlen (nmea) - 3] == '*') {
	strcat(nmea,"\n"); // fake having received a NL after checksum
	if (debug) fprintf(stderr,"NL added after checksum\n");
  }
#endif

  // first look if we even have one
  if (nmea[strlen (nmea) - 4] == '*')
    {
      uint16_t sum = parseHex (nmea[strlen (nmea) - 3]) * 16;
      sum += parseHex (nmea[strlen (nmea) - 2]);

      // check checksum 
      for (uint8_t i = 1; i < (strlen (nmea) - 4); i++)
      {
        sum ^= nmea[i];
      }
      if (sum != 0)
      {
        // bad checksum :(
		if(debug)fprintf(stderr,"bad checksum\n");
        return false;
      }
    } else {
  		char star = nmea[strlen (nmea) - 4];
	    if(debug)fprintf(stderr,"star=%c not an NMEA sentence\n",star);
	}

  // look for response to PMTK_Q_RELEASE ("$PMTK705...")
  if (strstr (nmea, "$PMTK705"))
    {
      // just print it
      printf ("PMTK_Q_RELEASE:%s\n", nmea);
      return true;
    }

  // look for a few common sentences
  //
  if (strstr (nmea, "$GPGGA"))
    {
      // found GGA
      char *p = nmea;
      // get time
      p = strchr (p, ',') + 1;
      float timef = atof (p);
      GPStime = timef;
#ifdef COOKED
	  if (chkHighTime(GPStime)) return false;
#endif
      hour = GPStime / 10000;
      minute = (GPStime % 10000) / 100;
      seconds = (GPStime % 100);

      milliseconds = fmod (timef, 1.0) * 1000;

      // parse out latitude
      p = strchr (p, ',') + 1;
      latitude = atof (p);

      p = strchr (p, ',') + 1;
      if (p[0] == 'N')
        lat = 'N';
      else if (p[0] == 'S')
        lat = 'S';
      else if (p[0] == ',')
        lat = 0;
      else {
		fprintf(stderr,"GGA lat [%c] != 'N' | 'S'\n", p[0]);
        return false;
	  }

      // parse out longitude
      p = strchr (p, ',') + 1;
      longitude = atof (p);

      p = strchr (p, ',') + 1;
      if (p[0] == 'W')
        lon = 'W';
      else if (p[0] == 'E')
        lon = 'E';
      else if (p[0] == ',')
        lon = 0;
      else {
		fprintf(stderr,"GGA lon [%c] != 'E' | 'W'\n", p[0]);
        return false;
	  }

      p = strchr (p, ',') + 1;
      fixquality = atoi (p);

      p = strchr (p, ',') + 1;
      satellites = atoi (p);

      p = strchr (p, ',') + 1;
      HDOP = atof (p);

      p = strchr (p, ',') + 1;
      altitude = atof (p);
      p = strchr (p, ',') + 1;
      p = strchr (p, ',') + 1;
      geoidheight = atof (p);

      rc = true;
    }
  else if (strstr (nmea, "$GPRMC"))
    {
      // found RMC
      char *p = nmea;

      // get time
      p = strchr (p, ',') + 1;
      float timef = atof (p);
      GPStime = timef;
#ifdef COOKED
	  if (chkHighTime(GPStime)) return false;
#endif
      hour = GPStime / 10000;
      minute = (GPStime % 10000) / 100;
      seconds = (GPStime % 100);

      milliseconds = fmod (timef, 1.0) * 1000;

      p = strchr (p, ',') + 1;
      // Serial.println(p);
      if (p[0] == 'A')
        fix = true;
      else if (p[0] == 'V')
        fix = false;
      else {
		fprintf(stderr,"RMC fix [%c] != 'A' | 'V'\n", p[0]);
        return false;
	  }

      // parse out latitude
      p = strchr (p, ',') + 1;
      latitude = atof (p);

      p = strchr (p, ',') + 1;
      if (p[0] == 'N')
        lat = 'N';
      else if (p[0] == 'S')
        lat = 'S';
      else if (p[0] == ',')
        lat = 0;
      else {
		fprintf(stderr,"RMC lat [%c] != 'N' | 'S'\n", p[0]);
        return false;
	  }

      // parse out longitude
      p = strchr (p, ',') + 1;
      longitude = atof (p);

      p = strchr (p, ',') + 1;
      if (p[0] == 'W')
        lon = 'W';
      else if (p[0] == 'E')
        lon = 'E';
      else if (p[0] == ',')
        lon = 0;
      else {
		fprintf(stderr,"RMC lon [%c] != 'E' | 'W'\n", p[0]);
        return false;
	  }

      // speed
      p = strchr (p, ',') + 1;
      speed = atof (p);

      // angle
      p = strchr (p, ',') + 1;
      angle = atof (p);

      p = strchr (p, ',') + 1;
      uint32_t fulldate = atof (p);
      day = fulldate / 10000;
      month = (fulldate % 10000) / 100;
      year = (fulldate % 100);

      rc = true;
    }
  // end of parsing - we don't parse the other sentences, yet!
}

char
Adafruit_GPS::read (void)
{
  char c = 0;

  if (paused)
    return c;

  c = fgetc (fp);

  if (c == '$')
    {
      currentline[lineidx] = 0;    // start of new sentence
      lineidx = 0;
    }
  if (c == '\n')
    {
      currentline[lineidx] = 0;    // replace NL with NULL
      if (currentline == line1)
    {
      currentline = line2;
      lastline = line1;
    }
      else
    {
      currentline = line1;
      lastline = line2;
    }

      if (debug)
    	fprintf (stderr,"--\n%s\n", lastline);

      lineidx = 0;
      recvdflag = true;
    }

  currentline[lineidx++] = c;
  if (lineidx >= MAXLINELENGTH)
    lineidx = MAXLINELENGTH - 1;

  return c;
}

// Constructor when using *nix stream I/O
Adafruit_GPS::Adafruit_GPS (void *)
{
  common_init ();        // Set everything to common state, then...
}


// Initialization code used by all constructor types
void
Adafruit_GPS::common_init (void)
{
  recvdflag = false;
  paused = false;
  lineidx = 0;
  currentline = line1;
  lastline = line2;

  hour = minute = seconds = year = month = day = fixquality = satellites = 0;    // uint8_t
  lat = lon = mag = 0;        // char
  fix = false;            // boolean
  milliseconds = 0;        // uint16_t
  latitude = longitude = geoidheight = altitude = speed = angle = magvariation = HDOP = 0.0;    // float
}

//
void
Adafruit_GPS::begin (char *device, uint16_t baud)
{
  // call with parameters like:
  //
  //  GPS.begin("/dev/ttyAMA0", 9600);
  //
  int rc = 0;
  char cmd[80];

  //  Using the stty cmd here, to set the baud rate,
  //  is kind of a cheat, but it works ;-)
  //  Use "raw" mode to eliminate inter-sentence drek that fails in DPS.parse
  sprintf(cmd,"stty -F %s %d raw", device, baud);
  rc = system(cmd);
  if ( rc != 0 ) {
     fprintf(stderr, "GPS.begin [%s] failed\n", cmd);
	 exit(1);
  }

  fp = fopen (device, "r+");
  if (fp == NULL)
    {
      perror ("GPS.begin.fopen");
      exit (1);
    }
}

void
Adafruit_GPS::sendCommand (char *str)
{
  int rc = 0;
  if(debug)fprintf (stderr,"Adafruit_GPS.sendCommand:[%s]\n", str);
  rc = fprintf (fp, "%s\n", str); // write to serial/GPS device
  if (rc < 0)
    {
      perror ("Adafruit_GPS.sendCommand");
      exit (1);
    }
}

boolean
Adafruit_GPS::newNMEAreceived (void)
{
  return recvdflag;
}

void
Adafruit_GPS::pause (boolean p)
{
  paused = p;
}

char *
Adafruit_GPS::lastNMEA (void)
{
  recvdflag = false;
  return (char *) lastline;
}

// read a Hex value and return the decimal equivalent
uint8_t
Adafruit_GPS::parseHex (char c)
{
  if (c < '0')
    return 0;
  if (c <= '9')
    return c - '0';
  if (c < 'A')
    return 0;
  if (c <= 'F')
    return (c - 'A') + 10;
}

boolean
Adafruit_GPS::waitForSentence (char *wait4me, uint8_t max)
{
  char str[20];

  uint8_t i = 0;
  while (i < max)
    {
      if (newNMEAreceived ())
    {
      char *nmea = lastNMEA ();
      strncpy (str, nmea, 20);
      str[19] = 0;
      i++;

      if (strstr (str, wait4me))
        return true;
    }
    }

  return false;
}

boolean
Adafruit_GPS::LOCUS_StartLogger (void)
{
  sendCommand ((char *) PMTK_LOCUS_STARTLOG);
  recvdflag = false;
  return waitForSentence ((char *) PMTK_LOCUS_LOGSTARTED);
}

boolean
Adafruit_GPS::LOCUS_ReadStatus (void)
{
  sendCommand ((char *) PMTK_LOCUS_QUERY_STATUS);

  if (!waitForSentence ((char *) "$PMTKLOG"))
    return false;

  char *response = lastNMEA ();
  uint16_t parsed[10];
  uint8_t i;

  for (i = 0; i < 10; i++)
    parsed[i] = -1;

  response = strchr (response, ',');
  for (i = 0; i < 10; i++)
    {
      if (!response || (response[0] == 0) || (response[0] == '*'))
    break;
      response++;
      parsed[i] = 0;
      while ((response[0] != ',') &&
         (response[0] != '*') && (response[0] != 0))
    {
      parsed[i] *= 10;
      char c = response[0];
      //if (isDigit(c))
      if (isdigit (c))
        parsed[i] += c - '0';
      else
        parsed[i] = c;
      response++;
    }
    }
  LOCUS_serial = parsed[0];
  LOCUS_type = parsed[1];
  //if (isAlpha(parsed[2])) {
  if (isalpha (parsed[2]))
    {
      parsed[2] = parsed[2] - 'a' + 10;
    }
  LOCUS_mode = parsed[2];
  LOCUS_config = parsed[3];
  LOCUS_interval = parsed[4];
  LOCUS_distance = parsed[5];
  LOCUS_speed = parsed[6];
  LOCUS_status = !parsed[7];
  LOCUS_records = parsed[8];
  LOCUS_percent = parsed[9];

  return true;
}

// Standby Mode Switches
boolean
Adafruit_GPS::standby (void)
{
  if (inStandbyMode)
    {
      return false;        // Returns false if already in standby mode, so that you do not wake it up by sending commands to GPS
    }
  else
    {
      inStandbyMode = true;
      sendCommand ((char *) PMTK_STANDBY);
      //return waitForSentence((char *)PMTK_STANDBY_SUCCESS);  // don't seem to be fast enough to catch the message, or something else just is not working
      return true;
    }
}

boolean
Adafruit_GPS::wakeup (void)
{
  if (inStandbyMode)
    {
      inStandbyMode = false;
      sendCommand ((char *) "");    // send byte to wake it up
      return waitForSentence ((char *) PMTK_AWAKE);
    }
  else
    {
      return false;        // Returns false if not in standby mode, nothing to wakeup
    }
}

#ident "$Name:  $ $Header: /projRCS/rpi/AdaGPS/Adafruit_GPS.cpp,v 1.11 2015/01/30 13:35:16 dmk%leno Exp $"
