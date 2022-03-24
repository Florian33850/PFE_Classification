#include "data_augmentation_tab.h"

DataAugmentationTab::DataAugmentationTab() : Tab()
{
    this->imagePreviewList = new std::vector<ImageLabel*>();
    this->imageTransformationViewer = new DataAugmentationViewer(this->imagePreviewList);
    this->imagesPreviewWidget = new ImagesPreviewWidget(this->imagePreviewList, this->imageTransformationViewer);
    connect(this->imageTransformationViewer, &ImageTransformationViewer::reloadPreviewSignal, this->imagesPreviewWidget, &ImagesPreviewWidget::reloadPreview);
    this->mainLayout->addWidget(this->imagesPreviewWidget, ROW_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET, COLUMN_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET,
                                ROW_SPAN_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET, COLUMN_SPAN_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET);
    this->mainLayout->addWidget(this->imageTransformationViewer, ROW_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER, COLUMN_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER,
                                ROW_SPAN_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER, COLUMN_SPAN_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER);
    this->addSaveButton();
    this->addDataBaseCountDisplay();
}

void DataAugmentationTab::addSaveButton()
{
    QPushButton *saveImagesButton = new QPushButton("&Save");
    connect(saveImagesButton, &QPushButton::released, [=](){this->handleSaveButton("/savedData/Data_Augmentation");});
    this->mainLayout->addWidget(saveImagesButton, ROW_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON, COLUMN_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON,
                                ROW_SPAN_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON, COLUMN_SPAN_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON);
}

void DataAugmentationTab::handleNewDataHandler(DataHandler *dataHandler)
{
    this->dataHandler = dataHandler;
    this->dataHandler->loadNextPreview();
    this->imagesPreviewWidget->display(this->dataHandler);
    this->refreshDataBaseCountDisplay();
}

void DataAugmentationTab::addDataBaseCountDisplay()
{
    this->dataBaseCountLayout = new QVBoxLayout();
    this->originalImagesLabel = new QLabel();
    this->dataBaseCountLayout->insertWidget(this->dataBaseCountLayout->count()-1, originalImagesLabel);
    this->mainLayout->addLayout(dataBaseCountLayout, ROW_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT, COLUMN_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT,
                                ROW_SPAN_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT, COLUMN_SPAN_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT);
}

void DataAugmentationTab::refreshDataBaseCountDisplay()
{
    QString numberOriginalImages = QString::number(dataHandler->pathToImages.size());
    this->originalImagesLabel->setText("Original images: " + numberOriginalImages);
}