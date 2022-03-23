#include "preprocessing_tab.h"

PreprocessingTab::PreprocessingTab() : Tab()
{
    this->imagePreviewList = new std::vector<ImageLabel*>();
    this->imageTransformationViewer = new PreprocessingViewer(this->imagePreviewList, this);
    this->imagesPreviewWidget = new ImagesPreviewWidget(this->imagePreviewList, this->imageTransformationViewer);
    connect(this->imageTransformationViewer, &ImageTransformationViewer::reloadPreviewSignal, this->imagesPreviewWidget, &ImagesPreviewWidget::reloadPreview);
    this->mainLayout->addWidget(this->imagesPreviewWidget, ROW_PREPROCESSING_TAB_PREVIEW_WIDGET, COLUMN_PREPROCESSING_TAB_PREVIEW_WIDGET,
                                                            ROW_SPAN_PREPROCESSING_TAB_PREVIEW_WIDGET, COLUMN_SPAN_PREPROCESSING_TAB_PREVIEW_WIDGET);
    this->mainLayout->addWidget(this->imageTransformationViewer, ROW_PREPROCESSING_TAB_TRANSFORMATION_VIEWER, COLUMN_PREPROCESSING_TAB_TRANSFORMATION_VIEWER,
                                                                ROW_SPAN_PREPROCESSING_TAB_TRANSFORMATION_VIEWER, COLUMN_SPAN_PREPROCESSING_TAB_TRANSFORMATION_VIEWER);
}

void PreprocessingTab::addSaveButton()
{
    QPushButton *saveImagesButton = new QPushButton("&Save");
    connect(saveImagesButton, &QPushButton::released, [=](){this->handleSaveButton("/savedData/Preprocessing");});
    this->mainLayout->addWidget(saveImagesButton, ROW_PREPROCESSING_TAB_SAVE_BUTTON, COLUMN_PREPROCESSING_TAB_SAVE_BUTTON,
                                                    ROW_SPAN_PREPROCESSING_TAB_SAVE_BUTTON, COLUMN_SPAN_PREPROCESSING_TAB_SAVE_BUTTON);
}

void PreprocessingTab::handleNewDataHandler(DataHandler *dataHandler)
{
    this->dataHandler = dataHandler;
    this->dataHandler->loadNextPreview();
    this->addSaveButton();
    this->imagesPreviewWidget->display(this->dataHandler);
}