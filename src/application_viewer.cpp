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
    addDataAugmentationTab(tabWidget);
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
    QObject::connect(openImageSelection, &QAction::triggered, this, &ApplicationViewer::handleOpenImageSelectionDataHandler);
    QAction *openLymeDatabase = openSubMenu->addAction("&Lyme Database");
    QObject::connect(openLymeDatabase, &QAction::triggered, this, &ApplicationViewer::handleOpenLymeDatabaseDataHandler);
}

void ApplicationViewer::addPreprocessingTab(QTabWidget *mainTabWidget)
{
    this->preprocessingTab = new PreprocessingTab();
    mainTabWidget->addTab(this->preprocessingTab, tr("Preprocessing"));
}

void ApplicationViewer::addDataAugmentationTab(QTabWidget *mainTabWidget)
{
    this->dataAugmentationTab = new DataAugmentationTab();
    mainTabWidget->addTab(this->dataAugmentationTab, tr("Data Augmentation"));
}

void ApplicationViewer::addClassificationTrainingTab(QTabWidget *mainTabWidget)
{
    this->classificationTrainingTab = new ClassificationTrainingTab();
    mainTabWidget->addTab(this->classificationTrainingTab, tr("Classification Training"));
}

void ApplicationViewer::addResultTab(QTabWidget *mainTabWidget)
{
    this->resultTab = new ResultTab();
    mainTabWidget->addTab(this->resultTab, tr("Result"));
}

void ApplicationViewer::updateDataHandlers()
{
    this->preprocessingDataHandler->selectDataBasePath();
    if(this->preprocessingDataHandler->pathToImages.size() !=0)
    {
    this->dataAugmentationDataHandler->pathToImages = this->preprocessingDataHandler->pathToImages;

    this->preprocessingTab->handleNewDataHandler(this->preprocessingDataHandler);
    this->dataAugmentationTab->handleNewDataHandler(this->dataAugmentationDataHandler);
    }
}

void ApplicationViewer::handleOpenImageSelectionDataHandler()
{
    this->preprocessingDataHandler = new ImageSelectionHandler(this->mainWidget, this->preprocessingTab->imagePreviewList);
    this->dataAugmentationDataHandler = new ImageSelectionHandler(this->mainWidget, this->dataAugmentationTab->imagePreviewList);
    this->updateDataHandlers();
}

void ApplicationViewer::handleOpenLymeDatabaseDataHandler()
{
    this->preprocessingDataHandler = new LymeDatabaseHandler(this->mainWidget, this->preprocessingTab->imagePreviewList);
    this->dataAugmentationDataHandler = new LymeDatabaseHandler(this->mainWidget, this->dataAugmentationTab->imagePreviewList);
    this->updateDataHandlers();
}
