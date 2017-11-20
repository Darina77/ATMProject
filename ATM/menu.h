#ifndef MENU_H
#define MENU_H
#include <QWidget>
#include "ui_menu.h"
#include "AtmInput.h"
class AtmInput;

class Menu : public QWidget
{
    Q_OBJECT
    public:
        explicit Menu(QWidget *parent = 0, AtmInput *ai = 0);
        ~Menu();
    private slots:

    void on_getMoney_clicked();

    void on_deposit_clicked();

    void on_balance_clicked();

    void on_payments_clicked();

    void on_transfer_clicked();

    void on_other_clicked();

    void on_anotherButt_clicked();

private:
        Ui::Menu* _ui;
        AtmInput* _ai;
};

#endif // MENU_H
