#ifndef CONNECTUTIL_H
#define CONNECTUTIL_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QStringList>
#include <QDesktopServices>
#include <QDebug>
#include "globals.h"
#include "networkutil.h"

class ConnectUtil : public QThread
{
    Q_OBJECT
public:
    ConnectUtil()
    {
        _url = _param = "";
        _params.clear();
    }

    ConnectUtil(QString url, QString param)
    {
        _url = url;
        _param = param;
    }

    ConnectUtil(QString url, QStringList params)
    {
        _url = url;
        _params = params;
    }

protected:
    void run()
    {
        NetworkUtil net;
        QString content;
        if (_params.size() == 0)
            content = net.getHttpSource(_url, _param);
        else
            content = net.getHttpSource(_url, _params);
        emit signalFinished(content);
    }

private:
    void setVal(QString url, QString param)
    {
        _url = url;
        _param = param;
    }
    void setVal(QString url, QStringList params)
    {
        _url = url;
        _params = params;
    }

signals:
    void signalFinished(QString content);

private:
    QString _url;
    QString _param;
    QStringList _params;
};

#endif // CONNECTUTIL_H
