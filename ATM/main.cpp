#include "AtmInput.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AtmInput mainWindow(QUrl(QStringLiteral("ws://peroa.dlinkddns.com:40000")));
    mainWindow.show();
    return app.exec();
}
