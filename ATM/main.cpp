#include "AtmInput.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFontDatabase::addApplicationFont(":/fonts/kenpixel.ttf");
    AtmInput mainWindow(QUrl(QStringLiteral("ws://peroa.dlinkddns.com:40000")));
    mainWindow.show();
    return app.exec();
}
