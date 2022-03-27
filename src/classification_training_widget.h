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

#ifndef CLASSIFICATION_TRAINING_WIDGET_H
#define CLASSIFICATION_TRAINING_WIDGET_H

#include "classification_thread.h"
#include "constants.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QLabel>
#include <QScrollArea>
#include <QIntValidator>

class ClassificationTrainingWidget : public QWidget
{
    Q_OBJECT
    public:
        ClassificationTrainingWidget(QVBoxLayout *parametersLayout, QVBoxLayout *trainingOutputLayout);
    
    protected:
        QVBoxLayout *parametersLayout;
        QVBoxLayout *trainingOutputLayout;

        QGroupBox *formGroupBox;
        QFormLayout *formLayout;
        QPushButton *addClassifierButton;
        QLineEdit *classifierLineEdit;
        QPushButton *addTrainingSetButton;
        QLineEdit *trainingSetLineEdit;
        QLineEdit *heightOfImagesLineEdit;
        QLineEdit *widthOfImagesLineEdit;
        QPushButton *launchTrainingClassifierButton;

        void readAndDisplayOutputTrainingFile();
        void initializeFormParameters();
        void initializeFormLayout();

        void handleWaitingClassification();
        void handleEndingClassification();

        virtual void handleLaunchTrainingClassifierButton() = 0;
};

class DeepLearningWidget : public ClassificationTrainingWidget
{
    Q_OBJECT
    public:
        DeepLearningWidget(QVBoxLayout *parametersLayout, QVBoxLayout *trainingOutputLayout);
    
    private:
        QPushButton *addTestingSetButton;
        QLineEdit *testingSetLineEdit;
        QLineEdit *numberOfEpochsLineEdit;

        void handleLaunchTrainingClassifierButton();
};

class RandomForestWidget : public ClassificationTrainingWidget
{
    Q_OBJECT
    public:
        RandomForestWidget(QVBoxLayout *parametersLayout, QVBoxLayout *trainingOutputLayout);

    private:
        QLineEdit *numberOfTreesLineEdit;

        void handleLaunchTrainingClassifierButton();
};

#endif // CLASSIFICATION_TRAINING_WIDGET_H
