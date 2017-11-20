#include "menu.h"

Menu::Menu(QWidget *parent, AtmInput* ai)
    :QWidget(parent), _ui(new Ui::Menu), _ai(ai)
{
   _ui->setupUi(this);
}

 Menu::~Menu()
 {
     delete _ui;
     delete _ai;
 }

void Menu::on_getMoney_clicked()
{

}

void Menu::on_deposit_clicked()
{

}

void Menu::on_balance_clicked()
{

}

void Menu::on_payments_clicked()
{

}

void Menu::on_transfer_clicked()
{

}

void Menu::on_other_clicked()
{

}

void Menu::on_anotherButt_clicked()
{

}
