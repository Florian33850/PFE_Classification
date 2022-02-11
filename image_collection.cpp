#include "image_collection.h"

#include <iostream>

ImageCollection::ImageCollection()
{
}

void ImageCollection::loadCollection()
{
    for(int fileNum=0; fileNum<pathToImages.length(); fileNum++)
    {
        QImage qImg;
        if(qImg.load(pathToImages.at(fileNum)) == false)
        {
            std::cout << "Cannot open image\n" << std::endl;
        }
        ImageLabel *imageLabel = new ImageLabel();
        imageLabel->setImage(qImg);
        imageDataBase.push_back(imageLabel);
    }
}

void ImageCollection::eraseCollectionIfNotEmpty()
{
    if(!imageDataBase.empty())
    {
        imageDataBase.clear();
    }
}

void ImageCollection::setPathToImages(QStringList newPathToImages)
{
    pathToImages = newPathToImages;
}

ImageLabel* ImageCollection::getImageLabelFromDataBase(int index)
{
    return imageDataBase.at(index);
}

int ImageCollection::getDataBaseSize()
{
    return imageDataBase.size();
}
