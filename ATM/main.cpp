#include "AtmInput.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    int id = QFontDatabase::addApplicationFont(":/fonts/kenvector_future.ttf");
    QString f = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(f);
    AtmInput mainWindow(QUrl(QStringLiteral("ws://peroa.dlinkddns.com:40000")));
    mainWindow.setFont(font);
    mainWindow.show();
    return app.exec();
}
