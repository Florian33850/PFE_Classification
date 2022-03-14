#include "images_preview_widget.h"

ImagesPreviewWidget::ImagesPreviewWidget(std::vector<ImageLabel*> *imagePreviewList, ImageTransformationViewer *imageTransformationViewer){
    this->mainLayout = new QGridLayout();
    this->mainLayout->setSpacing(1);
    this->mainLayout->setMargin(1);

    this->imagesLayout = new QGridLayout();
    this->mainLayout->addLayout(imagesLayout, 0, 0, 3, 3);

    this->imageTransformationViewer = imageTransformationViewer;
    this->imagePreviewList = imagePreviewList;
    this->dataHandler = dataHandler;
    this->setLayout(this->mainLayout);
}

void ImagesPreviewWidget::display(DataHandler *dataHandler)
{
    this->dataHandler = dataHandler;
    clearImagesLayout();
    displayDataBasePreview();
    addPreviousPreviewButton();
    addNextPreviewButton();
}

void ImagesPreviewWidget::clearImagesLayout()
{
    QLayoutItem *item;
    while ((item = imagesLayout->takeAt(0)) != 0)
    {
        imagesLayout->removeItem(item);
        delete item->widget();
        delete item;
    }
}

void ImagesPreviewWidget::displayDataBasePreview()
{
    int imageIndex = 0;
    int previewListSize = imagePreviewList->size();
    for(int row = 0; row < IMAGES_PREVIEW_MAXIMUM_ROWS; row++)
    {
        for(int col = 0; col < IMAGES_PREVIEW_MAXIMUM_COLLUMNS; col++)
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

void ImagesPreviewWidget::addPreviousPreviewButton()
{
    QPushButton *previousDataBasePreview = new QPushButton("Prev");
    connect(previousDataBasePreview, &QPushButton::released, this, &ImagesPreviewWidget::handleLoadPreviousPreviewButton);
    this->mainLayout->addWidget(previousDataBasePreview, 3, 0, 1, 1);
}

void ImagesPreviewWidget::addNextPreviewButton()
{
    QPushButton *nextDataBasePreview = new QPushButton("Next");
    connect(nextDataBasePreview, &QPushButton::released, this, &ImagesPreviewWidget::handleLoadNextPreviewButton);
    this->mainLayout->addWidget(nextDataBasePreview, 3, 2, 1, 1);
}

void ImagesPreviewWidget::reloadPreview()
{
    this->dataHandler->reloadPreview();
    clearImagesLayout();
    displayDataBasePreview();
}

void ImagesPreviewWidget::handleLoadNextPreviewButton()
{
    if(this->dataHandler->loadNextPreview())
    {
        clearImagesLayout();
        this->imageTransformationViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }    
}

void ImagesPreviewWidget::handleLoadPreviousPreviewButton()
{
    if(this->dataHandler->loadPreviousPreview())
    {
        clearImagesLayout();
        this->imageTransformationViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }
}