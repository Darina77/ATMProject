#include "AtmInput.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AtmInput mainWindow;
    mainWindow.show();
    return app.exec();
}
