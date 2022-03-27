//     PFE_Classification --- Generic classification software
//     Copyright © <2022> Florian Dayre <florian.dayre33850@gmail.com>
//     Copyright © <2022> Élodie Gaudry <elodie.gaudry@etu.u-bordeaux.fr>
//     Copyright © <2022> Hugo Lecomte <hugolecomte932@protonmail.com>
//     Copyright © <2022> Hugo Trarieux <htrarieux@gmail.com>

//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
    this->dataAugmentationDataHandler->pathToImages = this->preprocessingDataHandler->pathToImages;

    this->preprocessingTab->handleNewDataHandler(this->preprocessingDataHandler);
    this->dataAugmentationTab->handleNewDataHandler(this->dataAugmentationDataHandler);
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
