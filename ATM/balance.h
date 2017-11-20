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
    explicit Balance(QWidget *parent = 0, AtmInput *ai = 0);
    ~Balance();
private slots:
  void on_anotherButt_clicked();
  void on_cancelButt_clicked();
private:
    Ui::Balance* _ui;
    AtmInput* _ai;
    QString& getBalance();
};
#endif // BALANCE_H
