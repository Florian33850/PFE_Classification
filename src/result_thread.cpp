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
    this->process.setStandardOutputFile(OUTPUT_RESULT_FILE_NAME, QIODevice::ReadWrite);
    this->process.setStandardErrorFile(ERROR_OUTPUT_RESULT_FILE_NAME, QIODevice::ReadWrite);
    this->process.start(COMMAND_RUNNER ,{this->pathToPredictionFile, this->pathToModel, this->pathToImage, this->pathToLabels});
    this->process.waitForStarted();
    this->process.waitForFinished(-1);
}
