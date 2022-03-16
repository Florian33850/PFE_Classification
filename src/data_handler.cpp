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
    this->buildPath = QDir::currentPath();

    return true;
}

bool ImageSelectionLoader::loadPreview()
{
    if(indexPathToImagesList >= pathToImages.size())
    {
        std::cout << "No more images to load" << std::endl;
        return false;
    }
    else
    {
        imagePreviewList->clear();
        for(int fileIndex = indexPathToImagesList; fileIndex < indexPathToImagesList + maxNumberOfImagesToLoad; fileIndex++)
        {
            if(fileIndex == pathToImages.size())
            {
                break;
            }
            QImage qImage = loadImageFromPath(pathToImages.at(fileIndex));
            addImageToImageDataBasePreview(qImage);
        }
        indexPathToImagesList += maxNumberOfImagesToLoad;
        return true;
    }
}

bool ImageSelectionLoader::loadPreviousPreview()
{
    int previousIndex = indexPathToImagesList - 2*maxNumberOfImagesToLoad;
    if(previousIndex < 0)
    {
        std::cout << "No more images to load" << std::endl;
        return false;
    }
    else
    {
        imagePreviewList->clear();
        for(int fileIndex = previousIndex; fileIndex < indexPathToImagesList - maxNumberOfImagesToLoad; fileIndex++)
        {
            QImage qImage = loadImageFromPath(pathToImages.at(fileIndex));
            addImageToImageDataBasePreview(qImage);
        }
        indexPathToImagesList -= maxNumberOfImagesToLoad;
        return true;
    }
}
//bool ImageSelectionLoader::saveImagesInFile()

bool ImageSelectionLoader::saveImagesInFile(QString saveFolderName, QVector<QImage> imagesToSave)
{
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
    for(int unsigned index_image = 0 ; index_image < imagesToSave.size() ; index_image++)
    {
        imageAndItsRepositoryName = pathToImages[index_image].section("/", -2);
        repositoryName = imageAndItsRepositoryName.left(imageAndItsRepositoryName.lastIndexOf(QChar('/'))+1);

        directoryForSave.mkpath(repositoryName);

        imageToSavePath = directoryForSave.path() + "/"+ imageAndItsRepositoryName;
        imagesToSave[index_image].save(imageToSavePath);
    }
        
    return true;
}
