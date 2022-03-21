#ifndef IMAGE_TRANSFORMATION_VIEWER_H
#define IMAGE_TRANSFORMATION_VIEWER_H

#include <iostream>
#include <QVBoxLayout>
#include <QComboBox>

#include "image_transformation_widget.h"
#include "data_augmentation_widget.h"

class ImageTransformationViewer : public QWidget
{
    Q_OBJECT
    public:
        ImageTransformationViewer(std::vector<ImageLabel*>* imagePreviewList, QWidget *parentWidget = nullptr);

        void launchActivatedPreprocesses();

    protected:
        QVBoxLayout *mainLayout;
        std::vector<ImageLabel*> *imagePreviewList;
        QWidget *parent;
        std::vector<ImageTransformationWidget*> imageTransformationWidgetList;
        std::vector<ImageTransformation*> imageTransformationList;
        QStringList preprocessingStringList = {"Add Preprocessing", "Mirror", "Grayscale", "Automatic Rotation", "Erosion"};

        MirrorWidget* createMirrorImageTransformation();
        GrayscaleWidget* createGrayscaleImageTransformation();
        AutomaticRotationWidget* createAutomaticRotationImageTransformation();
        ErosionWidget* createErosionImageTransformation();

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