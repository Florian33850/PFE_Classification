#include "dataloader_tab.h"

DataloaderTab::DataloaderTab(Tab *parent)
    : Tab(parent)
{
    imageCollection = new ImageCollection();
    mainLayout = new QGridLayout();
    mainLayout->setSpacing(1);
    mainLayout->setMargin(1);
    setLayout(mainLayout);

    QPushButton *loadDataBaseButton = new QPushButton("Load database");
    connect(loadDataBaseButton, &QPushButton::released, this, &DataloaderTab::handleLoadDataBaseButton);
    mainLayout->addWidget(loadDataBaseButton, 0, 0, 1, 5);

    maximumNumberOfImagesToDisplay = 10;
    maximumRowsOfImages = 3;
    maximumCollumnsOfImages = 5;

    mainLayout->addWidget(new PreprocessingViewer(imageCollection), 0, 5, maximumRowsOfImages, 1);
}

void DataloaderTab::handleLoadDataBaseButton()
{
    selectDataBasePath();
    imageCollection->eraseCollectionIfNotEmpty();
    imageCollection->loadCollection();
    displayDataBaseImages();
}

bool DataloaderTab::selectDataBasePath()
{
    QStringList pathToImages = QFileDialog::getOpenFileNames(this, "Select images to open", tr("Images (*.jpg *.jpeg *.png *.tiff)"));
    if (pathToImages.size() == 0)
    {
        printf("Loading problem, cannot open selected files.\n");
        return false;
    }
    imageCollection->setPathToImages(pathToImages);
    return true;
}

void DataloaderTab::displayDataBaseImages()
{
    int imageIndex = 0;
    int imageDataBaseSize = imageCollection->getDataBaseSize();
    for(int row=1; row<maximumRowsOfImages; row++)
    {
        for(int col=0; col<maximumCollumnsOfImages; col++)
        {
            if(imageIndex >= maximumNumberOfImagesToDisplay || imageIndex >= imageDataBaseSize)
            {
                break;
            }
            mainLayout->addWidget(imageCollection->getImageLabelFromDataBase(imageIndex), row, col);
            imageIndex++;
        }
    }
}

void DataloaderTab::updateWindow()
{
    
}