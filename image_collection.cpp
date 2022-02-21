#include "image_collection.h"

#include <iostream>

ImageCollection::ImageCollection()
{
    indexPathToImagesList = 0;
    maxNumberOfImagesToLoad = 10;
}

void ImageCollection::loadPreview()
{
    if(indexPathToImagesList >= pathToImages.size())
    {
        printf("No more images to load.\n");
    }
    else
    {
        erasePreviewIfNotEmpty();
        for(int fileNum=indexPathToImagesList; fileNum<indexPathToImagesList+maxNumberOfImagesToLoad; fileNum++)
        {
            if(fileNum == pathToImages.size())
            {
                break;
            }
            QImage qImg;
            if(qImg.load(pathToImages.at(fileNum)) == false)
            {
                std::cout << "Cannot open image\n" << std::endl;
            }
            ImageLabel *imageLabel = new ImageLabel();
            imageLabel->setImage(qImg);
            imageDataBasePreview.push_back(imageLabel);
        }
        indexPathToImagesList += maxNumberOfImagesToLoad;
    }
}

void ImageCollection::erasePreviewIfNotEmpty()
{
    if(!imageDataBasePreview.empty())
    {
        imageDataBasePreview.clear();
    }
}

void ImageCollection::loadPreviousPreview()
{
    int previousIndex = indexPathToImagesList - 2*maxNumberOfImagesToLoad;
    if(previousIndex < 0)
    {
        std::cout << "No more images to load" << std::endl;
    }
    else
    {
        erasePreviewIfNotEmpty();
        for(int fileNum=previousIndex; fileNum<indexPathToImagesList-maxNumberOfImagesToLoad; fileNum++)
        {
            QImage qImg;
            if(qImg.load(pathToImages.at(fileNum)) == false)
            {
                std::cout << "Cannot open image\n" <<std::endl;
            }
            ImageLabel *imageLabel = new ImageLabel();
            imageLabel->setImage(qImg);
            imageDataBasePreview.push_back(imageLabel);
        }
        indexPathToImagesList -= maxNumberOfImagesToLoad;
    }
}

bool ImageCollection::pathListToImagesIsEmpty()
{
    return pathToImages.empty();
}

void ImageCollection::setPathToImages(QStringList newPathToImages)
{
    pathToImages = newPathToImages;
}

ImageLabel* ImageCollection::getImageLabelFromDataBase(int index)
{
    return imageDataBasePreview.at(index);
}

int ImageCollection::getPreviewListSize()
{
    return imageDataBasePreview.size();
}
