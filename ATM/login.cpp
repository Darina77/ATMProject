#include "login.h"

Login::Login(QWidget *parent)
    :QWidget(parent), _ui(new Ui::Login), _login(""), _count(0), _enterLogin("")
{
   _ui->setupUi(this);
}

 Login::~Login()
 {
     delete _ui;
 }

 void Login::enterNumber(unsigned char num)
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

void Login::catchLoginOk(const bool res, const QString& str, const QString& reason)
{
    if (currentPageIndex() != 0 || _count != limit) return;
    if (res)
    {
        this->close();
        emit userChoosed(_login, "0");
        _login =  "";
        _enterLogin = "";
        _ui->CardNumLine->setText(_enterLogin);
        _count = 0;
        setMessege("");
        nextPageIndex(1);
     }
     else
     {
        setMessege(reason);
     }
}

void Login::on_okAct_clicked()
{
    if (_count == limit)
    {
        setMessege("Wait a minute...");
        emit getLogin(_login);

    } else setMessege("Card number is not full");
}

void Login::setMessege(const QString& messege)
{
    _ui->info->setText(messege);
}

void Login::on_num1_clicked()
{
    enterNumber('1');
}

void Login::on_num2_clicked()
{
    enterNumber('2');
}

void Login::on_num3_clicked()
{
    enterNumber('3');
}

void Login::on_num4_clicked()
{
    enterNumber('4');
}

void Login::on_num5_clicked()
{
    enterNumber('5');
}

void Login::on_num6_clicked()
{
    enterNumber('6');
}

void Login::on_num7_clicked()
{
    enterNumber('7');
}

void Login::on_num8_clicked()
{
   enterNumber('8');
}

void Login::on_num9_clicked()
{
    enterNumber('9');
}

void Login::on_num0_clicked()
{
   enterNumber('0');
}

void Login::on_eraseAct_clicked()
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

void Login::on_cancelAct_clicked()
{
    _login =  "";
    _enterLogin = "";
    _ui->CardNumLine->setText(_enterLogin);
    _count = 0;
}

void Login::on_cancelButt_clicked()
{
    _login =  "";
    _enterLogin = "";
    _ui->CardNumLine->setText(_enterLogin);
    _count = 0;
}



