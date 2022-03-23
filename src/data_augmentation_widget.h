#ifndef DATA_AUGMENTATION_WIDGET_H
#define DATA_AUGMENTATION_WIDGET_H

#include "image_transformation_widget.h"

class DataAugmentationWidget : public QWidget
{
    Q_OBJECT
    public:
        explicit DataAugmentationWidget(QWidget *parentWidget);

        enum transformationWidgetsEnum{mirror=0, grayscale=1};
        std::vector<ImageTransformationWidget*> imageTransformationWidgetList;

    Q_SIGNALS:
        void previewSignal(DataAugmentationWidget* sender);

    private:
        QVBoxLayout *mainLayout;
        QWidget *parentWidget;
        QPushButton *previewButton;

        QCheckBox *mirrorCheckBox;
        QCheckBox *grayscaleCheckBox;

        MirrorWidget *mirrorWidget;
        GrayscaleWidget *grayscaleWidget;

        void addMirrorCheckBox();
        void addGrayscaleCheckBox();
        void addPreviewButton();
        void deleteImageTransformationWidget(ImageTransformationWidget *imageTransformationWidget);
        ImageTransformationWidget* initialiseImageTransformationWidget(transformationWidgetsEnum index);

        void handleImageTransformationCheckBox(ImageTransformationWidget *imageTransformationWidget, QCheckBox *imageTransformationCheckbox, transformationWidgetsEnum index);
        void handleDeleteImageTransformationWidgetButton(ImageTransformationWidget *imageTransformationWidget, QCheckBox *imageTransformationCheckbox);
        void handlePreviewButton();
};

#endif // DATA_AUGMENTATION_WIDGET_H