#include "classifier_viewer.h"

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
  tabWidget->addTab(new ResultTab(), tr("Result"));
  mainLayout->addWidget(tabWidget);
}

ClassifierViewer::~ClassifierViewer() {}

void ClassifierViewer::settingMenu(ClassifierViewer *classifierViewer)
{
  QMenu *fileMenu = menuBar()->addMenu("&File");
  QAction *helpAction = menuBar()->addAction("&Help");
}