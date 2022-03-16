#include <gtest/gtest.h>
#define private public
#define protected public
#include "../src/data_handler.h"

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

bool createAndSaveBlackImage(int height, int width)
{
    Mat testImage(height, width, CV_8UC3, Scalar(0, 0, 0));

    if(testImage.empty())
    {
        cout << "Image not created.\n";
        return false;
    }

    imwrite("testImage.png", testImage);
    return true;
}

TEST(DataHandler, TestLoadImageFromPath)
{
    //DataHandler Instantiation
    QWidget *parent = NULL;
    std::vector<ImageLabel*> *imagePreviewList = new std::vector<ImageLabel*>();
    ImageSelectionHandler *datahandler = new ImageSelectionHandler(parent, imagePreviewList);

    if(createAndSaveBlackImage(200, 200) == false)
    {
        FAIL() << "[INFO] Cannot create Image to correctly execute the test.\n";
    }
    
    QString pathToImage = "testImage.png";
    QImage emptyImage;
    ASSERT_TRUE(datahandler->loadImageFromPath(pathToImage) != emptyImage);
}

TEST(DataHandler, TestAddImageToImagePreviewList)
{
    //DataHandler Instantiation
    QWidget *parent = NULL;
    std::vector<ImageLabel*> *imagePreviewList = new std::vector<ImageLabel*>();
    ImageSelectionHandler *datahandler = new ImageSelectionHandler(parent, imagePreviewList);

    int sizeAtBegin = datahandler->imagePreviewList->size();
    QImage newImageToAdd;
    datahandler->addImageToImagePreviewList(newImageToAdd);
    ASSERT_TRUE(datahandler->imagePreviewList->size() == sizeAtBegin + 1);
}
