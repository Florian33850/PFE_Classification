#ifndef PREPROCESSING_VIEWER_H
#define PREPROCESSING_VIEWER_H

#include "image_collection.h"
#include "image_label.h"
#include "preprocessing.h"
#include "preprocessing_widget.h"

#include <iostream>

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>

class PreprocessingViewer : public QWidget
{
    public:
        explicit PreprocessingViewer(ImageCollection *imageCollection, QWidget *parent = nullptr);

    private:
        QVBoxLayout *mainLayout;
        std::vector<PreprocessingWidget*> preprocessingWidgetList;
        std::vector<Preprocessing*> preprocessingList;

        QPushButton *launchPreprocessingButton;
        QComboBox *addPreprocessingComboBox;
        ImageCollection *imageCollection;

        void handleLaunchPreprocessingButton();
        void handleAddPreprocessingComboBox();
        void handleMirrored();
        void handleGrayscale();    
};
#endif // PREPROCESSING_VIEWER_H