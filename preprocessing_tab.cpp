#include "preprocessing_tab.h"

PreprocessingTab::PreprocessingTab(Tab *parent)
    : Tab(parent)
{
    this->mainLayout = new QGridLayout();
    this->mainLayout->setSpacing(1);
    this->mainLayout->setMargin(1);

    imagesLayout = new QGridLayout();
    mainLayout->addLayout(imagesLayout, 0, 0, 3, 3);
    setLayout(mainLayout);

    this->maximumRowsOfPreviewImages = 3;
    this->maximumCollumnsOfPreviewImages = 5;
    this->imageCollection = new ImageCollection(); 
    this->preprocessingViewer = new PreprocessingViewer(imageCollection);
    this->mainLayout->addWidget(preprocessingViewer, 0, 3, 4, 1);
}

void PreprocessingTab::clearImagesLayout()
{
    QLayoutItem *item;
    while ((item = imagesLayout->takeAt(0)) != 0)
    {
        imagesLayout->removeItem(item);
        delete item->widget();
        delete item;
    }
}

void PreprocessingTab::displayDataBasePreview()
{
    int imageIndex = 0;
    int previewListSize = this->imageCollection->getPreviewListSize();
    for(int row = 0; row < maximumRowsOfPreviewImages; row++)
    {
        for(int col = 0; col < maximumCollumnsOfPreviewImages; col++)
        {
            if(imageIndex >= this->dataLoader->maxNumberOfImagesToLoad || imageIndex >= previewListSize)
            {
                break;
            }
            this->imagesLayout->addWidget(this->imageCollection->getImageLabelFromDataBase(imageIndex), row, col);
            imageIndex++;
        }
    }
}

void PreprocessingTab::addPreviousPreviewButton()
{
    QPushButton *previousDataBasePreview = new QPushButton("Prev");
    connect(previousDataBasePreview, &QPushButton::released, this, &PreprocessingTab::handleLoadPreviousPreviewButton);
    this->mainLayout->addWidget(previousDataBasePreview, 3, 0, 1, 1);
}

void PreprocessingTab::addNextPreviewButton()
{
    QPushButton *nextDataBasePreview = new QPushButton("Next");
    connect(nextDataBasePreview, &QPushButton::released, this, &PreprocessingTab::handleLoadNextPreviewButton);
    this->mainLayout->addWidget(nextDataBasePreview, 3, 2, 1, 1);
}

void PreprocessingTab::handleLoadDataBase()
{
    this->dataLoader->selectDataBasePath();
    this->dataLoader->loadPreview();
    clearImagesLayout();
    displayDataBasePreview();
    addPreviousPreviewButton();
    addNextPreviewButton();
}

void PreprocessingTab::handleLoadNextPreviewButton()
{
    if(this->dataLoader->loadPreview())
    {
        clearImagesLayout();
        this->preprocessingViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }
    
}

void PreprocessingTab::handleLoadPreviousPreviewButton()
{
    if(this->dataLoader->loadPreviousPreview())
    {
        clearImagesLayout();
        this->preprocessingViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }
}