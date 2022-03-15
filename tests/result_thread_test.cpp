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

TEST(FilesExistTest, TestIfOutputFilesOfResultThreadAreCreatedAfterRunFunction)
{
    QString pathToPredictionFile = "";
    QString pathToModel = "";
    QString pathToImage = "";
    QString pathToLabels = "";
    ResultThread *resultThread = new ResultThread(pathToPredictionFile, pathToModel, pathToImage, pathToLabels);
    resultThread->run();
    bool isCreated = true;
    FILE *file1, *file2;
    if((file1 = fopen("outputResult.txt", "r")) && (file2 = fopen("errorResult.txt", "r")))
    {
      fclose(file1);
      fclose(file2);
      isCreated = true;
    }
    else
    {
        isCreated = false;
    }
    std::remove("outputResult.txt");
    std::remove("errorResult.txt");
    EXPECT_TRUE(isCreated == true);
}