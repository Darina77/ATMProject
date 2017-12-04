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

    explicit Other(QWidget *parent = 0);
    ~Other();

signals:

    void nextPageIndex(const int);
    int currentPageIndex();

private slots:

    void on_anotherButt_clicked();
    void on_cancelButt_clicked();

private:

    Ui::Other* _ui;
};

#endif // OTHER_H
