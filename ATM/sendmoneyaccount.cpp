#include "sendmoneyaccount.h"

SendMoneyAccount::SendMoneyAccount(QWidget *parent, AtmInput* ai):QWidget(parent), _ui(new Ui::SendMoneyAccount), _ai(ai), _login(""), _count(0)
{
   _ui->setupUi(this);
}

SendMoneyAccount::~SendMoneyAccount()
{
    delete _ui;
}

void SendMoneyAccount::enterNumber(unsigned char num)
{
    if(_count < limit)
    {
        _login.append(num);
        _ui->CardNumLine->setText(_login);
        _count++;
    }
    if (_count%4 == 0) _login.append(' ');
}

void SendMoneyAccount::setMessege(const QString& messege)
{
    _ui->info->setText(messege);
}

bool SendMoneyAccount::sendSendLogin()
{
    //TODO Beckend
    return true;
}
void SendMoneyAccount::on_pushButton_1_clicked()
{
    enterNumber('1');
}

void SendMoneyAccount::on_pushButton_2_clicked()
{
    enterNumber('2');
}

void SendMoneyAccount::on_pushButton_3_clicked()
{
    enterNumber('3');
}

void SendMoneyAccount::on_pushButton_4_clicked()
{
    enterNumber('4');
}

void SendMoneyAccount::on_pushButton_5_clicked()
{
    enterNumber('5');
}

void SendMoneyAccount::on_pushButton_6_clicked()
{
    enterNumber('6');
}

void SendMoneyAccount::on_pushButton_7_clicked()
{
    enterNumber('7');
}

void SendMoneyAccount::on_pushButton_8_clicked()
{
    enterNumber('8');
}

void SendMoneyAccount::on_pushButton_9_clicked()
{
    enterNumber('9');
}

void SendMoneyAccount::on_pushButton_0_clicked()
{
    enterNumber('0');
}

void SendMoneyAccount::on_okAct_clicked()
{
    if (_count == limit)
    {
        if (sendSendLogin())
        {
            this->close();
            _ai->setCurrentIndex(8);
        } else
        {
            setMessege("No such card number");
        }
    } else setMessege("Card number is not full");
}

void SendMoneyAccount::on_eraseAct_clicked()
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

        _ui->CardNumLine->setText(_login);
        _count--;
    }
}

void SendMoneyAccount::on_cancelAct_clicked()
{
    _login =  "";
    _ui->CardNumLine->setText(_login);
    _count = 0;
}

void SendMoneyAccount::on_cancelButt_clicked()
{
    _login =  "";
    _ui->CardNumLine->setText(_login);
    _count = 0;
    this->close();
    _ai->setCurrentIndex(2);
}
