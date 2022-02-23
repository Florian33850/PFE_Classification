#include "result_thread.h"

ResultThread::ResultThread(QString pathToPredictionFile, QString pathToModel, QString pathToImage)
{
    this->pathToPredictionFile = pathToPredictionFile;
    this->pathToModel = pathToModel;
    this->pathToImage = pathToImage;
}

void ResultThread::run()
{
    QProcess process;
    process.setStandardOutputFile("../data/output/outputResult.txt", QIODevice::ReadWrite);
    process.setStandardErrorFile("../data/output/errorResult.txt", QIODevice::ReadWrite);
    process.start("python3" ,{this->pathToPredictionFile, this->pathToModel, this->pathToImage});
}