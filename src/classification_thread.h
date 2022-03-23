#ifndef CLASSIFICATION_THREAD_H
#define CLASSIFICATION_THREAD_H

#include "constants.h"

#include <QProcess>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore>

#define NO_TIME_OUT -1
#define COMMAND_RUNNER "python3"

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