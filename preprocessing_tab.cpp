#include "preprocessing_tab.h"

PreprocessingTab::PreprocessingTab(Tab *parent)
    : Tab(parent)
{
    this->imagePreviewList = new std::vector<ImageLabel*>();
    this->imageTransformationViewer = new PreprocessingViewer(this->imagePreviewList, this);
    this->imagesPreviewWidget = new ImagesPreviewWidget(this->imagePreviewList, this->imageTransformationViewer);
    connect(this->imageTransformationViewer, &ImageTransformationViewer::reloadPreviewSignal, this->imagesPreviewWidget, &ImagesPreviewWidget::reloadPreview);
    this->mainLayout->addWidget(this->imagesPreviewWidget, 0, 0, 3, 3);
    this->mainLayout->addWidget(this->imageTransformationViewer, 0, 3, 3, 1);
}

void PreprocessingTab::handleNewDataHandler(DataHandler *dataHandler)
{
    this->dataHandler = dataHandler;
    this->dataHandler->loadNextPreview();
    this->imagesPreviewWidget->display(this->dataHandler);
}