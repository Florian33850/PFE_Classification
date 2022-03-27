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

#ifndef DATA_AUGMENTATION_WIDGET_H
#define DATA_AUGMENTATION_WIDGET_H

#include "image_transformation_widget.h"

class DataAugmentationWidget : public QWidget
{
    Q_OBJECT
    public:
        DataAugmentationWidget(QWidget *parentWidget);

        enum transformationWidgetsEnum{mirror=0, grayscale=1};
        std::vector<ImageTransformationWidget*> imageTransformationWidgetList;

    Q_SIGNALS:
        void previewSignal(DataAugmentationWidget* sender);

    private:
        QVBoxLayout *mainLayout;
        QWidget *parentWidget;
        QPushButton *previewButton;

        QCheckBox *mirrorCheckBox;
        QCheckBox *grayscaleCheckBox;

        MirrorWidget *mirrorWidget;
        GrayscaleWidget *grayscaleWidget;

        void addMirrorCheckBox();
        void addGrayscaleCheckBox();
        void addPreviewButton();
        void deleteImageTransformationWidget(ImageTransformationWidget *imageTransformationWidget);
        ImageTransformationWidget* initialiseImageTransformationWidget(transformationWidgetsEnum index);

        void handleImageTransformationCheckBox(ImageTransformationWidget *imageTransformationWidget, QCheckBox *imageTransformationCheckbox, transformationWidgetsEnum index);
        void handleDeleteImageTransformationWidgetButton(ImageTransformationWidget *imageTransformationWidget, QCheckBox *imageTransformationCheckbox);
        void handlePreviewButton();
};

#endif // DATA_AUGMENTATION_WIDGET_H
