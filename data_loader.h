#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include "image_collection.h"

#include <QStringList>
#include <QFileDialog>

class DataLoader
{
    public:
        DataLoader(QWidget *parent, ImageCollection *imageCollection);
        
        int maxNumberOfImagesToLoad;
        int totalNumberOfImages;

        virtual bool selectDataBasePath() = 0;
        virtual bool loadPreview() = 0;
        virtual bool loadPreviousPreview() = 0;

    protected:
        QWidget *parent;
        ImageCollection *imageCollection;

        QImage loadImageFromPath(QString pathToImage);
        void addImageToImageDataBasePreview(QImage qImage);
};

class ImageSelectionLoader : public DataLoader
{
    public:
        ImageSelectionLoader(QWidget *parent, ImageCollection *imageCollection);

        bool selectDataBasePath();
        bool loadPreview();
        bool loadPreviousPreview();

    private:
        int indexPathToImagesList;
        QStringList pathToImages;
};
#endif //IMAGE_COLLECTION_H