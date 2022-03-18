#include "data_handler.h"
#include <iostream>
#include <QImage>

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
        std::cout << "Cannot open image\n" << std::endl;
    }
    return qImage;
}

void DataHandler::addImageToImageDataBasePreview(QImage qImage)
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
        std::cout << "No more images to load" << std::endl;
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
        addImageToImageDataBasePreview(qImage);
    }
    return true;
}

bool DataHandler::saveImagesInFile(QString saveFolderName, std::vector<ImageTransformationWidget*> imageTransformationWidgetList, ImageTransformationViewer *imageTransformationViewer)
{
    QString buildPath = QDir::currentPath();

    //Initialize the path for saving images next to build repository and create the repository
    QString savedImagesPath = buildPath;
    savedImagesPath = savedImagesPath.left(savedImagesPath.lastIndexOf(QChar('/')));

    QDir directoryForSave(savedImagesPath);
    if (!directoryForSave.exists())
    {
        qWarning("Cannot find the directory to save images");
        return false;
    }
    
    directoryForSave.setPath(savedImagesPath.append("/savedData/"+saveFolderName));

    //Save each selected image in a repository with the same name as the original
    QString imageToSavePath, repositoryName, imageAndItsRepositoryName;
    QString transformationsPerformed;

    for(int unsigned image_index = 0 ; image_index < pathToImages.size() ; image_index++)
    {
        QImage qImage = loadImageFromPath(pathToImages.at(image_index));
        QImage modifiedImage = qImage;
        
        for(ImageTransformationWidget *imageTransformationWidget : imageTransformationWidgetList)
        {
            if(imageTransformationWidget->isActivated)
            {
                modifiedImage = imageTransformationWidget->imageTransformation->runImageTransformation(modifiedImage);
            }
        }

        imageAndItsRepositoryName = pathToImages[image_index].section("/", -2);
        repositoryName = imageAndItsRepositoryName.left(imageAndItsRepositoryName.lastIndexOf(QChar('/'))+1);

        directoryForSave.mkpath(repositoryName);

        imageToSavePath = directoryForSave.path() + "/" + imageAndItsRepositoryName;
        
        modifiedImage.save(imageToSavePath);
    }
    return true;
}



ImageSelectionLoader::ImageSelectionLoader(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList) : DataHandler::DataHandler(parent, imagePreviewList)
{
    this->indexPathToImagesList = 0;
    this->maxNumberOfImagesToLoad = 10;
}

bool ImageSelectionLoader::selectDataBasePath()
{
    QStringList newPathToImages = QFileDialog::getOpenFileNames(this->parent, "Select images to open", "Images (*.jpg *.jpeg *.png *.tiff)");
    if (newPathToImages.size() == 0)
    {
        printf("Loading problem, cannot open selected files.\n");
        return false;
    }
    this->pathToImages = newPathToImages;

    return true;
}

bool ImageSelectionLoader::loadNextPreview()
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
            addImageToImageDataBasePreview(qImage);
        }
        this->indexPathToImagesList += this->maxNumberOfImagesToLoad;
        return true;
    }
}

bool ImageSelectionLoader::loadPreviousPreview()
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
            addImageToImageDataBasePreview(qImage);
        }
        this->indexPathToImagesList -= this->maxNumberOfImagesToLoad;
        return true;
    }
}



LymeDatabaseLoader::LymeDatabaseLoader(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList) : DataHandler::DataHandler(parent, imagePreviewList)
{
    this->indexPathToImagesList = 0;
    this->maxNumberOfImagesToLoad = 10;
}

bool LymeDatabaseLoader::selectDataBasePath()
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

bool LymeDatabaseLoader::loadNextPreview()
{
    if(indexPathToImagesList >= pathToImages.size())
    {
        std::cout << "No more images to load" << std::endl;
        return false;
    }
    else
    {
        imagePreviewList->clear();
        for(int fileIndex = this->indexPathToImagesList; fileIndex < this->indexPathToImagesList + this->maxNumberOfImagesToLoad; fileIndex++)
        {
            if(fileIndex == pathToImages.size())
            {
                break;
            }
            QString pathToImage = this->pathToImages.at(fileIndex);
            QImage qImage = loadImageFromPath(pathToImage);
            addImageToImageDataBasePreview(qImage);
        }
        this->indexPathToImagesList += this->maxNumberOfImagesToLoad;
        return true;
    }
}

bool LymeDatabaseLoader::loadPreviousPreview()
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
            QImage qImage = loadImageFromPath(this->pathToImages.at(fileIndex));
            addImageToImageDataBasePreview(qImage);
        }
        this->indexPathToImagesList -= this->maxNumberOfImagesToLoad;
        return true;
    }
}
