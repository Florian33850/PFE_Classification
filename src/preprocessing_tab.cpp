#include "preprocessing_tab.h"

PreprocessingTab::PreprocessingTab() : Tab()
{
    this->imagePreviewList = new std::vector<ImageLabel*>();
    this->imageTransformationViewer = new PreprocessingViewer(this->imagePreviewList, this);
    this->imagesPreviewWidget = new ImagesPreviewWidget(this->imagePreviewList, this->imageTransformationViewer);
    connect(this->imageTransformationViewer, &ImageTransformationViewer::reloadPreviewSignal, this->imagesPreviewWidget, &ImagesPreviewWidget::reloadPreview);
    this->mainLayout->addWidget(this->imagesPreviewWidget, 0, 0, 3, 3);
    this->mainLayout->addWidget(this->imageTransformationViewer, 0, 3, 3, 1);
}

void PreprocessingTab::addSaveButton()
{
    QPushButton *saveImages = new QPushButton("&Save");
    connect(saveImages, &QPushButton::released, this, &PreprocessingTab::handleSaveButton);
    this->mainLayout->addWidget(saveImages, 2, 3, 1, 1);
}

void PreprocessingTab::handleNewDataHandler(DataHandler *dataHandler)
{
    this->dataHandler = dataHandler;
    this->dataHandler->loadNextPreview();
    addSaveButton();
    this->imagesPreviewWidget->display(this->dataHandler);
}

void PreprocessingTab::handleSaveButton()
{
    this->dataHandler->saveImagesInFile("Preprocessing", this->imageTransformationViewer->getImageTransformationWidgetList());
}