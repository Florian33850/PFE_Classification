#ifndef IMAGE_COLLECTION_H
#define IMAGE_COLLECTION_H

#include "image_label.h"
#include <QStringList>

class ImageCollection {

    public:
        ImageCollection();

        void loadCollection();
        void eraseCollectionIfNotEmpty();

        void setPathToImages(QStringList newPathToImages);
        ImageLabel* getImageLabelFromDataBase(int index);
        int getDataBaseSize();

    private:
        QStringList pathToImages;
        std::vector<ImageLabel*> imageDataBase;
};

#endif // IMAGE_COLLECTION_H
