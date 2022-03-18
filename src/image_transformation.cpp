#include "image_transformation.h"

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

void MirrorImageTransformation::runImageTransformation(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber = 0; imageNumber < (int) imagePreviewList->size(); imageNumber++)
    {
        QImage mirrorImage = imagePreviewList->at(imageNumber)->getQImage().mirrored(horizontalMirror, verticalMirror);
        imagePreviewList->at(imageNumber)->setImage(mirrorImage);
    }
}



GrayscaleImageTransformation::GrayscaleImageTransformation()
{
}

void GrayscaleImageTransformation::runImageTransformation(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber = 0; imageNumber < (int) imagePreviewList->size(); imageNumber++)
    {
        QImage grayscaleImage = imagePreviewList->at(imageNumber)->getQImage().convertToFormat(QImage::Format_Grayscale8);
        imagePreviewList->at(imageNumber)->setImage(grayscaleImage);
    }
}