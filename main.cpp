#include "mainwindow.h"
#include <QApplication>

void initCore()
{
    APPLICATION_PATH = QApplication::applicationDirPath();
    if (!APPLICATION_PATH.endsWith("/")) APPLICATION_PATH += "/";
    NETWORK_PATH = "http://127.0.0.1/EasyMeeting/public/index.php/Android/Client/";
    DEBUG_MODE = true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initCore();

    MainWindow w;
    w.show();

    return a.exec();
}
