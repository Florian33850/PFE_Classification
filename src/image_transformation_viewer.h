#ifndef IMAGE_TRANSFORMATION_VIEWER_H
#define IMAGE_TRANSFORMATION_VIEWER_H

#include "image_transformation_widget.h"
#include "data_augmentation_widget.h"

#include <iostream>
#include <QVBoxLayout>
#include <QComboBox>

#define MAIN_LAYOUT_MARGIN 1
#define MAIN_LAYOUT_SPACING 1

class ImageTransformationViewer : public QWidget
{
    Q_OBJECT
    public:
        ImageTransformationViewer(std::vector<ImageLabel*>* imagePreviewList, QWidget *parentWidget = nullptr);

        void launchActivatedPreprocesses();
        std::vector<ImageTransformationWidget*> getImageTransformationWidgetList();

    protected:
        QVBoxLayout *mainLayout;
        std::vector<ImageLabel*> *imagePreviewList;
        QWidget *parent;
        std::vector<ImageTransformationWidget*> imageTransformationWidgetList;
        std::vector<ImageTransformation*> imageTransformationList;
        QStringList preprocessingStringList = {"Add Preprocessing", "Mirror", "Grayscale", "Automatic Rotation for Lyme Data", "Morphological Transformation"};

        MirrorWidget* createMirrorImageTransformation();
        GrayscaleWidget* createGrayscaleImageTransformation();
        AutomaticRotationLymeDataWidget* createAutomaticRotationLymeDataImageTransformation();
        MorphologicalTransformationWidget* createMorphologicalTransformationImageTransformation();

        void handleLaunchImageTransformationButton();
        void handleImageTransformationComboBox();
        void handleDeleteImageTransformationWidgetButton(ImageTransformationWidget* imageTransformationWidget);

    Q_SIGNALS:
        void reloadPreviewSignal();
};

class PreprocessingViewer : public ImageTransformationViewer
{
    Q_OBJECT
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
    Q_OBJECT
    public:
        DataAugmentationViewer(std::vector<ImageLabel*>* imagePreviewList, QWidget *parentWidget = nullptr);

    private:
        std::vector<DataAugmentationWidget*> dataAugmentationWidgetList;
        QPushButton *addDataAugmentationButton;

        void addAddDataAugmentationButton();

        void handleAddDataAugmentationButton();

    public Q_SLOTS:
        void handlePreview(DataAugmentationWidget* sender);
};

#endif // IMAGE_TRANSFORMATION_VIEWER_H