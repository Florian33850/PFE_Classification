#include "dataloader_tab.h"

DataloaderTab::DataloaderTab(Tab *parent)
    : Tab(parent)
{
    mainLayout = new QGridLayout();
    mainLayout->setSpacing(1);
    mainLayout->setMargin(1);
    setLayout(mainLayout);

    imageCollection = new ImageCollection();
    maximumRowsOfImages = 3;
    maximumCollumnsOfImages = 5;
    preprocessingViewer = new PreprocessingViewer(imageCollection);
    mainLayout->addWidget(preprocessingViewer, 0, 5, maximumRowsOfImages, 1);

    addLoadDataBaseButton();
}

void DataloaderTab::addLoadDataBaseButton()
{
    QPushButton *loadDataBaseButton = new QPushButton("Load database");
    connect(loadDataBaseButton, &QPushButton::released, this, &DataloaderTab::handleLoadDataBaseButton);
    mainLayout->addWidget(loadDataBaseButton, 0, 0, 1, 5); 
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

void DataloaderTab::displayDataBasePreview()
{
    int imageIndex = 0;
    int previewListSize = imageCollection->getPreviewListSize();
    for(int row=1; row<maximumRowsOfImages; row++)
    {
        for(int col=0; col<maximumCollumnsOfImages; col++)
        {
            if(imageIndex >= imageCollection->maxNumberOfImagesToLoad || imageIndex >= previewListSize)
            {
                break;
            }
            mainLayout->addWidget(imageCollection->getImageLabelFromDataBase(imageIndex), row, col);
            imageIndex++;
        }
    }
}

void DataloaderTab::addPreviousNextButtons()
{
    QPushButton *previousDataBasePreview = new QPushButton("Prev");
    connect(previousDataBasePreview, &QPushButton::released, this, &DataloaderTab::handleLoadPreviousPreviewButton);
    mainLayout->addWidget(previousDataBasePreview, 6, 0, 1, 1);

    QPushButton *nextDataBasePreview = new QPushButton("Next");
    connect(nextDataBasePreview, &QPushButton::released, this, &DataloaderTab::handleLoadNextPreviewButton);
    mainLayout->addWidget(nextDataBasePreview, 6, 2, 1, 1);  
}

void DataloaderTab::handleLoadDataBaseButton()
{
    selectDataBasePath();
    imageCollection->erasePreviewIfNotEmpty();
    imageCollection->loadPreview();
    displayDataBasePreview();
    addPreviousNextButtons();
}

void DataloaderTab::handleLoadNextPreviewButton()
{
    imageCollection->loadPreview();
    preprocessingViewer->launchActivatedPreprocesses();
    displayDataBasePreview();
}

void DataloaderTab::handleLoadPreviousPreviewButton()
{
    imageCollection->loadPreviousPreview();
    preprocessingViewer->launchActivatedPreprocesses();
    displayDataBasePreview();
}