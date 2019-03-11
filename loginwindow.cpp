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

    if (DEBUG_MODE)
    {
        username_edit->setText("user0");
        password_edit->setText("0");
    }
    password_edit->setEchoMode(QLineEdit::Password);

    connect(login_btn, SIGNAL(clicked()), this, SLOT(slotLogin()));
    connect(register_btn, SIGNAL(clicked()), this, SLOT(slotRegister()));

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

void LoginWindow::slotLogin()
{
    QString username = username_edit->text();
    QString password = password_edit->text();
    if (username.isEmpty())
    {
        QMessageBox::warning(this, "登录", "请输入用户账号");
        return ;
    }
    if (password.isEmpty())
    {
        QMessageBox::warning(this, "登录", "请输入用户密码");
        return ;
    }

    // 开始登录
    QStringList params = { "username", username, "password", password };

    ConnectUtil* con = new ConnectUtil("login", params);
    connect(con, SIGNAL(signalFinished(QString)), this, SLOT(slotLoginFinished(QString)));
}

void LoginWindow::slotRegister()
{
    QMessageBox::information(this, "注册", "本程序仅提供会议室桌面端签到，请登录《智能会议室管理系统》官网进行注册");
}

void LoginWindow::slotLoginFinished(QString content)
{
    QString result = getXml(content, "result");
    if (result == "" || result == "0")
    {
        QMessageBox::critical(this, "登录", "登录失败！\n"+result);
        return ;
    }

    user.username = username_edit->text();
    user.password = password_edit->text();
    user.nickname = getXml(content, "nickname");
    user.user_id = getXml(content, "user_id");
    qDebug() << "登录成功 : " << "user_id:" << user.user_id << "    nickname:" << user.nickname;

    emit signalLoginFinished();

    this->close();
}
