#ifndef IMAGE_TRANSFORMATION_WIDGET_H
#define IMAGE_TRANSFORMATION_WIDGET_H

#include "image_transformation.h"
#include "integer_slider.h"
#include "constants.h"

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>

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