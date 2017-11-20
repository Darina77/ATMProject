#ifndef PIN_H
#define PIN_H
#include <QWidget>
#include "ui_pin.h"
#include "AtmInput.h"
class AtmInput;

class Pin : public QWidget
{
   Q_OBJECT
    public:
        explicit Pin(QWidget *parent = 0, AtmInput *ai = 0);
        ~Pin();
    private slots:

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();

    void on_okAct_clicked();

    void on_eraseAct_clicked();

    void on_cancelAct_clicked();

    void on_cancelButt_clicked();

private:
    Ui::Pin* _ui;
    AtmInput* _ai;
    QString _pass;
    QString _setedPass;
    unsigned int _tryCount;
    unsigned int _count;
    const int limit = 4;
    void enterNumber(char num);
    bool sendPass();
    void setMessege(const QString&);
};
#endif // PIN_H
