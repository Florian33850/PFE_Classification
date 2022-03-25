#include <gtest/gtest.h>
#define private public
#define protected public
#include "../src/classification_thread.h"
#include<stdio.h>

TEST(InstantiationTest, TestIfInstantiationOfClassificationThreadIsNotNull)
{
    QString pathToClassifier = "";
    QString pathToTrainingSet = ""; 
    QString widthOfImages = "";
    QString heightOfImages = "";
    ClassificationThread *classificationThread = new ClassificationThread(pathToClassifier, pathToTrainingSet, widthOfImages, heightOfImages);
    ASSERT_TRUE(classificationThread != NULL);
}

TEST(InstantiationTest, TestIfInstantiationOfDeepLearningThreadIsNotNull)
{
    QString pathToClassifier = "";
    QString pathToTrainingSet = ""; 
    QString pathToTestingSet = ""; 
    QString numberOfEpochs = ""; 
    QString widthOfImages = "";
    QString heightOfImages = "";
    DeepLearningThread *deepLearningThread = new DeepLearningThread(pathToClassifier, pathToTrainingSet, pathToTestingSet, numberOfEpochs, widthOfImages, heightOfImages);
    ASSERT_TRUE(deepLearningThread != NULL);
}

TEST(InstantiationTest, TestIfInstantiationOfRandomForestThreadIsNotNull)
{
    QString pathToClassifier = "";
    QString pathToTrainingSet = ""; 
    QString numberOfTrees = ""; 
    QString widthOfImages = "";
    QString heightOfImages = "";
    RandomForestThread *randomForestThread = new RandomForestThread(pathToClassifier, pathToTrainingSet, numberOfTrees, widthOfImages, heightOfImages);
    ASSERT_TRUE(randomForestThread != NULL);
}

TEST(NotRunningBeforeTest, TestIfQProcessOfClassificationThreadNotRunningBeforeRunFunction)
{
    QString pathToClassifier = "";
    QString pathToTrainingSet = ""; 
    QString widthOfImages = "";
    QString heightOfImages = "";
    ClassificationThread *classificationThread = new ClassificationThread(pathToClassifier, pathToTrainingSet, widthOfImages, heightOfImages);
    ASSERT_TRUE(classificationThread->process.state() == QProcess::NotRunning);
}

TEST(NotRunningAfterTest, TestIfQProcessOfClassificationThreadNotRunningAfterRunFunction)
{
    QString pathToClassifier = "";
    QString pathToTrainingSet = ""; 
    QString widthOfImages = "";
    QString heightOfImages = "";
    ClassificationThread *classificationThread = new ClassificationThread(pathToClassifier, pathToTrainingSet, widthOfImages, heightOfImages);
    QStringList arguments = {"", ""};
    classificationThread->launchClassification(arguments);
    ASSERT_TRUE(classificationThread->process.state() == QProcess::NotRunning);
}

TEST(FilesExistTest, TestIfOutputFilesOfDeepLearningThreadAreCreatedAfterRunFunction)
{
    QString pathToClassifier = "";
    QString pathToTrainingSet = ""; 
    QString pathToTestingSet = ""; 
    QString numberOfEpochs = ""; 
    QString widthOfImages = "";
    QString heightOfImages = "";
    DeepLearningThread *deepLearningThread = new DeepLearningThread(pathToClassifier, pathToTrainingSet, pathToTestingSet, numberOfEpochs, widthOfImages, heightOfImages);
    deepLearningThread->run();
    bool isCreated = true;
    FILE *file1, *file2;
    if((file1 = fopen("outputTraining.txt", "r")) && (file2 = fopen("errorTraining.txt", "r")))
    {
      fclose(file1);
      fclose(file2);
      isCreated = true;
    }
    else
    {
        isCreated = false;
    }
    EXPECT_TRUE(isCreated == true);
    std::remove("outputTraining.txt");
    std::remove("errorTraining.txt");
}

TEST(FilesExistTest, TestIfOutputFilesOfRandomForestThreadAreCreatedAfterRunFunction)
{
    QString pathToClassifier = "";
    QString pathToTrainingSet = ""; 
    QString numberOfTrees = ""; 
    QString widthOfImages = "";
    QString heightOfImages = "";
    RandomForestThread *randomForestThread = new RandomForestThread(pathToClassifier, pathToTrainingSet, numberOfTrees, widthOfImages, heightOfImages);
    randomForestThread->run();
    bool isCreated = true;
    FILE *file1, *file2;
    if((file1 = fopen("outputTraining.txt", "r")) && (file2 = fopen("errorTraining.txt", "r")))
    {
      fclose(file1);
      fclose(file2);
      isCreated = true;
    }
    else
    {
        isCreated = false;
    }
    EXPECT_TRUE(isCreated == true);
    std::remove("outputTraining.txt");
    std::remove("errorTraining.txt");
}