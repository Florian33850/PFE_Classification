#include "preprocessing.h"

MirrorPreprocess::MirrorPreprocess()
{
    horizontalMirror = false;
    verticalMirror = false;
}

void MirrorPreprocess::changeHorizontalMirrorMode()
{
    horizontalMirror = !horizontalMirror;
}

void MirrorPreprocess::changeVerticalMirrorMode()
{
    verticalMirror = !verticalMirror;
}

void MirrorPreprocess::runPreprocess(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber=0; imageNumber < imagePreviewList->size(); imageNumber++)
    {
        QImage mirrorImage = imagePreviewList->at(imageNumber)->getQImage().mirrored(horizontalMirror, verticalMirror);
        imagePreviewList->at(imageNumber)->setImage(mirrorImage);
    }
}



GrayscalePreprocess::GrayscalePreprocess()
{
}

void GrayscalePreprocess::runPreprocess(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber=0; imageNumber < imagePreviewList->size(); imageNumber++)
    {
        QImage grayscaleImage = imagePreviewList->at(imageNumber)->getQImage().convertToFormat(QImage::Format_Grayscale8);
        imagePreviewList->at(imageNumber)->setImage(grayscaleImage);
    }
}