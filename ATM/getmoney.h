#ifndef GETMONEY_H
#define GETMONEY_H
#include <QWidget>
#include "ui_getmoney.h"
#include "AtmInput.h"
class AtmInput;

class GetMoney: public QWidget
{
 Q_OBJECT
 public:
      explicit GetMoney(QWidget *parent = 0);
      ~GetMoney();

signals:

    void nextPageIndex(const int);
    void tryBanknotesValue();
    int currentPageIndex();
    void getMoney(const int);

 public slots:

    void catchBanknotesValue(const int);
    void catchGetMoney(const bool, const QString&);

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

    Ui::GetMoney* _ui;
    QString _strAmount;
    unsigned int _amount;
    unsigned int _count;

    const unsigned int _charLimit = 4;
    const unsigned int _amountLimit = 5000;

    void enterNumber(unsigned char num);
    void setMessege(const QString&);

};
#endif // GETMONEY_H
