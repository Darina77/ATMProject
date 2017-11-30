#include "balance.h"

Balance::Balance(QWidget *parent, AtmInput *ai)
    :QWidget(parent), _ui(new Ui::Balance), _ai(ai)
{
    _ui->setupUi(this);
}

Balance::~Balance()
{
    delete _ui;
}

QString Balance::getBalance()
{
    return QString(_ai->getBalance());
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
