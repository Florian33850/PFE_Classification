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
    process.setStandardOutputFile("../data/output/outputTraining.txt", QIODevice::ReadWrite);
    process.setStandardErrorFile("../data/output/errorTraining.txt", QIODevice::ReadWrite);
    process.start("python3" ,{this->pathToClassifier, this->pathToTrainingSet, this->pathToTestingSet});
}