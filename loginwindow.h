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

class LoginWindow : public QDialog
{
public:
    LoginWindow(QWidget* parent = nullptr);

private:
    void initView();


private:
    QLineEdit* username_edit;
    QLineEdit* password_edit;
    QPushButton* login_btn;
    QPushButton* register_btn;
};

#endif // LOGINWINDOW_H
