#include "dataloader_tab.h"

DataloaderTab::DataloaderTab(Tab *parent)
    : Tab(parent)
{
  imgCollection = new ImageCollection();
  mainLayout = new QGridLayout;
  void setLayoutParameters();
  mainLayout->setSpacing(1);
  mainLayout->setMargin(0);
  setLayout(mainLayout);

  QPushButton *loadDataBaseButton = new QPushButton("Load database");
  connect(loadDataBaseButton, &QPushButton::released, this, &DataloaderTab::handleLoadDataBaseButton);
  mainLayout->addWidget(loadDataBaseButton, 0, 0, 1, 5);

  maxNumberOfImagesToDisplay = 10;
  maxRowOfImages = 4;
  maxColOfImages = 5;
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
  int imgNumber = 0;
  int imageDataBaseSize = imgCollection->getDataBaseSize();
  for(int row=1; row<maxRowOfImages; row++)
  {
    for(int col=0; col<maxColOfImages; col++)
    {
      if(imgNumber >= maxNumberOfImagesToDisplay || imgNumber >= imageDataBaseSize)
      {
        break;
      }
      mainLayout->addWidget(imgCollection->getImageFromDataBase(imgNumber), row, col);
      imgNumber++;
    }
  }
}