#include "image_collection.h"

#include <iostream>

ImageCollection::ImageCollection()
{
}

void ImageCollection::erasePreviewIfNotEmpty()
{
    if(!imageDataBasePreview.empty())
    {
        imageDataBasePreview.clear();
    }
}

void ImageCollection::addImageLabelToDataBasePreview(ImageLabel *imageLabel)
{
    imageDataBasePreview.push_back(imageLabel);
}

ImageLabel* ImageCollection::getImageLabelFromDataBase(int index)
{
    return imageDataBasePreview.at(index);
}

int ImageCollection::getPreviewListSize()
{
    return imageDataBasePreview.size();
}