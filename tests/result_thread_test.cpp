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
#include "../src/result_thread.h"

TEST(InstantiationTest, TestIfInstantiationOfResultThreadIsNotNull)
{
    QString pathToPredictionFile = "";
    QString pathToModel = "";
    QString pathToImage = "";
    QString pathToLabels = "";
    ResultThread *resultThread = new ResultThread(pathToPredictionFile, pathToModel, pathToImage, pathToLabels);
    ASSERT_TRUE(resultThread != NULL);
}

TEST(NotRunningBeforeTest, TestIfQProcessOfResultThreadNotRunningBeforeRunFunction)
{
    QString pathToPredictionFile = "";
    QString pathToModel = "";
    QString pathToImage = "";
    QString pathToLabels = "";
    ResultThread *resultThread = new ResultThread(pathToPredictionFile, pathToModel, pathToImage, pathToLabels);
    ASSERT_TRUE(resultThread->process.state() == QProcess::NotRunning);
}

TEST(NotRunningAfterTest, TestIfQProcessOfResultThreadNotRunningAfterRunFunction)
{
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
    if((file1 = fopen(OUTPUT_RESULT_FILE_NAME, "r")) && (file2 = fopen(ERROR_OUTPUT_RESULT_FILE_NAME, "r")))
    {
      fclose(file1);
      fclose(file2);
      isCreated = true;
    }
    else
    {
        isCreated = false;
    }
    std::remove(OUTPUT_RESULT_FILE_NAME);
    std::remove(ERROR_OUTPUT_RESULT_FILE_NAME);
    EXPECT_TRUE(isCreated == true);
}
