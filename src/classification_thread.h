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
        ClassificationThread(QString pathToClassifier);

        void launchClassification(QString command, QStringList arguments);
    
    protected:
        QString pathToClassifier;
};
#endif // CLASSIFICATION_THREAD_H

#ifndef DEEP_LEARNING_THREAD_H
#define DEEP_LEARNING_THREAD_H

class DeepLearningThread : public ClassificationThread
{
    Q_OBJECT
    public:
        DeepLearningThread(QString pathToClassifier, QString pathToTrainingSet, QString pathToTestingSet, QString numberOfEpochs, QString widthOfImages, QString heightOfImages);

        void run();
    
    private:
        QString pathToTrainingSet; 
        QString pathToTestingSet;
        QString numberOfEpochs;
        QString widthOfImages;
        QString heightOfImages;
};
#endif // DEEP_LEARNING_THREAD_H

#ifndef RANDOM_FOREST_THREAD_H
#define RANDOM_FOREST_THREAD_H

class RandomForestThread : public ClassificationThread
{
    Q_OBJECT
    public:
        RandomForestThread(QString pathToClassifier, QString pathToTrainingSet, QString numberOfTrees, QString widthOfImages, QString heightOfImages);

        void run();
    
    private:
        QString pathToTrainingSet; 
        QString numberOfTrees;
        QString widthOfImages;
        QString heightOfImages;
};
#endif // RANDOM_FOREST_THREAD_H