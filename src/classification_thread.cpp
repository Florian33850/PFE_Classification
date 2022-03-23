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
    this->process.waitForFinished(NO_TIME_OUT);
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