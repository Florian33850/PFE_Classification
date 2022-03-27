#include <string>
#include <QWidget>
#include <QLineEdit>
#include <QtTest/QtTest>

#include "opencv2/highgui.hpp"

#define private public
#define protected public

#include "../src/data_handler.h"

class DataHandlerTests: public QObject
{
    Q_OBJECT

    private:
        QImage loadImageFromPath(QString pathToImage);
        bool createAndSaveRandomNoiseColorImage(int height, int width, std::string pathToSave);
        ImageSelectionHandler* createImageSelectionHandler();
        LymeDatabaseHandler* createLymeDatabaseHandler();
        std::vector<ImageTransformationWidget*> createFullAndActivatedImageTransformationWidgetList();

    private Q_SLOTS:
        void testImageSelectionHandlerInstantiation();
        void testLymeDatabaseHandlerInstantiation();
        void testAddImageToImagePreviewList();
        void testReloadPreviewFail();
        void testReloadPreviewSuccess();
        void testLoadNextPreviewFail();
        void testLoadNextPreviewSuccess();
        void testLoadPreviousPreviewFail();
        void testLoadPreviousPreviewSuccess();
        void testImageSelectionSaveImagesInFile();
        void testLymeDatabaseSaveImagesInFile();
};

QImage DataHandlerTests::loadImageFromPath(QString pathToImage)
{
    QImage qImage;
    if(qImage.load(pathToImage) == false)
    {
        std::cout << "Cannot open image : " << pathToImage.toUtf8().constData() << std::endl;
    }
    return qImage;
}

void DataHandlerTests::testImageSelectionHandlerInstantiation()
{
    QWidget *parent = NULL;
    std::vector<ImageLabel*> *imagePreviewList = new std::vector<ImageLabel*>();
    ImageSelectionHandler *imageSelectionHandler = new ImageSelectionHandler(parent, imagePreviewList);
    QVERIFY(imageSelectionHandler != NULL);
}

void DataHandlerTests::testLymeDatabaseHandlerInstantiation()
{
    QWidget *parent = NULL;
    std::vector<ImageLabel*> *imagePreviewList = new std::vector<ImageLabel*>();
    LymeDatabaseHandler *lymeDatabaseHandler = new LymeDatabaseHandler(parent, imagePreviewList);
    QVERIFY(lymeDatabaseHandler != NULL);
}

bool DataHandlerTests::createAndSaveRandomNoiseColorImage(int height, int width, std::string pathToSave)
{
    cv::Mat testImage(height, width, CV_8UC3);
    cv::randu(testImage, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));

    if(testImage.empty())
    {
        return false;
    }

    cv::imwrite(pathToSave, testImage);
    return true;
}

ImageSelectionHandler* DataHandlerTests::createImageSelectionHandler()
{
    QWidget *parent = NULL;
    std::vector<ImageLabel*> *imagePreviewList = new std::vector<ImageLabel*>();
    ImageSelectionHandler *dataHandler = new ImageSelectionHandler(parent, imagePreviewList);
    return dataHandler;
}

LymeDatabaseHandler* DataHandlerTests::createLymeDatabaseHandler()
{
    QWidget *parent = NULL;
    std::vector<ImageLabel*> *imagePreviewList = new std::vector<ImageLabel*>();
    LymeDatabaseHandler *dataHandler = new LymeDatabaseHandler(parent, imagePreviewList);
    return dataHandler;
}

void DataHandlerTests::testAddImageToImagePreviewList()
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();

    long unsigned int sizeAtBegin = dataHandler->imagePreviewList->size();
    QImage newImageToAdd;
    dataHandler->addImageToImagePreviewList(newImageToAdd);
    QVERIFY(dataHandler->imagePreviewList->size() == sizeAtBegin + 1);
}

void DataHandlerTests::testReloadPreviewFail()
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();
    dataHandler->indexPathToImagesList = 0;
    dataHandler->maxNumberOfImagesToLoad = 10;
    QVERIFY(!dataHandler->reloadPreview());
}

void DataHandlerTests::testReloadPreviewSuccess()
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();
    dataHandler->indexPathToImagesList = 1;
    dataHandler->maxNumberOfImagesToLoad = 1;

    createAndSaveRandomNoiseColorImage(200, 200, "testImage.png");

    QString pathToImage = "testImage.png";
    dataHandler->pathToImages.push_back(pathToImage);

    QImage qImageA = loadImageFromPath(pathToImage);
    QImage qImageTransform = loadImageFromPath(pathToImage).convertToFormat(QImage::Format_Grayscale8);
    dataHandler->addImageToImagePreviewList(qImageTransform);

    if(dataHandler->reloadPreview() != true)
    {
        QFAIL("[INFO] Fail to reload");
    }

    QVERIFY(dataHandler->imagePreviewList->at(0)->qImage == qImageA);
}

void DataHandlerTests::testLoadNextPreviewFail()
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();
    dataHandler->indexPathToImagesList = 10;
    QVERIFY(!dataHandler->loadNextPreview());
}

void DataHandlerTests::testLoadNextPreviewSuccess()
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();
    dataHandler->maxNumberOfImagesToLoad = 1;

    QString pathToImageA = "testImageA.png";
    dataHandler->pathToImages.push_back(pathToImageA);
    QString pathToImageB = "testImageB.png";
    dataHandler->pathToImages.push_back(pathToImageB);

    createAndSaveRandomNoiseColorImage(100, 100, "testImageA.png");
    createAndSaveRandomNoiseColorImage(200, 200, "testImageB.png");

    QImage imageA = loadImageFromPath(pathToImageA);
    QImage imageB = loadImageFromPath(pathToImageB);

    dataHandler->addImageToImagePreviewList(imageA);

    dataHandler->loadNextPreview();

    if(dataHandler->imagePreviewList->at(0)->qImage != imageA)
    {
        QFAIL("[INFO] Fail to load first batch\n");
    }

    dataHandler->loadNextPreview();
    
    if(dataHandler->imagePreviewList->at(0)->qImage != imageB)
    {
        QFAIL("[INFO] Fail to load second batch\n");
    }

    QVERIFY(true);
}

void DataHandlerTests::testLoadPreviousPreviewFail()
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();
    dataHandler->indexPathToImagesList = 2;
    dataHandler->maxNumberOfImagesToLoad = 2;
    QVERIFY(!dataHandler->loadPreviousPreview());
}

void DataHandlerTests::testLoadPreviousPreviewSuccess()
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();
    dataHandler->indexPathToImagesList = 3;
    dataHandler->maxNumberOfImagesToLoad = 1;

    QString pathToImageA = "testImageA.png";
    dataHandler->pathToImages.push_back(pathToImageA);
    QString pathToImageB = "testImageB.png";
    dataHandler->pathToImages.push_back(pathToImageB);

    createAndSaveRandomNoiseColorImage(100, 100, "testImageA.png");
    createAndSaveRandomNoiseColorImage(200, 200, "testImageB.png");

    QImage imageA = loadImageFromPath(pathToImageA);
    QImage imageB = loadImageFromPath(pathToImageB);

    dataHandler->addImageToImagePreviewList(imageA);

    dataHandler->loadPreviousPreview();

    if(dataHandler->imagePreviewList->at(0)->qImage != imageB)
    {
        QFAIL("[INFO] Fail to load first batch\n");
    }

    dataHandler->loadPreviousPreview();
    
    if(dataHandler->imagePreviewList->at(0)->qImage != imageA)
    {
        QFAIL("[INFO] Fail to load second batch\n");
    }

    QVERIFY(true);
}

std::vector<ImageTransformationWidget*> DataHandlerTests::createFullAndActivatedImageTransformationWidgetList()
{
    std::vector<ImageTransformationWidget*> imageTransformationWidgetList;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QWidget *parentWidget = new QWidget();

    MirrorImageTransformation *mirrorTransformation = new MirrorImageTransformation();
    mirrorTransformation->verticalMirror = true;
    mirrorTransformation->horizontalMirror = true;
    MirrorWidget *mirrorWidget = new MirrorWidget(mainLayout, parentWidget, mirrorTransformation);
    mirrorWidget->isActivated = true;
    imageTransformationWidgetList.push_back(mirrorWidget);

    GrayscaleImageTransformation *grayscaleTransformation = new GrayscaleImageTransformation();
    GrayscaleWidget *grayscaleWidget = new GrayscaleWidget(mainLayout, parentWidget, grayscaleTransformation);
    imageTransformationWidgetList.push_back(grayscaleWidget);
    grayscaleWidget->isActivated = true;

    AutomaticRotationLymeDataImageTransformation *automaticRotationTransformation = new AutomaticRotationLymeDataImageTransformation();
    AutomaticRotationLymeDataWidget *automaticRotationWidget = new AutomaticRotationLymeDataWidget(mainLayout, parentWidget, automaticRotationTransformation);
    imageTransformationWidgetList.push_back(automaticRotationWidget);
    automaticRotationWidget->isActivated = true;

    return imageTransformationWidgetList;
}

void DataHandlerTests::testImageSelectionSaveImagesInFile()
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();
    createAndSaveRandomNoiseColorImage(100, 100, "testImage.png");
    dataHandler->pathToImages.push_back("testImage.png");

    QImage imageA = loadImageFromPath("testImage.png");
    std::vector<ImageTransformationWidget*> imageTransformationWidgetList = createFullAndActivatedImageTransformationWidgetList();
    for(ImageTransformationWidget *imageTransformationWidget : imageTransformationWidgetList)
    {
        imageA = imageTransformationWidget->imageTransformation->applyImageTransformation(imageA);
    }

    dataHandler->saveImagesInFile(imageTransformationWidgetList, "/build");
    QImage imageB = loadImageFromPath("testImage.png");

    QVERIFY(imageA == imageB);
}

void DataHandlerTests::testLymeDatabaseSaveImagesInFile()
{
    QDir dir("database/malade/1/main_droite");
    dir.mkpath(".");
    LymeDatabaseHandler *dataHandler = createLymeDatabaseHandler();
    createAndSaveRandomNoiseColorImage(100, 100, "database/malade/1/main_droite/testImage.png");
    dataHandler->pathToImages.push_back("database/malade/1/main_droite/testImage.png");

    QImage imageA = loadImageFromPath("database/malade/1/main_droite/testImage.png");
    std::vector<ImageTransformationWidget*> imageTransformationWidgetList = createFullAndActivatedImageTransformationWidgetList();
    for(ImageTransformationWidget *imageTransformationWidget : imageTransformationWidgetList)
    {
        imageA = imageTransformationWidget->imageTransformation->applyImageTransformation(imageA);
    }

    dataHandler->saveImagesInFile(imageTransformationWidgetList, "/build");
    QImage imageB = loadImageFromPath("malade/1_main_droite_testImage.png");
    QDir("database").removeRecursively();
    QDir("malade").removeRecursively();

    QVERIFY(imageA == imageB);
}

QTEST_MAIN(DataHandlerTests)
#include "data_handler_test.moc"