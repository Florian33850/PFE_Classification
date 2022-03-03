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
        PreprocessingWidget(QVBoxLayout *mainLayout, QWidget *parentWidget);

        bool isActivated;
        Preprocessing *preprocess;
        
        virtual void displayUI() = 0;
        void deleteMainWidgetGroupBox();

        QPushButton* getDeletePreprocessingWidgetButton();
        
    protected:
        QVBoxLayout *mainLayout;
        QWidget *parentWidget;
        QGroupBox *mainWidgetGroupBox;
        QPushButton *deletePreprocessingWidgetButton;

        void connectWidgetDeleteButton();
};

class MirrorWidget : public PreprocessingWidget
{
    public:
        MirrorWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, MirrorPreprocess *mirrorPreprocessing);

        void displayUI();
    
    private:
        QCheckBox *horizontalMirrorCheckBox;
        QCheckBox *verticalMirrorCheckBox;
};

class GrayscaleWidget : public PreprocessingWidget
{
    public:
        GrayscaleWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, GrayscalePreprocess *grayscale);

        void displayUI();
};

#endif // PREPROCESSING_WIDGET_H