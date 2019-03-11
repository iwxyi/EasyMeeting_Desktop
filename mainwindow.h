#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QMessageBox>
#include "globals.h"
#include "loginwindow.h"
#include "leasewindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void initView();
    void initData();

    void gotoLogin();
    void gotoChoose();

public slots:
    void slotLoginFinished();
    void slotChooseLease();
    void slotChooseLeaseFinished(QString choosen);
    void slotExit();

private:
    QPushButton* nickname_btn; // 用户昵称按钮
    QPushButton* lease_btn;    // 切换订单按钮
    QPushButton* exit_btn;     // 退出程序按钮

    QPushButton* meeting_name_btn; // 会议名字按钮
    QPushButton* num_btn;          // 人数情况按钮

    QPushButton* check_btn; // 签到按钮
    QPushButton* leave_btn; // 签退按钮

};

#endif // MAINWINDOW_H
