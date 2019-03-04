#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPalette>
#include <QBrush>
#include <QImage>
#include <QMessageBox>
#include <QDebug>

#include "include/arcsoft_idcardveri.h"
#include "include/amcomdef.h"
#include "include/asvloffscreen.h"
#include "include/merror.h"

#include "core.hpp"
#include "opencv.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    struct Image
    {
        QImage img;
        QRect rect;
        int age;
        int gender;
    };

private:
    void initView();
    void initData();
    void setPhotoImage(QString fileName);
    void setCardImage(QString fileName);
    bool doCompare(Image& photo, Image& card, double value);

private slots:
    void slotPhotoChoosed();
    void slotCardChoosed();
    void slotCompare();

private:
    double threhold;
    QString path_prefix;

    QPushButton* photo_button;
    QPushButton* card_button;
    QPushButton* compare_button;

    QImage photo_image;
    QImage card_image;

    Image photo_struct;
    Image card_struct;

};

#endif // MAINWINDOW_H
