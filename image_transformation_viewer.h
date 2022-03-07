#ifndef IMAGE_TRANSFORMATION_VIEWER_H
#define IMAGE_TRANSFORMATION_VIEWER_H

#include "image_transformation_widget.h"

#include <iostream>
#include <QVBoxLayout>
#include <QComboBox>

class ImageTransformationViewer : public QWidget
{
    public:
        ImageTransformationViewer(std::vector<ImageLabel*>* imagePreviewList, QWidget *parentWidget = nullptr);

        void launchActivatedPreprocesses();

    protected:
        QVBoxLayout *mainLayout;
        std::vector<ImageLabel*> *imagePreviewList;
        QWidget *parent;
        std::vector<ImageTransformationWidget*> imageTransformationWidgetList;
        std::vector<ImageTransformation*> imageTransformationList;
        QStringList preprocessingStringList = {"Add Preprocessing", "Mirror", "Grayscale"};

        MirrorWidget* createMirrorImageTransformation();
        GrayscaleWidget* createGrayscaleImageTransformation();
        
        void handleLaunchImageTransformationButton();
        void handleImageTransformationComboBox();
        void handleDeleteImageTransformationWidgetButton(ImageTransformationWidget* imageTransformationWidget);
};

class PreprocessingViewer : public ImageTransformationViewer
{
    public:
        PreprocessingViewer(std::vector<ImageLabel*>* imagePreviewList, QWidget *parentWidget = nullptr);
    private:
        QPushButton *launchPreprocessingButton;
        QComboBox *addPreprocessingComboBox;

        void addLaunchPreprocessingButton();
        void addAddPreprocessingComboBox();

        void handleImageTransformationComboBox();
};

class DataAugmentationViewer : public ImageTransformationViewer
{
    public:
        DataAugmentationViewer(std::vector<ImageLabel*>* imagePreviewList, QWidget *parentWidget = nullptr);
};
#endif // IMAGE_TRANSFORMATION_VIEWER_H