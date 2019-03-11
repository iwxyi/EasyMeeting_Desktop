#include "leasewindow.h"

LeaseWindow::LeaseWindow(QWidget *parent) : QDialog(parent)
{
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
}

void LeaseWindow::chooseLease()
{
    QStringList params = { "user_id", user.user_id };
    ConnectUtil* con = new ConnectUtil("leases", params);
    connect(con, SIGNAL(signalFinished(QString)), this, SLOT(slotGetLeasesFinished(QSting)));
}

void LeaseWindow::slotGetLeaseFinished(QString result)
{
    leases = getXmls(result, "lease");
}
