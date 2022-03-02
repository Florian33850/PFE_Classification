#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include "image_label.h"

#include <QStringList>
#include <QFileDialog>

class DataLoader
{
    public:
        DataLoader(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);
        
        int maxNumberOfImagesToLoad;
        int totalNumberOfImages;

        virtual bool selectDataBasePath() = 0;
        virtual bool loadPreview() = 0;
        virtual bool loadPreviousPreview() = 0;

    protected:
        QWidget *parent;
        std::vector<ImageLabel*> *imagePreviewList;

        QImage loadImageFromPath(QString pathToImage);
        void addImageToImageDataBasePreview(QImage qImage);
};

class ImageSelectionLoader : public DataLoader
{
    public:
        ImageSelectionLoader(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);

        bool selectDataBasePath();
        bool loadPreview();
        bool loadPreviousPreview();

    private:
        int indexPathToImagesList;
        QStringList pathToImages;
};
#endif //DATA_LOADER_H