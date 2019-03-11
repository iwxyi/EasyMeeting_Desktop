#ifndef LEASEWINDOW_H
#define LEASEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QListView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStringListModel>
#include <QList>
#include "stringutil.h"
#include "globals.h"
#include "connectutil.h"

class LeaseWindow : public QDialog
{
    Q_OBJECT
public:
    explicit LeaseWindow(QWidget *parent = nullptr);

    void initView();

    void chooseLease();

signals:
    void signalChooseLeaseFinished(QString result);

private slots:
    void slotConnectLeasesFinished(QString result);
    void slotChooseBtnClicked();

private:
    QStringList leases;
    QListView* list_view;
    QPushButton* choose_btn;
};

#endif // LEASEWINDOW_H
