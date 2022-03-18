#ifndef PREPROCESSING_VIEWER_H
#define PREPROCESSING_VIEWER_H

#include "image_transformation_widget.h"

#include <iostream>
#include <QVBoxLayout>
#include <QComboBox>
#include <QVector>

class PreprocessingViewer : public QWidget
{
    public:
        PreprocessingViewer(std::vector<ImageLabel*>* imagePreviewList, QWidget *parent = nullptr);

        void launchActivatedPreprocesses();

    private:
        QVBoxLayout *mainLayout;
        std::vector<ImageLabel*> *imagePreviewList;
        std::vector<ImageTransformationWidget*> imageTransformationWidgetList;
        std::vector<ImageTransformation*> preprocessingList;

        QPushButton *launchPreprocessingButton;
        QComboBox *addPreprocessingComboBox;
        QStringList preprocessingStringList = {"Add Preprocessing", "Mirror", "Grayscale"};

        void addLaunchPreprocessingButton();
        void addAddPreprocessingComboBox();
        
        MirrorWidget* createMirrorImageTransformation();
        GrayscaleWidget* createGrayscaleImageTransformation();
        
        void handleLaunchPreprocessingButton();
        void handlePreprocessingComboBox();
        void handleDeleteImageTransformationWidgetButton(ImageTransformationWidget* imageTransformationWidget);

};
#endif // PREPROCESSING_VIEWER_H