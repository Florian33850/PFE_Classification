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
  if (pathToImages.size() == 0)
  {
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