#include "leasewindow.h"

LeaseWindow::LeaseWindow(QWidget *parent) : QDialog(parent)
{
    initView();

    if (user.isLogin())
    {
        chooseLease();
    }
    else
    {
        QMessageBox::information(this, "错误", "请先登录");
        this->close();
    }
}

void LeaseWindow::initView()
{
    this->setMinimumSize(150, 250);
    this->setWindowTitle("请选择租约");

    list_view = new QListView(this);
    choose_btn = new QPushButton("选择", this);

    QHBoxLayout* btn_layout = new QHBoxLayout;
    QWidget* spacer = new QWidget(this);
    btn_layout->addWidget(spacer);
    btn_layout->addWidget(choose_btn);

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(list_view);
    main_layout->addLayout(btn_layout);
    this->setLayout(main_layout);

    list_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(choose_btn, SIGNAL(clicked()), this, SLOT(slotChooseBtnClicked()));
}

void LeaseWindow::chooseLease()
{
    QStringList params = { "user_id", user.user_id };
    ConnectUtil* con = new ConnectUtil("leases", params);
    connect(con, SIGNAL(signalFinished(QString)), this, SLOT(slotConnectLeasesFinished(QString)));
}

void LeaseWindow::slotConnectLeasesFinished(QString result)
{
    // 获取所有的租约订单
    leases = getXmls(result, "lease");
    int count = leases.size();
    if (count == 0) // 没有租约订单，返回
    {
        QMessageBox::warning(this, "提示", "您还没有租约订单，请到官方网站或者APP进行租借会议室后方可继续");
        user.lease_id = "";
        this->close();
    }
    qDebug() << "检测到租约订单数量：" << count;

    // 格式化名称
    QStringList names;
    QList<bool> enabled; // 过期或者时间不对是否变灰
    for (int i = 0; i < count; i++)
    {
        QString name = getXml(leases[i], "theme") + "(" + getXml(leases[i], "room_name") + ")";
        names << name;

        enabled.append(true);
    }

    // ListView 的 Model，将名称显示在列表中
    QStringListModel* model = new QStringListModel(names);
    list_view->setModel(model);

    list_view->setCurrentIndex(model->index(0));

    // 过期或者时间远远未到的租约是否变灰
    for (int i = 0; i < count; i++)
    {
        if (!enabled[i])
        {
            ;
        }
    }
}

void LeaseWindow::slotChooseBtnClicked()
{
    int current_index = list_view->currentIndex().row();
    if (current_index < 0)
    {
        QMessageBox::warning(this, "错误", "请先选择一个订单");
        return ;
    }

    QString lease = leases[current_index];
    int start_time = getXml(lease, "start_time").toInt();
    int finish_time = getXml(lease, "finish_time").toInt();
    int current_time = getTimestamp() / 1000; // 秒级时间戳

    qDebug() << "选择租约订单：" << getXml(lease, "theme") << "current:" << current_time <<    "start_time:" << start_time << "    finish_time:" << finish_time;

    if (!DEBUG_MODE)
    {
        /*if (finish_time < current_time - 1800) // 允许延迟半小时
            QMessageBox::warning(this, "警告", "本会议已经过期，但为方便演示，将强行允许");
        else if (start_time > current_time + 3600 * 2)
            QMessageBox::warning(this, "警告", "本会议时间未到，但为方便演示，将强行允许");*/
    }

    emit signalChooseLeaseFinished(lease);

    this->close();
}
