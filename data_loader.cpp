#include "data_loader.h"

#include <iostream>

DataLoader::DataLoader(QWidget *parent, ImageCollection *imageCollection)
{
    this->parent = parent;
    this->imageCollection = imageCollection;
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
    this->imageCollection->addImageLabelToDataBasePreview(newImageLabel);
}



ImageSelectionLoader::ImageSelectionLoader(QWidget *parent, ImageCollection *imageCollection) : DataLoader::DataLoader(parent, imageCollection)
{
    this->indexPathToImagesList = 0;
    this->maxNumberOfImagesToLoad = 50;
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
        imageCollection->erasePreviewIfNotEmpty();
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
        imageCollection->erasePreviewIfNotEmpty();
        for(int fileIndex = previousIndex; fileIndex < indexPathToImagesList - maxNumberOfImagesToLoad; fileIndex++)
        {
            QImage qImage = loadImageFromPath(pathToImages.at(fileIndex));
            addImageToImageDataBasePreview(qImage);
        }
        indexPathToImagesList -= maxNumberOfImagesToLoad;
        return true;
    }
}
