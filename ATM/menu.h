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
        explicit Menu(QWidget *parent = 0);
        ~Menu();
signals:
    void nextPageIndex(int);
    int currentPageIndex();
private slots:

    void on_getMoney_clicked();

    void on_deposit_clicked();

    void on_balance_clicked();

    void on_payments_clicked();

    void on_transfer_clicked();

    void on_other_clicked();

    void on_anotherButt_clicked();

    void on_cancelButt_clicked();

private:
        Ui::Menu* _ui;
        //AtmInput* _ai;
};

#endif // MENU_H
