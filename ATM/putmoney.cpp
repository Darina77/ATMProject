#include "putmoney.h"

PutMoney::PutMoney(QWidget *parent, AtmInput *ai)
    : QWidget(parent), _ui(new Ui::PutMoney), _ai(ai), _strAmount(""),
      _amount(0), _count(0)
{
    _ui->setupUi(this);
}

PutMoney::~PutMoney()
{
    delete _ui;
}

void PutMoney::enterNumber(unsigned char num)
{
    if(_count < _charLimit)
    {
        _strAmount.append(num);
        _ui->lineEdit->setText(_strAmount);
        _count++;
    }
}

bool PutMoney::sendSum()
{
    //TODO to server
    return true;
}

void PutMoney::setMessege(const QString& messege)
{
    _ui->info->setText(messege);
}

void PutMoney::on_pushButton_1_clicked()
{
    enterNumber('1');
}

void PutMoney::on_pushButton_2_clicked()
{
    enterNumber('2');
}

void PutMoney::on_pushButton_3_clicked()
{
    enterNumber('3');
}

void PutMoney::on_pushButton_4_clicked()
{
    enterNumber('4');
}

void PutMoney::on_pushButton_5_clicked()
{
    enterNumber('5');
}

void PutMoney::on_pushButton_6_clicked()
{
    enterNumber('6');
}

void PutMoney::on_pushButton_7_clicked()
{
    enterNumber('7');
}

void PutMoney::on_pushButton_8_clicked()
{
    enterNumber('8');
}

void PutMoney::on_pushButton_9_clicked()
{
    enterNumber('9');
}

void PutMoney::on_pushButton_0_clicked()
{
    enterNumber('0');
}

void PutMoney::on_okAct_clicked()
{
    _amount = _strAmount.toInt();
    if (_amount <= _amountLimit){
        if (sendSum())
        {
            setMessege("Success");
        }
        else
        {
            setMessege("Error");
        }
    } else setMessege("Maximum amount " + QString::number(_amountLimit));
}

void PutMoney::on_eraseAct_clicked()
{
    if(_count > 0)
    {
        int amountSize = _strAmount.size();
        if(amountSize > 1){
            _strAmount.remove(amountSize-1, amountSize-1);
            amountSize--;
        } else _strAmount =  "";

        _ui->lineEdit->setText(_strAmount);
        _count--;
    }
}

void PutMoney::on_cancelAct_clicked()
{
    _strAmount =  "";
    _amount = 0;
    _ui->lineEdit->setText(_strAmount);
    _count = 0;
}

void PutMoney::on_cancelButt_clicked()
{
    _strAmount =  "";
    _amount = 0;
    _ui->lineEdit->setText(_strAmount);
    _ui->info->setText("");
    _count = 0;
    this->close();
    _ai->setCurrentIndex(2);
}
