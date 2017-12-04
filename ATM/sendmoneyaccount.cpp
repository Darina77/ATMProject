#include "sendmoneyaccount.h"

SendMoneyAccount::SendMoneyAccount(QWidget *parent):
    QWidget(parent)
  , _ui(new Ui::SendMoneyAccount), _login(""), _count(0), _enterLogin("")
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
        _enterLogin.append(num);
        _login.append(num);
        _ui->CardNumLine->setText(_enterLogin);
        _count++;
   }
   if (_count%4 == 0 && _count != limit) _enterLogin.append(' ');
}

void SendMoneyAccount::setMessege(const QString& messege)
{
    _ui->info->setText(messege);
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

 void SendMoneyAccount::catchSendMoneyAcc(const bool res, const QString&, const QString& reason)
 {
     if (currentPageIndex() != 7 || _login.length() == 0) return;
     if (res)
     {
         this->close();
         _login =  "";
         _enterLogin = "";
         _ui->CardNumLine->setText(_enterLogin);
         _count = 0;
         setMessege("");
         nextPageIndex(8);
     }
     else
     {
         setMessege(reason);
     }
 }

void SendMoneyAccount::on_okAct_clicked()
{
    if (_count == limit)
    {
        setMessege("Wait a second...");
        sendMoneyAcc(_login);   
    } else setMessege("Card number is not full");
}

void SendMoneyAccount::on_eraseAct_clicked()
{
    if(_count > 0)
    {
        int enterLoginSize = _enterLogin.size();
        if (_enterLogin.at(enterLoginSize-1) == ' ')
        {
            _enterLogin.remove(enterLoginSize-1, enterLoginSize-1);
            enterLoginSize--;
        }
        if(enterLoginSize > 1){
            _login.remove(_count-1, _count-1);
            _enterLogin.remove(enterLoginSize-1, enterLoginSize-1);
            enterLoginSize--;
        } else {
            _login =  "";
            _enterLogin = "";
         }
        _ui->CardNumLine->setText(_enterLogin);
        _count--;
    }
}

void SendMoneyAccount::on_cancelAct_clicked()
{
    _login =  "";
    _enterLogin = "";
    _ui->CardNumLine->setText(_enterLogin);
    _count = 0;
}

void SendMoneyAccount::on_cancelButt_clicked()
{
    _login =  "";
    _enterLogin = "";
    _ui->CardNumLine->setText(_enterLogin);
    _count = 0;
    this->close();
    nextPageIndex(2);
}
