#include "preprocessing_tab.h"

PreprocessingTab::PreprocessingTab(Tab *parent)
    : Tab(parent)
{
    this->mainLayout = new QGridLayout();
    this->mainLayout->setSpacing(1);
    this->mainLayout->setMargin(1);

    imagesPreviewLayout = new QGridLayout();
    mainLayout->addLayout(imagesPreviewLayout, 0, 0, 3, 3);
    setLayout(mainLayout);

    this->maximumRowsOfPreviewImages = 3;
    this->maximumCollumnsOfPreviewImages = 5;
    this->imagePreviewList = new std::vector<ImageLabel*>();
    this->preprocessingViewer = new PreprocessingViewer(this->imagePreviewList);
    this->mainLayout->addWidget(preprocessingViewer, 0, 3, 4, 1);
}

void PreprocessingTab::displayDataBasePreview()
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
            this->imagesPreviewLayout->addWidget(this->imagePreviewList->at(imageIndex), row, col);
            imageIndex++;
        }
    }
}

void PreprocessingTab::addPreviousPreviewButton()
{
    QPushButton *previousDataBasePreview = new QPushButton("Prev");
    connect(previousDataBasePreview, &QPushButton::released, this, &PreprocessingTab::handleLoadPreviousPreviewButton);
    this->mainLayout->addWidget(previousDataBasePreview, 3, 0, 1, 1);
}

void PreprocessingTab::addNextPreviewButton()
{
    QPushButton *nextDataBasePreview = new QPushButton("Next");
    connect(nextDataBasePreview, &QPushButton::released, this, &PreprocessingTab::handleLoadNextPreviewButton);
    this->mainLayout->addWidget(nextDataBasePreview, 3, 1, 1, 1);
}

void PreprocessingTab::addSaveButton()
{
    QPushButton *saveImages = new QPushButton("&Save");
    connect(saveImages, &QPushButton::released, this, &PreprocessingTab::handleSaveButton);
    this->mainLayout->addWidget(saveImages, 3, 3, 1, 1);
}

void PreprocessingTab::handleLoadDataBase()
{
    this->dataHandler->selectDataBasePath();
    this->dataHandler->loadPreview();
    clearLayout(this->imagesPreviewLayout);
    displayDataBasePreview();
    addPreviousPreviewButton();
    addNextPreviewButton();
    addSaveButton();
    std::cout << preprocessingViewer->imagesToSave.size() << std::endl;
}

void PreprocessingTab::handleLoadNextPreviewButton()
{
    if(this->dataHandler->loadPreview())
    {
        clearLayout(this->imagesPreviewLayout);
        this->preprocessingViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }
    
}

void PreprocessingTab::handleLoadPreviousPreviewButton()
{
    if(this->dataHandler->loadPreviousPreview())
    {
        clearLayout(this->imagesPreviewLayout);
        this->preprocessingViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }
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