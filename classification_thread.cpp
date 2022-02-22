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
    process.setStandardOutputFile("../data/output/outputTraining.txt", QIODevice::WriteOnly);
    process.setStandardErrorFile("../data/output/errorTraining.txt", QIODevice::WriteOnly);

    std::cout << process.state() << std::endl;

    process.start("python3" ,{this->pathToClassifier, this->pathToTrainingSet, this->pathToTestingSet});

    std::cout << process.state() << std::endl;

    if (!process.waitForStarted())
        printf("false1\n");

    std::cout << process.state() << std::endl;

    if (!process.waitForFinished(-1))
        printf("false2\n");

    std::cout << process.state() << std::endl;
}