#include "result_thread.h"

ResultThread::ResultThread(QString pathToPredictionFile, QString pathToModel, QString pathToImage, QString pathToLabels)
{
    this->pathToPredictionFile = pathToPredictionFile;
    this->pathToModel = pathToModel;
    this->pathToImage = pathToImage;
    this->pathToLabels = pathToLabels;
}

void ResultThread::run()
{
    QProcess process;
    process.setStandardOutputFile("outputResult.txt", QIODevice::ReadWrite);
    process.setStandardErrorFile("errorResult.txt", QIODevice::ReadWrite);
    process.start("python3" ,{this->pathToPredictionFile, this->pathToModel, this->pathToImage, this->pathToLabels});
    process.waitForStarted();
    process.waitForFinished(-1);
}