#ifndef BALANCE_H
#define BALANCE_H
#include <QWidget>
#include "ui_balance.h"
#include "AtmInput.h"
class AtmInput;

class Balance: public QWidget
{
 Q_OBJECT
public:
    explicit Balance(QWidget *parent = 0);
    ~Balance();
    void showEvent(QShowEvent *ev);
signals:
    void nextPageIndex(int);
    void getBalance();
    int currentPageIndex();
public slots:
    void catchBalance(const bool, const QString&);
private slots:
    void on_anotherButt_clicked();
    void on_cancelButt_clicked();
private:
    Ui::Balance* _ui;
};
#endif // BALANCE_H
