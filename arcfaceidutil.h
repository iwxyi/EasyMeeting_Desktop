#ifndef ARCFACEIDUTIL_H
#define ARCFACEIDUTIL_H

#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QStringList>
#include <QFile>
#include <stdio.h>
#include "include/arcsoft_idcardveri.h"
#include "include/amcomdef.h"
#include "include/asvloffscreen.h"
#include "include/merror.h"
#include "core.hpp"
#include "opencv.hpp"

#define APPID   "9AmspkNzRQDuyjfwAsU4SPvgwCGfaA4tdrz4V7rjLSux"  //APPID
#define SDKKey  "7bQ23oQFnfmybDCxdL2eipNsHz3zU5oSoh9jtw8tjtXs"  //SDKKey
#define MERR_ASF_BASE_ALREADY_ACTIVATED (0x16002)

class ArcFaceIdUtil
{
public:
    ArcFaceIdUtil();
    ~ArcFaceIdUtil();

    bool refreshCards(QString path);

    static bool Compare(QString path_face, QString path_card);
    static bool Compare(QString path_face, QStringList paths_card);

    static QSize getImageSize(QString path);

private:
    //MHandle hEngine;
};

#endif // ARCFACEIDUTIL_H
