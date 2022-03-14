#include <gtest/gtest.h>
#define private public
#include "../src/result_thread.h"

TEST(InstantiationTest, TestIfInstantiationOfResultThreadIsNotNull) {
    QString pathToPredictionFile = "";
    QString pathToModel = "";
    QString pathToImage = "";
    QString pathToLabels = "";
    ResultThread *resultThread = new ResultThread(pathToPredictionFile, pathToModel, pathToImage, pathToLabels);
    ASSERT_TRUE(resultThread != NULL);
}

TEST(NotRunningBeforeTest, TestIfQProcessOfResultThreadNotRunningBeforeRunFunction) {
    QString pathToPredictionFile = "";
    QString pathToModel = "";
    QString pathToImage = "";
    QString pathToLabels = "";
    ResultThread *resultThread = new ResultThread(pathToPredictionFile, pathToModel, pathToImage, pathToLabels);
    ASSERT_TRUE(resultThread->process.state() == QProcess::NotRunning);
}

TEST(NotRunningAfterTest, TestIfQProcessOfResultThreadNotRunningAfterRunFunction) {
    QString pathToPredictionFile = "";
    QString pathToModel = "";
    QString pathToImage = "";
    QString pathToLabels = "";
    ResultThread *resultThread = new ResultThread(pathToPredictionFile, pathToModel, pathToImage, pathToLabels);
    resultThread->run();
    ASSERT_TRUE(resultThread->process.state() == QProcess::NotRunning);
}