#ifndef CLASSIFICATION_THREAD_H
#define CLASSIFICATION_THREAD_H

#include <QProcess>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore>

class ClassificationThread : public QThread
{
    Q_OBJECT
    public:
        ClassificationThread(QString pathToClassifier, QString pathToTrainingSet, QString pathToTestingSet, QString numberOfEpochs, QString heightOfImages, QString widthOfImages);

        void run();
    
    private:
        QString pathToClassifier;
        QString pathToTrainingSet; 
        QString pathToTestingSet;
        QString numberOfEpochs;
        QString heightOfImages;
        QString widthOfImages;
};
#endif // CLASSIFICATION_THREAD_H