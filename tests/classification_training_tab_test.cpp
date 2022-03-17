#include <gtest/gtest.h>
#include "../src/classification_training_tab.h"
#include <QWidget>

TEST(InstantiationTest, TestIfInstantiationOfClassificationTrainigTabIsNotNull) {
    ClassificationTrainingTab *classificationTrainingTab = new ClassificationTrainingTab();
    ASSERT_TRUE(classificationTrainingTab != NULL);
}
