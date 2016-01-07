#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cstdlib>
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

using namespace std;
void error(const char *msg)
{
    perror(msg);
    exit(0);
}


//globals
int sockfd, portno, n, size;
int previousLoc = -1;
int current = 1;
void handler(int signal);

void handler(int signal)
{
	printf("caught ctrl-c\n");
	close(sockfd);
	exit(0);

}
#include "compass.h"

#define ANGLEHATA 		5

#define ANGLE1TO2 		350
#define ANGLE1TO11		250
#define ANGLE2TO1 		155
#define ANGLE2TO3 		8
#define ANGLE3TO2 		123
#define ANGLE3TO4 		5
#define ANGLE4TO3 		84
#define ANGLE4TO5 		322
#define ANGLE5TO4 		69
#define ANGLE5TO6 		341
#define ANGLE6TO5 		70
#define ANGLE6TO7 		256
#define ANGLE7TO6 		69
#define ANGLE7TO8 		75
#define ANGLE8TO7 		16
#define ANGLE8TO9 		122
#define ANGLE9TO8 		38
#define ANGLE9TO10 		116
#define ANGLE10TO9 		8
#define ANGLE10TO11 	69
#define ANGLE11TO10 	317
#define ANGLE11TO1 		65


//smart

int averageVector(const vector<int> &values);
int findLocal();
int calculateNearest(const vector< vector< int> > values);
vector<string> split(string str, char delimiter);

void go(int *path);


int main(int argc, char const *argv[])
{
	int path[10] = {1,2,3};

	 system("sudo ./../ServoBlaster-master/user/servod");
	//socket connection
	 system("clear");
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

//socket connection end
	int clientId = 0;
	usleep(400);

	n = write(sockfd,&clientId,sizeof(int));
	if (n < 0) 
			 error("ERROR writing to socket");
	else
			printf("client id has been sent\n");

	current = findLocal();
	usleep(25000);

	n = write(sockfd,&current,sizeof(int));
	if (n < 0) 
			 error("ERROR writing to socket");
	else
			printf("current location has been sent\n");

	size = 255;
	n = read(sockfd, &size, sizeof(int));
	cout << "size " << size << endl;
	char shortestPath[size];
	usleep(100);
	n = read(sockfd, shortestPath, size);
	if (n < 0) 
		error("ERROR reading shortest path");
	else
        cout << "shortestPath has been received : " << shortestPath << endl;

	int intPath[size-1];
	
	for(int i=0; i < size-1; ++i)
	{
		intPath[i] = (int)(shortestPath[i] - 'A' + 1);
		cout << intPath[i];
	}
	
	//set servos
	system("echo 1=1800us > /dev/servoblaster");
	system("echo 2=1800us > /dev/servoblaster");
	go(intPath);
	
	
	sleep(5);
  close(sockfd);

	return 0;
}


void go(int * path)
{
	int location = path[0];
	float angle;
	int finalLocation = path[size - 2];
	
	for(int i=0; location != finalLocation; ++i)
	{
		
		if(location == 1){
			
			if(path[i] == 2){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE1TO2 - ANGLEHATA || angle > ANGLE1TO2 + ANGLEHATA){
					
					if(angle < ANGLE1TO2 - ANGLEHATA && angle > ANGLE1TO2 - 180 - ANGLEHATA)
					
						system("echo 2=2300us > /dev/servoblaster");
					
					else
					
						system("echo 2=1300us > /dev/servoblaster");
				
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal()));
				
				 

				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
				
			}
			
			if(path[i] == 11){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE1TO11 - ANGLEHATA || angle > ANGLE1TO11 + ANGLEHATA){
					
					if(angle < ANGLE1TO11 - ANGLEHATA && angle > ANGLE1TO11 - 180 - ANGLEHATA)
					
						system("echo 2=2300us > /dev/servoblaster");
					
					else
					
						system("echo 2=1300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
		}
		
		if(location == 2){
			
			if(path[i] == 1){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE2TO1 - ANGLEHATA || angle > ANGLE2TO1 + ANGLEHATA){
					
					if(angle < ANGLE2TO1 + 180 + ANGLEHATA && angle > ANGLE2TO1 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal()));
				
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
			
			if(path[i] == 3){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE2TO3 - ANGLEHATA || angle > ANGLE2TO3 + ANGLEHATA){
					
					if(angle < ANGLE2TO3 + 180 + ANGLEHATA && angle > ANGLE2TO3 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
		}
		
		if(location == 3){
			
			if(path[i] == 2){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE3TO2 - ANGLEHATA || angle > ANGLE3TO2 + ANGLEHATA){
					
					if(angle < ANGLE3TO2 + 180 + ANGLEHATA && angle > ANGLE3TO2 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal()));
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
			
			if(path[i] == 4){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE3TO4 - ANGLEHATA || angle > ANGLE3TO4 + ANGLEHATA){
					
					if(angle < ANGLE3TO4 + 180 + ANGLEHATA && angle > ANGLE3TO4 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
			
			if(location == 4){
			
				if(path[i] == 3){
					
					angle = getAngle(); usleep(100000);
						
					while(angle < ANGLE4TO3 - ANGLEHATA || angle > ANGLE4TO3 + ANGLEHATA){
						
						if(angle < ANGLE4TO3 + 180 + ANGLEHATA && angle > ANGLE4TO3 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
						
						angle = getAngle(); usleep(100000);
					}
					
					system("echo 2=1800us > /dev/servoblaster");
					
					do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
				}
				
				if(path[i] == 5){
					
					angle = getAngle(); usleep(100000);
						
					while(angle < ANGLE4TO5 - ANGLEHATA || angle > ANGLE4TO5 + ANGLEHATA){
						
						if(angle < ANGLE4TO5 - ANGLEHATA && angle > ANGLE4TO5 - 180 - ANGLEHATA)
					
						system("echo 2=2300us > /dev/servoblaster");
					
					else
					
						system("echo 2=1300us > /dev/servoblaster");
						
						angle = getAngle(); usleep(100000);
					}
					
					system("echo 2=1800us > /dev/servoblaster");
					
					do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal()));
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
				}
			}
		}
		
		if(location == 5){
			
			if(path[i] == 4){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE5TO4 - ANGLEHATA || angle > ANGLE5TO4 + ANGLEHATA){
					
					if(angle < ANGLE5TO4 + 180 + ANGLEHATA && angle > ANGLE5TO4 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
			
			if(path[i] == 6){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE5TO6 - ANGLEHATA || angle > ANGLE5TO6 + ANGLEHATA){
					
					if(angle < ANGLE5TO6 - ANGLEHATA && angle > ANGLE5TO6 - 180 - ANGLEHATA)
					
						system("echo 2=2300us > /dev/servoblaster");
					
					else
					
						system("echo 2=1300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal()));
				 
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
		}
		
		if(location == 6){
			
			if(path[i] == 5){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE6TO5 - ANGLEHATA || angle > ANGLE6TO5 + ANGLEHATA){
					
					if(angle < ANGLE6TO5 + 180 + ANGLEHATA && angle > ANGLE6TO5 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal()));
				 
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
			
			if(path[i] == 7){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE6TO7 - ANGLEHATA || angle > ANGLE6TO7 + ANGLEHATA){
					
					if(angle < ANGLE6TO7 - ANGLEHATA && angle > ANGLE6TO7 - 180 - ANGLEHATA)
					
						system("echo 2=2300us > /dev/servoblaster");
					
					else
					
						system("echo 2=1300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				 
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
		}
		
		if(location == 7){
			
			if(path[i] == 6){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE7TO6 - ANGLEHATA || angle > ANGLE7TO6 + ANGLEHATA){
					
					if(angle < ANGLE7TO6 + 180 + ANGLEHATA && angle > ANGLE7TO6 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
			
			if(path[i] == 8){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE7TO8 - ANGLEHATA || angle > ANGLE7TO8 + ANGLEHATA){
					
					if(angle < ANGLE7TO8 + 180 + ANGLEHATA && angle > ANGLE7TO8 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
		}
		
		if(location == 8){
			
			if(path[i] == 7){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE8TO7 - ANGLEHATA || angle > ANGLE8TO7 + ANGLEHATA){
					
					if(angle < ANGLE8TO7 + 180 + ANGLEHATA && angle > ANGLE8TO7 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
			
			if(path[i] == 9){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE8TO9 - ANGLEHATA || angle > ANGLE8TO9 + ANGLEHATA){
					
					if(angle < ANGLE8TO9 + 180 + ANGLEHATA && angle > ANGLE8TO9 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
		}
		
		if(location == 9){
			
			if(path[i] == 8){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE9TO8 - ANGLEHATA || angle > ANGLE9TO8 + ANGLEHATA){
					
					if(angle < ANGLE9TO8 + 180 + ANGLEHATA && angle > ANGLE9TO8 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
			
			if(path[i] == 10){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE9TO10 - ANGLEHATA || angle > ANGLE9TO10 + ANGLEHATA){
					
					if(angle < ANGLE9TO10 + 180 + ANGLEHATA && angle > ANGLE9TO10 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
		}
		
		if(location == 10){
			
			if(path[i] == 9){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE10TO9 - ANGLEHATA || angle > ANGLE10TO9 + ANGLEHATA){
					
					if(angle < ANGLE10TO9 + 180 + ANGLEHATA && angle > ANGLE10TO9 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
			
			if(path[i] == 11){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE10TO11 - ANGLEHATA || angle > ANGLE10TO11 + ANGLEHATA){
					
					if(angle < ANGLE10TO11 + 180 + ANGLEHATA && angle > ANGLE10TO11 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal()));
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
		}
		
		if(location == 11){
			
			if(path[i] == 10){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE11TO10 - ANGLEHATA || angle > ANGLE11TO10 + ANGLEHATA){
					
					if(angle < ANGLE11TO10 - ANGLEHATA && angle > ANGLE11TO10 - 180 - ANGLEHATA)
					
						system("echo 2=2300us > /dev/servoblaster");
					
					else
					
						system("echo 2=1300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
			
			if(path[i] == 1){
				
				angle = getAngle(); usleep(100000);
					
				while(angle < ANGLE11TO1 - ANGLEHATA || angle > ANGLE11TO1 + ANGLEHATA){
					
					if(angle < ANGLE11TO1 + 180 + ANGLEHATA && angle > ANGLE11TO1 + ANGLEHATA)
					
						system("echo 2=1300us > /dev/servoblaster");
					
					else
					
						system("echo 2=2300us > /dev/servoblaster");
					
					angle = getAngle(); usleep(100000);
				}
				
				system("echo 2=1800us > /dev/servoblaster");
				
				do{
					
					system("echo 1=2300us > /dev/servoblaster");
					system("echo 2=1400us > /dev/servoblaster");
					
				}while(path[i] != (current = findLocal())); 
				  
				write(sockfd, &current, sizeof(int));
				
				system("echo 1=1800us > /dev/servoblaster");
				system("echo 2=1800us > /dev/servoblaster");
			}
		}
		
		location = path[i];
	}
}


vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}




int findLocal()
{
    string temp;
    int counter = 0;
	string after;
    int flag = 0;

    vector< vector < int > > dbs(11);

    for (int i = 0; i < dbs.size(); ++i)
    	dbs[i].push_back(0);



	FILE *fp;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("sudo iwlist wlan0 scan|grep -o -e 'Signal level=.*' -e 'ESSID:.*'", "r");
	if (fp == NULL) 
	{
		printf("Failed to run command\n" );
		exit(1);
	}

	while(fgets(path, sizeof(path)-1, fp) != NULL)
  {	
    	string temp(path);
      cout << temp;

			if(strlen(path) > 0 && temp[0] == 'E')
			{
				//readESSID 
				vector<string> res = split(temp, '"');
				//outfile << res[1] << " ";
				after = res[1];
	
			}
			else if(strlen(path) > 0 && temp[0] == 'S')
			{
				vector<string> res = split(temp, '=');

				if(atoi(after.c_str()) > 0 && atoi(after.c_str()) < 12)
				{
					dbs[atoi(after.c_str()) -1 ].push_back(atoi(res[1].c_str()));
				}

			}
	}   
	
	int nearest = calculateNearest(dbs);
	cout << "You are about " << nearest << " area" << endl;
	
	/* close */
		pclose(fp);
	return nearest;
}

//find nearest as real (return + 1)
int calculateNearest(const vector< vector< int> > values)
{
	int maxArea = -9999, area = 0;
	
	for (int i = 0; i < values.size(); ++i)
	{
		int currentArea = averageVector(values[i]);
		if(currentArea > maxArea ){
			maxArea = currentArea;
			area = i;
		}
		//cout << currentArea << "\t" << i+1 << endl;
	}
	return area + 1;
}


//calc avg single vector elements
int averageVector(const vector <int> &values)
{
	int sum = 0;
	for (int i = 1; i < values.size(); ++i)
	{
		sum += values[i];
	}
	int size = static_cast<int>(values.size())-1;
	if (size == 0) size = 1;
	return static_cast<int>(sum / size);
}








