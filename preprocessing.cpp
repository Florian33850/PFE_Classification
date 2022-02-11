#include "preprocessing.h"

Mirrored::Mirrored( Preprocessing *parent)
{
}

void Mirrored::runPreprocess(ImageCollection *imageCollection)
{
    for(int imgNumber=0; imgNumber < imageCollection->getDataBaseSize(); imgNumber++)
    {
        imageCollection->getImageLabelFromDataBase(imgNumber)->getQImage().mirrored();
    }
}
