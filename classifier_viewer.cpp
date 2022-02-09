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
    mainLayout = new QVBoxLayout;
    
    QPushButton *loadModelButton = new QPushButton("Load classification model");
    connect(loadModelButton, &QPushButton::released, this, &ClassificationTrainingTab::handleLoadModelButton);
    mainLayout->addWidget(loadModelButton);

    QPushButton *launchModelButton = new QPushButton("Launch classification model");
    connect(launchModelButton, &QPushButton::released, this, &ClassificationTrainingTab::handleLaunchModelButton);
    mainLayout->addWidget(launchModelButton);

    setLayout(mainLayout);
}

ExperimentationTab::ExperimentationTab(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);
}

void ClassificationTrainingTab::handleLoadModelButton()
{
    pathToModel = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION MODEL to LOAD"), "../data", tr("PT (*.pt)"));
    if (pathToModel == NULL)
    {
        printf("model loading problem\n");
        return;
    }

    pathToLabels = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION LABELS to LOAD"), "../data", tr("TXT (*.txt)"));
    if (pathToLabels == NULL)
    {
        printf("labels loading problem\n");
        return;
    }

    pathToImage = QFileDialog::getOpenFileName(this, tr("Select IMAGE to CLASSIFY"), "../data", tr("JPEG (*.jpeg, *.jpg);;PNG(*.png)"));
    if (pathToImage == NULL)
    {
        printf("image loading problem\n");
        return;
    }

    QImage qImg;
    qImg.load(pathToImage);
    ImageLabel *imageLabel = new ImageLabel();
    imageLabel->setImg(qImg);
    mainLayout->addWidget(imageLabel);

    modelLoad = true;
}

void ClassificationTrainingTab::handleLaunchModelButton()
{
    if(modelLoad == true)
    {
        QByteArray ba_pathToModel = pathToModel.toLocal8Bit();
        const char *c_pathToModel = ba_pathToModel.data();

        QByteArray ba_pathToLabels = pathToLabels.toLocal8Bit();
        const char *c_pathToLabels = ba_pathToLabels.data();

        QByteArray ba_pathToImage = pathToImage.toLocal8Bit();
        const char *c_pathToImage = ba_pathToImage.data();

        ModelRunner model(c_pathToModel, c_pathToLabels, c_pathToImage);
        model.run();
        printClassificationResults(model);
    }
}

void ClassificationTrainingTab::printClassificationResults(ModelRunner model)
{
    QLabel *label = new QLabel(this);
    label->setText("Image label : " + QString::fromUtf8(model.getLabelImageClassify().c_str()) + " Classification probability : " + QString::number(model.getProbabilityImageClassify()));
    mainLayout->addWidget(label);
}