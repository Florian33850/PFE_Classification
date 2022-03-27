//     PFE_Classification --- Generic classification software
//     Copyright © <2022> Florian Dayre <florian.dayre33850@gmail.com>
//     Copyright © <2022> Élodie Gaudry <elodie.gaudry@etu.u-bordeaux.fr>
//     Copyright © <2022> Hugo Lecomte <hugolecomte932@protonmail.com>
//     Copyright © <2022> Hugo Trarieux <htrarieux@gmail.com>

//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <gtest/gtest.h>
#define private public
#define protected public
#include "../src/classification_thread.h"
#include "../src/constants.h"
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
    if((file1 = fopen(OUTPUT_TRAINING_FILE_NAME, "r")) && (file2 = fopen(ERROR_OUTPUT_TRAINING_FILE_NAME, "r")))
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
    std::remove(OUTPUT_TRAINING_FILE_NAME);
    std::remove(ERROR_OUTPUT_TRAINING_FILE_NAME);
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
    if((file1 = fopen(OUTPUT_TRAINING_FILE_NAME, "r")) && (file2 = fopen(ERROR_OUTPUT_TRAINING_FILE_NAME, "r")))
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
    std::remove(OUTPUT_TRAINING_FILE_NAME);
    std::remove(ERROR_OUTPUT_TRAINING_FILE_NAME);
}
