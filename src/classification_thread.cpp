#include "classification_thread.h"

ClassificationThread::ClassificationThread(QString pathToClassifier, QString pathToTrainingSet, QString pathToTestingSet)
{
    this->pathToClassifier = pathToClassifier;
    this->pathToTrainingSet = pathToTrainingSet;
    this->pathToTestingSet = pathToTestingSet;
}

ClassificationThread::ClassificationThread(QString pathToClassifier)
{
    this->pathToClassifier = pathToClassifier;
}

void ClassificationThread::run()
{
    QProcess process;
    process.setStandardOutputFile("outputTraining.txt", QIODevice::ReadWrite);
    process.setStandardErrorFile("errorTraining.txt", QIODevice::ReadWrite);

    process.start("python3" ,{this->pathToClassifier, this->pathToTrainingSet, this->pathToTestingSet});
    process.waitForStarted();
    process.waitForFinished(-1);
}