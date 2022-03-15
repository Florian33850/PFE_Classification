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
    ASSERT_TRUE(new ImageSelectionHandler(parent, imagePreviewList) != NULL);
}

TEST(LymeDatabaseHandler, TestLymeDatabaseHandlerInstantiation)
{
    QWidget *parent = NULL;
    std::vector<ImageLabel*> *imagePreviewList = new std::vector<ImageLabel*>();
    ASSERT_TRUE(new LymeDatabaseHandler(parent, imagePreviewList) != NULL);
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
