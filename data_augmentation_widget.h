#ifndef DATA_AUGMENTATION_WIDGET_H
#define DATA_AUGMENTATION_WIDGET_H

#include "image_transformation_widget.h"

class DataAugmentationWidget : public QWidget
{
    Q_OBJECT
    public:
        DataAugmentationWidget(QWidget *parentWidget);
    
        std::vector<ImageTransformation*> imageTransformationList;

    private:
        QVBoxLayout *mainLayout;
        QWidget *parentWidget;
        QPushButton *previewButton;
        QCheckBox *mirrorCheckBox;


        MirrorWidget *mirrorWidget;

        void deleteImageTransformationWidget(ImageTransformationWidget *imageTransformationWidget);

        void addMirrorCheckBox();
        void addPreviewButton();

        void handleMirrorCheckbox();
        void handleDeleteImageTransformationWidgetButton();
        void handlePreviewButton();
};

#endif // DATA_AUGMENTATION_WIDGET_H