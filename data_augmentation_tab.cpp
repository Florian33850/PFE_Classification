#include "data_augmentation_tab.h"

DataAugmentationTab::DataAugmentationTab(Tab *parent)
    : Tab(parent)
{
    this->imagePreviewList = new std::vector<ImageLabel*>();
    this->imageTransformationViewer = new DataAugmentationViewer(this->imagePreviewList);
    this->imagesPreviewWidget = new ImagesPreviewWidget(this->imagePreviewList, this->imageTransformationViewer);
    connect(this->imageTransformationViewer, &ImageTransformationViewer::reloadPreviewSignal, this->imagesPreviewWidget, &ImagesPreviewWidget::reloadPreview);
    this->mainLayout->addWidget(this->imagesPreviewWidget, 0, 0, 3, 3);
    this->mainLayout->addWidget(this->imageTransformationViewer, 0, 3, 3, 1);
}

void DataAugmentationTab::handleNewDataHandler(DataHandler *dataHandler)
{
    this->dataHandler = dataHandler;
    this->dataHandler->loadNextPreview();
    this->imagesPreviewWidget->display(this->dataHandler);
    addDataBaseCountDisplay();
}

void DataAugmentationTab::addDataBaseCountDisplay()
{
    this->dataBaseCountLayout = new QVBoxLayout();
    this->dataBaseCountLayout->addStretch();
    QLabel *basicImagesLabel = new QLabel();
    this->dataBaseCountLayout->insertWidget(this->dataBaseCountLayout->count() - 1, basicImagesLabel);
    this->mainLayout->addLayout(dataBaseCountLayout, 3, 0, 1, 3);

    QString numberBasicImages = QString::number(dataHandler->pathToImages.size());
    basicImagesLabel->setText("Basic images: " + numberBasicImages);
}
