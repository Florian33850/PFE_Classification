#include <QtTest/QtTest>

#include "../src/image_transformation_widget.h"

class ImageTransformationWidgetTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testMirrorWidgetInstantiation();
        void testGrayscaleWidgetInstantiation();
        void testAutomaticRotationLymeDataWidgetInstantiation();
        void testMorphologicalTransformationWidgetInstantiation();
};

void ImageTransformationWidgetTests::testMirrorWidgetInstantiation()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QWidget *parentWidget = new QWidget();
    MirrorImageTransformation *mirrorImageTransformation = new MirrorImageTransformation();
    MirrorWidget *mirrorWidget = new MirrorWidget(mainLayout, parentWidget, mirrorImageTransformation);
    QVERIFY(mirrorWidget != NULL);
}

void ImageTransformationWidgetTests::testGrayscaleWidgetInstantiation()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QWidget *parentWidget = new QWidget();
    GrayscaleImageTransformation *grayscaleImageTransformation = new GrayscaleImageTransformation();
    GrayscaleWidget *grayscaleWidget = new GrayscaleWidget(mainLayout, parentWidget, grayscaleImageTransformation);
    QVERIFY(grayscaleWidget != NULL);
}

void ImageTransformationWidgetTests::testAutomaticRotationLymeDataWidgetInstantiation()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QWidget *parentWidget = new QWidget();
    AutomaticRotationLymeDataImageTransformation *automaticRotationImageTransformation = new AutomaticRotationLymeDataImageTransformation();
    AutomaticRotationLymeDataWidget *automaticRotationWidget = new AutomaticRotationLymeDataWidget(mainLayout, parentWidget, automaticRotationImageTransformation);
    QVERIFY(automaticRotationWidget != NULL);
}

void ImageTransformationWidgetTests::testMorphologicalTransformationWidgetInstantiation()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QWidget *parentWidget = new QWidget();
    MorphologicalTransformationImageTransformation *morphologicalTransformationImageTransformation = new MorphologicalTransformationImageTransformation();
    MorphologicalTransformationWidget *morphologicalTransformationWidget = new MorphologicalTransformationWidget(mainLayout, parentWidget, morphologicalTransformationImageTransformation);
    QVERIFY(morphologicalTransformationWidget != NULL);
}

QTEST_MAIN(ImageTransformationWidgetTests)
#include "image_transformation_widget_test.moc"
