#include "other.h"

Other::Other(QWidget *parent, AtmInput *ai):
QWidget(parent), _ui(new Ui::Other), _ai(ai)
{
    _ui->setupUi(this);
}

Other::~Other()
{
    delete _ui;
    delete _ai;
}

void Other::on_anotherButt_clicked()
{
    this->close();
    _ai->setCurrentIndex(2);
}

void Other::on_cancelButt_clicked()
{
    this->close();
    _ai->setCurrentIndex(2);
}
