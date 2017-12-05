#include "balance.h"

Balance::Balance(QWidget *parent)
    :QWidget(parent), _ui(new Ui::Balance)
{
    _ui->setupUi(this);
    _ui->info->setText("Wait a minute...");
    emit getBalance();
}

void Balance::catchBalance(const bool res, QString& str, const QString& reason)
{
    _ui->info->setText("Current balance");
    if(res){
        str = str.insert((str.length()-2), '.');
       _ui->amount->setText(str);
    }
    else
    {
        _ui->amount->setText("0");
        _ui->info->setText(reason);
    }
    this->update();
}

void Balance::showEvent(QShowEvent *ev)
{
    QWidget::showEvent(ev);
    _ui->info->setText("Wait a minute...");
    emit getBalance();
}

Balance::~Balance()
{
    delete _ui;
}


void Balance::on_anotherButt_clicked()
{
    _ui->amount->setText("");
    this->close();
    nextPageIndex(2);
}

void Balance::on_cancelButt_clicked()
{
    _ui->amount->setText("");
    this->close();
    nextPageIndex(2);
}
