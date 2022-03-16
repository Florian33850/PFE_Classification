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
    this->mainLayout->addWidget(saveImages, 3, 3, 1, 1);
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
    QVector<QImage> ok;
    std::cout << "image preview size : " << imagePreviewList->size() << std::endl;
    for(int i = 0; i < imagePreviewList->size() ; i++)
    {
        ok.append(imagePreviewList->at(i)->getQImage());
    }
    //this->dataHandler->saveImagesInFile("Preprocessing", this->preprocessingViewer->imagesToSave);
    this->dataHandler->saveImagesInFile("Preprocessing", ok);
}