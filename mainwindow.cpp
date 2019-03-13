#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow (parent)
{
    initView();

    initData();
}

void MainWindow::initView()
{
    this->resize(800, 600);

    // 创建控件
    nickname_btn = new QPushButton("昵称", this);
    exit_btn = new QPushButton("退出", this);
    meeting_name_btn = new QPushButton("会议", this);
    num_btn = new QPushButton("人数情况", this);
    refresh_card_btn = new QPushButton("刷新证件照", this);
    check_btn = new QPushButton("签到", this);
    leave_btn = new QPushButton("签退", this);
    camera = new QCamera(this);
    finder = new QCameraViewfinder(this);
    capture = new QCameraImageCapture(camera);
    identify_btn = new QPushButton("人证识别", this);
    result_label = new QLabel("结果", this);
    result_reset_timer = new QTimer(this);
    result_reset_timer->setInterval(3000);
    result_reset_timer->setSingleShot(true);

    // 设置属性
    capture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(finder);
    finder->setMinimumSize(500, 400);
    meeting_name_btn->setFont(QFont("微软雅黑", 20));
    result_label->setFont(QFont("微软雅黑", 20));
    result_label->setAlignment(Qt::AlignCenter);

    // 设置按钮提示
    check_btn->setEnabled(false); // 默认开启签到模式
    nickname_btn->setToolTip("登录账号后选择会议");
    exit_btn->setToolTip("退出程序；本次记录将会保留");
    meeting_name_btn->setToolTip("本次会议主题；可以在APP或者官网上修改");
    num_btn->setToolTip("已到人数/总人数");
    refresh_card_btn->setToolTip("刷新所有与会人员证件；图片放到 【"+APPLICATION_PATH+"cards/订单ID/】 文件夹中");
    check_btn->setToolTip("切换到签到模式");
    leave_btn->setToolTip("切换到签退模式");
    identify_btn->setToolTip("开始人证识别");

    // 连接信号槽
    connect(nickname_btn, SIGNAL(clicked()), this, SLOT(slotChooseLease()));
    connect(exit_btn, SIGNAL(clicked()), this, SLOT(slotExit()));
    connect(refresh_card_btn, SIGNAL(clicked()), this, SLOT(slotRefreshCards()));
    connect(capture, SIGNAL(imageCaptured(int, QImage)), this, SLOT(slotCameraImageCaptured(int, QImage)));
    connect(check_btn, SIGNAL(clicked()), this, SLOT(slotSwitchCheckLeave()));
    connect(leave_btn, SIGNAL(clicked()), this, SLOT(slotSwitchCheckLeave()));
    connect(identify_btn, SIGNAL(clicked()), this, SLOT(slotIdentifyBtnClicked()));
    connect(result_reset_timer, SIGNAL(timeout()), this, SLOT(slotResultReset()));

    // 顶部布局
    QHBoxLayout* top_layout = new QHBoxLayout;
    top_layout->addWidget(nickname_btn);
    top_layout->addStretch();
    top_layout->addWidget(exit_btn);

    // 中间布局
    QHBoxLayout* mid_layout = new QHBoxLayout;
    // 中间左半部分布局
    {
        QVBoxLayout* camera_layout = new QVBoxLayout;
        QHBoxLayout* camera_btn_layout = new QHBoxLayout;
        camera_btn_layout->addWidget(check_btn);
        camera_btn_layout->addWidget(leave_btn);
        camera_layout->addLayout(camera_btn_layout);
        camera_layout->addWidget(finder);
        camera_layout->addWidget(identify_btn);
        camera_layout->addWidget(result_label);
        mid_layout->addLayout(camera_layout);
    }
    // 中间右半部分布局
    {
        QVBoxLayout* situation_layout = new QVBoxLayout;
        situation_layout->addWidget(meeting_name_btn);
        situation_layout->addWidget(num_btn);
        situation_layout->addWidget(refresh_card_btn);
        mid_layout->addLayout(situation_layout);
    }

    // 总体布局（分上下两层）
    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addLayout(top_layout);
    main_layout->addLayout(mid_layout);
    main_layout->addStretch();

    QWidget* widget = new QWidget(this);
    this->setCentralWidget(widget);
    widget->setLayout(main_layout);
}

void MainWindow::initData()
{
    can_close = false;

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
    if (!user.isLogin())
    {
        gotoLogin();
        return ;
    }

    LeaseWindow* lease_window = new LeaseWindow(this);
    connect(lease_window, SIGNAL(signalChooseLeaseFinished(QString)), this, SLOT(slotChooseLeaseFinished(QString)));
    lease_window->show();
}

void MainWindow::refreshChecked()
{
    num_btn->setText(QString("%1 / %2").arg(user.arrive).arg(user.all_num));
}

void MainWindow::particiChecked(QString name)
{
    checked_list.append(name);
}

void MainWindow::particiLeaved(QString name)
{
    checked_list.removeOne(name);
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    if (can_close || !user.isLogin())
    {
        //event->accept();
        this->close();
    }
    else
    {
        event->ignore();
        slotExit();
    }
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
    user.lease_id = getXml(choosen, "lease_id");

    cards_dir = APPLICATION_PATH + "cards/" + user.lease_id;
    QDir dir(cards_dir);
    dir.mkpath(cards_dir);

    meeting_name_btn->setText(getXml(choosen, "theme"));
    this->setWindowTitle(getXml(choosen, "room_name"));
    camera->start();
}

void MainWindow::slotExit()
{
    if (!user.isLogin())
    {
        this->close();
        return ;
    }

    bool isOK;
    QString text = QInputDialog::getText(nullptr, "请输入密码", "为保护会议安全，请输入用户（"+user.username+"）的密码", QLineEdit::Normal, "", &isOK);
    if (isOK)
    {
        if (text == user.password)
        {
            can_close = true;
            this->close();
        }
        else
        {
            QMessageBox::warning(this, "错误", "密码输入错误,请重试");
        }
    }
}

void MainWindow::slotRefreshCards()
{
    if (!user.isLogin())
    {
        QMessageBox::warning(this, "提示", "请先登录并选择一个租约");
        return ;
    }

    QDir dir(cards_dir);
    int count = 0;
    foreach(QFileInfo fi, dir.entryInfoList())
    {
        if (fi.isFile())
        {
            //qDebug() << "find image : " << fi.fileName();
            count++;
        }
        else if (fi.fileName() == "." || fi.fileName() == "..")
        {
            continue;
        }
        else
        {
            qDebug() << "find dir : " << fi.absoluteFilePath();
        }
    }

    if (count == 0)
    {
        QMessageBox::information(this, "证件照", "请将证件照放到路径：" + cards_dir + "中，人脸识别将自动匹配");
    }
    else
    {
        if (QMessageBox::information(this, "刷新结果", "获取到" + QString("%1").arg(count) + "张证件照\n是否清空已签到记录，重新计算？", "清空", "取消", 0, 1) == 0)
            checked_list.clear();
    }

    user.all_num = count;
    refreshChecked();
}

void MainWindow::slotIdentifyBtnClicked()
{
    capture->capture();
}

void MainWindow::slotCameraImageCaptured(int id, QImage image)
{
    QString face_path = APPLICATION_PATH+"captured.bmp";
    image.save(face_path);
    
    startCompare(face_path);
}

void MainWindow::slotSwitchCheckLeave()
{
    if (check_btn->isEnabled()) // 切换到签到模式
    {
        check_btn->setEnabled(false);
        leave_btn->setEnabled(true);
    }
    else // 切换到签退模式
    {
        check_btn->setEnabled(true);
        leave_btn->setEnabled(false);
    }
}

void MainWindow::slotResultReset()
{
    result_label->setText("");
}

void MainWindow::startCompare(QString face_path)
{
    result_reset_timer->start();

    QDir dir(cards_dir);
    foreach(QFileInfo fi, dir.entryInfoList())
    {
        if (fi.isFile())
        {
            QString file_name = fi.filePath();
            QString base_name = fi.baseName();
            int code = ArcFaceIdUtil::Compare(face_path, file_name);
            if (code == 0) // 不是这个人
            {
                ;
            }
            else if (code == 1) // 是这个人
            {
                if (!check_btn->isEnabled())
                {
                    particiChecked(base_name);
                    result_label->setText(base_name + " 签到成功");
                }
                else
                {
                    particiLeaved(base_name);
                    result_label->setText(base_name + " 签退成功");
                }
                return ;
            }
            else if (code == 81925) // 人脸检测失败
            {
                result_label->setText("请对准镜头，重新识别");
                return ;
            }
        }
    }
    result_label->setText("识别失败，请重试");
}




