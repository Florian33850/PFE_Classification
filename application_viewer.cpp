#include "application_viewer.h"

ApplicationViewer::ApplicationViewer(QWidget *parent)
  : QMainWindow(parent){
  
    addSettingMenu(this);
    setWindowTitle(tr("Application"));

    this->mainWidget = new QWidget();
    setCentralWidget(mainWidget);
    this->mainLayout = new QVBoxLayout;
    this->mainWidget->setLayout(mainLayout);

    this->tabWidget = new QTabWidget();
    addPreprocessingTab(tabWidget);
    addClassificationTrainingTab(tabWidget);
    addResultTab(tabWidget);
    this->mainLayout->addWidget(tabWidget);
}

ApplicationViewer::~ApplicationViewer() {}

void ApplicationViewer::addSettingMenu(ApplicationViewer *applicationViewer)
{
    QMenu *fileMenu = menuBar()->addMenu("&File");
    QMenu *openSubMenu = fileMenu->addMenu("&Open");
    QAction *openImageSelection = openSubMenu->addAction("&Image selection");
    QObject::connect(openImageSelection, &QAction::triggered, this, &ApplicationViewer::handleOpenImageSelectionDataLoader);
    QAction *helpAction = menuBar()->addAction("&Help");
}

void ApplicationViewer::addPreprocessingTab(QTabWidget *mainTabWidget)
{
    preprocessingTab = new PreprocessingTab();
    mainTabWidget->addTab(preprocessingTab, tr("Preprocessing"));
}

void ApplicationViewer::addClassificationTrainingTab(QTabWidget *mainTabWidget)
{
    classificationTrainingTab = new ClassificationTrainingTab();
    mainTabWidget->addTab(classificationTrainingTab, tr("Classification Training"));
}

void ApplicationViewer::addResultTab(QTabWidget *mainTabWidget)
{
    resultTab = new ResultTab();
    mainTabWidget->addTab(resultTab, tr("Result"));
}

void ApplicationViewer::handleOpenImageSelectionDataLoader()
{
    this->dataLoader = new ImageSelectionLoader(mainWidget, preprocessingTab->imageCollection);
    this->preprocessingTab->dataLoader = this->dataLoader;
    this->preprocessingTab->handleLoadDataBase();
}