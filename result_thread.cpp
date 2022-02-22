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
    process.setStandardOutputFile("../data/output/outputResult.txt", QIODevice::WriteOnly);
    process.setStandardErrorFile("../data/output/errorResult.txt", QIODevice::WriteOnly);

    std::cout << process.state() << std::endl;

    process.start("python3" ,{this->pathToPredictionFile, this->pathToModel, this->pathToImage});

    std::cout << process.state() << std::endl;

    if (!process.waitForStarted())
        printf("false1\n");

    std::cout << process.state() << std::endl;

    if (!process.waitForFinished(-1))
        printf("false2\n");

    std::cout << process.state() << std::endl;
}