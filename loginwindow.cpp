#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QDialog (parent)
{
    initView();
}

void LoginWindow::initView()
{
    this->setMinimumSize(150, 200);
    this->setWindowTitle("用户登录");

    QLabel* username_label = new QLabel("账号", this);
    QLabel* password_label = new QLabel("密码", this);
    username_edit = new QLineEdit(this);
    password_edit = new QLineEdit(this);
    login_btn = new QPushButton("登录", this);
    register_btn = new QPushButton("注册", this);

    QHBoxLayout* username_layout = new QHBoxLayout();
    username_layout->addWidget(username_label);
    username_layout->addWidget(username_edit);
    username_layout->setStretch(0, 1);
    username_layout->setStretch(1, 2);

    QHBoxLayout* password_layout = new QHBoxLayout();
    password_layout->addWidget(password_label);
    password_layout->addWidget(password_edit);
    password_layout->setStretch(0, 1);
    password_layout->setStretch(1, 2);

    QHBoxLayout* btn_layout = new QHBoxLayout();
    btn_layout->addWidget(login_btn);
    btn_layout->addWidget(register_btn);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addLayout(username_layout);
    main_layout->addLayout(password_layout);
    main_layout->addLayout(btn_layout);
}
