#include "classifier_viewer.h"

#include <iostream>

#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>

ClassifierViewer::ClassifierViewer(QWidget *parent)
  : QMainWindow(parent){

  settingMenu(this);
  imgCollection = new ImageCollection();
  mainLayout = new QVBoxLayout();
  mainWidget = new QWidget();
  setCentralWidget(mainWidget);
  mainWidget->setLayout(mainLayout);
}

ClassifierViewer::~ClassifierViewer() {}

void ClassifierViewer::settingMenu(ClassifierViewer *classifierViewer)
{
  QMenu *fileMenu = menuBar()->addMenu("&File");
  openDataBaseButton(fileMenu);
  QAction *helpAction = menuBar()->addAction("&Help");
}

void ClassifierViewer::openDataBaseButton(QMenu *menu /*=NULL*/)
{
  QAction *openDataBaseAction = menu->addAction("&Open database");
  QObject::connect(openDataBaseAction, SIGNAL(triggered()), this,
                   SLOT(selectDataBaseFiles()));
}

void ClassifierViewer::selectDataBaseFiles()
{
  QStringList pathToImages = QFileDialog::getOpenFileNames(this, "Select files to open", "JPG (*.jpg)");
  if (pathToImages.size() == 0){
    printf("loading problem\n");
    return;
  }
  imgCollection->loadCollection(pathToImages);
  mainLayout->addWidget(imgCollection->imgLabel);
}