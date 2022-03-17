#include <gtest/gtest.h>
#define private public
#define protected public
#include "../src/data_handler.h"
#include <string>

#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;

TEST(ImageSelectionHandler, TestImageSelectionHandlerInstantiation)
{
    QWidget *parent = NULL;
    std::vector<ImageLabel*> *imagePreviewList = new std::vector<ImageLabel*>();
    ImageSelectionHandler *dataHandler = new ImageSelectionHandler(parent, imagePreviewList);
    ASSERT_TRUE(dataHandler != NULL);
}

TEST(LymeDatabaseHandler, TestLymeDatabaseHandlerInstantiation)
{
    QWidget *parent = NULL;
    std::vector<ImageLabel*> *imagePreviewList = new std::vector<ImageLabel*>();
    LymeDatabaseHandler *dataHandler = new LymeDatabaseHandler(parent, imagePreviewList);
    ASSERT_TRUE(dataHandler != NULL);
}

bool createAndSaveRandomNoiseColorImage(int height, int width, String pathToSave)
{
    Mat testImage(height, width, CV_8UC3);
    randu(testImage, Scalar(0, 0, 0), Scalar(255, 255, 255));

    if(testImage.empty())
    {
        cout << "Image not created.\n";
        return false;
    }

    imwrite(pathToSave, testImage);
    return true;
}

ImageSelectionHandler* createImageSelectionHandler()
{
    QWidget *parent = NULL;
    std::vector<ImageLabel*> *imagePreviewList = new std::vector<ImageLabel*>();
    ImageSelectionHandler *dataHandler = new ImageSelectionHandler(parent, imagePreviewList);
    return dataHandler;
}

TEST(DataHandler, TestLoadImageFromPath)
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();

    if(createAndSaveRandomNoiseColorImage(200, 200, "testImage.png") == false)
    {
        FAIL() << "[INFO] Cannot create Image to correctly execute the test.\n";
    }
    
    QImage emptyImage;
    ASSERT_TRUE(dataHandler->loadImageFromPath("testImage.png") != emptyImage);
}

TEST(DataHandler, TestAddImageToImagePreviewList)
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();

    long unsigned int sizeAtBegin = dataHandler->imagePreviewList->size();
    QImage newImageToAdd;
    dataHandler->addImageToImagePreviewList(newImageToAdd);
    ASSERT_TRUE(dataHandler->imagePreviewList->size() == sizeAtBegin + 1);
}

TEST(DataHandler, TestReloadPreviewFail)
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();
    dataHandler->indexPathToImagesList = 0;
    dataHandler->maxNumberOfImagesToLoad = 10;
    ASSERT_FALSE(dataHandler->reloadPreview());
}

TEST(DataHandler, TestReloadPreviewSuccess)
{
    ImageSelectionHandler *dataHandler = createImageSelectionHandler();
    dataHandler->indexPathToImagesList = 10;
    dataHandler->maxNumberOfImagesToLoad = 10;

    createAndSaveRandomNoiseColorImage(200, 200, "testImage.png");

    QString pathToImage = "testImage.png";
    dataHandler->pathToImages.push_back(pathToImage);

    QImage qImageA = dataHandler->loadImageFromPath(pathToImage);
    QImage qImageTransform = dataHandler->loadImageFromPath(pathToImage).convertToFormat(QImage::Format_Grayscale8);
    dataHandler->addImageToImagePreviewList(qImageTransform);

    dataHandler->reloadPreview();

    ASSERT_TRUE(dataHandler->imagePreviewList->at(0)->rawImage == qImageA);
}