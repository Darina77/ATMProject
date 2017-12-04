#include "getmoney.h"

GetMoney::GetMoney(QWidget *parent):
    QWidget(parent)
  , _ui(new Ui::GetMoney)
  , _strAmount(""),
    _amount(0), _count(0)
{
    _ui->setupUi(this);
}

GetMoney::~GetMoney()
{
    delete _ui;
}

void GetMoney::on_pushButton_1_clicked()
{
    enterNumber('1');
}

void GetMoney::on_pushButton_2_clicked()
{
    enterNumber('2');
}

void GetMoney::on_pushButton_3_clicked()
{
    enterNumber('3');
}

void GetMoney::on_pushButton_4_clicked()
{
    enterNumber('4');
}

void GetMoney::on_pushButton_5_clicked()
{
    enterNumber('5');
}

void GetMoney::on_pushButton_6_clicked()
{
    enterNumber('6');
}

void GetMoney::on_pushButton_7_clicked()
{
    enterNumber('7');
}

void GetMoney::on_pushButton_8_clicked()
{
    enterNumber('8');
}

void GetMoney::on_pushButton_9_clicked()
{
    enterNumber('9');
}

void GetMoney::on_pushButton_0_clicked()
{
    enterNumber('0');
}

void GetMoney::on_okAct_clicked()
{
    _amount = _strAmount.toInt();
    if (_amount <= _amountLimit){
        tryBanknotesValue();
        setMessege("Wait a second...");
    } else setMessege("Maximum amount " + QString::number(_amountLimit));
}

void GetMoney::catchGetMoney(const bool res, const QString& str)
{
    if(currentPageIndex() != 3 || _strAmount.length() < 1) return;
    if (res)
    {
        setMessege("Success");
    }
    else
    {
        setMessege("Error");
    }
}

void GetMoney::catchBanknotesValue(int val)
{
    if(_amount%(val) == 0)
    {
        getMoney(_amount);
    } else setMessege("Amount must be aliquot to " + QString::number(val));
}

void GetMoney::setMessege(const QString& messege)
{
    _ui->info->setText(messege);
    this->update();
}

void GetMoney::on_eraseAct_clicked()
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

void GetMoney::on_cancelAct_clicked()
{
    _strAmount =  "";
    _amount = 0;
    _ui->lineEdit->setText(_strAmount);
    _count = 0;
}

void GetMoney::on_cancelButt_clicked()
{
    _strAmount =  "";
    _amount = 0;
    _ui->lineEdit->setText(_strAmount);
    _ui->info->setText("");
    _count = 0;
    this->close();
    nextPageIndex(2);
}

void GetMoney::enterNumber(unsigned char num)
{
    if(_count < _charLimit)
    {
        _strAmount.append(num);
        _ui->lineEdit->setText(_strAmount);
        _count++;
    }
}

