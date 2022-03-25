#include "data_handler.h"

DataHandler::DataHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList)
{
    this->parent = parent;
    this->imagePreviewList = imagePreviewList; 
}

QImage loadImageFromPath(QString pathToImage)
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
    newImageLabel->qImage = qImage;
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
        std::cout << "[INFO] No more images to load" << std::endl;
        return false;
    }

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

bool DataHandler::loadPreviousPreview()
{
    int previousIndex = this->indexPathToImagesList - 2*this->maxNumberOfImagesToLoad;
    if(previousIndex < 0)
    {
        std::cout << "[INFO] No more images to load" << std::endl;
        return false;
    }

    imagePreviewList->clear();

    for(int fileIndex = previousIndex; fileIndex < this->indexPathToImagesList - this->maxNumberOfImagesToLoad; fileIndex++)
    {
        QImage qImage = loadImageFromPath(pathToImages.at(fileIndex));
        addImageToImagePreviewList(qImage);
    }
    this->indexPathToImagesList -= this->maxNumberOfImagesToLoad;
    return true;
}

QDir getGlobalSavingDirectory()
{
    QString buildPath = QDir::currentPath();

    //Initialize the path for saving images next to build repository
    QString applicationPath = buildPath;
    applicationPath = applicationPath.left(applicationPath.lastIndexOf(QChar('/')));

    QDir globalSaveDirectory(applicationPath);
    if (!globalSaveDirectory.exists())
    {
        qWarning("Cannot find the directory to save images");
    }
    return globalSaveDirectory;
}

ImageSelectionHandler::ImageSelectionHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList) : DataHandler::DataHandler(parent, imagePreviewList)
{
    this->indexPathToImagesList = 0;
    this->maxNumberOfImagesToLoad = MAX_NUMBER_OF_IMAGES_TO_LOAD_DATA_HANDLER_IMAGESELECTION;
}

bool ImageSelectionHandler::selectDataBasePath()
{
    QStringList newPathToImages = QFileDialog::getOpenFileNames(this->parent, "Select images to open", "Images (*.jpg *.jpeg *.png *.tiff)");
    if (newPathToImages.size() == 0)
    {
        std::cerr << "[INFO] Loading problem, cannot open selected files.\n" << std::endl;
        return false;
    }
    this->pathToImages = newPathToImages;
    return true;
}

bool ImageSelectionHandler::saveImagesInFile(std::vector<ImageTransformationWidget*> imageTransformationWidgetList, QString saveFolderName)
{
    QDir globalSaveDirectory = getGlobalSavingDirectory();
    globalSaveDirectory.setPath(globalSaveDirectory.path().append(saveFolderName));

    QString imageSavePath, repositoryName, imageAndItsRepositoryName;

    for(int unsigned image_index = 0 ; (int) image_index < pathToImages.size() ; image_index++)
    {
        QImage qImage = loadImageFromPath(pathToImages.at(image_index));
        
        for(ImageTransformationWidget *imageTransformationWidget : imageTransformationWidgetList)
        {
            if(imageTransformationWidget->isActivated)
            {
                qImage = imageTransformationWidget->imageTransformation->applyImageTransformation(qImage);
            }
        }

        imageAndItsRepositoryName = pathToImages[image_index].section("/", -2);
        repositoryName = imageAndItsRepositoryName.left(imageAndItsRepositoryName.lastIndexOf(QChar('/'))+1);
        if(!repositoryName.isEmpty())
        {
            globalSaveDirectory.mkpath(repositoryName);
        }
        imageSavePath = globalSaveDirectory.path() + "/" + imageAndItsRepositoryName;
        if(!qImage.save(imageSavePath))
        {
            std::cout << "[INFO] Save error for file: " << imageSavePath.toUtf8().constData() << "\n" << std::endl;
        }
    }
    return true;
}



LymeDatabaseHandler::LymeDatabaseHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList) : DataHandler::DataHandler(parent, imagePreviewList)
{
    this->indexPathToImagesList = 0;
    this->maxNumberOfImagesToLoad = MAX_NUMBER_OF_IMAGES_TO_LOAD_DATA_HANDLER_LYMEDATABASE;
}

bool LymeDatabaseHandler::selectDataBasePath()
{
    QString newPathToDatabase = QFileDialog::getExistingDirectory(this->parent, "Select lyme database to open");
    if (newPathToDatabase.size() == 0)
    {
        printf("[INFO] Loading problem, cannot open selected files.\n");
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

bool LymeDatabaseHandler::saveImagesInFile(std::vector<ImageTransformationWidget*> imageTransformationWidgetList, QString saveFolderName)
{
    QDir globalSaveDirectory = getGlobalSavingDirectory();
    globalSaveDirectory.setPath(globalSaveDirectory.path().append(saveFolderName));

    QString imageSavePath, repositoryName, imageAndItsRepositoryName, groupName;

    for(int unsigned image_index = 0 ; (int) image_index < pathToImages.size() ; image_index++)
    {
        QImage qImage = loadImageFromPath(pathToImages.at(image_index));

        for(ImageTransformationWidget *imageTransformationWidget : imageTransformationWidgetList)
        {
            if(imageTransformationWidget->isActivated)
            {
                qImage = imageTransformationWidget->imageTransformation->applyImageTransformation(qImage);
            }
        }

        imageAndItsRepositoryName = pathToImages[image_index].section("/", -4);
        groupName = imageAndItsRepositoryName.left(imageAndItsRepositoryName.indexOf(QChar('/')));
        imageAndItsRepositoryName = imageAndItsRepositoryName.right(imageAndItsRepositoryName.length() - imageAndItsRepositoryName.indexOf(QChar('/')) - 1);
        std::replace(imageAndItsRepositoryName.begin(), imageAndItsRepositoryName.end(), '/', '_');
        QDir imageSaveDirectory(globalSaveDirectory.path().append("/" + groupName));

        if(!imageSaveDirectory.exists())
        {
            imageSaveDirectory.mkpath(imageSaveDirectory.path());
        }

        imageSavePath = imageSaveDirectory.path() + "/" + imageAndItsRepositoryName;
        if(!qImage.save(imageSavePath))
        {
            std::cout << "save error for file: " << imageSavePath.toUtf8().constData() << "\n" << std::endl;
        }
    }
    return true;
}
