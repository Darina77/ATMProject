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

class Login;
class Pin;
class Menu;
class GetMoney;
class Balance;
class PutMoney;
class Other;
class SendMoneyAccount;
class SendMoneyAmount;
class PaymentAccount;
class PaymentAmount;

 class AtmInput : public QStackedWidget
 {
    Q_OBJECT
 public:
    explicit AtmInput(const QUrl url, QWidget* parent = 0);
     ~AtmInput();
    void blockUser();
    bool isBlocked() const;
    //які купюри має банкомат
    int getBanknotesValue() const {return banknotes;}
 Q_SIGNALS:
    void closed();
    void userIsBlocked(bool);
    void banknotesValue(int);
    void getBalance();
    void endOperation(const bool, const QString&);
public Q_SLOTS:
    void setUser(const QString& cardNum);
    void tryUserBlocked();
    void tryBanknotesValue();
    void tryGetBalance();
    void tryCheckLogin(const QString&);
    void tryCheckPin(const QString&);
    void tryPutMoney(const int);
    void tryGetMoney(const int);
    void trySendMoneyAcc(const QString&);
    void trySendMoney(const int money);
 private Q_SLOTS:
     void onConnected();
     void onTextMessageReceived(const QString& message);

 private:

     QWebSocket m_webSocket;
     QUrl m_url;
     QString _sendNum;
     bool last_resp_res;
     bool start;
     ShotUserInfo _userInfo;
     const int banknotes = 100; //значення купюр для видачі в банкоматі

     Login* _login;
     Pin* _pin;
     Menu* _menu;
     GetMoney* _getMoney;
     Balance* _balance;
     PutMoney* _putMoney;
     Other* _other;
     SendMoneyAccount* _sma;
     SendMoneyAmount* _sma2;
     PaymentAccount* _pa;
     PaymentAmount* _pa2;
 };

 #endif
