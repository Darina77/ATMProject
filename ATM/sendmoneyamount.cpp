#include "sendmoneyamount.h"

SendMoneyAmount::SendMoneyAmount(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::SendMoneyAmount)
    , _strAmount("")
    , _amount(0)
    , _count(0)
{
    _ui->setupUi(this);
}

SendMoneyAmount::~SendMoneyAmount()
{
    delete _ui;
}

void SendMoneyAmount::enterNumber(unsigned char num)
{
    if(_count < _charLimit)
    {
        _strAmount.append(num);
        _ui->lineEdit->setText(_strAmount);
        _count++;
    }
}

void SendMoneyAmount::setMessege(const QString& messege)
{
    _ui->info->setText(messege);
    this->update();
}

void SendMoneyAmount::on_pushButton_1_clicked()
{
    enterNumber('1');
}

void SendMoneyAmount::on_pushButton_2_clicked()
{
    enterNumber('2');
}

void SendMoneyAmount::on_pushButton_3_clicked()
{
    enterNumber('3');
}

void SendMoneyAmount::on_pushButton_4_clicked()
{
    enterNumber('4');
}

void SendMoneyAmount::on_pushButton_5_clicked()
{
    enterNumber('5');
}

void SendMoneyAmount::on_pushButton_6_clicked()
{
    enterNumber('6');
}

void SendMoneyAmount::on_pushButton_7_clicked()
{
    enterNumber('7');
}

void SendMoneyAmount::on_pushButton_8_clicked()
{
    enterNumber('8');
}

void SendMoneyAmount::on_pushButton_9_clicked()
{
    enterNumber('9');
}

void SendMoneyAmount::on_pushButton_0_clicked()
{
    enterNumber('0');
}

void SendMoneyAmount::catchSendMoney(const bool res, const QString& str)
{
    if (currentPageIndex() != 8 || _strAmount.length() == 0) return;
    if (res)
    {
        setMessege("Success");
    }
    else
    {
        setMessege("Error");
    }
}

void SendMoneyAmount::on_okAct_clicked()
{
    _amount = _strAmount.toInt();
    if (_amount <= _amountLimit){
        setMessege("Wait a minute ...");
        emit sendMoney(_amount);
    } else setMessege("Maximum amount " + QString::number(_amountLimit));
}

void SendMoneyAmount::on_eraseAct_clicked()
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

void SendMoneyAmount::on_cancelAct_clicked()
{
    _strAmount =  "";
    _amount = 0;
    _ui->lineEdit->setText(_strAmount);
    _count = 0;
}

void SendMoneyAmount::on_cancelButt_clicked()
{
    _strAmount =  "";
    _amount = 0;
    _ui->lineEdit->setText(_strAmount);
    _ui->info->setText("");
    _count = 0;
    this->close();
    nextPageIndex(2);
}
