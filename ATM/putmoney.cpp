#include "putmoney.h"

PutMoney::PutMoney(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::PutMoney)
    , _strAmount("")
    , _amount(0)
    , _count(0)
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


void PutMoney::setMessege(const QString& messege)
{
    _ui->info->setText(messege);
    this->update();
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
    if(_strAmount.length() > 0){
        _amount = _strAmount.toInt();
        if (_amount <= _amountLimit){
            setMessege("Wait a minute...");
            emit putMoney(_amount*100);
        } else setMessege("Maximum amount " + QString::number(_amountLimit));
    } else setMessege("Enter the amount");
}

void PutMoney::catchPutMoney(const bool res, const QString&, const QString& reason)
{

    if (currentPageIndex() != 5 || _strAmount.length() == 0) return;
    if (res)
    {
        setMessege("Success");
    }
    else
    {
        setMessege(reason);
    }
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
    nextPageIndex(2);
}
