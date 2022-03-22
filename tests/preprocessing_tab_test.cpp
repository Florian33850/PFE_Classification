#include <QtTest/QtTest>

#include "../src/preprocessing_tab.h"

class PreprocessingTabTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testPreprocessingTabInstantiation();
};

void PreprocessingTabTests::testPreprocessingTabInstantiation()
{
    PreprocessingTab *preprocessingTab = new PreprocessingTab();
    QVERIFY(preprocessingTab != NULL);
}

QTEST_MAIN(PreprocessingTabTests)
#include "preprocessing_tab_test.moc"
