#include "preprocessing.h"

Mirrored::Mirrored(Preprocessing *parent)
{
    horizontalMirror = false;
    verticalMirror = false;
}

void Mirrored::changeHorizontalMirrorMode()
{
    horizontalMirror = !horizontalMirror;
}

void Mirrored::changeVerticalMirrorMode()
{
    verticalMirror = !verticalMirror;
}

void Mirrored::runPreprocess(ImageCollection *imageCollection)
{
    for(int imgNumber=0; imgNumber < imageCollection->getDataBaseSize(); imgNumber++)
    {
        QImage mirroredImage = imageCollection->getImageLabelFromDataBase(imgNumber)->getQImage().mirrored(horizontalMirror, verticalMirror);
        imageCollection->getImageLabelFromDataBase(imgNumber)->setImage(mirroredImage);
    }
}



Grayscale::Grayscale(Preprocessing *parent)
{

}

void Grayscale::runPreprocess(ImageCollection *imageCollection)
{
    for(int imgNumber=0; imgNumber < imageCollection->getDataBaseSize(); imgNumber++)
    {
        QImage grayscaleImage = imageCollection->getImageLabelFromDataBase(imgNumber)->getQImage().convertToFormat(QImage::Format_Grayscale8);
        imageCollection->getImageLabelFromDataBase(imgNumber)->setImage(grayscaleImage);
    }
}