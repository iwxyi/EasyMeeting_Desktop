#ifndef NETWORKUTIL_H
#define NETWORKUTIL_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QTextCodec>
#include "globals.h"

class NetworkUtil
{
public:
    NetworkUtil();

    static QString getHttpSource(QString uri, QString param);
    static QString getHttpSource(QString uri, QStringList params);
};

#endif // NETWORKUTIL_H
