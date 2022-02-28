#ifndef IMAGE_COLLECTION_H
#define IMAGE_COLLECTION_H

#include "image_label.h"

#include <QStringList>

class ImageCollection
{
    public:
        ImageCollection();

        void erasePreviewIfNotEmpty();
        void addImageLabelToDataBasePreview(ImageLabel *imageLabel);

        ImageLabel* getImageLabelFromDataBase(int index);
        int getPreviewListSize();

    private:
        std::vector<ImageLabel*> imageDataBasePreview;
};

#endif //IMAGE_COLLECTION_H