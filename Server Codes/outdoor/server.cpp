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
#include "ShortestPath.h"



#define SOCKET_ERROR   -1


using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}



void handler(int signal);

int calculateShortestPath(int userInput);


//globals
int sockfd, newsockfd[10], portno;
int clientNumber = 0;
int cubeSocket = -1, interfaceSocket = -1;

string filename = "outdoor_graph.txt";



int main(int argc, char *argv[])
{
	system("clear");
	cout << "Waiting for clients" << endl;
	//signal(SIGINT, handler);
	int nthreads, tid;

	 
	socklen_t clilen[10];
	 
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr[10];
	int n;

	if (argc < 2) 
	{
	    fprintf(stderr,"ERROR, no port provided\n");
	    exit(1);
	}
	 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	   error("ERROR opening socket");
	 

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	 

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
	   error("ERROR on binding");
	 
	int listenstatus = listen(sockfd,5);

		if(listenstatus < 0)
		{
		error("listen error");
		exit(0);
		}


	int clientID = -1;
	clilen[0] = sizeof(cli_addr[0]);
	int socket = accept(sockfd,(struct sockaddr *) &cli_addr[0], &clilen[0]);
	if (socket < 0) 
	    error("ERROR on accept");

	n = read(socket, &clientID,sizeof(int));
	if (n < 0) error("ERROR reading client id");


	if(clientID == 0){
		cubeSocket = socket;
		printf("cube module has connected\n");
	}
	else 
	{
		interfaceSocket = socket;
		printf("interface module has connected\n");
	}


	clilen[1] = sizeof(cli_addr[1]);
	socket = accept(sockfd,(struct sockaddr *) &cli_addr[1], &clilen[1]);
	if (socket < 0) 
	    error("ERROR on accept");

	n = read(socket, &clientID,sizeof(int));
	if (n < 0) error("ERROR reading client id");

	if(clientID == 0){
		cubeSocket = socket;
		printf("cube module has connected\n");
	}
	else 
	{
		interfaceSocket = socket;
		printf("interface module has connected\n");
	}


	int current = -1;
			
	n = read(cubeSocket, &current, sizeof(int));
	if(n < 0) error("ERROR reading location");
	cout << "Cube's location is : " << current << endl;

		
	// write current location for interface
	n = write(interfaceSocket, &current, sizeof(int));
	if (n < 0) 
		error("ERROR sending current to socket");

	// user input read to interface
	int interfaceInput = -1;
	n = read(interfaceSocket, &interfaceInput, sizeof(int));
	if(n < 0) 
		error("ERROR reading user input");
	else
		cout << "User Input is : " << interfaceInput << endl;

	// calculate shortest path

	ShortestPath path;
	vector<vertex_t> v = path.dijkstra(filename, current-1, interfaceInput-1);
	char shortestPath[v.size()+1];	

	shortestPath[0] = '\0';
	for (int i = 0; i < v.size(); ++i)
	{
		shortestPath[i] = v[i] + 'A';
	}
	shortestPath[v.size()] = '\0';
	int size = v.size()+1;
	n = write(cubeSocket, &size, sizeof(int));
	usleep(100);
	n = write(cubeSocket, shortestPath, size);

	if (n < 0) 
		error("ERROR writing to cube");
	else
		cout << "The Shortest Path is : " << shortestPath << endl;

		
	n = write(interfaceSocket, &size, sizeof(int));
	usleep(100);
	n = write(interfaceSocket, shortestPath, size);

	if (n < 0) 
		error("ERROR writing to interface");


	for (int i = 0; i < size-1; ++i)
	{
		read(cubeSocket, &current, sizeof(int));
		usleep(100);
		write(interfaceSocket, &current, sizeof(int));
		cout << "Moved sent" << current << endl;
	}

	
	close(interfaceSocket);
	close(cubeSocket);
    close(sockfd);
    return 0; 
}


void handler(int signal)
{
	cout << "caught ctrl-c\n "<< clientNumber << " client will be closed";
	close(interfaceSocket);
	close(cubeSocket);
	close(sockfd);
}
