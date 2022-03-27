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

#ifndef IMAGE_TRANSFORMATION_H
#define IMAGE_TRANSFORMATION_H

#include "image_label.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "constants.h"

#include <stdio.h>
#include <iostream>

class ImageTransformation
{
    public:
        virtual ~ImageTransformation() = default;

        void runImageTransformationOnPreviewList(std::vector<ImageLabel*> *imagePreviewList);
        virtual QImage applyImageTransformation(QImage qImage) = 0;
};

class MirrorImageTransformation : public ImageTransformation
{   
    public:
        MirrorImageTransformation();

        bool horizontalMirror;
        bool verticalMirror;
        
        void changeHorizontalMirrorMode();
        void changeVerticalMirrorMode();
        QImage applyImageTransformation(QImage qImage);
};

class GrayscaleImageTransformation : public ImageTransformation
{
    public:
        QImage applyImageTransformation(QImage qImage);
};

class AutomaticRotationLymeDataImageTransformation : public ImageTransformation
{
    public:
        AutomaticRotationLymeDataImageTransformation();

        QImage applyImageTransformation(QImage qImage);

    private:
        int dilatationSizeMax;

        float getAngleBetweenVectors(const cv::Point &vec1, const cv::Point &shapeOrientationVector);
        cv::PCA createPCAAnalysis(const std::vector<cv::Point> pointList);
        double getMinAngleRadian(cv::Point shapeCenter, cv::PCA pcaAnalysis);
        void applyDilatation(cv::Mat &imageMat, int dilatationSize);
        void centerTranslation(cv::Mat &imageMat, const cv::Point shapeCenter);
};

class MorphologicalTransformationImageTransformation : public ImageTransformation
{
    public:
        MorphologicalTransformationImageTransformation();

        int kernelSize;
        int numberIterationMorphologicalTransformation;
        int typeMorphologicalTransformation;

        void changeKernelSize(int newKernelSize);
        void changeNumberIterationMorphologicalTransformation(int newNumberIterationMorphologicalTransformation);
        void changeTypeMorphologicalTransformation(int newTypeMorphologicalTransformation);
        void dilatation(cv::Mat &imageMat, cv::Mat structuringElement);
        void erosion(cv::Mat &imageMat, cv::Mat structuringElement);
        QImage applyImageTransformation(QImage qImage);
};
#endif // IMAGE_TRANSFORMATION_H
