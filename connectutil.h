#ifndef CONNECTUTIL_H
#define CONNECTUTIL_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QStringList>
#include <QDesktopServices>
#include "globals.h"
#include "networkutil.h"

class ConnectUtil : public QThread
{
public:
    ConnectUtil() { }

    static void Go(QString url, QString param)
    {
        ConnectUtil connect;
        connect.setVal(url, param);
        connect.start();
    }

    static void Go(QString url, QStringList params)
    {

    }

protected:
    void run()
    {
        NetworkUtil net;
        QString content = net.getHttpSource(_url, _param);
        emit signalFinished(content);
    }

private:
    void setVal(QString url, QString param)
    {
        _url = url;
        _param = param;
    }

signals:
    void signalFinished(QString content);

private:
    QString _url;
    QString _param;
};

#endif // CONNECTUTIL_H
