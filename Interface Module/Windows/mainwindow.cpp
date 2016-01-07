#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "ui_intcon.h"
#include "dialog.h"
#include "bilmuh.h"
#include "qmessagebox.h"
#include "qfiledialog.h"
#include "qgraphicsitem.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QHBoxLayout>

#include <QInputDialog>
#include <QDir>
#include <QString>
#include <QtGui>
#include <iostream>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    BilMuh obj;

    int x=obj.width()*1;
    int y=obj.height()*1;
    obj.setFixedSize(x,y);


    obj.setModal(true);
    obj.exec();
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
      }

      emit progressPortNum(text);
      emit progressIpAddress(text2);

*/

}



void MainWindow::on_pushButton_2_clicked()
{
   /* bool ok;
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
      }

      emit progressPortNum(text);
*/


    Dialog dialog;

    int x=dialog.width()*1;
    int y=dialog.height()*1;
    dialog.setFixedSize(x,y);



    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->close();
}


