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
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <QDebug>
#include <QInputDialog>
#include <QDir>

using namespace std;


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

        string str2 = "178.62.232.10";
        //string str2 = "127.0.0.1";

        QString str(str2.c_str());

        QByteArray t = str.toLatin1();
        ipAddress = t.data();

        userInput = -1;


        portNum = "4664";
        //portNum = "4665";



        system("clear");
        struct sockaddr_in serv_addr;
        struct hostent *server;



        portno = ::atoi(portNum);
        cout << portno << endl;
        cout << ipAddress << endl;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        setSocket(sockfd);
        cout << "In client " << sockfd << endl;


        if (sockfd < 0)
            cout << "ERROR opening socket\n";

        server = gethostbyname(ipAddress);

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

        if (::connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            std::cout << "ERROR connecting\n";



    /***************************************************************/

        int clientId = 1;
       //    cout « "Enter your client id" « endl;
       //    cin » clientId;
           usleep(400);


           n = write(sockfd,&clientId,sizeof(int));
           if (n < 0)
                std::cout << "ERROR writing to socket\n";
           else
               printf("client id has been sent\n");



           // wait server - get location
           int current = -1;

           n = read(sockfd, &current, sizeof(int));
           if(n < 0)
               std::cout << "ERROR reading location\n";
           else
           {
               printf("cubes's current location : %d\n",current);
              // getCurrentLocation(current);
               emit progressChanged(current);
           }


         std::cout << "once"<< userInput << endl;



        //userInput = getTarget();

        std::cout << userInput << endl;

        while (userInput < 0){} ;
        usleep(200);
        n = write(sockfd,&userInput,sizeof(int));
        if (n < 0)
             std::cout << "ERROR writing user input\n";
        else
            printf("user input has been sent\n");



        // read shortest path
        int size = 255;
        n = read(sockfd, &size, sizeof(int));
        cout << "size " << size << endl;
        char shortestPath[size];
        usleep(100);
        n = read(sockfd, shortestPath, size);
        if (n < 0)
            std::cout << "ERROR reading shortest path\n";
        //if(shortestPath != -1)
        else
        {
            cout << "shortestPath has been received : " << shortestPath << endl;
            emit progressShortestPath(size,shortestPath);
          //////  n = read(sockfd, shortestPath, size);
        }



        cout << endl << "Moving " << endl;
        for (int i = 0; i < size-1; ++i)
        {
            int currentPoint = -1;
            read(sockfd, &currentPoint, sizeof(int));
            cout << "at " << currentPoint << ". point" << endl;
            emit progressChanged(currentPoint);
            //setLocation(currentPoint);
        }

       /* int current;
        cout « "Enter your current location" « endl;
        cin » current;

        n = write(sockfd,&current,sizeof(int));
        if (n < 0)
             error("ERROR writing to socket");
        else
            printf("current location has been sent\n");

        void* size;
        n = read(sockfd,size,(size_t)sizeof(int));
        if (n < 0)
             error("ERROR reading from socket");



        char path[*((int*)size)];
        n = read(sockfd, path, (size_t)size);


        printf("%s\n",path);

    */

        sleep(10);
        close(sockfd);



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
