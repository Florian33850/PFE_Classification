#include "image_transformation.h"
#include <iostream>

void ImageTransformation::runImageTransformationOnPreviewList(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber=0; imageNumber < imagePreviewList->size(); imageNumber++)
    {
        QImage qImage = applyImageTransformation(imagePreviewList->at(imageNumber)->getQImage());
        imagePreviewList->at(imageNumber)->setImage(qImage);
    }
}

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

QImage MirrorImageTransformation::applyImageTransformation(QImage qImage)
{
    QImage mirrorImage = qImage.mirrored(horizontalMirror, verticalMirror);
    return mirrorImage;
}

GrayscaleImageTransformation::GrayscaleImageTransformation()
{
}

QImage GrayscaleImageTransformation::applyImageTransformation(QImage qImage)
{
    QImage grayscaleImage = qImage.convertToFormat(QImage::Format_Grayscale8);
    return grayscaleImage;
}