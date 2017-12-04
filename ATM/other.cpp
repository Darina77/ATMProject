#include "other.h"

//Other::Other(QWidget *parent, AtmInput *ai):
Other::Other(QWidget *parent):
QWidget(parent), _ui(new Ui::Other)//, _ai(ai)
{
    _ui->setupUi(this);
}

Other::~Other()
{
    delete _ui;
}

void Other::on_anotherButt_clicked()
{
    this->close();
    //_ai->setCurrentIndex(2);
    nextPageIndex(2);
}

void Other::on_cancelButt_clicked()
{
    this->close();
    //_ai->setCurrentIndex(2);
    nextPageIndex(2);
}
