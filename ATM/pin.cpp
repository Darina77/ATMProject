#include "pin.h"

Pin::Pin(QWidget *parent, AtmInput* ai)
    :QWidget(parent), _ui(new Ui::Pin), _ai(ai), _pass(""),
    _setedPass(""), _tryCount(0), _count(0)
{
   _ui->setupUi(this);
}

 Pin::~Pin()
 {
     delete _ui;
 }


void Pin::on_pushButton_1_clicked()
{
    enterNumber('1');
}

void Pin::on_pushButton_2_clicked()
{
    enterNumber('2');
}

void Pin::on_pushButton_3_clicked()
{
    enterNumber('3');
}

void Pin::on_pushButton_4_clicked()
{
    enterNumber('4');
}

void Pin::on_pushButton_5_clicked()
{
    enterNumber('5');
}

void Pin::on_pushButton_6_clicked()
{
    enterNumber('6');
}

void Pin::on_pushButton_7_clicked()
{
    enterNumber('7');
}

void Pin::on_pushButton_8_clicked()
{
    enterNumber('8');
}

void Pin::on_pushButton_9_clicked()
{
    enterNumber('9');
}

void Pin::on_pushButton_0_clicked()
{
    enterNumber('0');
}

void Pin::on_okAct_clicked()
{
    if (!_ai->isBlocked()){
        if (_count == limit){
            if (sendPass())
            {
                _pass =  "";
                _setedPass = "";
                _ui->lineEdit->setText(_setedPass);
                _count = 0;
                this->close();
                _ai->setCurrentIndex(2);
            } else
            {
                _tryCount++;
                setMessege("Wrong password");
            }
        } else setMessege("Wrong password");
    } else setMessege("You are blocked");
}

void Pin::on_eraseAct_clicked()
{
    if(_count > 0)
    {
        int passSize = _pass.size();
        if(passSize > 1)
        {
            _pass.remove(passSize-1, passSize-1);
            _setedPass.remove(passSize-1, passSize-1);
            passSize --;
        }
        else
        {
           _setedPass = "";
           _pass =  "";
        }

        _ui->lineEdit->setText(_setedPass);
        _count--;
    }
}

void Pin::on_cancelAct_clicked()
{
    _pass =  "";
    _setedPass = "";
    _ui->lineEdit->setText(_setedPass);
    _count = 0;
}

void Pin::on_cancelButt_clicked()
{
    _pass =  "";
    _setedPass = "";
    _ui->lineEdit->setText(_setedPass);
    _count = 0;
}

bool Pin::sendPass()
{
    if (_tryCount >= 3)
    {
        _ai->blockUser();
        return false;
    }
    //TODO Beckend
    return true;
}

void Pin::setMessege(const QString& messege)
{
    _ui->info->setText(messege);
}

void Pin::enterNumber(char num)
{
    if(_count < limit)
    {
        _pass.append(num);
        _setedPass.append('*');
        _ui->lineEdit->setText(_setedPass);
        _count++;
    }
}
