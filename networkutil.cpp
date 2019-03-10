#include "networkutil.h"

NetworkUtil::NetworkUtil()
{

}

QString NetworkUtil::getHttpSource(QString uri, QString param)
{
    if (!uri.startsWith("http"))
        uri = NETWORK_PATH+uri;

    QUrl url(uri);
    QNetworkAccessManager manager;
    QEventLoop loop;
    //QTextCodec *codec;
    QNetworkReply *reply;
    QNetworkRequest request;

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // reply = manager.get(QNetworkRequest(url)); // 这是GET方法
    reply = manager.post(request, param.toLatin1());
    qDebug() << "联网：" << (uri + "?" + param);

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QString code_content = reply->readAll();
    //codec = QTextCodec::codecForHtml(code_content.toLatin1());
    //code_content = codec->toUnicode(code_content.toLatin1());

    qDebug() << "返回：" << code_content;

    return code_content;
}

QString NetworkUtil::getHttpSource(QString uri, QStringList params)
{
    QString builder = "";
    int size = params.length();
    for (int i = 0;  i < size; i++)
    {
        if (i&1) // 奇数，是值，进行URL编码
            builder += QUrl::toPercentEncoding(params[i]);
        else // 偶数，是键
        {
            if (i > 0)
                builder += "&";
            builder += params[i] + "=";
        }
    }
    return getHttpSource(uri, builder);
}
