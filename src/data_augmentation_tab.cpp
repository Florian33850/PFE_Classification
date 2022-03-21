#include "data_augmentation_tab.h"

DataAugmentationTab::DataAugmentationTab() : Tab()
{
    this->imagePreviewList = new std::vector<ImageLabel*>();
    this->imageTransformationViewer = new DataAugmentationViewer(this->imagePreviewList);
    this->imagesPreviewWidget = new ImagesPreviewWidget(this->imagePreviewList, this->imageTransformationViewer);
    connect(this->imageTransformationViewer, &ImageTransformationViewer::reloadPreviewSignal, this->imagesPreviewWidget, &ImagesPreviewWidget::reloadPreview);
    this->mainLayout->addWidget(this->imagesPreviewWidget, 0, 0, 3, 3);
    this->mainLayout->addWidget(this->imageTransformationViewer, 0, 3, 3, 1);
    addSaveButton();
}

void DataAugmentationTab::addSaveButton()
{
    QPushButton *saveImages = new QPushButton("&Save");
    connect(saveImages, &QPushButton::released, this, &DataAugmentationTab::handleSaveButton);
    this->mainLayout->addWidget(saveImages, 5, 3, 3, 1);
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

void DataAugmentationTab::handleSaveButton()
{
    this->dataHandler->saveImagesInFile(imageTransformationViewer->getImageTransformationWidgetList(), "SavedData/Data_augmentation");
}
