#include "client.h"

#include "bilmuh.h"

using namespace std;



//globals
int sockfd, portno, n;


inline void error(const char* msg)
{
    perror(msg);
    exit(0);
}


inline void handler(int signal)
{
    printf("caught ctrl-c\n");
    close(sockfd);
    exit(0);

}


Client::Client()
{

}



//main func
int Client::mainF(const char* portNum, const char* ipAddress)
{

    struct sockaddr_in serv_addr;
    struct hostent *server;

   // char buffer[256];
    //signal(SIGINT, handler);
  /*  if (argc < 3 || argc > 4) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }*/

    portno = atoi(portNum);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        qDebug("ERROR opening socket");

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

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        qDebug("ERROR connecting");



/***************************************************************/

    int clientId=1;
   cout << "Enter your client id" << endl;
   // cin >> clientId;
    usleep(400);

    n = write(sockfd,&clientId,sizeof(int));
    if (n < 0)
         qDebug("ERROR writing to socket");
    else
        printf("client id has been sent\n");


    // wait server - get location
    int current = -1, shortestPath = -1;

    n = read(sockfd, &current, sizeof(int));
    if(n < 0) qDebug("ERROR reading location");
    else
        printf("cubes's current location : %d\n",current);


    int userInput;


    bool ok;
    QInputDialog* inputDialog2 = new QInputDialog();
    inputDialog2->setOptions(QInputDialog::NoButtons);

    QString text2 =  inputDialog2->getText(NULL ,"QInputDialog::getText() Example",
                                          "Nereye Gideceksin ? ", QLineEdit::Normal,
                                          QDir::home().dirName(), &ok);

     if (ok && !text2.isEmpty())
     {
           std::cout<<text2.toStdString()<<std::endl;
     }

    userInput = text2.toInt();

    BilMuh obj;
    obj.setModal(true);
    obj.exec();

while(1)
{


   // cout << "Enter your user input" << endl;
    //cin >> userInput;






    usleep(600);
    n = write(sockfd,&userInput,sizeof(int));
    if (n < 0)
         qDebug("ERROR writing user input");
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
        qDebug("ERROR reading shortest path");
    //if(shortestPath != -1)
    else
        cout << "shortestPath has been received : " << shortestPath << endl;



}


   /* int current;
    cout << "Enter your current location" << endl;
    cin >> current;

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
    return 0;
}

