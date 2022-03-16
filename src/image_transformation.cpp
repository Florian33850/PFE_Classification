#include "image_transformation.h"
#include <iostream>

MirrorImageTransformation::MirrorImageTransformation()
{
    horizontalMirror = false;
    verticalMirror = false;
}

void MirrorImageTransformation::changeHorizontalMirrorMode()
{
    horizontalMirror = !horizontalMirror;
}

void MirrorImageTransformation::changeVerticalMirrorMode()
{
    verticalMirror = !verticalMirror;
}

QVector<QImage> MirrorImageTransformation::runImageTransformation(std::vector<ImageLabel*> *imagePreviewList)
//void MirrorImageTransformation::runImageTransformation(std::vector<ImageLabel*> *imagePreviewList)
{
    //imagesToSave.clear();
    for(int imageNumber=0; imageNumber < imagePreviewList->size(); imageNumber++)
    {
        QImage mirrorImage = imagePreviewList->at(imageNumber)->getQImage().mirrored(horizontalMirror, verticalMirror);
        imagePreviewList->at(imageNumber)->setImage(mirrorImage);
        //imagesToSave.push_back(mirrorImage);
    }
    std::cout << imagesToSave.size() << std::endl;
    return imagesToSave;
    //return;
}



GrayscaleImageTransformation::GrayscaleImageTransformation()
{
}

QVector<QImage> GrayscaleImageTransformation::runImageTransformation(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber=0; imageNumber < imagePreviewList->size(); imageNumber++)
    {
        QImage grayscaleImage = imagePreviewList->at(imageNumber)->getQImage().convertToFormat(QImage::Format_Grayscale8);
        imagePreviewList->at(imageNumber)->setImage(grayscaleImage);
        //imagesToSave.push_back(grayscaleImage);
    }
    return imagesToSave;
    //return;
}