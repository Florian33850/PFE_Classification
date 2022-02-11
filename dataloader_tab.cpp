#include "dataloader_tab.h"

DataloaderTab::DataloaderTab(Tab *parent)
    : Tab(parent)
{
    imgCollection = new ImageCollection();
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QPushButton *loadDataBaseButton = new QPushButton("Load database");
    connect(loadDataBaseButton, &QPushButton::released, this, &DataloaderTab::handleLoadDataBaseButton);
    mainLayout->addWidget(loadDataBaseButton);

    maxNumberOfImagesToDisplay = 10;

    mainLayout->addWidget(new PreprocessingViewer());
}

void DataloaderTab::handleLoadDataBaseButton()
{
  selectDataBasePath();
  imgCollection->eraseCollectionIfNotEmpty();
  imgCollection->loadCollection();
  displayDataBaseImages();
}

bool DataloaderTab::selectDataBasePath()
{
  QStringList pathToImages = QFileDialog::getOpenFileNames(this, "Select images to open", tr("Images (*.jpg *.jpeg *.png *.tiff)"));
  if (pathToImages.size() == 0)
  {
    printf("Loading problem, cannot open selected files.\n");
    return false;
  }
  imgCollection->setPathToImages(pathToImages);
  return true;
}

void DataloaderTab::displayDataBaseImages()
{   
  for(int imgNumber=0; imgNumber < imgCollection->getDataBaseSize(); imgNumber++)
  {
    if(imgNumber >= maxNumberOfImagesToDisplay)
    {
      break;
    }
    mainLayout->addWidget(imgCollection->getImageLabelFromDataBase(imgNumber));
  }
}