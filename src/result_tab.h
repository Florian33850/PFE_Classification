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

#ifndef RESULT_TAB_H
#define RESULT_TAB_H

#include "tab.h"
#include "result_thread.h"

#include <QPushButton>
#include <QProcess>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore>
#include <QGroupBox>
#include <QFormLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QFileDialog>

class ResultTab : public Tab
{
    Q_OBJECT
    public:
        ResultTab();

    private:
        QBoxLayout *classificationParametersLayout;
        QBoxLayout *resultOutputLayout;
        QGroupBox *formGroupBox;
        QFormLayout *formLayout;
        QPushButton *addPredicitonFileButton;
        QLineEdit *predictionFileLineEdit;
        QPushButton *addModelClassifierButton;
        QLineEdit *modelClassifierLineEdit;
        QPushButton *addLabelsButton;
        QLineEdit *labelsLineEdit;
        QPushButton *addImageButton;
        QLineEdit *imageLineEdit;
        QPushButton *launchModelButton;

        void readAndDisplayOutputResultFile();

        void addClassificationParametersFormLayout();
        void initializeFormLayout();
        void initializeFormParameters();
        void addLaunchModelButton();

        void handleLaunchModelButton();
        void handleWaitingResult();
        void handleEndingResult();
};
#endif // RESULT_TAB_H
