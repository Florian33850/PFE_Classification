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
        
        int maxNumberOfImagesToLoad;
        int totalNumberOfImages;
        QStringList pathToImages;

        virtual bool selectDataBasePath() = 0;
        virtual bool loadPreview() = 0;
        virtual bool loadPreviousPreview() = 0;

    protected:
        QWidget *parent;
        std::vector<ImageLabel*> *imagePreviewList;

        QImage loadImageFromPath(QString pathToImage);
        void addImageToImageDataBasePreview(QImage qImage);
};

class ImageSelectionLoader : public DataHandler
{
    public:
        ImageSelectionLoader(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);

        bool selectDataBasePath();
        bool loadPreview();
        bool loadPreviousPreview();

    private:
        int indexPathToImagesList;
};

class LymeDatabaseLoader : public DataHandler
{
    public:
        LymeDatabaseLoader(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);

        bool selectDataBasePath();
        bool loadPreview();
        bool loadPreviousPreview();

    private:
        int indexPathToImagesList;
        QString pathToDatabase;
};
#endif //data_handler_H