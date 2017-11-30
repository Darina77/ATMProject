#ifndef ATMINPUT_H
#define ATMINPUT_H
#include <QStackedWidget>
#include <QCoreApplication>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QThread>
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
#include "fromjson.h"

 class AtmInput : public QStackedWidget
 {
    Q_OBJECT
 public:
    explicit AtmInput(const QUrl url, QWidget* parent = 0);
     ~AtmInput();
    void setUser(const QString& cardNum, const QString& balance);
    void blockUser();
    bool isBlocked() const;
    //які купюри має банкомат
    const int banknotesValue() const {return banknotes;}
    const QString getBalance();
    const bool isRightLogin(QString& str);
    const bool isRightPin(QString& pin);
 Q_SIGNALS:
     void closed();

 private Q_SLOTS:
     void onConnected();
     void onTextMessageReceived(const QString& message);
 private:

     QWebSocket m_webSocket;
     QUrl m_url;
     bool last_resp_res;
     bool start;
     ShotUserInfo _userInfo;
     const int banknotes = 100; //значення купюр для видачі в банкоматі
 };

 #endif
