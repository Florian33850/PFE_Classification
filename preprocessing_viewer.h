#ifndef PREPROCESSING_VIEWER_H
#define PREPROCESSING_VIEWER_H

#include "image_collection.h"
#include "image_label.h"
#include "preprocessing.h"

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
        std::vector<Preprocessing*> qWidgetList;
        QPushButton *launchPreprocessingButton;
        QComboBox *addPreprocessingComboBox;
        ImageCollection *imageCollection;

        void handleLaunchPreprocessingButton();
        void handleAddPreprocessingComboBox();
        void handleMirrored();
        void handleGrayscale();
    
};
#endif // PREPROCESSING_VIEWER_H