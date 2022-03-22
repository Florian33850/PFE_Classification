#ifndef data_handler_H
#define data_handler_H

#include "image_label.h"
#include "image_transformation_widget.h"

#include <iostream>
#include <unistd.h>
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
        virtual bool saveImagesInFile(std::vector<ImageTransformationWidget*> imageTransformationWidgetList, QString saveFolderName = "") = 0;
        
    protected:
        QWidget *parent;
        std::vector<ImageLabel*> *imagePreviewList;

        QImage loadImageFromPath(QString pathToImage);
        void addImageToImagePreviewList(QImage qImage);
        QDir getGlobalSavingDirectory();
};

class ImageSelectionHandler : public DataHandler
{
    public:
        ImageSelectionHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);

        bool selectDataBasePath();
        bool saveImagesInFile(std::vector<ImageTransformationWidget*> imageTransformationWidgetList, QString saveFolderName = "");
};

class LymeDatabaseHandler : public DataHandler
{
    public:
        LymeDatabaseHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);

        bool selectDataBasePath();
        bool saveImagesInFile(std::vector<ImageTransformationWidget*> imageTransformationWidgetList, QString saveFolderName = "");

    private:
        QString pathToDatabase;
};
#endif //data_handler_H