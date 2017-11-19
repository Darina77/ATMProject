#include "AtmInput.h"
#include <QCoreApplication>
#include <QUiLoader>
#include <QFile>
#include <QVBoxLayout>

AtmInput::AtmInput(QWidget *parent)
   : QMainWindow(parent), allWidgets(new QStackedWidget)
{
    QWidget* loginWidget = new Login(parent, this);
    allWidgets->addWidget(loginWidget);
    setAtmWidget(loginWidget);

}

void AtmInput::setAtmWidget(QWidget* current)
{
    this->close();
    allWidgets->currentWidget()->close();
    allWidgets->setCurrentWidget(current);
    allWidgets->currentWidget()->show();
}



