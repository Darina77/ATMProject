#include "paymentaccount.h"

PaymentAccount::PaymentAccount(QWidget *parent, AtmInput* ai):QWidget(parent), _ui(new Ui::PaymentAccount), _ai(ai), _login(""), _count(0)
{
   _ui->setupUi(this);
}

PaymentAccount::~PaymentAccount()
{
    delete _ui;
    delete _ai;
}

void PaymentAccount::enterNumber(unsigned char num)
{
    if(_count < limit)
    {
        _login.append(num);
        _ui->lineEdit->setText(_login);
        _count++;
    }
    if (_count%4 == 0) _login.append(' ');
}

void PaymentAccount::setMessege(const QString& messege)
{
    _ui->info->setText(messege);
}

bool PaymentAccount::sendPaymentLogin()
{
    //TODO Beckend
    return true;
}

void PaymentAccount::on_pushButton_1_clicked()
{
    enterNumber('1');
}

void PaymentAccount::on_pushButton_2_clicked()
{
    enterNumber('2');
}

void PaymentAccount::on_pushButton_3_clicked()
{
    enterNumber('3');
}

void PaymentAccount::on_okAct_clicked()
{
    if (_count == limit)
    {
        if (sendPaymentLogin())
        {
            this->close();
            _ai->setCurrentIndex(8);
        } else
        {
            setMessege("No such card number");
        }
    } else setMessege("Card number is not full");
}

void PaymentAccount::on_pushButton_4_clicked()
{
    enterNumber('4');
}

void PaymentAccount::on_pushButton_5_clicked()
{
    enterNumber('5');
}

void PaymentAccount::on_pushButton_6_clicked()
{
    enterNumber('6');
}

void PaymentAccount::on_pushButton_7_clicked()
{
    enterNumber('7');
}

void PaymentAccount::on_pushButton_8_clicked()
{
    enterNumber('8');
}

void PaymentAccount::on_pushButton_9_clicked()
{
    enterNumber('9');
}

void PaymentAccount::on_pushButton_0_clicked()
{
    enterNumber('0');
}

void PaymentAccount::on_eraseAct_clicked()
{
    if(_count > 0)
    {
        int loginSize = _login.size();
        if (_login.at(loginSize-1) == ' ')
        {
            _login.remove(loginSize-1, loginSize-1);
            loginSize--;
        }
        if(loginSize > 1){
            _login.remove(loginSize-1, loginSize-1);
            loginSize--;
        } else _login =  "";

        _ui->lineEdit->setText(_login);
        _count--;
    }
}

void PaymentAccount::on_cancelButt_clicked()
{
    _login =  "";
    _ui->lineEdit->setText(_login);
    _count = 0;
}

void PaymentAccount::on_cancelAct_clicked()
{
    _login =  "";
    _ui->lineEdit->setText(_login);
    _count = 0;
    this->close();
    _ai->setCurrentIndex(2);
}
