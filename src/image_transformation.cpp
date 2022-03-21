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

void MirrorImageTransformation::runImageTransformationOnPreviewList(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber=0; imageNumber < imagePreviewList->size(); imageNumber++)
    {
        QImage mirrorImage = applyImageTransformation(imagePreviewList->at(imageNumber)->getQImage());
        imagePreviewList->at(imageNumber)->setImage(mirrorImage);
    }
}

QImage MirrorImageTransformation::applyImageTransformation(QImage qImage)
{
    QImage mirrorImage = qImage.mirrored(horizontalMirror, verticalMirror);
    return mirrorImage;
}

GrayscaleImageTransformation::GrayscaleImageTransformation()
{
}

void GrayscaleImageTransformation::runImageTransformationOnPreviewList(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber=0; imageNumber < imagePreviewList->size(); imageNumber++)
    {
        QImage grayscaleImage = applyImageTransformation(imagePreviewList->at(imageNumber)->getQImage());
        imagePreviewList->at(imageNumber)->setImage(grayscaleImage);
    }
}

QImage GrayscaleImageTransformation::applyImageTransformation(QImage qImage)
{
    QImage grayscaleImage = qImage.convertToFormat(QImage::Format_Grayscale8);
    return grayscaleImage;
}