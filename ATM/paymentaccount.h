#ifndef PAYMENTACCOUNT_H
#define PAYMENTACCOUNT_H
#include <QWidget>
#include "ui_paymentAccount.h"
#include "AtmInput.h"
class AtmInput;

class PaymentAccount : public QWidget
{
   Q_OBJECT
public:
   explicit PaymentAccount(QWidget *parent = 0, AtmInput *ai = 0);
   ~PaymentAccount();
private slots:

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_okAct_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();

    void on_eraseAct_clicked();

    void on_cancelButt_clicked();

    void on_cancelAct_clicked();

private:
    Ui::PaymentAccount* _ui;
    AtmInput* _ai;
    QString _login;
    unsigned int _count;
    const unsigned int limit = 16;
    void enterNumber(unsigned char num);
    bool sendPaymentLogin();
    void setMessege(const QString&);
};
#endif // PAYMENTACCOUNT_H
