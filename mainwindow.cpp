#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow (parent)
{
    initView();

    initData();
}

void MainWindow::initView()
{
    this->resize(600, 600);

    nickname_btn = new QPushButton("昵称", this);
    lease_btn = new QPushButton("租约", this);
    exit_btn = new QPushButton("退出", this);
    meeting_name_btn = new QPushButton("会议", this);
    num_btn = new QPushButton("人数情况", this);
    check_btn = new QPushButton("签到", this);
    leave_btn = new QPushButton("签退", this);

    connect(lease_btn, SIGNAL(clicked()), this, SLOT(slotChooseLease()));

    QHBoxLayout* top_layout = new QHBoxLayout;
    top_layout->addWidget(nickname_btn);
    top_layout->addWidget(lease_btn);
    top_layout->addStretch();
    top_layout->addWidget(exit_btn);

    QHBoxLayout* mid_layout = new QHBoxLayout;
    {
        QHBoxLayout* camera_layout = new QHBoxLayout;
        camera_layout->addWidget(check_btn);
        camera_layout->addWidget(leave_btn);
        mid_layout->addLayout(camera_layout);
    }
    {
        QVBoxLayout* situation_layout = new QVBoxLayout;
        situation_layout->addWidget(meeting_name_btn);
        situation_layout->addWidget(num_btn);
        mid_layout->addLayout(situation_layout);
    }

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addLayout(top_layout);
    main_layout->addLayout(mid_layout);

    QWidget* widget = new QWidget(this);
    this->setCentralWidget(widget);
    widget->setLayout(main_layout);
}

void MainWindow::initData()
{
    gotoLogin();
}

/**
 * 打开 LoginWIndows 进行登录
 */
void MainWindow::gotoLogin()
{
    LoginWindow* login_window = new LoginWindow(this);
    connect(login_window, SIGNAL(signalLoginFinished()), this, SLOT(slotLoginFinished()));
    login_window->show();
}

/**
 * 登录后选择Lease
 */
void MainWindow::slotLoginFinished()
{
    qDebug() << "登录结束";
    // 登录成功，获取LEASE_ID列表
    if (user.isLogin())
    {
        nickname_btn->setText(user.nickname);

        gotoChoose();
    }
}

/**
 * 打开 LeaseWindow 进行选择 Lease
 */
void MainWindow::gotoChoose()
{
    LeaseWindow* lease_window = new LeaseWindow(this);
    connect(lease_window, SIGNAL(signalChooseLeaseFinished(QString)), this, SLOT(slotChooseLeaseFinished(QString)));
    lease_window->show();
}

/**
 * 切换Lease，必须要先登录
 * 避免被别人恶意切换
 */
void MainWindow::slotChooseLease()
{
    gotoLogin();
}

void MainWindow::slotChooseLeaseFinished(QString choosen)
{
    qDebug() << "选择的租约：" << choosen;
}

void MainWindow::slotExit()
{

}
