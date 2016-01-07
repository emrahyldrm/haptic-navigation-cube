#include "compass.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>

//#include <Adafruit_GPS.h>
#include "Adafruit_GPS.h"

using namespace std;
// HATA PAYLARI
#define COMPASSHATA			 	5
#define GPSHATA					 	0.006
#define CURRENT_LOCATION 	3
// COMPASS DEGERLERI

#define AB 128
#define AJ 68
#define BA 9
#define BC 68
#define BF 130
#define CB 290
#define CD 67
#define DC 304
#define DE 147
#define ED 12 
#define EG 297
#define EK 72
#define FB 8
#define FG 133
#define GE 70
#define GF 12
#define HI 130
#define HJ 338
#define IK 303
#define IH 12
#define JA 290 
#define JH 71
#define KE 296
#define KI 67

// LONGITUDE DEGERLERI
#define LONGITUDEVALUE_A 2921.34290
#define LONGITUDEVALUE_B 2921.402100
#define LONGITUDEVALUE_C 2921.387207
#define LONGITUDEVALUE_D 2921.380300
#define LONGITUDEVALUE_E 2921.568604
#define LONGITUDEVALUE_F 2921.462800
#define LONGITUDEVALUE_G 2921.589111
#define LONGITUDEVALUE_H 2921.317871
#define LONGITUDEVALUE_I 2921.524470
#define LONGITUDEVALUE_J 2921.306068
#define LONGITUDEVALUE_K 2921.552490

// LATITUDE DEGERLERI
#define LATITUDEVALUE_A 4048.511230
#define LATITUDEVALUE_B 4048.496094
#define LATITUDEVALUE_C 4048.447754
#define LATITUDEVALUE_D 4048.449700
#define LATITUDEVALUE_E 4048.412842
#define LATITUDEVALUE_F 4048.488100
#define LATITUDEVALUE_G 4048.460693
#define LATITUDEVALUE_H 4048.298584
#define LATITUDEVALUE_I 4048.261417
#define LATITUDEVALUE_J 4048.400254
#define LATITUDEVALUE_K 4048.339355

extern int debug;  // parsing.c controls debug output
char device[20] = "/dev/ttyAMA0";  // default device

// on the Pi, we use fopen() and fgetc() to read the GPS "messages"
Adafruit_GPS GPS (NULL);

static void
usage(void) {
  printf("Usage: parsing [-d] [/dev/ttyXXXX]\n");
  printf("     -d enables debug output\n");
  printf("     /dev/ttyXXXX specifies alternate serial device,\n");
  printf("         default is /dev/ttyAMA0.\n");
  exit(0);
}

void
setup ()
{
  int rc = 0;

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800

  GPS.begin ((char *)device,9600);

GPS.sendCommand ((char *) PMTK_SET_NMEA_OUTPUT_ALLDATA);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  //GPS.sendCommand ((char *) PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand((char *)PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  GPS.sendCommand ((char *) PMTK_SET_NMEA_UPDATE_1HZ);	// 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Ask for firmware version
  //mySerial.println(PMTK_Q_RELEASE);
  //    printf ("setup():%s\n", PMTK_Q_RELEASE);
  //
  // I believe that should be a sendCommand(), as below. See also change
  // to Adafruit_GPS.cpp to recognize & print the response sentence (dmk)
  //
  GPS.sendCommand ((char *) PMTK_Q_RELEASE);
  // don't sleep here, or the PMTK_Q_RELEASE response will be missed.
}

unsigned int now = 0;
unsigned int lastPrint = 0;
unsigned int goodParse = 0;
unsigned int badParse = 0;

void
loop (float *latitude, float *longitude, int *fix)				// run over and over again
{	

  char c = GPS.read ();

  now = time (0);

  // if a good NMEA sentence is received, we can check the checksum, parse it...
  //
  if (GPS.newNMEAreceived ())
  {
    if (GPS.parse (GPS.lastNMEA ()))
	{  	// call to GPS.lastNMEA() sets the newNMEAreceived() flag to false
	  goodParse++;
	}
      else
	{
	  badParse++;
	  if(debug)fprintf(stderr, "GPS.parse ERROR\n");
	  //return;  // ignore bad sentence, wait for another
	}
    //  GPS.lastNMEA parse OK, see if it's time to print
    if (now >= lastPrint + 2)
	{
	  lastPrint = now;
	  printf ("\nGPS.lastNMEA OK:%d FAILED:%d\n", goodParse, badParse);
	  goodParse = badParse = 0;
	  printf ("Time: %02d:%02d:%02d.%03d ",
	   GPS.hour, GPS.minute, GPS.seconds, GPS.milliseconds);
	  printf ("Date: %02d/%02d/%d\n", GPS.day, GPS.month, GPS.year);
	  printf ("Fix: %d quality: %d\n", GPS.fix, GPS.fixquality);
	  if (GPS.fix)
	  {
	    printf ("Location: %f %c, ", GPS.latitude, GPS.lat);
	    printf ("%f, %c\n", GPS.longitude, GPS.lon);
	    printf ("Speed (knots): %f\n", GPS.speed);
	    printf ("Angle: %f\n", GPS.angle);
	    printf ("Altitude: %f\n", GPS.altitude);
	    printf ("Satellites: %d\n", GPS.satellites);
	    
	    *latitude = GPS.latitude;
	    *longitude = GPS.longitude;
			*fix = GPS.fixquality;
	  }
	}
  }
}

int sendLocation(char location){

	if(location == 'A')
		return 1;
	if(location == 'B')
		return 2;
	if(location == 'C')
		return 3;
	if(location == 'D')
		return 4;
	if(location == 'E')
		return 5;
	if(location == 'F')
		return 6;
	if(location == 'G')
		return 7;
	if(location == 'H')
		return 8;
	if(location == 'I')
		return 9;
	if(location == 'J')
		return 10;
	if(location == 'K')
		return 11;
}

void locationA(const char msg[],const int i);
void locationB(const char msg[],const int i);
void locationC(const char msg[],const int i);
void locationD(const char msg[],const int i);
void locationE(const char msg[],const int i);
void locationF(const char msg[],const int i);
void locationG(const char msg[],const int i);
void locationH(const char msg[],const int i);
void locationI(const char msg[],const int i);
void locationJ(const char msg[],const int i);
void locationK(const char msg[],const int i);

float getAngle();
void selectDevice(int fd, int addr, char * name);
void writeToDevice(int fd, int reg, int val);
void loop (float *latitude, float *longitude, int *fix);


void error(const char *msg)
{
    perror(msg);
    exit(0);
}
void handler(int signal);


//globals
int sockfd, portno, n;



int main(int argc, char **argv){

	system("sudo ./../ServoBlaster-master/user/servod");
	char location = 'C';
	//char msg[6] = {'D','E','G','F','B','C'};
	char *msg;
	int i;
	
	int rc = 0;
	
	
	//socket connection
	//////////////////////////////////////////////////////////////////////
	struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    signal(SIGINT, handler);
    if (argc < 3 || argc > 4) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
	
	//socket connection finish
	//////////////////////////////////////////////////////////////////////////
	
	int clientId = 0;
    usleep(400);
    n = write(sockfd,&clientId,sizeof(int));
    if (n < 0) 
         error("ERROR writing to socket");
    else
        printf("client id has been sent\n");
	
	
	//current location definement
	int current = CURRENT_LOCATION;
	//location = (char)(current + 'A' - 1);

    n = write(sockfd, &current,sizeof(int));
    if (n < 0) 
         error("ERROR writing to socket");
    else
        printf("current location has been sent\n");
	
	
	
	int size = 255;
    n = read(sockfd, &size, sizeof(int));
    cout << "size " << size << endl;
    char shortestPath[size];
    usleep(100);
    n = read(sockfd, shortestPath, size);
	if (n < 0) 
		error("ERROR reading shortest path");
	else
        cout << "shortestPath has been received : " << shortestPath << endl;

	
	location = shortestPath[0];
	msg = shortestPath;
  	// set stdout stream to "line buffered" mode, to facilitate "useful" 
  	//  redirect to to a pipe or a file .
  	rc = setvbuf(stdout, NULL, _IOLBF, 0);
  	if ( rc != 0 ) {
    	perror("parsing.setvbuf");
		exit(1);
  	}

  	debug = 0;  // default

  	//  process cmdline args
/*  	if ( argc >= 2 ) {
    	int n = 1;
    	//  debug: 1/enable, 0/disable debug output here 
    	//         and in the Adafruit_GPS methods
		if ( strcmp(argv[n], "-d") == 0 ) {
  			debug = 1;
			if (argc > n + 1 ) n++;
		}
		if (strncmp(argv[n], "/dev/tty", 8) == 0 ) {
  			strncpy(device, argv[n], sizeof(device));
			if (argc > n + 1 ) n++;
		}
		if (strcmp(argv[n], "-h") == 0 ) {
	  		usage();
		}
  	}
*/
  	setup ();

		system("echo 1=1800us > /dev/servoblaster");
		system("echo 2=1800us > /dev/servoblaster");
	
	
	
	
	for(i = 1; msg[i] != '\0'; i++){
	
		if(tolower(location) == 'a'){
		
			locationA(msg,i);
		}
		
		if(tolower(location) == 'b'){
		
			locationB(msg,i);
		}
	
		if(tolower(location) == 'c'){
		
			locationC(msg,i);
		}
		
		if(tolower(location) == 'd'){
		
			locationD(msg,i);
		}
		
		if(tolower(location) == 'e'){
		
			locationE(msg,i);
		}
		
		if(tolower(location) == 'f'){
		
			locationF(msg,i);
		}
		
		if(tolower(location) == 'h'){
		
			locationH(msg,i);
		}
		
		if(tolower(location) == 'i'){
		
			locationI(msg,i);
		}
		
		if(tolower(location) == 'j'){
		
			locationJ(msg,i);
		}
		
		if(tolower(location) == 'k'){
		
			locationK(msg,i);
		}
	
		location = msg[i];
		
		int loc = sendLocation(location);
		write(sockfd, &loc, sizeof(int));
	}
	
	return 0;
}

void locationA(const char msg[],const int i){

	float longitude;
	float latitude;
	float compass;
	int fix;
	
	printf("You are in A\n");
	
	compass = getAngle(); usleep(25000);
	
	if(tolower(msg[i]) == 'b'){
			
		while(compass < AB - COMPASSHATA || compass > AB + COMPASSHATA){
		
			compass = getAngle(); usleep(25000);
		
			if(compass > AB + COMPASSHATA && compass < 180 + AB + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
	
		}while(fix < 1);
		
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to B\n");
		
		while((latitude < LATITUDEVALUE_B - GPSHATA || latitude > LATITUDEVALUE_B + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_B - GPSHATA || longitude > LONGITUDEVALUE_B + GPSHATA) ){			

			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
		
		
	}
			
	if(tolower(msg[i]) == 'j'){
			
		while(compass < AJ - COMPASSHATA || compass > AJ + COMPASSHATA){
		
			compass = getAngle(); usleep(25000);

				if(compass > AJ + COMPASSHATA && compass < 180 + AJ + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
		
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to J\n");
				
		while((latitude < LATITUDEVALUE_J - GPSHATA || latitude > LATITUDEVALUE_J + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_J - GPSHATA || longitude > LONGITUDEVALUE_J + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
}

void locationB(const char msg[],const int i){

	float longitude;
	float latitude;
	double compass;
	int fix;
	
	printf("You are in B\n");
	
	compass = getAngle(); usleep(25000);

	if(tolower(msg[i]) == 'c'){
			
		while(compass < BC - COMPASSHATA || compass > BC + COMPASSHATA){
		
			compass = getAngle(); usleep(25000);
		
			if(compass > BC + COMPASSHATA && compass < 180 + BC + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix != 1);
				
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to C\n");
				
		while((latitude < LATITUDEVALUE_C - GPSHATA || latitude > LATITUDEVALUE_C + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_C - GPSHATA || longitude > LONGITUDEVALUE_C + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
			
	if(tolower(msg[i]) == 'f'){
			
		while(compass < BF - COMPASSHATA || compass > BF + COMPASSHATA){
		
			compass = getAngle(); usleep(25000);
		
			if(compass > BF + COMPASSHATA && compass < 180 + BF + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);

		}while(fix < 1);
		
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to F\n");
				
		while((latitude < LATITUDEVALUE_F - GPSHATA || latitude > LATITUDEVALUE_F + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_F - GPSHATA || longitude > LONGITUDEVALUE_F + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	if(tolower(msg[i]) == 'a'){
			
		while(compass < BA - COMPASSHATA || compass > BA + COMPASSHATA){
		
			compass = getAngle(); usleep(25000);
		
			if(compass > BA + COMPASSHATA && compass < 180 + BA + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{

			loop(&latitude,&longitude,&fix); usleep(600);

		}while(fix < 1);
						
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to A\n");
				
		while((latitude < LATITUDEVALUE_A - GPSHATA || latitude > LATITUDEVALUE_A + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_A - GPSHATA || longitude > LONGITUDEVALUE_A + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
}

void locationC(const char msg[],const int i){

	float longitude;
	float latitude;
	double compass;
	int fix;
	
	printf("You are in C\n");
	
	compass = getAngle(); usleep(25000);
	
	if(tolower(msg[i]) == 'b'){
			
		while(compass < CB - COMPASSHATA || compass > CB + COMPASSHATA){
		
			compass = getAngle(); usleep(25000);
		
			if(compass > CB - 180 - COMPASSHATA && compass < CB - COMPASSHATA){
			
				system("echo 2=2300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=1300us > /dev/servoblaster");
			}
		}
		
		system("echo 1=1800us > /dev/servoblaster");
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);

		}while(fix < 1);
			
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to B\n");
				
		while((latitude < LATITUDEVALUE_B - GPSHATA || latitude > LATITUDEVALUE_B + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_B - GPSHATA || longitude > LONGITUDEVALUE_B + GPSHATA)){

			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
			
	if(tolower(msg[i]) == 'd'){
			
		while(compass < CD - COMPASSHATA || compass > CD + COMPASSHATA){
		
			compass = getAngle(); usleep(25000);
		
			if(compass > CD + COMPASSHATA && compass < 180 + CD + COMPASSHATA){
				
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{

			loop(&latitude,&longitude,&fix); usleep(600);

		}while(fix < 1);
			
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to D\n");
				
		while((latitude < LATITUDEVALUE_D - GPSHATA || latitude > LATITUDEVALUE_D + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_D - GPSHATA || longitude > LONGITUDEVALUE_D + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
}

void locationD(const char msg[],const int i){

	float longitude;
	float latitude;
	double compass;
	int fix;
	
	printf("You are in D\n");
	
	compass = getAngle(); usleep(25000);
			
	if(tolower(msg[i]) == 'c'){
			
		while(compass < DC - COMPASSHATA || compass > DC + COMPASSHATA){
		
			compass = getAngle(); usleep(25000);
		
			if(compass > DC - 180 - COMPASSHATA && compass < DC - COMPASSHATA){
			
				system("echo 2=2300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=1300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);

		}while(fix < 1);
			
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to C\n");
				
		while((latitude < LATITUDEVALUE_C - GPSHATA || latitude > LATITUDEVALUE_C + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_C - GPSHATA || longitude > LONGITUDEVALUE_C + GPSHATA) ){	
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	if(tolower(msg[i]) == 'e'){
			
		while(compass < DE - COMPASSHATA || compass > DE + COMPASSHATA){
		
			compass = getAngle(); usleep(25000);
		
			if(compass > DE + COMPASSHATA && compass < 180 + DE + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
		}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{

			loop(&latitude,&longitude,&fix); usleep(600);

		}while(fix < 1);
		
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to E\n");
				
		while((latitude < LATITUDEVALUE_E - GPSHATA || latitude > LATITUDEVALUE_E + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_E - GPSHATA || longitude > LONGITUDEVALUE_E + GPSHATA) ){

			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
}

void locationE(const char msg[],const int i){

	float longitude;
	float latitude;
	double compass;
	int fix;
	
	printf("You are in E\n");
		
	compass = getAngle(); usleep(25000);

	if(tolower(msg[i]) == 'g'){
			
		while(compass < EG - COMPASSHATA || compass > EG + COMPASSHATA){
		
			compass = getAngle(); usleep(25000);
			
			if(compass > EG - 180 - COMPASSHATA && compass < EG - COMPASSHATA){
			
				system("echo 2=2300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=1300us > /dev/servoblaster");
			}
		}
		cout << "eeee " << compass << endl;
		system("echo 2=1800us > /dev/servoblaster");
		
		do{

			loop(&latitude,&longitude,&fix); usleep(600);

		}while(fix < 1);
			
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to G\n");
		
		while((latitude < LATITUDEVALUE_G - GPSHATA || latitude > LATITUDEVALUE_G + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_G - GPSHATA || longitude > LONGITUDEVALUE_G + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	if(tolower(msg[i]) == 'd'){
			
		while(compass < ED - COMPASSHATA || compass > ED + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > ED + COMPASSHATA && compass < 180 + ED + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{

			loop(&latitude,&longitude,&fix); usleep(600);

		}while(fix < 1);
			
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to D\n");
					
		while((latitude < LATITUDEVALUE_D - GPSHATA || latitude > LATITUDEVALUE_D + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_D - GPSHATA || longitude > LONGITUDEVALUE_D + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	if(tolower(msg[i]) == 'k'){
			
		while(compass < EK - COMPASSHATA || compass > EK + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > EK + COMPASSHATA && compass < 180 + EK + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{

			loop(&latitude,&longitude,&fix); usleep(600);

		}while(fix < 1);
		
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to K\n");
						
		while((latitude < LATITUDEVALUE_K - GPSHATA || latitude > LATITUDEVALUE_K + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_K - GPSHATA || longitude > LONGITUDEVALUE_K + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
}

void locationF(const char msg[],const int i){

	float longitude;
	float latitude;
	double compass;
	int fix;
	
	printf("You are in F\n");
	
	compass = getAngle(); usleep(25000);
			
	if(tolower(msg[i]) == 'g'){
			
		while(compass < FG - COMPASSHATA || compass > FG + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > FG + COMPASSHATA && compass < 180 + FG + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
	
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to G\n");
							
		while((latitude < LATITUDEVALUE_G - GPSHATA || latitude > LATITUDEVALUE_G + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_G - GPSHATA || longitude > LONGITUDEVALUE_G + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	if(tolower(msg[i]) == 'b'){
			
		while(compass < FB - COMPASSHATA || compass > FB + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > FB + COMPASSHATA && compass < 180 + FB + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
			
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to B\n");
					
		while((latitude < LATITUDEVALUE_B - GPSHATA || latitude > LATITUDEVALUE_B + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_B - GPSHATA || longitude > LONGITUDEVALUE_B + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
}

void locationG(const char msg[],const int i){

	float longitude;
	float latitude;
	double compass;
	int fix;
	
	printf("You are in G\n");
	
	compass = getAngle(); usleep(25000);
	
	if(tolower(msg[i]) == 'f'){
			
		while(compass < GF - COMPASSHATA || compass > GF + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > GF + COMPASSHATA && compass < 180 + GF + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
			
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to F\n");
					
		while((latitude < LATITUDEVALUE_F - GPSHATA || latitude > LATITUDEVALUE_F + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_F - GPSHATA || longitude > LONGITUDEVALUE_F + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
			
	if(tolower(msg[i]) == 'e'){
			
		while(compass < GE - COMPASSHATA || compass > GE + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > GE + COMPASSHATA && compass < 180 + GE + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
				
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to E\n");
				
		while((latitude < LATITUDEVALUE_E - GPSHATA || latitude > LATITUDEVALUE_E + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_E - GPSHATA || longitude > LONGITUDEVALUE_E + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
}

void locationH(const char msg[],const int i){

	float longitude;
	float latitude;
	double compass;
	int fix;
	
	compass = getAngle(); usleep(25000);
	
	printf("You are in H\n");
			
	if(tolower(msg[i]) == 'j'){
			
		while(compass < HJ - COMPASSHATA || compass > HJ + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > HJ - 180 - COMPASSHATA && compass < HJ - COMPASSHATA){
			
				system("echo 2=2300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=1300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
				
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
				
		printf("You are going to J\n");		
				
		while((latitude < LATITUDEVALUE_J - GPSHATA || latitude > LATITUDEVALUE_J + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_J - GPSHATA || longitude > LONGITUDEVALUE_J + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	if(tolower(msg[i]) == 'i'){
			
		while(compass < HI - COMPASSHATA || compass > HI + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > HI + COMPASSHATA && compass < 180 + HI + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
			
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to I\n");
					
		while((latitude < LATITUDEVALUE_I - GPSHATA || latitude > LATITUDEVALUE_I + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_I - GPSHATA || longitude > LONGITUDEVALUE_I + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
}

void locationI(const char msg[],const int i){

	float longitude;
	float latitude;
	double compass;
	int fix;
	
	printf("You are in I\n");
	
	compass = getAngle(); usleep(25000);
	
	if(tolower(msg[i]) == 'k'){
			
		while(compass < IK - COMPASSHATA || compass > IK + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > IK - 180 - COMPASSHATA && compass < IK - COMPASSHATA){
			
				system("echo 2=2300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=1300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
				
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to K\n");
				
		while((latitude < LATITUDEVALUE_K - GPSHATA || latitude > LATITUDEVALUE_K + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_K - GPSHATA || longitude > LONGITUDEVALUE_K + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
			
	if(tolower(msg[i]) == 'h'){
			
		while(compass < IH - COMPASSHATA || compass > IH + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > IH + COMPASSHATA && compass < 180 + IH + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
			
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to H\n");
					
		while((latitude < LATITUDEVALUE_H - GPSHATA || latitude > LATITUDEVALUE_H + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_H - GPSHATA || longitude > LONGITUDEVALUE_H + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
}

void locationJ(const char msg[],const int i){

	float longitude;
	float latitude;
	double compass;
	int fix;
	
	printf("You are in J\n");
	
	compass = getAngle(); usleep(25000);
	
	if(tolower(msg[i]) == 'a'){
			
		while(compass < JA - COMPASSHATA || compass > JA + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > JA - 180 - COMPASSHATA && compass < JA - COMPASSHATA){
			
				system("echo 2=2300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=1300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
				
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to A\n");
				
		while((latitude < LATITUDEVALUE_A - GPSHATA || latitude > LATITUDEVALUE_A + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_A - GPSHATA || longitude > LONGITUDEVALUE_A + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
			
	if(tolower(msg[i]) == 'h'){
			
		while(compass < JH - COMPASSHATA || compass > JH + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > JH + COMPASSHATA && compass < 180 + JH + COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
			
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to H\n");
					
		while((latitude < LATITUDEVALUE_H - GPSHATA || latitude > LATITUDEVALUE_H + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_H - GPSHATA || longitude > LONGITUDEVALUE_H + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
}

void locationK(const char msg[],const int i){

	float longitude;
	float latitude;
	double compass;
	int fix;
	
	printf("You are in K\n");
	
	compass = getAngle(); usleep(25000);
	
	if(tolower(msg[i]) == 'e'){
			
		while(compass < KE - COMPASSHATA || compass > KE + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > 0 && compass < KE - COMPASSHATA){
			
				system("echo 2=1300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=2300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
				
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to E\n");
				
		while((latitude < LATITUDEVALUE_E - GPSHATA || latitude > LATITUDEVALUE_E + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_E - GPSHATA || longitude > LONGITUDEVALUE_E + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
			
	if(tolower(msg[i]) == 'i'){
			
		while(compass < KI - COMPASSHATA || compass > KI + COMPASSHATA){
	
			compass = getAngle(); usleep(25000);
		
			if(compass > KI + COMPASSHATA && compass < 180 + KI + COMPASSHATA){
			
				system("echo 2=2300us > /dev/servoblaster");
			}
			else{
			
				system("echo 2=1300us > /dev/servoblaster");
			}
		}
		
		system("echo 2=1800us > /dev/servoblaster");
		
		do{
		
			loop(&latitude,&longitude,&fix); usleep(600);
		
		}while(fix < 1);
			
		system("echo 1=2300us > /dev/servoblaster");
		system("echo 2=1400us > /dev/servoblaster");
		
		printf("You are going to I\n");
					
		while((latitude < LATITUDEVALUE_I - GPSHATA || latitude > LATITUDEVALUE_I + GPSHATA) ||
		      (longitude < LONGITUDEVALUE_I - GPSHATA || longitude > LONGITUDEVALUE_I + GPSHATA) ){
			
			if(fix < 1){
			
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			
				while(fix < 1){
					
					loop(&latitude,&longitude,&fix); usleep(600);
				}
				
				system("echo 1=2300us > /dev/servoblaster");
				system("echo 2=1400us > /dev/servoblaster");
			}

			loop(&latitude,&longitude,&fix); usleep(600);
		}
	}
	
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
}

void handler(int signal)
{
	printf("caught ctrl-c\n");
	close(sockfd);
	exit(0);

}

