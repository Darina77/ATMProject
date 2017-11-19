#include "atminput.h"
#include <QCoreApplication>
#include <QUiLoader>
#include <QFile>
#include <QVBoxLayout>
#include <QRect>

AtmInput::AtmInput(QWidget *parent)
   : QMainWindow(parent)
{
    QUiLoader loader;
    QFile file(":/forms/login.ui");
    file.open(QFile::ReadOnly);
    QWidget *myWidget = loader.load(&file, this);
    file.close();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(myWidget);
    setLayout(layout);

    resize(myWidget->size());
    setMaximumSize(myWidget->size());
    setMinimumSize(myWidget->size());
}
