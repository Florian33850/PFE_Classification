#include "image_transformation.h"

#include <iostream>

Mat ImageTransformation::qImageToMat(QImage qImage)
{
    cv::Mat imageMat(qImage.height(), qImage.width(), CV_8UC4, (uchar*)qImage.bits(), qImage.bytesPerLine());
    return imageMat;
}

QImage ImageTransformation::matToQImage(Mat imageMat)
{
    QImage qImage = QImage((uchar*) imageMat.data, imageMat.cols, imageMat.rows, static_cast<int>(imageMat.step), QImage::Format_RGB32 );
    return qImage;
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

void MirrorImageTransformation::runImageTransformation(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber=0; imageNumber < imagePreviewList->size(); imageNumber++)
    {
        QImage mirrorImage = imagePreviewList->at(imageNumber)->getQImage().mirrored(horizontalMirror, verticalMirror);
        imagePreviewList->at(imageNumber)->setImage(mirrorImage);
    }
}



GrayscaleImageTransformation::GrayscaleImageTransformation()
{
}

void GrayscaleImageTransformation::runImageTransformation(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber=0; imageNumber < imagePreviewList->size(); imageNumber++)
    {
        QImage grayscaleImage = imagePreviewList->at(imageNumber)->getQImage().convertToFormat(QImage::Format_Grayscale8);
        imagePreviewList->at(imageNumber)->setImage(grayscaleImage);
    }
}

AutomaticRotationImageTransformation::AutomaticRotationImageTransformation()
{
}


float AutomaticRotationImageTransformation::getAngleBetweenVectors(const Point &vec1, const Point &shapeOrientationVector)
{
    float length1 = sqrt(vec1.x * vec1.x + vec1.y * vec1.y);
    float length2 = sqrt(shapeOrientationVector.x * shapeOrientationVector.x + shapeOrientationVector.y * shapeOrientationVector.y);

    float dot = vec1.x * shapeOrientationVector.x + vec1.y * shapeOrientationVector.y;

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

PCA AutomaticRotationImageTransformation::createPCAAnalysis(const std::vector<Point> &pointList)
{
    int pointListSize = static_cast<int>(pointList.size());
    Mat dataPointsMat = Mat(pointListSize, 2, CV_64F);
    for (int i = 0; i < dataPointsMat.rows; i++)
    {
        dataPointsMat.at<double>(i, 0) = pointList[i].x;
        dataPointsMat.at<double>(i, 1) = pointList[i].y;
    }

    PCA pcaAnalysis(dataPointsMat, Mat(), PCA::DATA_AS_ROW);
    return pcaAnalysis;
}

double AutomaticRotationImageTransformation::getMinAngleRadian(Point shapeCenter, PCA pcaAnalysis)
{
    Point verticalPoint = Point(shapeCenter.x, shapeCenter.y-10.);
    Point verticalVector = verticalPoint-shapeCenter;

    std::vector<Point2d> eigenVecs(2);
    std::vector<double> eigenVal(2);
    for (int i = 0; i < 2; i++)
    {
        eigenVecs[i] = Point2d(pcaAnalysis.eigenvectors.at<double>(i, 0),
                                pcaAnalysis.eigenvectors.at<double>(i, 1));
        eigenVal[i] = pcaAnalysis.eigenvalues.at<double>(i);
    }

    Point shapePoint = shapeCenter + 0.02 * Point(static_cast<int>(eigenVecs[0].x * eigenVal[0]), static_cast<int>(eigenVecs[0].y * eigenVal[0]));
    Point shapeOrientationVector = shapePoint-shapeCenter;

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

void AutomaticRotationImageTransformation::dilatation(Mat &imageMat, int dilatationSize)
{
  Mat structuringElement = getStructuringElement( MORPH_RECT,
                       Size( 2*dilatationSize + 1, 2*dilatationSize+1 ),
                       Point( dilatationSize, dilatationSize ) );
  dilate(imageMat, imageMat, structuringElement);
}

void AutomaticRotationImageTransformation::centerTranslation(Mat &imageMat, const Point shapeCenter)
{
    Point imageMatCenter = {imageMat.cols/2, imageMat.rows/2};
    float translationX = imageMatCenter.x-shapeCenter.x;
    float translationY = imageMatCenter.y-shapeCenter.y;
    float warpValues[] = {1.0, 0.0, translationX, 0.0, 1.0, translationY};
    cv::Mat translationMat = Mat(2, 3, CV_32F, warpValues);

    cv::warpAffine(imageMat, imageMat, translationMat, imageMat.size());
}

void AutomaticRotationImageTransformation::runImageTransformation(std::vector<ImageLabel*> *imagePreviewList)
{
    for(int imageNumber=0; imageNumber < imagePreviewList->size(); imageNumber++)
    {
        QImage qImage = imagePreviewList->at(imageNumber)->getQImage();
        qImage.save("imageTmp.tif");

        Mat imageMat = imread("imageTmp.tif");
        if(imageMat.empty())
        {
            std::cout << "Problem loading image !!!" << std::endl;
        }
        else
        {

            Mat grayMat;
            cvtColor(imageMat, grayMat, COLOR_BGR2GRAY);
            Mat thresholdMat;
            threshold(grayMat, thresholdMat, 50, 255, THRESH_BINARY | THRESH_OTSU);
            std::vector<std::vector<Point> > contours;
            findContours(thresholdMat, contours, RETR_LIST, CHAIN_APPROX_NONE);
            int dilation_size = 0;
            while(contours.size() >2)
            {
                this->dilatation(thresholdMat, dilation_size);
                dilation_size++;
                findContours(thresholdMat, contours, RETR_LIST, CHAIN_APPROX_TC89_L1);
            }

            double areaMin = DBL_MAX;
            int indexMin = INT_MAX;
            for(int i = 0; i < contours.size(); i++)
            {
                double area = contourArea(contours[i]);
                
                if (area < 1e2 || 1e5 < area) 
                {
                    continue; // Ignore contours that are too small or too large
                }

                if(area < areaMin)
                {
                    areaMin = area;
                    indexMin = i;
                }
            }

            PCA pcaAnalysis = createPCAAnalysis(contours[indexMin]);
            Point shapeCenter = Point(static_cast<int>(pcaAnalysis.mean.at<double>(0, 0)), static_cast<int>(pcaAnalysis.mean.at<double>(0, 1)));
            double angleRadian = getMinAngleRadian(shapeCenter, pcaAnalysis);
            double angleDegree = angleRadian*(180.0/CV_PI);

            cv::Mat rotationMat = cv::getRotationMatrix2D(shapeCenter, angleDegree, 1.0);

            cv::Mat rotatedImageMat;
            cv::warpAffine(imageMat, rotatedImageMat, rotationMat, imageMat.size());

            cv::Mat translatedImageMat = rotatedImageMat.clone();
            centerTranslation(translatedImageMat, shapeCenter);

            cv::imwrite("imageTmp.tif", translatedImageMat);

            QImage rotatedQImage;
            rotatedQImage.load("imageTmp.tif");
            remove("imageTmp.tif");
            imagePreviewList->at(imageNumber)->setImage(rotatedQImage);
        }
    }
}