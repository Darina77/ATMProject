#include "balance.h"

Balance::Balance(QWidget *parent, AtmInput *ai)
    :QWidget(parent), _ui(new Ui::Balance), _ai(ai)
{
    _ui->setupUi(this);
}

Balance::~Balance()
{
    delete _ui;
    delete _ai;
}

QString Balance::getBalance()
{
    //TODO
    return QString("5000");
}

void Balance::showEvent(QShowEvent *ev)
{
    QWidget::showEvent(ev);
    _ui->amount->setText(getBalance());
}

void Balance::on_anotherButt_clicked()
{
    _ui->amount->setText("");
    this->close();
    _ai->setCurrentIndex(2);
}

void Balance::on_cancelButt_clicked()
{
    _ui->amount->setText("");
    this->close();
    _ai->setCurrentIndex(2);
}
