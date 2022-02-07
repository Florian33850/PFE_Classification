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

void ClassifierViewer::settingMenu(ClassifierViewer *classifierViewer){
  QMenu *fileMenu = menuBar()->addMenu("&File");
  QAction *openAction = fileMenu->addAction("&Open");
  QAction *helpAction = menuBar()->addAction("&Help");
}


DataloaderTab::DataloaderTab(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

ClassificationTrainingTab::ClassificationTrainingTab(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    
    QPushButton *loadModelButton = new QPushButton("Load classification model");
    connect(loadModelButton, &QPushButton::released, this, &ClassifierViewer::handleLoadModelButton);
    mainLayout->addWidget(loadModelButton);

    setLayout(mainLayout);
}

ExperimentationTab::ExperimentationTab(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);
}

void ClassifierViewer::handleLoadModelButton()
{
    QString pathToModel = QFileDialog::getOpenFileName(this, "Select files to open", "PT (*.pt)");
    if (pathToModel == NULL){
        printf("loading problem\n");
        return;
    }
    QByteArray ba = pathToModel.toLocal8Bit();
    const char *c_pathToModel = ba.data();

    QString pathToLabels = QFileDialog::getOpenFileName(this, "Select files to open", "TXT (*.txt)");
    if (pathToLabels == NULL){
        printf("loading problem\n");
        return;
    }
    ba = pathToLabels.toLocal8Bit();
    const char *c_pathToLabels = ba.data();

    QString pathToImage = QFileDialog::getOpenFileName(this, "Select files to open", "JPEG, JPG, PNG (*.jpeg, *.jpg, *.png)");
    if (pathToImage == NULL){
        printf("loading problem\n");
        return;
    }
    ba = pathToImage.toLocal8Bit();
    const char *c_pathToImage = ba.data();

    ModelRunner model = new ModelRunner();
    model.run(c_pathToModel, c_pathToLabels, c_pathToImage);

}