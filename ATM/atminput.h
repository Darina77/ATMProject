#ifndef ATMINPUT_H
#define ATMINPUT_H

#include <QMainWindow>
#include <QSslSocket>
#include "ui_login.h"


 class AtmInput : public QMainWindow
 {
    Q_OBJECT
 public:
    explicit AtmInput(QWidget *parent = 0);
 private slots:
   // void getCardNumber();
   // void getPin();
   // void takeMoney();
   // void getMoney();
   // void sendMoney();
   // void showCount();
 private:
    QSslSocket* out;
    QSslSocket* in;
    Ui::Login ui;
 };

 #endif