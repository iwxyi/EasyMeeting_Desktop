#include "stringutil.h"

QStringList getStrMids(QString text, QString l, QString r)
{
    QStringList ans;
    int posl = 0, posr = -r.length();
    while (posl != -1 && posr != -1)
    {
        posl = text.indexOf(l, posr+r.length());
        if (posl == -1) return ans;
        posl += l.length();
        posr = text.indexOf(r, posl);
        if (posr == -1) return ans;
        ans << text.mid(posl, posr-posl);
    }
    return ans;
}

QString getStrMid(QString text, QString l, QString r)
{
    int posl = text.indexOf(l);
    if (posl == -1) return "";
    posl += l.length();
    int posr = text.indexOf(r, posl);
    if (posr == -1) return "";
    return text.mid(posl, posr-posl);
}

QString fnEncode(QString text)
{
    QString cs[] = {"\\", "/", ":", "*", "?", "\"", "<", ">", "|", "\'", "\n", "\t"};
    for (int i = 0; i < 12; i++)
        text.replace(cs[i], QString("[&c%1;]").arg(i));
    return text;
}

QString fnDecode(QString text)
{
    QString cs[] = {"\\", "/", ":", "*", "?", "\"", "<", ">", "|", "\'", "\t", "\n"};
    for (int i = 0; i < 12; i++)
        text.replace( QString("[&c%1;]").arg(i), cs[i]);
    return text;
}

bool canRegExp(QString str, QString pat)
{
    return QRegExp(pat).indexIn(str) > -1;
}

QString getXml(QString str, QString pat)
{
    int pos1 = str.indexOf(QString("<%1>").arg(pat));
    if (pos1 == -1) return "";
    pos1 += pat.length()+2;
    int pos2 = str.indexOf(QString("</%1>").arg(pat));
    if (pos2 == -1) pos2 = str.length();
    return str.mid(pos1, pos2-pos1);
}

QString makeXml(QString str, QString pat)
{
    return QString("<%1>%2</%3>").arg(pat).arg(str).arg(pat);
}

QString makeXml(int i, QString pat)
{
    return QString("<%1>%2</%3>").arg(pat).arg(i).arg(pat);
}

QString ArabToCN(int num)
{
    static const QString letter[] = {"零","一","二","三","四","五","六","七","八","九"};
    static const QString unit[] = {"","十","百","千","万","十","百","千","亿","十"};
    QString src, des;
    char tmp[12];
    sprintf(tmp, "%d", num);
    src.append(tmp);

    if ( num < 0 )
    {
        des.append("负");
        src.remove(0, 1);
    }

    int len = src.length();
    bool bPreZero = false;
    for ( int i = 0; i < len; i++)
    {
        int digit = src.at(i).unicode() - '0';
        int unit_index = len - i - 1;
        if (i == 0 && digit == 1 && (unit_index == 1 || unit_index == 5 || unit_index == 9))
        {
            des.append(unit[unit_index]);
        }
        else if ( digit == 0 )
        {
            bPreZero = true;
            if (unit_index ==  4 ||
                    unit_index ==  8)
            {
                des.append(unit[unit_index]);
            }
        }
        else
        {
            if ( bPreZero )
            {
                des.append(letter[0]);
            }
            des.append(letter[digit]);
            des.append(unit[unit_index]);
            bPreZero = false;
        }
    }
    return des;
}

