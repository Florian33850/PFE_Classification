#include "data_augmentation_tab.h"

DataAugmentationTab::DataAugmentationTab(Tab *parent)
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
    this->imagePreviewList = new std::vector<ImageLabel*>();
}

void DataAugmentationTab::clearImagesLayout()
{
    QLayoutItem *item;
    while ((item = imagesLayout->takeAt(0)) != 0)
    {
        imagesLayout->removeItem(item);
        delete item->widget();
        delete item;
    }
}

void DataAugmentationTab::displayDataBasePreview()
{
    int imageIndex = 0;
    int previewListSize = imagePreviewList->size();
    for(int row = 0; row < maximumRowsOfPreviewImages; row++)
    {
        for(int col = 0; col < maximumCollumnsOfPreviewImages; col++)
        {
            if(imageIndex >= this->dataHandler->maxNumberOfImagesToLoad || imageIndex >= previewListSize)
            {
                break;
            }
            this->imagesLayout->addWidget(this->imagePreviewList->at(imageIndex), row, col);
            imageIndex++;
        }
    }
}

void DataAugmentationTab::addPreviousPreviewButton()
{
    QPushButton *previousDataBasePreview = new QPushButton("Prev");
    connect(previousDataBasePreview, &QPushButton::released, this, &DataAugmentationTab::handleLoadPreviousPreviewButton);
    this->mainLayout->addWidget(previousDataBasePreview, 3, 0, 1, 1);
}

void DataAugmentationTab::addNextPreviewButton()
{
    QPushButton *nextDataBasePreview = new QPushButton("Next");
    connect(nextDataBasePreview, &QPushButton::released, this, &DataAugmentationTab::handleLoadNextPreviewButton);
    this->mainLayout->addWidget(nextDataBasePreview, 3, 2, 1, 1);
}

void DataAugmentationTab::handleLoadDataBase()
{
    this->dataHandler->selectDataBasePath();
    this->dataHandler->loadPreview();
    clearImagesLayout();
    displayDataBasePreview();
    addPreviousPreviewButton();
    addNextPreviewButton();
}

void DataAugmentationTab::handleLoadNextPreviewButton()
{
    if(this->dataHandler->loadPreview())
    {
        clearImagesLayout();
        //this->preprocessingViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }
    
}

void DataAugmentationTab::handleLoadPreviousPreviewButton()
{
    if(this->dataHandler->loadPreviousPreview())
    {
        clearImagesLayout();
        //this->preprocessingViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }
}