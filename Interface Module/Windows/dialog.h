#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include <qgraphicsitemanimation.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    static int getLocation() {return location;}
    static int getTarget() { return target;}

    static void setLocation(int loc) { location = loc; }
    static void setTarget(int trgt) { target = trgt;}


    void show_flag_A_B();
     void show_flag_B_F();
     void show_flag_F_G();
     void show_flag_G_E();
     void show_flag_E_K();
     void show_flag_K_I();
     void show_flag_B_C();
     void show_flag_C_D();
     void show_flag_D_E();
     void show_flag_A_J();
     void show_flag_J_H();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    qreal roll;
    qreal pitch;

    static int target;
    static int location;
    void startWorkInAThreadDialog();
    void setShortestPath(int lenght, char* shortPath);


public slots:

    void reset();

    void pressA();
    void pressB();
    void pressC();
    void pressD();
    void pressE();
    void pressF();
    void pressG();
    void pressH();
    void pressI();
    void pressJ();
    void pressK();



    void onProcessChanged(int info);
    void onProgressShortestPath(int info1, char* info);


signals:
    void progressSetLocation(int loc);


protected:
    void paintEvent(QPaintEvent *event);
};


#endif // DIALOG_H
