#include <gtest/gtest.h>
#include "../src/image_transformation.h"

TEST(InstantiationTest, TestIfInstantiationOfMirrorImageTransformationIsNotNull)
{
    MirrorImageTransformation *mirrorImageTransformation = new MirrorImageTransformation();
    ASSERT_TRUE(mirrorImageTransformation != NULL);
}

TEST(InstantiationTest, TestIfInstantiationOfGrayscaleImageTransformationIsNotNull)
{
    GrayscaleImageTransformation *grayscaleImageTransformation = new GrayscaleImageTransformation();
    ASSERT_TRUE(grayscaleImageTransformation != NULL);
}

TEST(InstantiationTest, TestIfInstantiationOfAutomaticRotationLymeDataImageTransformationIsNotNull)
{
    AutomaticRotationLymeDataImageTransformation *automaticRotationImageTransformation = new AutomaticRotationLymeDataImageTransformation();
    ASSERT_TRUE(automaticRotationImageTransformation != NULL);
}

TEST(InstantiationTest, TestIfInstantiationOfMorphologicalTransformationImageTransformationIsNotNull)
{
    MorphologicalTransformationImageTransformation *morphologicalTransformationImageTransformation = new MorphologicalTransformationImageTransformation();
    ASSERT_TRUE(morphologicalTransformationImageTransformation != NULL);
}

TEST(MirrorModeTest, TestIfChangeHorizontalMirrorModeIsCorrect)
{
    MirrorImageTransformation *mirrorImageTransformation = new MirrorImageTransformation();
    mirrorImageTransformation->horizontalMirror = false;
    mirrorImageTransformation->changeHorizontalMirrorMode();
    ASSERT_TRUE(mirrorImageTransformation->horizontalMirror == true);
}

TEST(MirrorModeTest, TestIfChangeVerticalMirrorModeIsCorrect)
{
    MirrorImageTransformation *mirrorImageTransformation = new MirrorImageTransformation();
    mirrorImageTransformation->verticalMirror = false;
    mirrorImageTransformation->changeVerticalMirrorMode();
    ASSERT_TRUE(mirrorImageTransformation->verticalMirror == true);
}

TEST(AutomaticRotationLymeDataTest, TestIfAutomaticRotationLymeDataIsCorrect)
{
    AutomaticRotationLymeDataImageTransformation *automaticRotationImageTransformation = new AutomaticRotationLymeDataImageTransformation();
    cv::Mat testImage(200, 200, CV_8UC3);
    cv::randu(testImage, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
    cv::imwrite("testAutomaticRotation.png", testImage);
    QImage qImage1;
    qImage1.load("testAutomaticRotation.png");
    qImage1 = automaticRotationImageTransformation->applyImageTransformation(qImage1);
    QImage *qImage2 = new QImage(qImage1);
    ASSERT_TRUE(qImage2 != NULL);
}

TEST(MorphologicalTransformationTest, TestIfMorphologicalTransformationErodeIsCorrect)
{
    cv::Mat testImage(200, 200, CV_8UC3);
    cv::randu(testImage, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
    cv::imwrite("testMorphologicalTranformation.png", testImage);

    MorphologicalTransformationImageTransformation *morphologicalTransformationImageTransformation = new MorphologicalTransformationImageTransformation();
    morphologicalTransformationImageTransformation->changeKernelSize(2);
    morphologicalTransformationImageTransformation->changeNumberIterationMorphologicalTransformation(1);
    morphologicalTransformationImageTransformation->changeTypeMorphologicalTransformation(0);
    QImage qImage1;
    qImage1.load("testMorphologicalTranformation.png");
    qImage1 = morphologicalTransformationImageTransformation->applyImageTransformation(qImage1);

    int kernelSize = 2;
    cv::Mat structuringElement = getStructuringElement(cv::MORPH_RECT,
                                                                cv::Size(2*kernelSize+1, 2*kernelSize+1),
                                                                cv::Point(kernelSize, kernelSize));
    cv::erode(testImage, testImage, structuringElement);
    cv::imwrite("testErodeImage.png", testImage);
    QImage qImage2;
    qImage2.load("testErodeImage.png");

    ASSERT_TRUE(qImage1 == qImage2);
}

TEST(MorphologicalTransformationTest, TestIfMorphologicalTransformationDilateIsCorrect)
{
    cv::Mat testImage(200, 200, CV_8UC3);
    cv::randu(testImage, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
    cv::imwrite("testMorphologicalTranformation.png", testImage);

    MorphologicalTransformationImageTransformation *morphologicalTransformationImageTransformation = new MorphologicalTransformationImageTransformation();
    morphologicalTransformationImageTransformation->changeKernelSize(2);
    morphologicalTransformationImageTransformation->changeNumberIterationMorphologicalTransformation(1);
    morphologicalTransformationImageTransformation->changeTypeMorphologicalTransformation(1);
    QImage qImage1;
    qImage1.load("testMorphologicalTranformation.png");
    qImage1 = morphologicalTransformationImageTransformation->applyImageTransformation(qImage1);

    int kernelSize = 2;
    cv::Mat structuringElement = getStructuringElement(cv::MORPH_RECT,
                                                                cv::Size(2*kernelSize+1, 2*kernelSize+1),
                                                                cv::Point(kernelSize, kernelSize));
    cv::dilate(testImage, testImage, structuringElement);
    cv::imwrite("testDilateImage.png", testImage);
    QImage qImage2;
    qImage2.load("testDilateImage.png");

    ASSERT_TRUE(qImage1 == qImage2);
}