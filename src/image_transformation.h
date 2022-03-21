#ifndef IMAGE_TRANSFORMATION_H
#define IMAGE_TRANSFORMATION_H

#include "image_label.h"
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#define AUTOMATIC_ROTATION_MAX_DILATATION_SIZE 20;

class ImageTransformation
{
    public:
        void runImageTransformationOnPreviewList(std::vector<ImageLabel*> *imagePreviewList);
        virtual QImage applyImageTransformation(QImage qImage) = 0;
        
        virtual ~ImageTransformation() = default;
};

class MirrorImageTransformation : public ImageTransformation
{   
    public:
        MirrorImageTransformation();

        bool horizontalMirror;
        bool verticalMirror;
        
        void changeHorizontalMirrorMode();
        void changeVerticalMirrorMode();

    private:
        QImage applyImageTransformation(QImage qImage);

};

class GrayscaleImageTransformation : public ImageTransformation
{
    public:
        GrayscaleImageTransformation();
    
    private:
        QImage applyImageTransformation(QImage qImage);
};

class AutomaticRotationImageTransformation : public ImageTransformation
{
    public:
        AutomaticRotationImageTransformation();

    private:
        int dilationSizeMax;

        float getAngleBetweenVectors(const cv::Point &vec1, const cv::Point &shapeOrientationVector);
        cv::PCA createPCAAnalysis(const std::vector<cv::Point> pointList);
        double getMinAngleRadian(cv::Point shapeCenter, cv::PCA pcaAnalysis);
        void applyDilatation(cv::Mat &imageMat, int dilatationSize);
        void centerTranslation(cv::Mat &imageMat, const cv::Point shapeCenter);
        QImage applyImageTransformation(QImage qImage);
};

#endif // IMAGE_TRANSFORMATION_H