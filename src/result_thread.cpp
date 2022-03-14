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
    this->process.setStandardOutputFile("outputResult.txt", QIODevice::ReadWrite);
    this->process.setStandardErrorFile("errorResult.txt", QIODevice::ReadWrite);
    this->process.start("python3" ,{this->pathToPredictionFile, this->pathToModel, this->pathToImage, this->pathToLabels});
    this->process.waitForStarted();
    this->process.waitForFinished(-1);
}