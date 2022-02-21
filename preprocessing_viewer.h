#ifndef PREPROCESSING_VIEWER_H
#define PREPROCESSING_VIEWER_H

#include "preprocessing_widget.h"

#include <iostream>
#include <QVBoxLayout>
#include <QComboBox>

class PreprocessingViewer : public QWidget
{
    public:
        explicit PreprocessingViewer(ImageCollection *imageCollection, QWidget *parent = nullptr);

        void launchActivatedPreprocesses();
    private:
        QVBoxLayout *mainLayout;
        std::vector<PreprocessingWidget*> preprocessingWidgetList;
        std::vector<Preprocessing*> preprocessingList;

        QPushButton *launchPreprocessingButton;
        QComboBox *addPreprocessingComboBox;
        ImageCollection *imageCollection;

        void handleLaunchPreprocessingButton();
        void handleAddPreprocessingComboBox();
        void connectWidgetDeleteButton(QPushButton* deleteWidgetButton, PreprocessingWidget* preprocessingWidgetToDelete);
        void handleDeletePreprocessingWidgetButton(PreprocessingWidget* preprocessingWidget);
        MirrorWidget* addMirrorPreprocess();
        GrayscaleWidget* addGrayscalePreprocess();    
};

#endif // PREPROCESSING_VIEWER_H