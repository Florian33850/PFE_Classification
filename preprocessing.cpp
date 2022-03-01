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
    for(int imgNumber=0; imgNumber < imagePreviewList->size(); imgNumber++)
    {
        QImage mirrorImage = imagePreviewList->at(imgNumber)->getQImage().mirrored(horizontalMirror, verticalMirror);
        imagePreviewList->at(imgNumber)->setImage(mirrorImage);
    }
}



GrayscalePreprocess::GrayscalePreprocess()
{
}

void GrayscalePreprocess::runPreprocess(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imgNumber=0; imgNumber < imagePreviewList->size(); imgNumber++)
    {
        QImage grayscaleImage = imagePreviewList->at(imgNumber)->getQImage().convertToFormat(QImage::Format_Grayscale8);
        imagePreviewList->at(imgNumber)->setImage(grayscaleImage);
    }
}