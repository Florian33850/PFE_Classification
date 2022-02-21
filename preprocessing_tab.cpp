#include "preprocessing_tab.h"

PreprocessingTab::PreprocessingTab(Tab *parent)
    : Tab(parent)
{
    mainLayout = new QGridLayout();
    mainLayout->setSpacing(1);
    mainLayout->setMargin(1);
    setLayout(mainLayout);

    imageCollection = new ImageCollection();
    maximumRowsOfImages = 3;
    maximumCollumnsOfImages = 5;
    preprocessingViewer = new PreprocessingViewer(imageCollection);
    mainLayout->addWidget(preprocessingViewer, 0, 5, maximumRowsOfImages, 1);

    addLoadDataBaseButton();
}

void PreprocessingTab::addLoadDataBaseButton()
{
    QPushButton *loadDataBaseButton = new QPushButton("Load database");
    connect(loadDataBaseButton, &QPushButton::released, this, &PreprocessingTab::handleLoadDataBaseButton);
    mainLayout->addWidget(loadDataBaseButton, 0, 0, 1, 5); 
}

bool PreprocessingTab::selectDataBasePath()
{
    QStringList pathToImages = QFileDialog::getOpenFileNames(this, "Select images to open", tr("Images (*.jpg *.jpeg *.png *.tiff)"));
    if (pathToImages.size() == 0)
    {
        printf("Loading problem, cannot open selected files.\n");
        return false;
    }
    imageCollection->setPathToImages(pathToImages);
    return true;
}

void PreprocessingTab::displayDataBasePreview()
{
    int imageIndex = 0;
    int previewListSize = imageCollection->getPreviewListSize();
    for(int row=1; row<maximumRowsOfImages; row++)
    {
        for(int col=0; col<maximumCollumnsOfImages; col++)
        {
            if(imageIndex >= imageCollection->maxNumberOfImagesToLoad || imageIndex >= previewListSize)
            {
                break;
            }
            mainLayout->addWidget(imageCollection->getImageLabelFromDataBase(imageIndex), row, col);
            imageIndex++;
        }
    }
}

void PreprocessingTab::addPreviousNextButtons()
{
    QPushButton *previousDataBasePreview = new QPushButton("Prev");
    connect(previousDataBasePreview, &QPushButton::released, this, &PreprocessingTab::handleLoadPreviousPreviewButton);
    mainLayout->addWidget(previousDataBasePreview, 6, 0, 1, 1);

    QPushButton *nextDataBasePreview = new QPushButton("Next");
    connect(nextDataBasePreview, &QPushButton::released, this, &PreprocessingTab::handleLoadNextPreviewButton);
    mainLayout->addWidget(nextDataBasePreview, 6, 2, 1, 1);  
}

void PreprocessingTab::handleLoadDataBaseButton()
{
    selectDataBasePath();
    imageCollection->erasePreviewIfNotEmpty();
    imageCollection->loadPreview();
    displayDataBasePreview();
    addPreviousNextButtons();
}

void PreprocessingTab::handleLoadNextPreviewButton()
{
    imageCollection->loadPreview();
    preprocessingViewer->launchActivatedPreprocesses();
    displayDataBasePreview();
}

void PreprocessingTab::handleLoadPreviousPreviewButton()
{
    imageCollection->loadPreviousPreview();
    preprocessingViewer->launchActivatedPreprocesses();
    displayDataBasePreview();
}