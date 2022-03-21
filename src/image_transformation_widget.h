#ifndef IMAGE_TRANSFORMATION_WIDGET_H
#define IMAGE_TRANSFORMATION_WIDGET_H

#include "image_transformation.h"

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>

#define MIRRORED_WIDGET_MAXIMUM_HEIGHT 110
#define GRAYSCALE_WIDGET_MAXIMUM_HEIGHT 65
#define AUTOMATIC_ROTATION_WIDGET_MAXIMUM_HEIGHT 65
#define EROSION_WIDGET_MAXIMUM_HEIGHT 110

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

class AutomaticRotationWidget : public ImageTransformationWidget
{
    public:
        AutomaticRotationWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, AutomaticRotationImageTransformation *erosionImageTransformation);

        void displayUI(int indexInLayout);
};

class ErosionWidget : public ImageTransformationWidget
{
    public:
        AutomaticRotationWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, ErosionImageTransformation *automaticRotationImageTransformation);

        void displayUI(int indexInLayout);
    
    private:
        QSlider *kernelSizeSlider;
        QSlider *numberIterationErosionSlider;
};
#endif // IMAGE_TRANSFORMATION_WIDGET_H