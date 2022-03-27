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

#include "image_transformation.h"
#include <iostream>

void ImageTransformation::runImageTransformationOnPreviewList(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber=0; imageNumber < (int) imagePreviewList->size(); imageNumber++)
    {
        QImage qImage = applyImageTransformation(imagePreviewList->at(imageNumber)->qImage);
        imagePreviewList->at(imageNumber)->qImage = qImage;
    }
}

MirrorImageTransformation::MirrorImageTransformation()
{
    horizontalMirror = false;
    verticalMirror = false;
}

void MirrorImageTransformation::changeHorizontalMirrorMode()
{
    horizontalMirror = !horizontalMirror;
}

void MirrorImageTransformation::changeVerticalMirrorMode()
{
    verticalMirror = !verticalMirror;
}

QImage MirrorImageTransformation::applyImageTransformation(QImage qImage)
{
    QImage mirrorImage = qImage.mirrored(horizontalMirror, verticalMirror);
    return mirrorImage;
}

QImage GrayscaleImageTransformation::applyImageTransformation(QImage qImage)
{
    QImage grayscaleImage = qImage.convertToFormat(QImage::Format_Grayscale8);
    return grayscaleImage;
}

AutomaticRotationLymeDataImageTransformation::AutomaticRotationLymeDataImageTransformation()
{
    dilatationSizeMax = AUTOMATIC_ROTATION_IMAGE_TRANSFORMATION_MAX_DILATATION_SIZE;
}

float AutomaticRotationLymeDataImageTransformation::getAngleBetweenVectors(const cv::Point &vector1, const cv::Point &vector2)
{
    float length1 = sqrt(vector1.x * vector1.x + vector1.y * vector1.y);
    float length2 = sqrt(vector2.x * vector2.x + vector2.y * vector2.y);

    float dot = vector1.x * vector2.x + vector1.y * vector2.y;

    float angleRadian = dot / (length1 * length2);

    if (angleRadian >= 1.0)
    {
        return 0.0;
    }
    else if(angleRadian <= -1.0)
    {
        return CV_PI;
    }
    else
    {
        return acos(angleRadian);
    }
}

cv::PCA AutomaticRotationLymeDataImageTransformation::createPCAAnalysis(const std::vector<cv::Point> pointList)
{
    int pointListSize = static_cast<int>(pointList.size());
    cv::Mat dataPointsMat = cv::Mat(pointListSize, 2, CV_64F);

    for (int i = 0; i < dataPointsMat.rows; i++)
    {
        dataPointsMat.at<double>(i, 0) = pointList[i].x;
        dataPointsMat.at<double>(i, 1) = pointList[i].y;
    }

    cv::PCA pcaAnalysis(dataPointsMat, cv::Mat(), cv::PCA::DATA_AS_ROW);
    return pcaAnalysis;
}

double AutomaticRotationLymeDataImageTransformation::getMinAngleRadian(cv::Point shapeCenter, cv::PCA pcaAnalysis)
{
    cv::Point verticalPoint = cv::Point(shapeCenter.x, shapeCenter.y-10.);
    cv::Point verticalVector = verticalPoint-shapeCenter;

    std::vector<cv::Point2d> eigenVecs(2);
    std::vector<double> eigenVal(2);
    for (int i = 0; i < 2; i++)
    {
        eigenVecs[i] = cv::Point2d(pcaAnalysis.eigenvectors.at<double>(i, 0),
                                    pcaAnalysis.eigenvectors.at<double>(i, 1));
        eigenVal[i] = pcaAnalysis.eigenvalues.at<double>(i);
    }

    cv::Point shapePoint = shapeCenter + 0.02 * cv::Point(static_cast<int>(eigenVecs[0].x * eigenVal[0]),
                                                            static_cast<int>(eigenVecs[0].y * eigenVal[0]));
    cv::Point shapeOrientationVector = shapePoint-shapeCenter;

    double angleRadian;
    if(getAngleBetweenVectors(verticalVector, shapeOrientationVector) < getAngleBetweenVectors(-verticalVector, shapeOrientationVector))
    {
        if((shapePoint.x > verticalPoint.x && shapePoint.y < verticalPoint.y) || (shapePoint.x < verticalPoint.x && shapePoint.y > verticalPoint.y))
        {
            angleRadian = getAngleBetweenVectors(verticalVector, shapeOrientationVector);
        }
        else
        {
            angleRadian = -getAngleBetweenVectors(verticalVector, shapeOrientationVector);
        }
    }
    else
    {
        if((shapePoint.x > verticalPoint.x && shapePoint.y < verticalPoint.y) || (shapePoint.x < verticalPoint.x && shapePoint.y > verticalPoint.y))
        {
            angleRadian = getAngleBetweenVectors(-verticalVector, shapeOrientationVector);
        }
        else
        {
            angleRadian = -getAngleBetweenVectors(-verticalVector, shapeOrientationVector);
        }
    }

    return angleRadian;
}

void AutomaticRotationLymeDataImageTransformation::applyDilatation(cv::Mat &imageMat, int dilatationSize)
{
    cv::Mat structuringElement = getStructuringElement(cv::MORPH_RECT,
                                                        cv::Size(2*dilatationSize + 1, 2*dilatationSize + 1),
                                                        cv::Point(dilatationSize, dilatationSize) );
    dilate(imageMat, imageMat, structuringElement);
}

void AutomaticRotationLymeDataImageTransformation::centerTranslation(cv::Mat &imageMat, const cv::Point shapeCenter)
{
    cv::Point imageMatCenter = {imageMat.cols/2, imageMat.rows/2};
    float translationX = imageMatCenter.x-shapeCenter.x;
    float translationY = imageMatCenter.y-shapeCenter.y;
    float warpValues[] = {1.0, 0.0, translationX, 0.0, 1.0, translationY};
    cv::Mat translationMat = cv::Mat(2, 3, CV_32F, warpValues);

    cv::warpAffine(imageMat, imageMat, translationMat, imageMat.size());
}

QImage AutomaticRotationLymeDataImageTransformation::applyImageTransformation(QImage qImage)
{
    qImage.save("imageRotationTmp.tif");

    cv::Mat imageMat = cv::imread("imageRotationTmp.tif");
    if(imageMat.empty())
    {
        std::cout << "Problem loading image !!!" << std::endl;
        return qImage;
    }
    else
    {
        cv::Mat grayMat;
        cvtColor(imageMat, grayMat, cv::COLOR_BGR2GRAY);
        cv::Mat thresholdMat;
        threshold(grayMat, thresholdMat, 50, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        std::vector<std::vector<cv::Point> > contours;
        findContours(thresholdMat, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

        int dilationSize = 0;
        while(contours.size() > 2 && dilationSize < dilatationSizeMax)
        {
            this->applyDilatation(thresholdMat, dilationSize);
            dilationSize++;
            findContours(thresholdMat, contours, cv::RETR_LIST, cv::CHAIN_APPROX_TC89_L1);
        }

        double areaMin = DBL_MAX;
        int indexMin = INT_MAX;

        //Recover the smallest area
        for(int i = 0; i < (int) contours.size(); i++)
        {
            double area = contourArea(contours[i]);
            
            // Ignore areas that are too small or too large
            if (area < 1e2 || 1e5 < area)
            {
                continue;
            }

            if(area < areaMin)
            {
                areaMin = area;
                indexMin = i;
            }
        }

        // Check if no contours of the right size are found
        if(areaMin == DBL_MAX)
        {
            indexMin = 0;
        }

        cv::PCA pcaAnalysis = createPCAAnalysis(contours[indexMin]);
        cv::Point shapeCenter = cv::Point(static_cast<int>(pcaAnalysis.mean.at<double>(0, 0)), static_cast<int>(pcaAnalysis.mean.at<double>(0, 1)));
        double angleDegree = getMinAngleRadian(shapeCenter, pcaAnalysis) * (180.0/CV_PI);

        cv::Mat rotationMat = cv::getRotationMatrix2D(shapeCenter, angleDegree, 1.0);

        cv::Mat rotatedImageMat;
        cv::warpAffine(imageMat, rotatedImageMat, rotationMat, imageMat.size());

        cv::Mat translatedImageMat = rotatedImageMat.clone();
        centerTranslation(translatedImageMat, shapeCenter);

        cv::imwrite("imageRotationTmp.tif", translatedImageMat);

        QImage rotatedQImage;
        rotatedQImage.load("imageRotationTmp.tif");
        remove("imageRotationTmp.tif");
        return rotatedQImage;
    }
}

MorphologicalTransformationImageTransformation::MorphologicalTransformationImageTransformation()
{
    this->kernelSize = 0;
    this->numberIterationMorphologicalTransformation = 1;
    this->typeMorphologicalTransformation = 0;
}

void MorphologicalTransformationImageTransformation::changeKernelSize(int newKernelSize)
{
    this->kernelSize = newKernelSize;
}

void MorphologicalTransformationImageTransformation::changeNumberIterationMorphologicalTransformation(int newNumberIterationMorphologicalTransformation)
{
    this->numberIterationMorphologicalTransformation = newNumberIterationMorphologicalTransformation;
}

void MorphologicalTransformationImageTransformation::changeTypeMorphologicalTransformation(int newTypeMorphologicalTransformation)
{
    this->typeMorphologicalTransformation = newTypeMorphologicalTransformation;
}

void MorphologicalTransformationImageTransformation::dilatation(cv::Mat &imageMat, cv::Mat structuringElement)
{
    for(int i=0; i<this->numberIterationMorphologicalTransformation; i++)
    {
        dilate(imageMat, imageMat, structuringElement);
    }
}

void MorphologicalTransformationImageTransformation::erosion(cv::Mat &imageMat, cv::Mat structuringElement)
{
    for(int i=0; i<this->numberIterationMorphologicalTransformation; i++)
    {
        erode(imageMat, imageMat, structuringElement);
    }
}

QImage MorphologicalTransformationImageTransformation::applyImageTransformation(QImage qImage)
{
        qImage.save("imageMorphologicalTransformationTmp.tif");

        cv::Mat imageMat = cv::imread("imageMorphologicalTransformationTmp.tif");
        if(imageMat.empty())
        {
            std::cout << "Problem loading image !!!" << std::endl;
        }
        else
        {
            cv::Mat structuringElement = getStructuringElement(cv::MORPH_RECT,
                                                                cv::Size(2*this->kernelSize+1, 2*this->kernelSize+1),
                                                                cv::Point(this->kernelSize, this->kernelSize));
            if(this->typeMorphologicalTransformation == 0)
            {
                this->erosion(imageMat, structuringElement);
            }
            else if(this->typeMorphologicalTransformation == 1)
            {
                this->dilatation(imageMat, structuringElement);
            }
        }

        cv::imwrite("imageMorphologicalTransformationTmp.tif", imageMat);

        QImage morphologicalTransformedQImage;
        morphologicalTransformedQImage.load("imageMorphologicalTransformationTmp.tif");
        remove("imageMorphologicalTransformationTmp.tif");
        return morphologicalTransformedQImage;
}
