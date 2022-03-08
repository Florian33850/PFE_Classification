#ifndef RESULT_THREAD_H
#define RESULT_THREAD_H

#include <QProcess>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore>

class ResultThread : public QThread
{
    Q_OBJECT
    public:
        ResultThread(QString pathToPredictionFile, QString pathToModel, QString pathToImage, QString pathToLabels);
        
        void run();
    
    private:
        QString pathToPredictionFile;
        QString pathToModel;
        QString pathToImage;
        QString pathToLabels; 
};
#endif // RESULT_THREAD_H