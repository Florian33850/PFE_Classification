#include "classifier_viewer.h"

#include <iostream>

#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>

ClassifierViewer::ClassifierViewer(QWidget *parent)
  : QMainWindow(parent){
  
  settingMenu(this);
  setWindowTitle(tr("Classifier"));

  mainWidget = new QWidget();
  setCentralWidget(mainWidget);
  mainLayout = new QVBoxLayout;
  mainWidget->setLayout(mainLayout);

  tabWidget = new QTabWidget();
  tabWidget->addTab(new DataloaderTab(), tr("Dataloader"));
  tabWidget->addTab(new ClassificationTrainingTab(), tr("Classification Training"));
  tabWidget->addTab(new ExperimentationTab(), tr("Experimentation"));
  mainLayout->addWidget(tabWidget);
}

ClassifierViewer::~ClassifierViewer() {}

void ClassifierViewer::settingMenu(ClassifierViewer *classifierViewer)
{
  QMenu *fileMenu = menuBar()->addMenu("&File");
  QAction *helpAction = menuBar()->addAction("&Help");
}

DataloaderTab::DataloaderTab(QWidget *parent)
    : QWidget(parent)
{
    imgCollection = new ImageCollection();
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QPushButton *loadDataBaseButton = new QPushButton("Load database");
    connect(loadDataBaseButton, &QPushButton::released, this, &DataloaderTab::handleLoadDataBaseButton);
    mainLayout->addWidget(loadDataBaseButton);

    maxNumberOfImageToDisplay = 10;
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
    if(imgNumber >= maxNumberOfImageToDisplay)
    {
      break;
    }
    mainLayout->addWidget(imgCollection->getImageFromDataBase(imgNumber));
  }
}

ClassificationTrainingTab::ClassificationTrainingTab(QWidget *parent): QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

ExperimentationTab::ExperimentationTab(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);
}
