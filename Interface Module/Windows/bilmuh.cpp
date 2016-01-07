

#include "bilmuh.h"

#include <QDebug>
#include "workerthread.h"
#include <QObject>



//pthread_t th1;

int BilMuh::target = 0;
int BilMuh::location = 0;

int loc = 0 ;
int tar = 0 ;



int flagOneTwo = 0, flagTwoThree = 0, flagThreeFour = 0,
    flagFourFive = 0, flagFiveSix = 0, flagSixSeven = 0,
    flagSevenEight = 0, flagEightNine = 0, flagNineTen = 0,
    flagTenEleven = 0 , flagElevenTwelve = 0;

int buttonFlag = 0;

BilMuh::BilMuh(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BilMuh)
{
    ui->setupUi(this);

    QImage imageObject;
    imageObject.load("bilmuhrenk.PNG");


    QPalette palette;
    palette.setBrush(QPalette::Background,imageObject);
    this->setPalette(palette);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

     roll = 0.0;
     pitch = 0.0;



     // yolları temizle
          QPushButton *button = new QPushButton("RESET", this);
          // set size and location of the button
          button->setGeometry(QRect(QPoint(760, 700),
          QSize(60, 40)));
          connect(button, SIGNAL(clicked()), this, SLOT(reset()));


          // giris -> kantin
          QPushButton *button1 = new QPushButton("Kantin", this);
          // set size and location of the button
          button1->setGeometry(QRect(QPoint(130, 640),
          QSize(50, 30)));
          connect(button1, SIGNAL(clicked()), this, SLOT(pressKantin()));

          QPushButton *button2 = new QPushButton("Giriş", this);
          // set size and location of the button
          button2->setGeometry(QRect(QPoint(380, 640),
          QSize(50, 30)));


          // giris -> Z23
          QPushButton *button3 = new QPushButton("Z23", this);
          // set size and location of the button
          button3->setGeometry(QRect(QPoint(670, 640),
          QSize(30, 30)));

          connect(button3, SIGNAL(clicked()), this, SLOT(pressZ23()));


          // giris -> Lab
          QPushButton *button4 = new QPushButton("Lab", this);
          // set size and location of the button
          button4->setGeometry(QRect(QPoint(130, 440),
          QSize(30, 30)));

          connect(button4, SIGNAL(clicked()), this, SLOT(pressLab()));


           // giris -> Z11
          QPushButton *button5 = new QPushButton("Z11", this);
          // set size and location of the button
          button5->setGeometry(QRect(QPoint(130, 240),
          QSize(30, 30)));

          connect(button5, SIGNAL(clicked()), this, SLOT(pressZ11()));


          // giris -> DevreLab
          QPushButton *button6 = new QPushButton("DevreLab", this);
          // set size and location of the button
          button6->setGeometry(QRect(QPoint(670, 440),
          QSize(70,30)));

          connect(button6, SIGNAL(clicked()), this, SLOT(pressDevreLab()));



          // giris -> MikroLab
          QPushButton *button7 = new QPushButton("MikroLab", this);
          // set size and location of the button
          button7->setGeometry(QRect(QPoint(670, 240),
          QSize(70,30)));

          connect(button7, SIGNAL(clicked()), this, SLOT(pressMikroLab()));


          // giris -> Z06
          QPushButton *button8 = new QPushButton("Z06", this);
          // set size and location of the button
          button8->setGeometry(QRect(QPoint(130, 140),
          QSize(30, 30)));

          connect(button8, SIGNAL(clicked()), this, SLOT(pressZ06()));


          // giris -> Z10
          QPushButton *button9 = new QPushButton("Z10", this);
          // set size and location of the button
          button9->setGeometry(QRect(QPoint(670, 140),
          QSize(30, 30)));

          connect(button9, SIGNAL(clicked()), this, SLOT(pressZ10()));


          // giris -> Robotik
          QPushButton *button10 = new QPushButton("Robotik", this);
          // set size and location of the button
          button10->setGeometry(QRect(QPoint(110, 40),
          QSize(60, 30)));

          connect(button10, SIGNAL(clicked()), this, SLOT(pressRobotik()));


          // giris -> Z02
          QPushButton *button11 = new QPushButton("Z02", this);
          // set size and location of the button
          button11->setGeometry(QRect(QPoint(300,40),
          QSize(60, 30)));

          connect(button11, SIGNAL(clicked()), this, SLOT(pressZ02()));

          // giris -> Z04
          QPushButton *button12 = new QPushButton("Z04", this);
          // set size and location of the button
          button12->setGeometry(QRect(QPoint(400, 40),
          QSize(60, 30)));

          connect(button12, SIGNAL(clicked()), this, SLOT(pressZ04()));

          // giris -> Z05
          QPushButton *button13 = new QPushButton("Z05", this);
          // set size and location of the button
          button13->setGeometry(QRect(QPoint(600, 40),
          QSize(60, 30)));

          connect(button13, SIGNAL(clicked()), this, SLOT(pressZ05()));

       startWorkInAThread();
/*
       bool ok;
       QInputDialog* inputDialog = new QInputDialog();
       inputDialog->setOptions(QInputDialog::NoButtons);

       QString text =  inputDialog->getText(NULL ,"QInputDialog::getText() Example",
                                             "IP Address:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);

        if (ok && !text.isEmpty())
        {
           std::cout<<text.toStdString()<<std::endl;
        }


        bool ok2;
        QInputDialog* inputDialog2 = new QInputDialog();
        inputDialog2->setOptions(QInputDialog::NoButtons);

        QString text2 =  inputDialog2->getText(NULL ,"QInputDialog::getText() Example",
                                              "Port Number:", QLineEdit::Normal,
                                              QDir::home().dirName(), &ok2);

         if (ok2 && !text2.isEmpty())
         {
               std::cout<<text2.toStdString()<<std::endl;
         }*/
         //emit progressPortNum(text);
        // emit progressIpAddress(text2);


}

void BilMuh::setShortestPath(int lenght, char* shortPath) {
    int areaFrom;
    int areaTo;

    lenght = lenght - 1;

    for (int i = 0 ; i < lenght ; i++) {
        areaFrom = shortPath[i]-'@';

        if( i !=  lenght-1 )
         areaTo = shortPath[i+1]-'@';

        cout << "from" << areaFrom << "to "<<areaTo << endl;

        if( areaFrom > areaTo && areaFrom-areaTo ==  1 )
        {
            if(areaTo == 10 )
                show_ten_eleven();
            if(areaTo == 9 )
                show_nine_ten();
            if(areaTo == 8 )
                show_eight_nine();
            if(areaTo == 7 )
                show_seven_eight();
            if(areaTo == 6 )
                show_six_seven();
            if(areaTo == 5 )
                show_five_six();
            if(areaTo == 4 )
                show_four_five();
            if(areaTo == 3 )
                show_three_four();
            if(areaTo == 2 )
                show_two_three();
            if(areaTo == 1 )
                show_one_two();

        } else if (areaFrom < areaTo && areaTo-areaFrom ==  1) {
            if(areaFrom == 10 )
                show_ten_eleven();
            if(areaFrom == 9 )
                show_nine_ten();
            if(areaFrom == 8 )
                show_eight_nine();
            if(areaFrom == 7 )
                show_seven_eight();
            if(areaFrom == 6 )
                show_six_seven();
            if(areaFrom == 5 )
                show_five_six();
            if(areaFrom == 4 )
                show_four_five();
            if(areaFrom == 3 )
                show_three_four();
            if(areaFrom == 2 )
                show_two_three();
            if(areaFrom == 1 )
                show_one_two();
        } else {
            if(areaFrom > areaTo ) {
                if((areaFrom-areaTo) > 1)
                    show_eleven_twelve();

            } else {
                if((areaTo - areaFrom) > 1)
                    show_eleven_twelve();
            }

        }


    }
}


void BilMuh::startWorkInAThread() {
    WorkerThread *workerThread = new WorkerThread;
    // Connect our signal and slot
    connect(workerThread, SIGNAL(progressChanged(int)),this,SLOT(onProcessChanged(int)));// Setup callback for cleanup when it finishes
    connect(this, SIGNAL(progressSetLocation(int)), workerThread,SLOT(onProgressLocationSet(int)));
    connect(workerThread,SIGNAL(progressShortestPath(int,char*)), this, SLOT(onProgressShortestPath(int,char*)));
    //connect(this,SIGNAL(progressIpAddress(QString)),workerThread,SLOT(onPortNumChanged(QString)));
     connect(workerThread, SIGNAL(finished()),
                workerThread, SLOT(deleteLater()));
        // Run, Forest, run!
        workerThread->start();
}


void BilMuh::onProcessChanged(int info) {

           location = info;

}

void BilMuh::onProgressShortestPath(int info1, char* info) {
    loc = info[0] - '@';
    tar = info[info1-2] - '@';


    setShortestPath(info1,info);
}



void BilMuh::reset()
{
     flagOneTwo = 0;
     flagTwoThree = 0;
     flagThreeFour = 0;
     flagFourFive = 0;
     flagFiveSix = 0;
     flagSixSeven = 0;
     flagSevenEight = 0;
     flagEightNine = 0;
     flagNineTen = 0;
     flagTenEleven = 0 ;
     flagElevenTwelve = 0;

     buttonFlag = 0 ;
     location = 0;
     target = 0 ;
     loc = 0 ;
     tar = 0 ;

    roll = 0.0;
    pitch = 0.0;

}



void BilMuh::show_one_two()
{
    flagOneTwo = 1;
}



void BilMuh::show_two_three()
{
    flagTwoThree = 1;
}

void BilMuh::show_three_four()
{
    flagThreeFour = 1;
}


void BilMuh::show_four_five()
{
    flagFourFive = 1;
}


void BilMuh::show_five_six()
{
    flagFiveSix = 1;
}


void BilMuh::show_six_seven()
{
    flagSixSeven = 1;
}


void BilMuh::show_seven_eight()
{
    flagSevenEight = 1;
}


void BilMuh::show_eight_nine()
{
    flagEightNine = 1;
}


void BilMuh::show_nine_ten()
{
    flagNineTen = 1;
}


void BilMuh::show_ten_eleven()
{
    flagTenEleven = 1;
}

void BilMuh::show_eleven_twelve()
{
    flagElevenTwelve = 1;
}


void BilMuh::pressKantin()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 1;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(1);
    }
}

void BilMuh::pressLab()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 2;
     //   location = 2;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(2);
    }
}

void BilMuh::pressZ11()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 3;
     //   location = 3;
       // write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(3);
    }
}

void BilMuh::pressZ06()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 4;
     //   location = 4;
      //  cout << Client::getSocket() << " In bilmuh target found and sent" << endl;

        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(4);

    }
}

void BilMuh::pressRobotik()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 4;
     //   location = 4;
       // write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(4);
    }
}


void BilMuh::pressZ02()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 5;
     //   location = 5;
       // write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(5);
    }
}

void BilMuh::pressZ04()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 6;
    //    location = 6;
       // write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(6);
    }
}

void BilMuh::pressZ05()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 7;
    //    location = 7;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(7);
    }
}

void BilMuh::pressZ10()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 7;
    //    location = 7;
       // write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(7);
    }
}

void BilMuh::pressMikroLab()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 8;
     //   location = 8;
       // write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(8);
    }
}

void BilMuh::pressDevreLab()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 9;
     //   location = 9;
       // write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(9);
    }
}

void BilMuh::pressZ23()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 10;
     //   location = 10;
       // write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(10);
    }
}


void BilMuh::pressGiris()
{
    if( buttonFlag == 0 ) {
        buttonFlag = -1;
        target = 11;
     //   location = 11;
       // write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(11);
    }
}


void BilMuh::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::RightButton)
        qDebug() << "Only right button";
}

void BilMuh::paintEvent(QPaintEvent *)
{

 //    QGraphicsView * parent;
  //  int r=0;
    QPainter painter(this);
    QBrush ellipseColor(QColor(48,172,220));
    painter.setPen( Qt::red );

    painter.setBrush(ellipseColor);

    if(flagOneTwo == 1)
    {

        painter.setPen(QPen(Qt::red, 12));
        painter.drawLine(270, 640, 270, 480);

        //flag_giris_z23 = 0;
    }
    if(flagTwoThree == 1)
    {
        painter.setPen(QPen(Qt::red, 12));
        painter.drawLine(270, 480, 270, 280);

    }
    if(flagThreeFour == 1)
    {
        painter.setPen(QPen(Qt::red, 12));
        painter.drawLine(270, 280, 270, 140);
        //flag_giris_kantin = 0;
    }
    if(flagFourFive == 1)
    {
        //painter.drawRect(380+roll,610+pitch,20,20);

        painter.setPen(QPen(Qt::red, 12));
        painter.drawLine(270, 140, 360, 140);


    }
    if(flagFiveSix == 1)
    {
       // painter.drawRect(380+roll,610+pitch,20,20);

        painter.setPen(QPen(Qt::red, 12));
        painter.drawLine(360, 140, 450, 140);


    }
    if(flagSixSeven == 1)
    {
        //painter.drawRect(400+roll,610+pitch,20,20);

        painter.setPen(QPen(Qt::red, 12));
        painter.drawLine(450, 140, 540, 140);

    }

    if(flagSevenEight == 1)
    {
        //painter.drawRect(400+roll,610+pitch,20,20);

        painter.setPen(QPen(Qt::red, 12));
        painter.drawLine(540, 140, 540, 280);

    }

    if(flagEightNine == 1)
    {
       //painter.drawRect(380+roll,610+pitch,20,20);

        painter.setPen(QPen(Qt::red, 12));
        painter.drawLine(540, 280, 540, 480);


    }

    if(flagNineTen == 1)
    {
       //painter.drawRect(400+roll,610+pitch,20,20);

        painter.setPen(QPen(Qt::red, 12));
       painter.drawLine(540, 480, 540, 640);


    }


    if(flagTenEleven == 1)
    {


        painter.setPen(QPen(Qt::red, 12));
        painter.drawLine(540, 640, 400, 640);


    }

    if( flagElevenTwelve == 1 ) {
        painter.setPen(QPen(Qt::red, 12));
        painter.drawLine(400,640,270,640);
    }

     QRect rect(0,0,0,0);//250 - 250 - 100 sari
/*
     rect.setRect(235,550,90,150);
     painter.fillRect(rect, QBrush(QColor(150, 150, 250)));
*/

     QRect rect2(0,0,0,0);
     QRect rect3(0,0,0,0);



    // read(Client::getSocket(), &location, sizeof(int));
    //Kantin
    if(getLocation() == 1)
    {
         rect.setRect(235,550,90,150);
         painter.fillRect(rect, QBrush(QColor(20, 20, 100)));
    } else if ( loc == 1 ) {
        rect2.setRect(235,550,90,150);
        painter.fillRect(rect2, QBrush(QColor(250,250,100)));
    } else if ( tar == 1 ) {
        rect3.setRect(235,550,90,150);
        painter.fillRect(rect3,QBrush(Qt::green));
    }

     //Lab
    if(getLocation() == 2)
    {
          rect.setRect(235,380,70,180);
         painter.fillRect(rect, QBrush(QColor(20, 20, 100)));
    } else if ( loc == 2 ) {
        rect2.setRect(235,380,70,180);
       painter.fillRect(rect2, QBrush(QColor(250,250,100)));
    } else if ( tar == 2 ) {
        rect3.setRect(235,380,70,180);
      painter.fillRect(rect3,QBrush(Qt::green));
    }

     //Z11
    if(getLocation() == 3)
    {
          rect.setRect(235,200,70,180);
         painter.fillRect(rect, QBrush(QColor(20, 20, 100)));
    } else if ( loc == 3 ) {
        rect2.setRect(235,200,70,180);
       painter.fillRect(rect2, QBrush(QColor(250,250,100)));
    } else if ( tar == 3 ) {
        rect3.setRect(235,200,70,180);
       painter.fillRect(rect3,QBrush(Qt::green));
    }

     //Z06 // Robotik
    if(getLocation() == 4)
    {
          rect.setRect(235,115,70,85);
         painter.fillRect(rect, QBrush(QColor(20, 20, 100)));
    } else if ( loc == 4 ) {
        rect2.setRect(235,115,70,85);
       painter.fillRect(rect2, QBrush(QColor(250,250,100)));
    } else if ( tar == 4 ) {
        rect3.setRect(235,115,70,85);
       painter.fillRect(rect3,QBrush(Qt::green));
    }

    // z02
    if(getLocation() == 5)
    {
         rect.setRect(305,110,100,50);
         painter.fillRect(rect, QBrush(QColor(20, 20, 100)));
    } else if ( loc == 5 ) {
        rect2.setRect(305,110,100,50);
        painter.fillRect(rect2, QBrush(QColor(250,250,100)));
    } else if ( tar == 5 ) {
        rect3.setRect(305,110,100,50);
       painter.fillRect(rect3,QBrush(Qt::green));
    }


     //z04
    if(getLocation() == 6)
    {
          rect.setRect(400,110,100,50);    //4.parametre genişlik
         painter.fillRect(rect, QBrush(QColor(20, 20, 100)));
    } else if ( loc == 6) {
        rect2.setRect(400,110,100,50);    //4.parametre genişlik
       painter.fillRect(rect2, QBrush(QColor(250,250,100)));
    } else if ( tar == 6 ) {
        rect3.setRect(400,110,100,50);    //4.parametre genişlik
       painter.fillRect(rect3,QBrush(Qt::green));
    }

     //z05 // z10
    if(getLocation() == 7)
    {
        rect.setRect(500,115,70,85);    //4.parametre genişlik
         painter.fillRect(rect, QBrush(QColor(20, 20, 100)));
    } else if ( loc == 7 ) {
        rect2.setRect(500,115,70,85);    //4.parametre genişlik
         painter.fillRect(rect2, QBrush(QColor(250,250,100)));
    } else if ( tar == 7 ) {
        rect3.setRect(500,115,70,85);    //4.parametre genişlik
        painter.fillRect(rect3,QBrush(Qt::green));
    }

     //mikrolab
    if(getLocation() == 8)
    {
         rect.setRect(500,200,70,180);
         painter.fillRect(rect, QBrush(QColor(20, 20, 100)));
    } else if ( loc == 8 ) {
        rect2.setRect(500,200,70,180);
        painter.fillRect(rect2, QBrush(QColor(250,250,100)));
    } else if ( tar == 8 ) {
        rect3.setRect(500,200,70,180);
        painter.fillRect(rect3,QBrush(Qt::green));
    }

     //devre lab
    if(getLocation() == 9)
    {
          rect.setRect(500,380,70,180);
         painter.fillRect(rect, QBrush(QColor(20, 20, 100)));
    } else if ( loc == 9 ) {
        rect2.setRect(500,380,70,180);
       painter.fillRect(rect2, QBrush(QColor(250,250,100)));
    } else if ( tar == 9 ) {
        rect3.setRect(500,380,70,180);
       painter.fillRect(rect3,QBrush(Qt::green));
    }

     //z23
     if(getLocation() == 10)
     {
          rect.setRect(480,550,90,150);
         painter.fillRect(rect, QBrush(QColor(20, 20, 100)));
    } else if ( loc == 10 ) {
         rect2.setRect(480,550,90,150);
        painter.fillRect(rect2, QBrush(QColor(250,250,100)));
     } else if ( tar == 10 ) {
         rect3.setRect(480,550,90,150);
       painter.fillRect(rect3,QBrush(Qt::green));
     }

     //giriş
     if(getLocation() == 11)
     {
          rect.setRect(325,590,155,100);
         painter.fillRect(rect, QBrush(QColor(20, 20, 100)));
     } else if ( loc == 11 ) {
         rect2.setRect(325,590,155,100);
        painter.fillRect(rect2, QBrush(QColor(250,250,100)));
     } else if ( tar == 11 ) {
         rect3.setRect(325,590,155,100);
        painter.fillRect(rect3,QBrush(Qt::red));
     }


}



void BilMuh::keyPressEvent(QKeyEvent *event)
 {
     switch (event->key())
     {
     case Qt::Key_A:    //left
         if(roll>-10.)
         roll -= 5.0;
         break;
     case Qt::Key_D:    //right
         if(roll<270.)
         roll += 5.0;
         break;
     case Qt::Key_S:    //down
          if(pitch>-520.)
          pitch -=5.0;
          break;
      case Qt::Key_W:   //up
          if(pitch<37.)
          pitch +=5.0;
          break;

     default: break;
//         QFrame::keyPressEvent(event);
     }
     update();
 }



inline void error(const char* msg)
{
    perror(msg);
    exit(0);
}

/*
inline void handler(int signal)
{
    printf("caught ctrl-c\n");
    close(sockfd);
    exit(0);

}*/


BilMuh::~BilMuh()
{
    delete ui;
}
