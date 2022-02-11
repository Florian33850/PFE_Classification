#include "preprocessing.h"

Mirrored::Mirrored( Preprocessing *parent)
{
    horizontalMirror = false;
    verticalMirror = false;
}

void Mirrored::runPreprocess(ImageCollection *imageCollection)
{
    for(int imgNumber=0; imgNumber < imageCollection->getDataBaseSize(); imgNumber++)
    {
        QImage mirroredImage = imageCollection->getImageLabelFromDataBase(imgNumber)->getQImage().mirrored(horizontalMirror, verticalMirror);
        imageCollection->getImageLabelFromDataBase(imgNumber)->setImage(mirroredImage);
    }
}

void Mirrored::changeHorizontalMirrorMode()
{
    horizontalMirror = !horizontalMirror;
}

void Mirrored::changeVerticalMirrorMode()
{
    verticalMirror = !verticalMirror;
}
