#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include "ui_login.h"
#include "AtmInput.h"
class AtmInput;

class Login : public QWidget
{
   Q_OBJECT
public:
   explicit Login(QWidget *parent = 0, AtmInput *ai = 0);
   ~Login();
private slots:
   void on_okAct_clicked();

   void on_num1_clicked();

   void on_num2_clicked();

   void on_num3_clicked();

   void on_num4_clicked();

   void on_num5_clicked();

   void on_num6_clicked();

   void on_num7_clicked();

   void on_num8_clicked();

   void on_num9_clicked();

   void on_num0_clicked();

   void on_eraseAct_clicked();

   void on_cancelAct_clicked();

   void on_cancelButt_clicked();

private:
   Ui::Login* _ui;
   AtmInput* _ai;
   QString _login;
   unsigned int _count;
   const unsigned int limit = 16;
   void enterNumber(unsigned char num);
   bool sendLogin();
   void setMessege(const QString&);
};
#endif // LOGIN_H
