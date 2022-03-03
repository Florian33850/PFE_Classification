#include "result_thread.h"

ResultThread::ResultThread(QString pathToPredictionFile, QString pathToModel, QString pathToLabel, QString pathToImage)
{
    this->pathToPredictionFile = pathToPredictionFile;
    this->pathToModel = pathToModel;
    this->pathToLabels = pathToLabels;
    this->pathToImage = pathToImage;
}

void ResultThread::run()
{
    QProcess process;
    process.setStandardOutputFile("outputResult.txt", QIODevice::ReadWrite);
    process.setStandardErrorFile("errorResult.txt", QIODevice::ReadWrite);
    process.start("python3" ,{this->pathToPredictionFile, this->pathToModel, this->pathToLabels, this->pathToImage});
    process.waitForStarted();
    process.waitForFinished(-1);
}