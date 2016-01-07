#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H


#include <QThread>
#include <QString>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <QDebug>
#include <QInputDialog>
#include <QDir>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>

using namespace std;
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


class WorkerThread : public QThread {
    Q_OBJECT

private:
    int sockfd;
    int socketOut;
    const char* portNum;
    const char* ipAddress;
    int userInput;



public:
    int getSocket(){ return socketOut; }
    int setSocket(int newS){ socketOut = newS; }

    void run() {
        int portno, n ;

        string str2 = "127.0.0.1";
        portNum = "4664";

        QString str(str2.c_str());

        QByteArray t = str.toLatin1();
        ipAddress = t.data();

        userInput = -1;




        portno = ::atoi(portNum);
        cout << portno << endl;
        cout << ipAddress << endl;


        WSADATA wsaData;
        SOCKET ConnectSocket = INVALID_SOCKET;
        struct addrinfo *result = NULL,
                        *ptr = NULL,
                        hints;

        int iResult;



        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
            return;
        }

        ZeroMemory( &hints, sizeof(hints) );
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        // Resolve the server address and port
        iResult = ::getaddrinfo("178.62.232.10", portNum, &hints, &result);
        if ( iResult != 0 ) {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            return;
        }

        // Attempt to connect to an address until one succeeds
        for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

            // Create a SOCKET for connecting to server
            ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                ptr->ai_protocol);
            if (ConnectSocket == INVALID_SOCKET) {
                printf("socket failed with error: %ld\n", WSAGetLastError());
                WSACleanup();
                return;
            }

            // Connect to server.
            iResult = ::connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                closesocket(ConnectSocket);
                ConnectSocket = INVALID_SOCKET;
                continue;
            }
            break;
        }

        freeaddrinfo(result);

        if (ConnectSocket == INVALID_SOCKET) {
            printf("Unable to connect to server!\n");
            WSACleanup();
            return;
        }




    /***************************************************************/

        int clientId = 1;
       //    cout « "Enter your client id" « endl;
       //    cin » clientId;
       usleep(400);

      iResult = send( ConnectSocket, (char *)&clientId, sizeof(int), 0 );
       if (iResult == SOCKET_ERROR) {
           printf("send failed with error: %d\n", WSAGetLastError());
           closesocket(ConnectSocket);
           WSACleanup();
           return;
       }
       else
           printf("client id has been sent\n");


           // wait server - get location
           int current = -1;
           iResult = recv(ConnectSocket, (char*)&current, sizeof(int), 0);
           if (iResult > 0) {
            printf("Bytes received: %d\n", current);
            emit progressChanged(current);
           }
           else
            std::cout << "ERROR reading location\n";




        //userInput = getTarget();

        std::cout << userInput << endl;

        while (userInput < 0){} ;
        usleep(200);

        std::cout << userInput << endl;

        iResult = send( ConnectSocket, (char *)&userInput, sizeof(int), 0 );
         if (iResult == SOCKET_ERROR) {
             printf("send failed with error: %d\n", WSAGetLastError());
             closesocket(ConnectSocket);
             WSACleanup();
             return;
         }
         else
         {
             printf("user input has been sent\n");
         }



        // read shortest path
        int size = 255;
        char shortestPath[size];

        iResult = recv(ConnectSocket, (char*)&size, sizeof(int), 0);
        if (iResult > 0) {
         printf("size received: %d\n", current);
        }
        else
         std::cout << "ERROR reading size\n";
         usleep(100);

        iResult = recv(ConnectSocket, shortestPath, size, 0);
        if (iResult > 0) {
         printf("path received: %s\n", shortestPath);
         emit progressShortestPath(size,shortestPath);
        }
        else
         std::cout << "ERROR reading path\n";







        cout << endl << "Moving " << endl;
        for (int i = 0; i < size-1; ++i)
        {
            int currentPoint = -1;
            recv(ConnectSocket, (char*)&currentPoint, sizeof(int), 0);
            cout << "at " << currentPoint << ". point" << endl;
            //setLocation(currentPoint);
            emit progressChanged(currentPoint);
        }

        sleep(10);
        closesocket(ConnectSocket);
        WSACleanup();



    }
    // Define signal:
    signals:
        void progressChanged(int info);
        void progressShortestPath(int info1 ,char* info);
    public slots:
        void onProgressLocationSet(int loc) {
            userInput = loc;
        }

};

#endif // WORKERTHREAD_H
