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

void MirrorPreprocess::runPreprocess(ImageCollection *imageCollection)
{
    for(int imgNumber=0; imgNumber < imageCollection->getDataBaseSize(); imgNumber++)
    {
        QImage mirrorImage = imageCollection->getImageLabelFromDataBase(imgNumber)->getQImage().mirrored(horizontalMirror, verticalMirror);
        imageCollection->getImageLabelFromDataBase(imgNumber)->setImage(mirrorImage);
    }
}



GrayscalePreprocess::GrayscalePreprocess()
{
}

void GrayscalePreprocess::runPreprocess(ImageCollection *imageCollection)
{
    for(int imgNumber=0; imgNumber < imageCollection->getDataBaseSize(); imgNumber++)
    {
        QImage grayscaleImage = imageCollection->getImageLabelFromDataBase(imgNumber)->getQImage().convertToFormat(QImage::Format_Grayscale8);
        imageCollection->getImageLabelFromDataBase(imgNumber)->setImage(grayscaleImage);
    }
}