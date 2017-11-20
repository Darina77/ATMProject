#ifndef PUTMONEY_H
#define PUTMONEY_H
#include <QWidget>
#include "ui_putmoney.h"
#include "AtmInput.h"
class AtmInput;
class PutMoney: public QWidget
{
 Q_OBJECT
 public:
    explicit PutMoney(QWidget *parent = 0, AtmInput *ai = 0);
    ~PutMoney();
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
    Ui::PutMoney* _ui;
    AtmInput* _ai;
    QString _strAmount;

    unsigned int _amount;
    unsigned int _count;
    const unsigned int _charLimit = 4;
    const unsigned int _amountLimit = 5000;
    void enterNumber(unsigned char num);
    bool sendSum();
    void setMessege(const QString&);
};
#endif // PUTMONEY_H
