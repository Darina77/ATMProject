#ifndef OTHER_H
#define OTHER_H
#include <QWidget>
#include "ui_other.h"
#include "AtmInput.h"
class AtmInput;

class Other : public QWidget
{
Q_OBJECT
public:
    explicit Other(QWidget *parent = 0, AtmInput *ai = 0);
    ~Other();
private slots:
    void on_anotherButt_clicked();
    void on_cancelButt_clicked();
private:
    Ui::Other* _ui;
    AtmInput* _ai;
};

#endif // OTHER_H
