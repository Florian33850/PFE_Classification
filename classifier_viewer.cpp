#include "classifier_viewer.h"

#include <iostream>

#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>

ClassifierViewer::ClassifierViewer(QWidget *parent)
  : QMainWindow(parent){
  
  settingMenu(this);

  QWidget *widget = new QWidget();
  setCentralWidget(widget);
  QTabWidget *tabWidget = new QTabWidget();
  tabWidget->addTab(new DataloaderTab(), tr("Dataloader"));
  tabWidget->addTab(new ClassificationTrainingTab(), tr("Classification Training"));
    tabWidget->addTab(new ExperimentationTab(), tr("Experimentation"));
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(tabWidget);
  widget->setLayout(mainLayout);
  setWindowTitle(tr("Classifier"));
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

    QPushButton *loadDataBaseButton = new QPushButton("Load database");
    connect(loadDataBaseButton, &QPushButton::released, this, &DataloaderTab::loadDataBaseFiles);
    mainLayout->addWidget(loadDataBaseButton);    
    setLayout(mainLayout);
}

void DataloaderTab::loadDataBaseFiles()
{
  QStringList pathToImages = QFileDialog::getOpenFileNames(this, "Select files to open", "JPG (*.jpg)");
  if (pathToImages.size() == 0){
    printf("loading problem\n");
    return;
  }
  imgCollection->setPathToImages(pathToImages);
  imgCollection->loadCollection();
    displayDataBaseImages();
}

void DataloaderTab::displayDataBaseImages()
{
    for(int img_number=0; img_number < imgCollection->getDataBaseSize(); img_number++)
    {
        mainLayout->addWidget(imgCollection->getImageFromDataBase(img_number));
    }
}

ClassificationTrainingTab::ClassificationTrainingTab(QWidget *parent)
    : QWidget(parent)
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
