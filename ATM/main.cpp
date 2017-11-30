#include "AtmInput.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AtmInput mainWindow(QUrl(QStringLiteral("ws://localhost:1234")));
    mainWindow.show();
    return app.exec();
}
