#include "arcfaceidutil.h"

ArcFaceIdUtil::ArcFaceIdUtil()
{

}

ArcFaceIdUtil::~ArcFaceIdUtil()
{

}

bool ArcFaceIdUtil::refreshCards(QString path)
{

}

int ArcFaceIdUtil::Compare(QString path_face, QString path_card)
{
    MRESULT res = ArcSoft_FIC_Activate(const_cast<char*>(APPID), const_cast<char*>(SDKKey));
    if (res != MOK && res != MERR_ASF_ALREADY_ACTIVATED)
    {
        qDebug() << "Activate failed, error code: " << res;
    }

    /* 初始化人证比对引擎*/
    MHandle hEngine = { 0 };
    res = ArcSoft_FIC_InitialEngine(&hEngine);
    if (res != MOK)
    {
        qDebug() << "Initial Engine failed, error code: " << res;
    }


    /* 读取预览静态图片信息，并保存到ASVLOFFSCREEN结构体 （以ASVL_PAF_RGB24_B8G8R8格式为例） 图片数据为BGR原始数据 */
    ASVLOFFSCREEN imgInfo0 = { 0 };
    QSize image_size = getImageSize(path_face);
    imgInfo0.i32Width = image_size.width();
    imgInfo0.i32Height = image_size.height();
    imgInfo0.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
    imgInfo0.pi32Pitch[0] = imgInfo0.i32Width * 3 ;
    imgInfo0.ppu8Plane[0] = (MUInt8*)malloc(imgInfo0.i32Height*imgInfo0.pi32Pitch[0]);

    FILE* fp1 = fopen(path_face.toLatin1().data(), "rb");
    if (fp1)
    {
        fread(imgInfo0.ppu8Plane[0], imgInfo0.i32Height*imgInfo0.pi32Pitch[0], 1, fp1);
        fclose(fp1);
    }
    else
    {
        qDebug() << "读取图片1失败";
    }

    /* 人脸特征提取 0-静态图片 1-视频 */
    LPAFIC_FSDK_FACERES pFaceRes=(LPAFIC_FSDK_FACERES)malloc(sizeof(AFIC_FSDK_FACERES));
    res = ArcSoft_FIC_FaceDataFeatureExtraction(hEngine, 0, &imgInfo0, pFaceRes);
    if (res != MOK)
    {
        qDebug() << "Face Feature Extraction failed, error code: " << res;
        /* 这个地方很可能会失败，所以特别释放内存 */
        free(pFaceRes);
        free(imgInfo0.ppu8Plane[0]);
        ArcSoft_FIC_UninitialEngine(hEngine);
        return res;
    }

    /* 读取证件照静态图片信息，并保存到ASVLOFFSCREEN结构体 （以ASVL_PAF_RGB24_B8G8R8格式为例） 图片数据为BGR原始数据 */
    ASVLOFFSCREEN imgInfo1 = { 0 };
    image_size = getImageSize(path_card);
    imgInfo1.i32Width = image_size.width();
    imgInfo1.i32Height = image_size.height();
    imgInfo1.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
    imgInfo1.pi32Pitch[0] = imgInfo1.i32Width * 3;
    imgInfo1.ppu8Plane[0] = (MUInt8*)malloc(imgInfo1.i32Height*imgInfo1.pi32Pitch[0]);
    FILE* fp2 = fopen(path_card.toLatin1().data(), "rb");
    if (fp2)
    {
        fread(imgInfo1.ppu8Plane[0], imgInfo1.i32Height*imgInfo1.pi32Pitch[0], 1, fp1);
        fclose(fp2);
    }
    else
    {
        qDebug() << "读取图片2失败" << path_card;
    }

    /* 证件照特征提取 */
    res = ArcSoft_FIC_IdCardDataFeatureExtraction(hEngine, &imgInfo1);
    if (res != MOK)
    {
        qDebug() << "IdCard Feature Extraction failed, error code: " << res;
        free(pFaceRes);
        free(imgInfo0.ppu8Plane[0]);
        free(imgInfo1.ppu8Plane[0]);
        ArcSoft_FIC_UninitialEngine(hEngine);
        return res;
    }

    /* 人证比对 */
    MFloat pSimilarScore = 0.0f;
    MInt32 pResult = 0;
    MFloat g_threshold = 0.82;
    res = ArcSoft_FIC_FaceIdCardCompare(hEngine, g_threshold, &pSimilarScore, &pResult);
    if (res != MOK)
    {
        qDebug() << "Face IdCard Compare failed, error code: " << res;
        free(pFaceRes);
        free(imgInfo0.ppu8Plane[0]);
        free(imgInfo1.ppu8Plane[0]);
        ArcSoft_FIC_UninitialEngine(hEngine);
        return res;
    }
    else
    {
        qDebug() << "result:" << pResult;
    }

    /* 反初始化引擎 */
    res = ArcSoft_FIC_UninitialEngine(hEngine);
    if (res != MOK)
    {
        qDebug() << "Uninitial Engine failed, error code: " << res;
    }

    free(pFaceRes);
    free(imgInfo0.ppu8Plane[0]);	//video模式下如果在compare接口之前图像数据被释放可能会导致比对失败或carsh
    free(imgInfo1.ppu8Plane[0]);

    return pResult;
}

bool ArcFaceIdUtil::Compare(QString path_face, QStringList paths_card)
{

}

QSize ArcFaceIdUtil::getImageSize(QString path)
{
    QImage image(path);
    //qDebug() << "获取图片尺寸 path:" << path << "    size:" << image.size();
    return image.size();
}
