#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QPushButton>
//#include "client.h"


namespace Ui
{
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

  //  void openNewWindow();

private:
    Ui::MainWindow *ui;

signals:
    void progressPortNum(QString info);
    void progressIpAddress(QString info);

};

#endif // MAINWINDOW_H

