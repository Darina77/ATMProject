#ifndef SENDMONEYACCOUNT_H
#define SENDMONEYACCOUNT_H
#include <QWidget>
#include "ui_sendmoneyAccount.h"
#include "AtmInput.h"
class AtmInput;

class SendMoneyAccount : public QWidget
{
   Q_OBJECT
public:

    explicit SendMoneyAccount(QWidget *parent = 0);
   ~SendMoneyAccount();

signals:

    void nextPageIndex(const int);
    int currentPageIndex();
    void sendMoneyAcc(const QString&);

public slots:

    void catchSendMoneyAcc(const bool, const QString&, const QString&);

private slots:

    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_0_clicked();

    void on_okAct_clicked();
    void on_eraseAct_clicked();
    void on_cancelAct_clicked();
    void on_cancelButt_clicked();

private:

    Ui::SendMoneyAccount* _ui;
    QString _login;
    QString _enterLogin;
    unsigned int _count;
    const unsigned int limit = 16;

    void enterNumber(unsigned char num);
    void setMessege(const QString&);
};
#endif // SENDMONEYACCOUNT_H
