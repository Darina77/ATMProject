#include "login.h"

Login::Login(QWidget *parent, AtmInput *ai)
    :QWidget(parent), _currentAI(ai)
{
    setupUi(this);
}

void Login::on_okAct_clicked()
{
   _currentAI->setAtmWidget(this);
}
