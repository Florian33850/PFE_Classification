#ifndef PREPROCESSING_VIEWER_H
#define PREPROCESSING_VIEWER_H

#include "preprocessing_widget.h"

#include <iostream>
#include <QVBoxLayout>
#include <QComboBox>

class PreprocessingViewer : public QWidget
{
    public:
        PreprocessingViewer(ImageCollection *imageCollection, QWidget *parent = nullptr);

        void launchActivatedPreprocesses();

    private:
        QVBoxLayout *mainLayout;
        ImageCollection *imageCollection;
        std::vector<PreprocessingWidget*> preprocessingWidgetList;
        std::vector<Preprocessing*> preprocessingList;

        QPushButton *launchPreprocessingButton;
        QComboBox *addPreprocessingComboBox;
        QStringList preprocessingStringList = {"Add Preprocessing", "Mirror", "Grayscale"};

        void addLaunchPreprocessingButton();
        void addAddPreprocessingComboBox();
        
        MirrorWidget* createMirrorPreprocess();
        GrayscaleWidget* createGrayscalePreprocess();
        
        void handleLaunchPreprocessingButton();
        void handlePreprocessingComboBox();
        void handleDeletePreprocessingWidgetButton(PreprocessingWidget* preprocessingWidget);
};
#endif // PREPROCESSING_VIEWER_H