#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>
#include <QByteArray>
#include <QColor>
#include <QDebug>
//#include "globalvar.h"

class Settings : public QSettings
{
public :
    Settings(QString filePath) : QSettings(filePath, QSettings::IniFormat)
    {
	this->setIniCodec("GBK");
    }

    /*Settings(QString section = "default", QString fileName = "settings.ini")
	    : QSettings(DataPath+fileName, QSettings::IniFormat)
    {
	if (section != "" && !section.endsWith("/"))
	    section += "/";
	this->section = section;
	this->setIniCodec("GBK");
    }*/

    void setSection(QString section = "")
    {
	if (section != "" && !section.endsWith("/"))
	    section += "/";
	this->section = section;
    }

    QString getSection()
    {
	return section;
    }

    void setVal(QString key, QVariant val)
    {
	setValue(section+key, val);
	sync();
    }

    QString getStr(QString key)
    {
	QVariant var = value(section+key);
	QString val = var.toString();
	return val;
    }

    QString getStr(QString key, QVariant def)
    {
	if (!contains(section+key))
	    return def.toString();
	QString val = value(section+key).toString();
	return val;
    }

    int getInt(QString key)
    {
	QVariant var = value(section+key);
	int val = var.toInt();
	return val;
    }

    int getInt(QString key, QVariant def)
    {
	if (!contains(section+key))
	    return def.toInt();
	int val = value(section+key).toInt();
	return val;
    }

    bool getBool(QString key)
    {
	QVariant var = value(section+key);
	bool val = var.toBool();
	return val;
    }

    bool getBool(QString key, QVariant def)
    {
	if (!contains(section+key))
	    return def.toBool();
	bool val = value(section+key).toBool();
	return val;
    }

    long long getLongLong(QString key)
    {
	QVariant var = value(section+key);
	long long val = var.toLongLong();
	return val;
    }

    long long getLongLong(QString key, QVariant def)
    {
	if (!contains(section+key))
	    return def.toLongLong();
	long long val = value(section+key).toLongLong();
	return val;
    }

    void setColor(QString key, QColor val)
    {
	setValue(key, QColorToInt(val));
    }

    QColor getColor(QString key)
    {
	QVariant var = value(section+key);
	int val = var.toInt();
	return IntToQColor(val);
    }

    QColor getColor(QString key, QColor def)
    {
	if (!contains(section+key))
	    return def;
	int val = value(section+key).toInt();
	return IntToQColor(val);
    }

    QVariant getVar(QString key)
    {
	QVariant val = value(section+key);
	return val;
    }

    QVariant getVar(QString key, QVariant def)
    {
	if (!contains(section+key))
	    return def;
	QVariant val = value(section+key);
	return val;
    }

    bool have(QString key)
    {
	return contains(section+key);
    }

private:
    int QColorToInt(const QColor &color)
    {
	//return (int)(((unsigned int)color.alpha()<< 24) | ((unsigned int)color.blue()<< 16) | (unsigned short)(((unsigned short)color.green()<< 8) | color.red()));
	return static_cast<int>(
		    (  static_cast<unsigned int>(color.alpha()<< 24)
		     | static_cast<unsigned int>(color.blue()<< 16)
		     | static_cast<unsigned int>(color.green()<< 8)
		     | static_cast<unsigned int>(color.red())
		    ));
    }

    QColor IntToQColor(const int &int_color)
    {
	int red = int_color & 255;
	int green = int_color >> 8 & 255;
	int blue = int_color >> 16 & 255;
	int alpha = int_color >> 24 & 255;
	return QColor(red, green, blue, alpha);
    }

private :
    QString section;
};

#endif // SETTINGS_H
