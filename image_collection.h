#ifndef IMAGE_COLLECTION_H
#define IMAGE_COLLECTION_H

#include "image_label.h"
#include <QStringList>

class ImageCollection {

    public:
        ImageCollection();

        int maxNumberOfImagesToLoad;

        void loadPreview();
        void erasePreviewIfNotEmpty();
        void loadPreviousPreview();

        bool pathListToImagesIsEmpty();
        void setPathToImages(QStringList newPathToImages);
        ImageLabel* getImageLabelFromDataBase(int index);
        int getPreviewListSize();

    private:
        QStringList pathToImages;
        int indexPathToImagesList;
        std::vector<ImageLabel*> imageDataBasePreview;
};

#endif // IMAGE_COLLECTION_H
