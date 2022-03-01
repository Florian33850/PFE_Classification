#include "data_loader.h"

#include <iostream>

DataLoader::DataLoader(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList)
{
    this->parent = parent;
    this->imagePreviewList = imagePreviewList; 
}

QImage DataLoader::loadImageFromPath(QString pathToImage)
{
    QImage qImage;
    if(qImage.load(pathToImage) == false)
    {
        std::cout << "Cannot open image\n" << std::endl;
    }
    return qImage;
}

void DataLoader::addImageToImageDataBasePreview(QImage qImage)
{
    ImageLabel *newImageLabel = new ImageLabel();
    newImageLabel->setImage(qImage);
    this->imagePreviewList->push_back(newImageLabel);
}

void DataLoader::eraseImagePreviewListIfNotEmpty()
{
    if(!this->imagePreviewList->empty())
    {
        imagePreviewList->clear();
    }
}


ImageSelectionLoader::ImageSelectionLoader(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList) : DataLoader::DataLoader(parent, imagePreviewList)
{
    this->indexPathToImagesList = 0;
    this->maxNumberOfImagesToLoad = 10;
}

bool ImageSelectionLoader::selectDataBasePath()
{
    QStringList newPathToImages = QFileDialog::getOpenFileNames(this->parent, "Select images to open", "Images (*.jpg *.jpeg *.png *.tiff)");
    if (newPathToImages.size() == 0)
    {
        printf("Loading problem, cannot open selected files.\n");
        return false;
    }
    this->pathToImages = newPathToImages;
    return true;
}

bool ImageSelectionLoader::loadPreview()
{
    if(indexPathToImagesList >= pathToImages.size())
    {
        std::cout << "No more images to load" << std::endl;
        return false;
    }
    else
    {
        eraseImagePreviewListIfNotEmpty();
        for(int fileIndex = indexPathToImagesList; fileIndex < indexPathToImagesList + maxNumberOfImagesToLoad; fileIndex++)
        {
            if(fileIndex == pathToImages.size())
            {
                break;
            }
            QImage qImage = loadImageFromPath(pathToImages.at(fileIndex));
            addImageToImageDataBasePreview(qImage);
        }
        indexPathToImagesList += maxNumberOfImagesToLoad;
        return true;
    }
}

bool ImageSelectionLoader::loadPreviousPreview()
{
    int previousIndex = indexPathToImagesList - 2*maxNumberOfImagesToLoad;
    if(previousIndex < 0)
    {
        std::cout << "No more images to load" << std::endl;
        return false;
    }
    else
    {
        eraseImagePreviewListIfNotEmpty();
        for(int fileIndex = previousIndex; fileIndex < indexPathToImagesList - maxNumberOfImagesToLoad; fileIndex++)
        {
            QImage qImage = loadImageFromPath(pathToImages.at(fileIndex));
            addImageToImageDataBasePreview(qImage);
        }
        indexPathToImagesList -= maxNumberOfImagesToLoad;
        return true;
    }
}
