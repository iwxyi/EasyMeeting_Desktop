#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include "connectutil.h"
#include "stringutil.h"

class LoginWindow : public QDialog
{
    Q_OBJECT
public:
    LoginWindow(QWidget* parent = nullptr);

private:
    void initView();

signals:
    void signalLoginFinished();

public slots:
    void slotLogin();
    void slotRegister();
    void slotLoginFinished(QString result);

private:
    QLineEdit* username_edit;
    QLineEdit* password_edit;
    QPushButton* login_btn;
    QPushButton* register_btn;
};

#endif // LOGINWINDOW_H
