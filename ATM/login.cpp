#include "login.h"

Login::Login(QWidget *parent, AtmInput* ai)
    :QWidget(parent), _ui(new Ui::Login), _ai(ai), _login(""), _count(0)
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
         _login.append(num);
         _ui->CardNumLine->setText(_login);
         _count++;
     }
     if (_count%4 == 0 && _count != limit) _login.append(' ');
 }

void Login::on_okAct_clicked()
{
    if (_count == limit){
        if (sendLogin())
        {
            this->close();
            _ai->setUser(_login);
            _login =  "";
            _ui->CardNumLine->setText(_login);
            _count = 0;
            _ai->setCurrentIndex(1);

        } else
        {
            setMessege("No such card number");
        }
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

void Login::on_cancelAct_clicked()
{
    _login =  "";
    _ui->CardNumLine->setText(_login);
    _count = 0;
}

void Login::on_cancelButt_clicked()
{
    _login =  "";
    _ui->CardNumLine->setText(_login);
    _count = 0;
}

bool Login::sendLogin()
{
    //TODO Beckend
    return true;
}

