#ifndef IMAGE_TRANSFORMATION_H
#define IMAGE_TRANSFORMATION_H

#include "image_label.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;

class ImageTransformation
{
    public:
        virtual void runImageTransformation(std::vector<ImageLabel*> *imagePreviewList) = 0;

    protected:
        Mat qImageToMat(QImage qImage);
        QImage matToQImage(Mat imageMat);
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
        void runImageTransformation(std::vector<ImageLabel*> *imagePreviewList);
};

class GrayscaleImageTransformation : public ImageTransformation
{
    public:
        GrayscaleImageTransformation();
    
    private:
        void runImageTransformation(std::vector<ImageLabel*> *imagePreviewList);
};

class AutomaticRotationImageTransformation : public ImageTransformation
{
    public:
        AutomaticRotationImageTransformation();
    
    private:
        float getAngleBetweenVectors(const Point &vec1, const Point &shapeOrientationVector);
        PCA createPCAAnalysis(const std::vector<Point> &pointList);
        double getMinAngleRadian(Point shapeCenter, PCA pcaAnalysis);
        void dilatation(Mat &imageMat, int dilatationSize);
        void centerTranslation(Mat &imageMat, const Point shapeCenter);
        void runImageTransformation(std::vector<ImageLabel*> *imagePreviewList);
};

#endif // IMAGE_TRANSFORMATION_H