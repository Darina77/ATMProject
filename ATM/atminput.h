#ifndef ATMINPUT_H
#define ATMINPUT_H
#include <QStackedWidget>
#include <QCoreApplication>
#include "shotuserinfo.h"
#include "login.h"
#include "pin.h"
#include "menu.h"

 class AtmInput : public QStackedWidget
 {
    Q_OBJECT
 public:
    explicit AtmInput(QWidget* parent = 0);
    void setUser(const QString& cardNum);
    void blockUser();
    bool isBlocked() const;
 private:
     ShotUserInfo _userInfo;
     //TODO розрахунок купюр?
 };

 #endif
