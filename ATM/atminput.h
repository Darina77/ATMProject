#ifndef ATMINPUT_H
#define ATMINPUT_H
#include <QStackedWidget>
#include <QCoreApplication>
#include "shotuserinfo.h"
#include "login.h"
#include "pin.h"
#include "menu.h"
#include "getmoney.h"
#include "balance.h"
#include "putmoney.h"
#include "other.h"
#include "sendmoneyaccount.h"
#include "sendmoneyamount.h"
#include "paymentaccount.h"
#include "paymentamount.h"

 class AtmInput : public QStackedWidget
 {
    Q_OBJECT
 public:
    explicit AtmInput(QWidget* parent = 0);
    void setUser(const QString& cardNum);
    void blockUser();
    bool isBlocked() const;
    const int banknotesValue() const {return banknotes;}
 private:
     ShotUserInfo _userInfo;
     const int banknotes = 100;
 };

 #endif
