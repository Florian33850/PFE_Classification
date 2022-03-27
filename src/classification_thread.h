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

#ifndef CLASSIFICATION_THREAD_H
#define CLASSIFICATION_THREAD_H

#include "constants.h"

#include <QProcess>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore>

class ClassificationThread : public QThread
{
    Q_OBJECT
    public:
        ClassificationThread(QString pathToClassifier, QString pathToTrainingSet, QString widthOfImages, QString heightOfImages);

        void launchClassification(QStringList arguments);
    
    protected:
        QString pathToClassifier;
        QString pathToTrainingSet; 
        QString widthOfImages;
        QString heightOfImages;
        QString commandRunner = COMMAND_RUNNER;
        QProcess process;
};

class DeepLearningThread : public ClassificationThread
{
    Q_OBJECT
    public:
        DeepLearningThread(QString pathToClassifier, QString pathToTrainingSet, QString pathToTestingSet, QString numberOfEpochs, QString widthOfImages, QString heightOfImages);

        void run();
    
    private:
        QString pathToTestingSet;
        QString numberOfEpochs;
};

class RandomForestThread : public ClassificationThread
{
    Q_OBJECT
    public:
        RandomForestThread(QString pathToClassifier, QString pathToTrainingSet, QString numberOfTrees, QString widthOfImages, QString heightOfImages);

        void run();
    
    private:
        QString numberOfTrees;
};
#endif // CLASSIFICATION_THREAD_H
