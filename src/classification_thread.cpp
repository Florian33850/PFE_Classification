#include "classification_thread.h"

ClassificationThread::ClassificationThread(QString pathToClassifier)
{
    this->pathToClassifier = pathToClassifier;
}

void ClassificationThread::launchClassification(QString command, QStringList arguments)
{
    
    this->process.setStandardOutputFile("outputTraining.txt", QIODevice::ReadWrite);
    this->process.setStandardErrorFile("errorTraining.txt", QIODevice::ReadWrite);
    this->process.start(command ,arguments);
    this->process.waitForStarted();
    this->process.waitForFinished(-1);
}

DeepLearningThread::DeepLearningThread(QString pathToClassifier, QString pathToTrainingSet, QString pathToTestingSet, QString numberOfEpochs, QString widthOfImages, QString heightOfImages)
    : ClassificationThread(pathToClassifier)
{
    this->pathToTrainingSet = pathToTrainingSet;
    this->pathToTestingSet = pathToTestingSet;
    this->numberOfEpochs = numberOfEpochs;
    this->heightOfImages = heightOfImages;
    this->widthOfImages = widthOfImages;
}

void DeepLearningThread::run()
{
    QString command = "python3";
    QStringList arguments = {this->pathToClassifier, this->pathToTrainingSet, this->pathToTestingSet, this->numberOfEpochs, this->widthOfImages, this->heightOfImages};
    this->launchClassification(command, arguments);
}

RandomForestThread::RandomForestThread(QString pathToClassifier, QString pathToTrainingSet, QString numberOfTrees, QString widthOfImages, QString heightOfImages)
: ClassificationThread(pathToClassifier)
{
    this->pathToTrainingSet = pathToTrainingSet;
    this->numberOfTrees = numberOfTrees;
    this->heightOfImages = heightOfImages;
    this->widthOfImages = widthOfImages;
}

void RandomForestThread::run()
{
    QString command = "python3";
    QStringList arguments = {this->pathToClassifier, this->pathToTrainingSet, this->numberOfTrees, this->widthOfImages, this->heightOfImages};
    this->launchClassification(command, arguments);
}