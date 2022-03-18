#include "data_handler.h"

#include <iostream>

DataHandler::DataHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList)
{
    this->parent = parent;
    this->imagePreviewList = imagePreviewList; 
}

QImage DataHandler::loadImageFromPath(QString pathToImage)
{
    QImage qImage;
    if(qImage.load(pathToImage) == false)
    {
        std::cout << "Cannot open image : " << pathToImage.toUtf8().constData() << std::endl;
    }
    return qImage;
}

void DataHandler::addImageToImagePreviewList(QImage qImage)
{
    ImageLabel *newImageLabel = new ImageLabel();
    newImageLabel->setImage(qImage);
    this->imagePreviewList->push_back(newImageLabel);
}

bool DataHandler::reloadPreview()
{
    int previousIndex = indexPathToImagesList - maxNumberOfImagesToLoad;
    if(previousIndex < 0)
    {
        std::cerr << "Impossible to reload." << std::endl;
        return false;
    }
    imagePreviewList->clear();
    for(int fileIndex = previousIndex; fileIndex < indexPathToImagesList; fileIndex++)
    {
        if(fileIndex == pathToImages.size())
        {
            break;
        }
        QImage qImage = loadImageFromPath(pathToImages.at(fileIndex));
        addImageToImagePreviewList(qImage);
    }
    return true;
}

bool DataHandler::loadNextPreview()
{
    if(this->indexPathToImagesList >= pathToImages.size())
    {
        std::cout << "No more images to load" << std::endl;
        return false;
    }
    else
    {
        imagePreviewList->clear();
        for(int fileIndex = this->indexPathToImagesList; fileIndex < this->indexPathToImagesList + this->maxNumberOfImagesToLoad; fileIndex++)
        {
            if(fileIndex == this->pathToImages.size())
            {
                break;
            }
            QImage qImage = loadImageFromPath(pathToImages.at(fileIndex));
            addImageToImagePreviewList(qImage);
        }
        this->indexPathToImagesList += this->maxNumberOfImagesToLoad;
        return true;
    }
}

bool DataHandler::loadPreviousPreview()
{
    int previousIndex = this->indexPathToImagesList - 2*this->maxNumberOfImagesToLoad;
    if(previousIndex < 0)
    {
        std::cout << "No more images to load" << std::endl;
        return false;
    }
    else
    {
        imagePreviewList->clear();
        for(int fileIndex = previousIndex; fileIndex < this->indexPathToImagesList - this->maxNumberOfImagesToLoad; fileIndex++)
        {
            QImage qImage = loadImageFromPath(pathToImages.at(fileIndex));
            addImageToImagePreviewList(qImage);
        }
        this->indexPathToImagesList -= this->maxNumberOfImagesToLoad;
        return true;
    }
}



ImageSelectionHandler::ImageSelectionHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList) : DataHandler::DataHandler(parent, imagePreviewList)
{
    this->indexPathToImagesList = 0;
    this->maxNumberOfImagesToLoad = 10;
}

bool ImageSelectionHandler::selectDataBasePath()
{
    QStringList newPathToImages = QFileDialog::getOpenFileNames(this->parent, "Select images to open", "Images (*.jpg *.jpeg *.png *.tiff)");
    if (newPathToImages.size() == 0)
    {
        std::cerr << "Loading problem, cannot open selected files.\n" << std::endl;
        return false;
    }
    this->pathToImages = newPathToImages;
    return true;
}



LymeDatabaseHandler::LymeDatabaseHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList) : DataHandler::DataHandler(parent, imagePreviewList)
{
    this->indexPathToImagesList = 0;
    this->maxNumberOfImagesToLoad = 10;
}

bool LymeDatabaseHandler::selectDataBasePath()
{
    QString newPathToDatabase = QFileDialog::getExistingDirectory(this->parent, "Select lyme database to open");
    if (newPathToDatabase.size() == 0)
    {
        printf("Loading problem, cannot open selected files.\n");
        return false;
    }
    this->pathToDatabase = newPathToDatabase;

    QDirIterator files(this->pathToDatabase, QDir::Files, QDirIterator::Subdirectories);
    do
    {
        if(files.filePath() != "")
        {
            this->pathToImages.append(files.filePath());
        }
    } while (files.next() != "");

    return true;
}
