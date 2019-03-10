#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow (parent)
{
    initCore();

    initView();

    judgeAccount();
}

void MainWindow::initCore()
{
    APPLICATION_PATH = QApplication::applicationDirPath();
    if (!APPLICATION_PATH.endsWith("/")) APPLICATION_PATH += "/";
    NETWORK_PATH = "http://127.0.0.1/EasyMeeting/public/index.php/Android/Client/";
}

void MainWindow::initView()
{
    this->resize(600, 600);
}

void MainWindow::initData()
{

}

void MainWindow::judgeAccount()
{
    if (USERNAME.isEmpty())
    {
        LoginWindow* login_window = new LoginWindow(this);
        login_window->show();
    }
}
