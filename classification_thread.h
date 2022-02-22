#ifndef CLASSIFICATION_THREAD_H
#define CLASSIFICATION_THREAD_H

#include <iostream>

#include <QProcess>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore>

class ClassificationThread : public QThread
{
    Q_OBJECT
    public:
        explicit ClassificationThread(QString pathToClassifier, QString pathToTrainingSet, QString pathToTestingSet);
        explicit ClassificationThread(QString pathToClassifier);
        void run();
    
    private:
        QString pathToClassifier;
        QString pathToTrainingSet; 
        QString pathToTestingSet;
};
#endif // CLASSIFICATION_THREAD_H