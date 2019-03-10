#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <QString>
#include <QStringList>
#include <QColor>

QStringList getStrMids(QString text, QString l, QString r); // 取中间文本数组
QString getStrMid(QString text, QString l, QString r); // 取中间文本2

QString fnEncode(QString text); // 可使用的文件名编码
QString fnDecode(QString text); // 文件名解码

bool canRegExp(QString str, QString pat); // 能否正则匹配

QString getXml(QString str, QString pat);
QString makeXml(QString str, QString pat);
QString makeXml(int i, QString pat);

QString ArabToCN(int num);

#endif // STRINGUTIL_H
