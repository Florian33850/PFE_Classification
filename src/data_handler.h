#ifndef data_handler_H
#define data_handler_H

#include "image_label.h"

#include <QStringList>
#include <QFileDialog>
#include <QDirIterator>
#include <QDir>

class DataHandler
{
    public:
        DataHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);

        QStringList pathToImages;
        int maxNumberOfImagesToLoad;
        int totalNumberOfImages;
        int indexPathToImagesList;
        
        bool reloadPreview();
        bool loadNextPreview();
        bool loadPreviousPreview();

        virtual bool selectDataBasePath() = 0;
        
    protected:
        QWidget *parent;
        std::vector<ImageLabel*> *imagePreviewList;

        QImage loadImageFromPath(QString pathToImage);
        void addImageToImagePreviewList(QImage qImage);
};

class ImageSelectionHandler : public DataHandler
{
    public:
        ImageSelectionHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);

        bool selectDataBasePath();
};

class LymeDatabaseHandler : public DataHandler
{
    public:
        LymeDatabaseHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);

        bool selectDataBasePath();

    private:
        QString pathToDatabase;
};
#endif //data_handler_H