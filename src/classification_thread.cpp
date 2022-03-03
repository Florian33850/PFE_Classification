#include "classification_thread.h"

ClassificationThread::ClassificationThread(QString pathToClassifier, QString pathToTrainingSet, QString pathToTestingSet, QString numberOfEpochs, QString heightOfImages, QString widthOfImages)
{
    this->pathToClassifier = pathToClassifier;
    this->pathToTrainingSet = pathToTrainingSet;
    this->pathToTestingSet = pathToTestingSet;
    this->numberOfEpochs = numberOfEpochs;
    this->heightOfImages = heightOfImages;
    this->widthOfImages = widthOfImages;
}

void ClassificationThread::run()
{
    QProcess process;
    process.setStandardOutputFile("outputTraining.txt", QIODevice::ReadWrite);
    process.setStandardErrorFile("errorTraining.txt", QIODevice::ReadWrite);

    process.start("python3" ,{this->pathToClassifier, this->pathToTrainingSet, this->pathToTestingSet, this->numberOfEpochs, this->heightOfImages, this->widthOfImages});
    process.waitForStarted();
    process.waitForFinished(-1);
}