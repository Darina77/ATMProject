#include "menu.h"

Menu::Menu(QWidget *parent)
    :QWidget(parent), _ui(new Ui::Menu)
{
   _ui->setupUi(this);
}

 Menu::~Menu()
 {
     delete _ui;
 }

void Menu::on_getMoney_clicked()
{
    this->close();
    nextPageIndex(3);
}

void Menu::on_deposit_clicked()
{
    this->close();
    nextPageIndex(5);
}

void Menu::on_balance_clicked()
{
    this->close();
    nextPageIndex(4);
}

void Menu::on_payments_clicked()
{
    this->close();
    nextPageIndex(9);
}

void Menu::on_transfer_clicked()
{
    this->close();
    nextPageIndex(7);
}

void Menu::on_other_clicked()
{
    this->close();
    nextPageIndex(6);
}

void Menu::on_anotherButt_clicked()
{
    this->close();
    nextPageIndex(0);
}

void Menu::on_cancelButt_clicked()
{
    this->close();
    nextPageIndex(0);
}
