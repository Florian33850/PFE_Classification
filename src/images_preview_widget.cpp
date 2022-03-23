#include "images_preview_widget.h"

ImagesPreviewWidget::ImagesPreviewWidget(std::vector<ImageLabel*> *imagePreviewList, ImageTransformationViewer *imageTransformationViewer){
    this->mainLayout = new QGridLayout();
    this->mainLayout->setSpacing(IMAGES_PREVIEW_MAIN_LAYOUT_SPACING);
    this->mainLayout->setMargin(IMAGES_PREVIEW_MAIN_LAYOUT_MARGIN);

    this->imagesLayout = new QGridLayout();
    this->mainLayout->addLayout(imagesLayout, ROW_IMAGES_PREVIEW_IMAGES_LAYOUT, COLUMN_IMAGES_PREVIEW_IMAGES_LAYOUT,
                                            ROW_SPAN_IMAGES_PREVIEW_IMAGES_LAYOUT, COLUMN_SPAN_IMAGES_PREVIEW_IMAGES_LAYOUT);

    this->imageTransformationViewer = imageTransformationViewer;
    this->imagePreviewList = imagePreviewList;
    this->dataHandler = dataHandler;
    this->setLayout(this->mainLayout);
}

void ImagesPreviewWidget::display(DataHandler *dataHandler)
{
    this->dataHandler = dataHandler;
    clearLayout(this->imagesLayout);
    displayDataBasePreview();
    addPreviousPreviewButton();
    addNextPreviewButton();
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
    this->mainLayout->addWidget(previousDataBasePreview, ROW_IMAGES_PREVIEW_PREVIOUS_BUTTON, COLUMN_IMAGES_PREVIEW_PREVIOUS_BUTTON,
                                                        ROW_SPAN_IMAGES_PREVIEW_PREVIOUS_BUTTON, COLUMN_SPAN_IMAGES_PREVIEW_PREVIOUS_BUTTON);
}

void ImagesPreviewWidget::addNextPreviewButton()
{
    QPushButton *nextDataBasePreview = new QPushButton("Next");
    connect(nextDataBasePreview, &QPushButton::released, this, &ImagesPreviewWidget::handleLoadNextPreviewButton);
    this->mainLayout->addWidget(nextDataBasePreview, ROW_IMAGES_PREVIEW_NEXT_BUTTON, COLUMN_IMAGES_PREVIEW_NEXT_BUTTON,
                                                    ROW_SPAN_IMAGES_PREVIEW_NEXT_BUTTON, COLUMN_SPAN_IMAGES_PREVIEW_NEXT_BUTTON);
}

void ImagesPreviewWidget::reloadPreview()
{
    this->dataHandler->reloadPreview();
    clearLayout(this->imagesLayout);
    displayDataBasePreview();
}

void ImagesPreviewWidget::handleLoadNextPreviewButton()
{
    if(this->dataHandler->loadNextPreview())
    {
        clearLayout(this->imagesLayout);
        this->imageTransformationViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }    
}

void ImagesPreviewWidget::handleLoadPreviousPreviewButton()
{
    if(this->dataHandler->loadPreviousPreview())
    {
        clearLayout(this->imagesLayout);
        this->imageTransformationViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }
}