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

#ifndef APPLICATION_VIEWER_H
#define APPLICATION_VIEWER_H

#include "classification_training_tab.h"
#include "preprocessing_tab.h"
#include "result_tab.h"
#include "data_augmentation_tab.h"

#include <iostream>

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMessageBox>

class ApplicationViewer : public QMainWindow
{
    Q_OBJECT
    public:
        ApplicationViewer(QWidget * parent = 0);
        ~ApplicationViewer();
    
    private:
        QVBoxLayout *mainLayout;
        QWidget *mainWidget;
        QTabWidget *tabWidget;
        DataHandler *preprocessingDataHandler;
        DataHandler *dataAugmentationDataHandler;

        PreprocessingTab *preprocessingTab;
        DataAugmentationTab *dataAugmentationTab;
        ClassificationTrainingTab *classificationTrainingTab;
        ResultTab *resultTab;

        void addSettingMenu(ApplicationViewer *applicationViewer);
        void addPreprocessingTab(QTabWidget *mainTabWidget);
        void addDataAugmentationTab(QTabWidget *mainTabWidget);
        void addClassificationTrainingTab(QTabWidget *mainTabWidget);
        void addResultTab(QTabWidget *mainTabWidget);

        void updateDataHandlers();

        void handleOpenImageSelectionDataHandler();
        void handleOpenLymeDatabaseDataHandler();
};
#endif // APPLICATION_VIEWER_H
