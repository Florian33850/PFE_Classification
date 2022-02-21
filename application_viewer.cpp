#include "application_viewer.h"

ApplicationViewer::ApplicationViewer(QWidget *parent)
  : QMainWindow(parent){
  
  settingMenu(this);
  setWindowTitle(tr("Application"));

  mainWidget = new QWidget();
  setCentralWidget(mainWidget);
  mainLayout = new QVBoxLayout;
  mainWidget->setLayout(mainLayout);

  tabWidget = new QTabWidget();
  tabWidget->addTab(new PreprocessingTab(), tr("Preprocessing"));
  tabWidget->addTab(new ClassificationTrainingTab(), tr("Classification Training"));
  tabWidget->addTab(new ResultTab(), tr("Result"));
  mainLayout->addWidget(tabWidget);
}

ApplicationViewer::~ApplicationViewer() {}

void ApplicationViewer::settingMenu(ApplicationViewer *applicationViewer)
{
  QMenu *fileMenu = menuBar()->addMenu("&File");
  QAction *helpAction = menuBar()->addAction("&Help");
}