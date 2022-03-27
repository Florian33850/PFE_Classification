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

#include "classification_thread.h"

ClassificationThread::ClassificationThread(QString pathToClassifier, QString pathToTrainingSet, QString widthOfImages, QString heightOfImages)
{
    this->pathToClassifier = pathToClassifier;
    this->pathToTrainingSet = pathToTrainingSet;
    this->widthOfImages = widthOfImages;
    this->heightOfImages = heightOfImages;
}

void ClassificationThread::launchClassification(QStringList arguments)
{
    
    this->process.setStandardOutputFile(OUTPUT_TRAINING_FILE_NAME, QIODevice::ReadWrite);
    this->process.setStandardErrorFile(ERROR_OUTPUT_TRAINING_FILE_NAME, QIODevice::ReadWrite);
    this->process.start(this->commandRunner ,arguments);
    this->process.waitForStarted();
    this->process.waitForFinished(QPROCESS_NO_TIME_OUT);
}

DeepLearningThread::DeepLearningThread(QString pathToClassifier, QString pathToTrainingSet, QString pathToTestingSet, QString numberOfEpochs, QString widthOfImages, QString heightOfImages)
    : ClassificationThread(pathToClassifier, pathToTrainingSet, widthOfImages, heightOfImages)
{
    this->pathToTestingSet = pathToTestingSet;
    this->numberOfEpochs = numberOfEpochs;
}

void DeepLearningThread::run()
{
    QStringList arguments = {this->pathToClassifier, this->pathToTrainingSet, this->pathToTestingSet, this->numberOfEpochs, this->widthOfImages, this->heightOfImages};
    this->launchClassification(arguments);
}

RandomForestThread::RandomForestThread(QString pathToClassifier, QString pathToTrainingSet, QString numberOfTrees, QString widthOfImages, QString heightOfImages)
    : ClassificationThread(pathToClassifier, pathToTrainingSet, widthOfImages, heightOfImages)
{
    this->numberOfTrees = numberOfTrees;
}

void RandomForestThread::run()
{
    QStringList arguments = {this->pathToClassifier, this->pathToTrainingSet, this->numberOfTrees, this->widthOfImages, this->heightOfImages};
    this->launchClassification(arguments);
}
