
#include "dialog.h"
#include "ui_dialog.h"
#include "qbrush.h"
#include <qgraphicsitem.h>
#include <QGraphicsPixmapItem>
#include "qfiledialog.h"
#include "qmessagebox.h"
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QThread>
#include <QPixmap>
#include <qdebug.h>
#include <QDebug>
#include <QPainter>
#include "dialogthread.h"

int buttonFlag2 = 0;

int Dialog::target = 0;
int Dialog::location = 0;



int flag_A_B = 0, flag_B_F = 0, flag_F_G = 0, flag_G_E = 0, flag_E_K = 0,
    flag_K_I = 0, flag_B_C = 0, flag_C_D = 0, flag_D_E = 0, flag_A_J = 0, flag_J_H = 0,
    flag_H_I = 0 ;

 QPushButton *button8, *button9, *button10, *button11,*button12,*button13,*button14,*button15,*button16,*button17,*button18;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QImage imageObject;
    imageObject.load("map.png");

  //  qDebug() << "basladi";

    QPalette palette;
    palette.setBrush(QPalette::Background,imageObject);
    this->setPalette(palette);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

     roll = 10.0;
     pitch = 10.0;

     // yolları temizle
     QPushButton *button = new QPushButton("RESET", this);
     // set size and location of the button
     button->setGeometry(QRect(QPoint(960, 820),
     QSize(60, 40)));
     connect(button, SIGNAL(clicked()), this, SLOT(reset()));


    // bina onu
    button8 = new QPushButton("C", this);
    // set size and location of the button
    button8->setGeometry(QRect(QPoint(200, 140),
    QSize(30, 30)));

    connect(button8, SIGNAL(clicked()), this, SLOT(pressC()));



    // bina onu yukari
    button9 = new QPushButton("B", this);
    // set size and location of the button
    button9->setGeometry(QRect(QPoint(200,70),
    QSize(30, 30)));

    connect(button9, SIGNAL(clicked()), this, SLOT(pressB()));



    // bina onu yukari
    button10 = new QPushButton("D", this);
    // set size and location of the button
    button10->setGeometry(QRect(QPoint(200, 245),
    QSize(30, 30)));

    connect(button10, SIGNAL(clicked()), this, SLOT(pressD()));


    // bina onu yukari
    button11 = new QPushButton("A", this);
    // set size and location of the button
    button11->setGeometry(QRect(QPoint(20, 70),
    QSize(30, 30)));
    connect(button11, SIGNAL(clicked()), this, SLOT(pressA()));


    //en asagi
    button12 = new QPushButton("H", this);
    // set size and location of the button
    button12->setGeometry(QRect(QPoint(20,740),
    QSize(30, 30)));
    connect(button12, SIGNAL(clicked()), this, SLOT(pressH()));

    //su deposu
    button13 = new QPushButton("F", this);
    // set size and location of the button
    button13->setGeometry(QRect(QPoint(430,65),
    QSize(30, 30)));
    connect(button13, SIGNAL(clicked()), this, SLOT(pressF()));

    //en yukari kutuphane
    button14 = new QPushButton("G", this);
    // set size and location of the button
    button14->setGeometry(QRect(QPoint(885,70),
    QSize(30, 30)));
    connect(button14, SIGNAL(clicked()), this, SLOT(pressG()));

    //orta yol kutuphane
    button15 = new QPushButton("E", this);
    // set size and location of the button
    button15->setGeometry(QRect(QPoint(885,240),
    QSize(30, 30)));
    connect(button15, SIGNAL(clicked()), this, SLOT(pressE()));

    //asagı kütüphane
    button16 = new QPushButton("I", this);
    // set size and location of the button
    button16->setGeometry(QRect(QPoint(890,740),
    QSize(30, 30)));
    connect(button16, SIGNAL(clicked()), this, SLOT(pressI()));


    //orta yol elektronik
    button18 = new QPushButton("J", this);
    // set size and location of the button
    button18->setGeometry(QRect(QPoint(20,400),
    QSize(30, 30)));
    connect(button18, SIGNAL(clicked()), this, SLOT(pressJ()));

    button17 = new QPushButton("K",this);
    button17->setGeometry(QRect(QPoint(890,500),
    QSize(30, 30)));
    connect(button17, SIGNAL(clicked()), this, SLOT(pressK()));

    startWorkInAThreadDialog();
}




void Dialog::startWorkInAThreadDialog() {
    DialogThread *dialogThread = new DialogThread;
    // Connect our signal and slot
    connect(dialogThread, SIGNAL(progressChanged(int)),this,SLOT(onProcessChanged(int)));// Setup callback for cleanup when it finishes
    connect(this, SIGNAL(progressSetLocation(int)), dialogThread,SLOT(onProgressLocationSet(int)));
    connect(dialogThread,SIGNAL(progressShortestPath(int,char*)), this, SLOT(onProgressShortestPath(int,char*)));
    //connect(this,SIGNAL(progressIpAddress(QString)),dialogThread,SLOT(onPortNumChanged(QString)));
     connect(dialogThread, SIGNAL(finished()),
                dialogThread, SLOT(deleteLater()));
        // Run, Forest, run!
        dialogThread->start();
}


void Dialog::onProcessChanged(int info) {

           location = info;

}

void Dialog::onProgressShortestPath(int info1, char* info) {
    cout << "sizebitch" << info1;
    cout << info << endl;



    setShortestPath(info1,info);
}

void Dialog::setShortestPath(int lenght, char *shortPath) {
    int areaFrom;
    int areaTo;

    lenght = lenght -1 ;

    for (int i = 0 ; i < lenght ; i++) {
        areaFrom = shortPath[i]-'@';

        if( i !=  lenght-1 )
         areaTo = shortPath[i+1]-'@';

        cout << "from" << areaFrom << "to "<<areaTo << endl;

        if((areaFrom == 1 && areaTo == 10) || (areaFrom == 10 && areaTo == 1))
            show_flag_A_J();
        if((areaFrom == 1 && areaTo == 2) || (areaFrom == 2 && areaTo == 1))
            show_flag_A_B();
        if((areaFrom == 2 && areaTo == 3) || (areaFrom == 3 && areaTo == 2))
            show_flag_B_C();
        if((areaFrom == 3 && areaTo == 4) || (areaFrom == 4 && areaTo == 3))
            show_flag_C_D();
        if((areaFrom == 2 && areaTo == 6) || (areaFrom == 6 && areaTo == 2))
            show_flag_B_F();
        if((areaFrom == 6 && areaTo == 7) || (areaFrom == 7 && areaTo == 6))
            show_flag_F_G();
        if((areaFrom == 7 && areaTo == 5) || (areaFrom == 5 && areaTo == 7))
            show_flag_G_E();
        if((areaFrom == 4 && areaTo == 5) || (areaFrom == 5 && areaTo == 4))
            show_flag_D_E();
        if((areaFrom == 5 && areaTo == 11) || (areaFrom == 11 && areaTo == 5))
            show_flag_E_K();
        if((areaFrom == 11 && areaTo == 9) || (areaFrom == 9 && areaTo == 11))
            show_flag_K_I();
        if((areaFrom == 10 && areaTo == 8) || (areaFrom == 8 && areaTo == 10))
            show_flag_J_H();
        if((areaFrom == 8 && areaTo == 9)||(areaFrom == 9 && areaTo == 8))
            flag_H_I = 0;
    }
}



void Dialog::reset()
{

    flag_A_B = 0;
    flag_B_F = 0;
    flag_F_G = 0;
    flag_G_E = 0;
    flag_E_K = 0;
    flag_K_I = 0;
    flag_B_C = 0;
    flag_C_D = 0;
    flag_D_E = 0;
    flag_A_J = 0;
    flag_J_H = 0;


    roll = 0.0;
    pitch = 0.0;

    location = 0;
    target = 0 ;

    buttonFlag2 = 0 ;

}

void Dialog::show_flag_A_B()
{
    flag_A_B = 1;
}
 void Dialog:: show_flag_B_F()
 {
     flag_B_F = 1;
 }
 void Dialog:: show_flag_F_G()
 {
      flag_F_G = 1;
 }
 void Dialog:: show_flag_G_E()
 {
     flag_G_E = 1;
 }
 void Dialog:: show_flag_E_K()
 {
     flag_E_K = 1;
 }
 void Dialog:: show_flag_K_I()
 {
     flag_K_I = 1;
 }
 void Dialog:: show_flag_B_C()
 {
     flag_B_C = 1;
 }
 void Dialog:: show_flag_C_D()
 {
     flag_C_D = 1;
 }
 void Dialog:: show_flag_D_E()
 {
     flag_D_E = 1;
 }
 void Dialog:: show_flag_A_J()
 {
     flag_A_J = 1;
 }
 void Dialog:: show_flag_J_H()
 {
     flag_J_H = 1;
 }





//*****************************************************************************************

void Dialog::pressK() {
    if( buttonFlag2 == 0 ) {
        buttonFlag2 = -1;
        target = 11;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(11);
    }
}

void Dialog::pressA()
{
    if( buttonFlag2 == 0 ) {
        buttonFlag2 = -1;
        target = 1;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(1);
    }
}


void Dialog::pressB()
{
    if( buttonFlag2 == 0 ) {
        buttonFlag2 = -1;
        target = 2;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(2);
    }
}



void Dialog::pressC()
{
    if( buttonFlag2 == 0 ) {
        buttonFlag2 = -1;
        target = 3;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(3);
    }
}





void Dialog::pressD()
{
    if( buttonFlag2 == 0 ) {
        buttonFlag2 = -1;
        target = 4;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(4);
    }
}




void Dialog::pressE()
{
    if( buttonFlag2 == 0 ) {
        buttonFlag2 = -1;
        target = 5;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(5);
    }
}


void Dialog::pressF()
{
    if( buttonFlag2 == 0 ) {
        buttonFlag2 = -1;
        target = 6;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(6);
    }
}



void Dialog::pressG()
{
    if( buttonFlag2 == 0 ) {
        buttonFlag2 = -1;
        target = 7;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(7);
    }
}



void Dialog::pressH()
{
    if( buttonFlag2 == 0 ) {
        buttonFlag2 = -1;
        target = 8;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(8);
    }
}



void Dialog::pressI()
{
    if( buttonFlag2 == 0 ) {
        buttonFlag2 = -1;
        target = 9;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(9);
    }
}



void Dialog::pressJ()
{
    if( buttonFlag2 == 0 ) {
        buttonFlag2 = -1;
        target = 10;
  //      location = 1;
        //write(getSocket(), &target, sizeof(int));
        emit progressSetLocation(10);
    }
}





void Dialog::paintEvent(QPaintEvent *)
{

 //    QGraphicsView * parent;
  //  int r=0;
    QPainter painter(this);
    QBrush ellipseColor(QColor(48,172,220));
    painter.setPen( QPen(Qt::red,12) );
    painter.setBrush(ellipseColor);

    //a -> b
    if(flag_A_B == 1)
        painter.drawLine(30,80, 210,80);
    //b -> f
    if(flag_B_F == 1)
        painter.drawLine(210,80,440,80);

    //b -> c
    if(flag_B_C == 1)
        painter.drawLine(220,80,220,150);

    //c -> d
    if(flag_C_D == 1)
        painter.drawLine(220,150,220,250);

    //d -> e
    if(flag_D_E == 1)
        painter.drawLine(210,260,900,260);

    //f -> g
    if(flag_F_G == 1)
        painter.drawLine(440,80,900,80);

    //g -> e
    if(flag_G_E == 1)
        painter.drawLine(900,80,900,250);

    //e -> k
    if(flag_E_K == 1)
        painter.drawLine(900,250,900,510);

    //k -> i
    if(flag_K_I == 1)
        painter.drawLine(900,510,900,750);

    //a -> j
    if(flag_A_J == 1)
        painter.drawLine(35,80,35,410);

    //j -> h
    if(flag_J_H == 1)
        painter.drawLine(35,410,35,750);
    //h->ı
    if(flag_H_I == 1)
        painter.drawLine(35,760,900,760);

    if( location == 1 ) {
        button11->setStyleSheet("QPushButton {background-color: red;color: red;}");
    }

    if( location == 2 ) {
        button9->setStyleSheet("QPushButton {background-color: red;color: red;}");
    }

    if( location == 3 ) {
        button8->setStyleSheet("QPushButton {background-color: red;color: red;}");
    }

    if( location == 4 ) {
        button10->setStyleSheet("QPushButton {background-color: red;color: red;}");
    }

    if( location == 5 ) {
        button15->setStyleSheet("QPushButton {background-color: red;color: red;}");
    }

    if( location == 6 ) {
        button13->setStyleSheet("QPushButton {background-color: red;color: red;}");
    }

    if( location == 7 ) {
        button14->setStyleSheet("QPushButton {background-color: red;color: red;}");
    }

    if( location == 8 ) {
        button12->setStyleSheet("QPushButton {background-color: red;color: red;}");
    }

    if( location == 9 ) {
        button16->setStyleSheet("QPushButton {background-color: red;color: red;}");
    }

    if( location == 10 ) {
        button18->setStyleSheet("QPushButton {background-color: red;color: red;}");
    }

    if( location == 11 ) {
        button17->setStyleSheet("QPushButton {background-color: red;color: red;}");
    }




/*

    painter.setPen(QColor(48,172,220));


     //A -> B
     QRect rect1(50,65,180,25);
     painter.fillRect(rect1, QBrush(QColor(128, 128, 255,128)));

     //B -> F
     QRect rect2(250,65,190,25);
     painter.fillRect(rect2, QBrush(QColor(128, 128, 255,128)));


    // F-> G
    QRect rect3(465,65,430,25);
    painter.fillRect(rect3, QBrush(QColor(128, 128, 255, 128)));

    // G -> E
    QRect rect4(888,75,25,175);
    painter.fillRect(rect4, QBrush(QColor(128, 128, 255, 128)));

    // K -> I
    QRect rect5(890,520,20,170);
    painter.fillRect(rect5, QBrush(QColor(128, 128, 255, 128)));

    // B -> C
    QRect rect6(225,80, 30,70);
    painter.fillRect(rect6, QBrush(QColor(128, 128, 255, 128)));

    // C -> D
    QRect rect7(225,170, 30,80);
    painter.fillRect(rect7, QBrush(QColor(128, 128,255, 128)));

    // E -> K
    QRect rect8(888,280,25,220);
    painter.fillRect(rect8, QBrush(QColor(128, 128,255, 128)));

    // D -> E
    QRect rect9(255,250,635,25);
    painter.fillRect(rect9, QBrush(QColor(128, 128, 255, 128)));

    // J -> K
   // QRect rect10(50,430,850,20);
    //painter.fillRect(rect10, QBrush(QColor(128, 128, 255,128)));

    // G -> E
    QRect rect11(20,80,25,340);
    painter.fillRect(rect11, QBrush(QColor(128, 128, 255, 128)));


    // J -> H
    QRect rect12(20,450,25,240);
    painter.fillRect(rect12, QBrush(QColor(128, 128, 255, 128)));

*/

}





Dialog::~Dialog()
{
    delete ui;
}
