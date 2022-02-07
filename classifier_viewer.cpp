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
    connect(loadModelButton, &QPushButton::released, this, &ClassificationTrainingTab::handleLoadModelButton);
    mainLayout->addWidget(loadModelButton);

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
    QString pathToModel = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION MODEL to LOAD"), "../data", tr("PT (*.pt)"));
    if (pathToModel == NULL){
        printf("loading problem\n");
        return;
    }
    QByteArray ba_pathToModel = pathToModel.toLocal8Bit();
    const char *c_pathToModel = ba_pathToModel.data();

    QString pathToLabels = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION LABELS to LOAD"), "../data", tr("TXT (*.txt)"));
    if (pathToLabels == NULL){
        printf("loading problem\n");
        return;
    }
    QByteArray ba_pathToLabels = pathToLabels.toLocal8Bit();
    const char *c_pathToLabels = ba_pathToLabels.data();

    QString pathToImage = QFileDialog::getOpenFileName(this, tr("Select IMAGE to CLASSIFY"), "../data", tr("JPEG, JPG, PNG (*.jpeg, *.jpg, *.png)"));
    if (pathToImage == NULL){
        printf("loading problem\n");
        return;
    }
    QByteArray ba_pathToImage = pathToImage.toLocal8Bit();
    const char *c_pathToImage = ba_pathToImage.data();

    ModelRunner model;
    model.run(c_pathToModel, c_pathToLabels, c_pathToImage);
}