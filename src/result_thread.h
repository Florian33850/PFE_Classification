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
        ResultThread(QString pathToPredictionFile, QString pathToModel, QString pathToLabels, QString pathToImage);
        
        void run();
    
    private:
        QString pathToPredictionFile;
        QString pathToModel;
        QString pathToLabels; 
        QString pathToImage;
};
#endif // RESULT_THREAD_H