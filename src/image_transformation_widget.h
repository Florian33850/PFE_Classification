#ifndef IMAGE_TRANSFORMATION_WIDGET_H
#define IMAGE_TRANSFORMATION_WIDGET_H

#include "image_transformation.h"
#include "integer_slider.h"

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>

//MIRROR WIDGET
#define ROW_MIRROR_WIDGET_TITLE 0
#define COLUMN_MIRROR_WIDGET_TITLE 0
#define ROW_SPAN_MIRROR_WIDGET_TITLE 1
#define COLUMN_SPAN_MIRROR_WIDGET_TITLE 1

#define ROW_HORIZONTAL_CHECK_BOX 1
#define COLUMN_HORIZONTAL_CHECK_BOX 0
#define ROW_SPAN_HORIZONTAL_CHECK_BOX 2
#define COLUMN_SPAN_HORIZONTAL_CHECK_BOX 1

#define ROW_VERTICAL_CHECK_BOX 2
#define COLUMN_VERTICAL_CHECK_BOX 0
#define ROW_SPAN_VERTICAL_CHECK_BOX 2
#define COLUMN_SPAN_VERTICAL_CHECK_BOX 1

#define ROW_DELETE_WIDGET_BUTTON 0
#define COLUMN_DELETE_WIDGET_BUTTON 1
#define ROW_SPAN_DELETE_WIDGET_BUTTON 1
#define COLUMN_SPAN_DELETE_WIDGET_BUTTON 1

//MORPHOLOGICAL_TRANSFORMATION WIDGET
#define MORPHOLOGICAL_TRANSFORMATION_MINIMUM_KERNEL_SIZE 1
#define MORPHOLOGICAL_TRANSFORMATION_MAXIMUM_KERNEL_SIZE 20

#define MORPHOLOGICAL_TRANSFORMATION_MINIMUM_NUMBER_ITERATION 1
#define MORPHOLOGICAL_TRANSFORMATION_MAXIMUM_NUMBER_ITERATION 10

#define ROW_MORPHOLOGICAL_TRANSFORMATION_WIDGET_TITLE 0
#define COLUMN_MORPHOLOGICAL_TRANSFORMATION_WIDGET_TITLE 0

#define ROW_MORPHOLOGICAL_TRANSFORMATION_TYPE 1
#define COLUMN_MORPHOLOGICAL_TRANSFORMATION_TYPE 0

#define ROW_MORPHOLOGICAL_TRANSFORMATION_KERNEL_SIZE_SLIDER 2
#define COLUMN_MORPHOLOGICAL_TRANSFORMATION_KERNEL_SIZE_SLIDER 0

#define ROW_MORPHOLOGICAL_TRANSFORMATION_NUMBER_ITERATION 3
#define COLUMN_MORPHOLOGICAL_TRANSFORMATION_NUMBER_ITERATION 0

#define ROW_MORPHOLOGICAL_TRANSFORMATION_DELETE_WIDGET_BUTTON 0
#define COLUMN_MORPHOLOGICAL_TRANSFORMATION_DELETE_WIDGET_BUTTON 1


class ImageTransformationWidget : public QWidget
{
    public:
        ImageTransformationWidget(QVBoxLayout *mainLayout, QWidget *parentWidget);

        bool isActivated;
        ImageTransformation *imageTransformation;

        virtual void displayUI(int indexInLayout) = 0;
        void deleteMainWidgetGroupBox();

        QPushButton* getDeleteImageTransformationWidgetButton();
        int getLayoutCount();

    protected:
        QVBoxLayout *mainLayout;
        QWidget *parentWidget;
        QGroupBox *mainWidgetGroupBox;
        QPushButton *deleteImageTransformationWidgetButton;

        void connectWidgetDeleteButton();
};

class MirrorWidget : public ImageTransformationWidget
{
    public:
        MirrorWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, MirrorImageTransformation *mirrorImageTransformation);

        void displayUI(int indexInLayout);

    private:
        QCheckBox *horizontalMirrorCheckBox;
        QCheckBox *verticalMirrorCheckBox;
};

class GrayscaleWidget : public ImageTransformationWidget
{
    public:
        GrayscaleWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, GrayscaleImageTransformation *grayscaleImageTransformation);

        void displayUI(int indexInLayout);
};

class AutomaticRotationLymeDataWidget : public ImageTransformationWidget
{
    public:
        AutomaticRotationLymeDataWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, AutomaticRotationLymeDataImageTransformation *automaticRotationLymeDataImageTransformation);

        void displayUI(int indexInLayout);
};

class MorphologicalTransformationWidget : public ImageTransformationWidget
{
    public:
        MorphologicalTransformationWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, MorphologicalTransformationImageTransformation *morphologicalTransformationImageTransformation);

        void displayUI(int indexInLayout);

    private:
        IntegerSlider *typeMorphologicalTransformation;
        IntegerSlider *kernelSizeSlider;
        IntegerSlider *numberIterationMorphologialTransformationSlider;
};
#endif // IMAGE_TRANSFORMATION_WIDGET_H