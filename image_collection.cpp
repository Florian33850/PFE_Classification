#include "image_collection.h"

#include <iostream>

ImageCollection::ImageCollection()
{
    imgLabel = new ImageLabel();
}

void ImageCollection::loadCollection(QStringList pathToImages)
{
    if(qImg.load(pathToImages.at(0)) == false){
        std::cout << "Cannot open image" << std::endl;
    }
    imgLabel->setImg(qImg);
}

