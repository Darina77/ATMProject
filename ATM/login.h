#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include "ui_login.h"
#include "AtmInput.h"
class AtmInput;

class Login : public QWidget, private Ui::Login
{
   Q_OBJECT
public:
   explicit Login(QWidget *parent = 0, AtmInput *ai = 0);
private slots:
    void on_okAct_clicked();
private:
    AtmInput* _currentAI;
};
#endif // LOGIN_H
