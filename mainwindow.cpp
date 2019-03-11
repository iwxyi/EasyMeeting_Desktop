#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow (parent)
{
    initView();

    judgeAccount();
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
