#ifndef PPREPROCESSING_WIDGET_H
#define PREPROCESSING_WIDGET_H

#include "preprocessing.h"

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>

#define MIRRORED_WIDGET_MAXIMUM_HEIGHT 110
#define GRAYSCALE_WIDGET_MAXIMUM_HEIGHT 65

class PreprocessingWidget : public QWidget
{
    public:
        PreprocessingWidget(QLayout *mainLayout, QWidget *parentWidget);

        bool isActivated;
        Preprocessing *preprocess;
        
        virtual void displayUI() = 0;
        void deleteMainWidgetGroupBox();
        QPushButton* getDeletePreprocessingWidgetButton();
        
    protected:
        QGroupBox *mainWidgetGroupBox;
        QPushButton *deletePreprocessingWidgetButton;
        QLayout *mainLayout;
        QWidget *parentWidget;

        void connectWidgetDeleteButton();
};

class MirrorWidget : public PreprocessingWidget
{
    public:
        MirrorWidget(QLayout *mainLayout, QWidget *parentWidget, MirrorPreprocess *mirrorPreprocessing);

        void displayUI();
    
    private:
        QCheckBox *horizontalMirrorCheckBox;
        QCheckBox *verticalMirrorCheckBox;
};

class GrayscaleWidget : public PreprocessingWidget
{
    public:
        GrayscaleWidget(QLayout *mainLayout, QWidget *parentWidget, GrayscalePreprocess *grayscale);

        void displayUI();
};

#endif // PREPROCESSING_WIDGET_H