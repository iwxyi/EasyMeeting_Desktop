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
#include <QInputDialog>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include "globals.h"
#include "loginwindow.h"
#include "leasewindow.h"
#include "arcfaceidutil.h"

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
    void startIdentify();

public slots:
    void slotLoginFinished();
    void slotChooseLease();
    void slotChooseLeaseFinished(QString choosen);
    void slotExit();
    void slotRefreshCards();
    void slotCameraImageCaptured(int id, QImage image);
    void slotIdentifyBtnClicked();
    void slotSwitchCheckLeave();

private:
    QPushButton* nickname_btn; // 用户昵称按钮
    QPushButton* exit_btn;     // 退出程序按钮

    QPushButton* meeting_name_btn; // 会议名字按钮
    QPushButton* num_btn;          // 人数情况按钮
    QPushButton* refresh_card_btn; // 证件照刷新按钮

    QPushButton* check_btn; // 签到按钮
    QPushButton* leave_btn; // 签退按钮

    QCamera* camera;
    QCameraViewfinder* finder;
    QCameraImageCapture* capture;
    QPushButton* identify_btn;

    QString cards_dir;

};

#endif // MAINWINDOW_H
