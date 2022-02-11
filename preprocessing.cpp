#include "preprocessing.h"

Mirrored::Mirrored( Preprocessing *parent)
{
}

void Mirrored::runPreprocess(ImageCollection *imageCollection)
{
    for(int imgNumber=0; imgNumber < imageCollection->getDataBaseSize(); imgNumber++)
    {
        QImage mirroredImage = imageCollection->getImageLabelFromDataBase(imgNumber)->getQImage().mirrored();
        imageCollection->getImageLabelFromDataBase(imgNumber)->setImage(mirroredImage);
    }
}
