#ifndef BilMuh_H
#define BilMuh_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <QDebug>
#include <QInputDialog>
#include <QDir>
#include <stdlib.h>


#include "ui_bilmuh.h"
#include "qbrush.h"
#include <qgraphicsitem.h>
#include <QGraphicsPixmapItem>
#include "qfiledialog.h"
#include "qmessagebox.h"
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QPixmap>
#include <QTransform>



namespace Ui {
class BilMuh;
}

class BilMuh : public QDialog
{
    Q_OBJECT

public:
    explicit BilMuh(QWidget *parent = 0);
    ~BilMuh();

    void show_one_two();
    void show_two_three();
    void show_three_four();
    void show_four_five();
    void show_five_six();
    void show_six_seven();
    void show_seven_eight();
    void show_eight_nine();
    void show_nine_ten();
    void show_ten_eleven();
    void show_eleven_twelve();

    static int getLocation() {return location;}
    static int getTarget() { return target;}

    static void setLocation(int loc) { location = loc; }
    static void setTarget(int trgt) { target = trgt;}


private:
    Ui::BilMuh *ui;
    QGraphicsScene *scene;
    qreal roll;
    qreal pitch;

    static int target;
    static int location;
    void startWorkInAThread();
    void setShortestPath(int lenght, char* shortPath);

public slots:
    void onProcessChanged(int info);
    void onProgressShortestPath(int info1, char* info);
    void pressKantin();
    void pressLab();
    void pressZ11();
    void pressZ06();
    void pressRobotik();
    void pressZ02();
    void pressZ04();
    void pressZ05();
    void pressZ10();
    void pressMikroLab();
    void pressDevreLab();
    void pressZ23();
    void pressGiris();
    void reset();

signals:
    void progressSetLocation(int loc);



protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *e);

};

#endif // BilMuh_H
