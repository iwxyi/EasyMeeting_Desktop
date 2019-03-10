#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QTextCodec>
#include <QFileInfo>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

QString readTextFile(QString path, QTextCodec* codec = QTextCodec::codecForName("utf-8"));
QString readTextFile(QString path, QString codec);
QString readExistedTextFile(QString path); // 文件不存在则创建
bool writeTextFile(QString path, QString text, QTextCodec* codec = QTextCodec::codecForName("utf-8"));
bool writeTextFile(QString path, QString text, QString codec);

bool copyFile(QString old_path, QString newPath); // 复制文件
bool copyFile2(QString old_path, QString new_path); // 复制文件（覆盖）

bool deleteFile(QString path);
bool renameFile(QString path, QString new_path/*完整路径*/);

bool isFileExist(QString path);
bool isDir(QString path);
bool ensureFileExist(QString path);
bool ensureDirExist(QString path);
bool ensureFileNotExist(QString path);
bool canBeFileName(QString name);
QString getPathWithIndex(QString dir, QString name, QString suffix);
QString getDirByFile(QString file_path);

void addLinkToDeskTop(const QString& filename,const QString& name); // 生成桌面快捷方式

#endif // FILEUTIL_H
