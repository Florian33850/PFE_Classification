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

#include "classification_training_tab.h"

ClassificationTrainingTab::ClassificationTrainingTab() : Tab()
{
    addChooseTrainingMethodComboBox();
    
    this->parametersLayout = new QVBoxLayout;
    this->mainLayout->addLayout(this->parametersLayout, ROW_CLASSIFICATION_TRAINING_TAB_PARAMETERS_LAYOUT, COLUMN_CLASSIFICATION_TRAINING_TAB_PARAMETERS_LAYOUT);

    this->trainingOutputLayout = new QVBoxLayout;
    this->mainLayout->addLayout(this->trainingOutputLayout, ROW_CLASSIFICATION_TRAINING_TAB_TRAINING_OUTPUT_LAYOUT, COLUMN_CLASSIFICATION_TRAINING_TAB_TRAINING_OUTPUT_LAYOUT);

    this->parametersLayout->addStretch();
    this->trainingOutputLayout->addStretch();
}

void ClassificationTrainingTab::addChooseTrainingMethodComboBox()
{
    this->chooseTrainingMethodComboBox = new QComboBox();
    this->chooseTrainingMethodComboBox->addItems(this->trainingMethodStringList);
    connect(this->chooseTrainingMethodComboBox, QOverload<int>::of(&QComboBox::activated), this, &ClassificationTrainingTab::handleTrainingMethodComboBox);
    this->mainLayout->addWidget(this->chooseTrainingMethodComboBox, ROW_CLASSIFICATION_TRAINING_TAB_COMBO_BOX, COLUMN_CLASSIFICATION_TRAINING_TAB_COMBO_BOX);
}

void ClassificationTrainingTab::handleTrainingMethodComboBox()
{
    QString newTrainingMethod = this->chooseTrainingMethodComboBox->currentText();

    if(newTrainingMethod.compare("Deep Learning") == QSTRINGS_ARE_EQUALS)
    {
        clearLayout(this->parametersLayout);
        new DeepLearningWidget(this->parametersLayout, this->trainingOutputLayout);
    }
    else if(newTrainingMethod.compare("Random Forest") == QSTRINGS_ARE_EQUALS)
    {
        clearLayout(this->parametersLayout);
        new RandomForestWidget(this->parametersLayout, this->trainingOutputLayout);
    }
}
