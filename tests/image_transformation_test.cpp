#include <gtest/gtest.h>
#define private public
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
