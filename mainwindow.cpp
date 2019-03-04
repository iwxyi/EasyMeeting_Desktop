#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initView();
    initData();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initView()
{
    photo_button = new QPushButton(this);
    card_button = new QPushButton(this);
    compare_button = new QPushButton("开始比较", this);

    photo_button->setFixedSize(300, 200);
    card_button->setFixedSize(300, 200);

    QObject::connect(photo_button, SIGNAL(clicked(bool)), this, SLOT(slotPhotoChoosed()));
    QObject::connect(card_button, SIGNAL(clicked(bool)), this, SLOT(slotCardChoosed()));
    QObject::connect(compare_button, SIGNAL(clicked(bool)), this, SLOT(slotCompare()));

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(photo_button);
    hlayout->addWidget(card_button);
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout);
    vlayout->addWidget(compare_button);

    QWidget* widget = new QWidget;
    this->setCentralWidget(widget);
    widget->setLayout(vlayout);
}

void MainWindow::initData()
{
    threhold = 0.82;

    setPhotoImage("img1.png");
    if (photo_image.isNull())
        path_prefix = "./release/";
    setPhotoImage(path_prefix+"img1.png");
    setCardImage(path_prefix+"img2.png");
}

void MainWindow::setPhotoImage(QString fileName)
{
    photo_image = QImage(fileName);
    if (photo_image.isNull())
        return ;
    photo_button->setIcon(QPixmap::fromImage(photo_image));
    photo_button->setIconSize(QSize(300, 200));

    photo_struct.img = photo_image;
}

void MainWindow::setCardImage(QString fileName)
{
    card_image = QImage(fileName);
    if (card_image.isNull())
        return ;
    card_button->setIcon(QPixmap::fromImage(card_image));
    card_button->setIconSize(QSize(300, 200));

    card_struct.img = card_image;
}

void MainWindow::slotPhotoChoosed()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", ".", "Images (*.png *.jpg)");
    if (fileName.isEmpty()) return ;
    setPhotoImage(fileName);
}

void MainWindow::slotCardChoosed()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", ".", "Images (*.png *.jpg)");
    if (fileName.isEmpty()) return ;
    setCardImage(fileName);
}

void MainWindow::slotCompare()
{
    if (photo_struct.img.isNull() || card_struct.img.isNull())
    {
        QMessageBox::critical(this, "错误", "请先选择图片");
        return ;
    }

    if (doCompare(photo_struct, card_struct, threhold))
    {
        //QMessageBox::information(this, "分析结果", "是同一个人");
    }
    else
    {
        //QMessageBox::information(this, "分析结果", "不是同一个人");
    }
}

#define APPID   "9AmspkNzRQDuyjfwAsU4SPvgwCGfaA4tdrz4V7rjLSux"  //APPID
#define SDKKey  "7bQ23oQFnfmybDCxdL2eipNsHz3zU5oSoh9jtw8tjtXs"  //SDKKey
#define MERR_ASF_BASE_ALREADY_ACTIVATED (0x16002)

bool MainWindow::doCompare(MainWindow::Image &photo, MainWindow::Image &card, double value)
{
    /** 1. 激活SDK */
    MRESULT res = ArcSoft_FIC_Activate(const_cast<char*>(APPID), const_cast<char*>(SDKKey));
    if (MOK == res || MERR_ASF_BASE_ALREADY_ACTIVATED == res)
    {
        qDebug() << "ALActivation sucess: " << res;
    }
    else
    {
        qDebug() << "ALActivation fail: " << res;
    }

    /** 2. 初始化引擎 */
    MHandle hEngine = { 0 };
    res = ArcSoft_FIC_InitialEngine(&hEngine);
    if (res == MOK)
    {
        qDebug() << "ALInitEngine sucess: " << res;
    }
    else
    {
        qDebug() << "ALInitEngine fail: " << res;
    }

    //photo_struct.img.scaled(photo_struct.img.width()/4*4, photo_struct.img.height()/4*4).save("img1.png");
    //card_struct.img.scaled(card_struct.img.width()/4*4, card_struct.img.height()/4*4).save("img2.png");

    /** 3. 人脸检测 */
    //photo_struct.img.scaled(photo_struct.img.width()/4*4, photo_struct.img.height()/4*4).save(path_prefix+"img1.png");
    //card_struct.img.scaled(card_struct.img.width()/4*4, card_struct.img.height()/4*4).save(path_prefix+"img2.png");

    IplImage* img1 = cvLoadImage(QString(path_prefix+"img1.png").toLatin1().data());
    IplImage* img2 = cvLoadImage(QString(path_prefix+"img2.png").toLatin1().data());

    if (img1 == nullptr || img2 == nullptr)
        qDebug() << "打开图片失败";
    //if (img1 && img2) {

    /** 3.1 第一张人脸特征提取 */
    /* 读取预览静态图片信息，并保存到ASVLOFFSCREEN结构体 （以ASVL_PAF_RGB24_B8G8R8格式为例） 图片数据为BGR原始数据 */
    ASVLOFFSCREEN imgInfo0 = { 0 };
    imgInfo0.i32Width = photo_struct.img.width();
    imgInfo0.i32Height = photo_struct.img.height();
    imgInfo0.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
    imgInfo0.pi32Pitch[0] = imgInfo0.i32Width * 3;
    imgInfo0.ppu8Plane[0] = (MUInt8*)malloc(imgInfo0.i32Height*imgInfo0.pi32Pitch[0]);
    FILE* fp1 = fopen(QString(path_prefix+"img1.png").toLatin1().data(), "rb");
    if (fp1)
    {
        fread(imgInfo0.ppu8Plane[0], imgInfo0.i32Height*imgInfo0.pi32Pitch[0], 1, fp1);
        fclose(fp1);
    }

    /* 人脸特征提取 0-静态图片 1-视频 */
    LPAFIC_FSDK_FACERES pFaceRes=(LPAFIC_FSDK_FACERES)malloc(sizeof(AFIC_FSDK_FACERES));
    res = ArcSoft_FIC_FaceDataFeatureExtraction(hEngine, 0, &imgInfo0, pFaceRes);
    if (res != MOK)
    {
        printf("Face Feature Extraction failed, error code: %d\n", res);
        return -1;
    }

    /** 3.2 第二张人脸特征提取 */
    /* 读取证件照静态图片信息，并保存到ASVLOFFSCREEN结构体 （以ASVL_PAF_RGB24_B8G8R8格式为例） 图片数据为BGR原始数据 */
    ASVLOFFSCREEN imgInfo1 = { 0 };
    imgInfo1.i32Width = card_struct.img.width();
    imgInfo1.i32Height = card_struct.img.height();
    imgInfo1.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
    imgInfo1.pi32Pitch[0] = imgInfo1.i32Width * 3;//
    imgInfo1.ppu8Plane[0] = (MUInt8*)malloc(imgInfo1.i32Height*imgInfo1.pi32Pitch[0]);
    FILE* fp2 = fopen(QString(path_prefix+"img2.png").toLatin1().data(), "rb");
    if (fp2)
    {
        fread(imgInfo1.ppu8Plane[0], imgInfo1.i32Height*imgInfo1.pi32Pitch[0], 1, fp1);
        fclose(fp2);
    }

    /* 证件照特征提取 */
    res = ArcSoft_FIC_IdCardDataFeatureExtraction(hEngine, &imgInfo1);
    if (res != MOK)
    {
        printf("IdCard Feature Extraction failed, error code: %d\n", res);
        return -1;
    }


    /** 3.3 人证比对 */
    MFloat pSimilarScore = 0.0f;
    MInt32 pResult = 0;
    MFloat g_threshold = static_cast<float>(value);
    res = ArcSoft_FIC_FaceIdCardCompare(hEngine, g_threshold, &pSimilarScore, &pResult);
    if (res == MOK)
    {
        qDebug() << "ASFFaceFeatureCompare sucess: " << pSimilarScore;
    }
    else
    {
        qDebug() << "ASFFaceFeatureCompare fail: " << res;
    }

    free(pFaceRes);
    free(imgInfo0.ppu8Plane); //video模式下如果在compare接口之前图像数据被释放可能会导致比对失败或carsh
    free(imgInfo1.ppu8Plane);
    //}

    /** 4. 反初始化 */
    res = ArcSoft_FIC_UninitialEngine(hEngine);
    if (res != MOK)
    {
        qDebug() << "ALUninitEngine fail: " << res;
    }
    else
    {
        qDebug() << "ALUninitEngine sucess: " << res;
    }

    qDebug() << "人脸识别结束";
    return pResult;
}
