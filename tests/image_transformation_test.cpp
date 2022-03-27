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
    cv::Mat testImage(200, 200, CV_8UC4);
    cv::randu(testImage, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
    cv::imwrite("testAutomaticRotation.tiff", testImage);
    QImage qImage1;
    qImage1.load("testAutomaticRotation.tiff");
    qImage1 = automaticRotationImageTransformation->applyImageTransformation(qImage1);
    QImage *qImage2 = new QImage(qImage1);
    ASSERT_TRUE(qImage2 != NULL);
}