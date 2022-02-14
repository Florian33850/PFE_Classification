#ifndef PPREPROCESSING_WIDGET_H
#define PREPROCESSING_WIDGET_H

#include "preprocessing.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QGroupBox>


class PreprocessingWidget : public QWidget
{
    public:
        virtual void displayUI() = 0;
        
    protected:
        QGroupBox *mainWidgetGroupBox;
        QLayout *parentLayout;
        QWidget *parentWidget;
};

class MirroredWidget : public PreprocessingWidget
{
    public:
        MirroredWidget(QLayout *parentLayout, QWidget *parentWidget, Mirrored *mirrored);

        void displayUI();
    
    private:
        QCheckBox *horizontalMirrorCheckBox;
        QCheckBox *verticalMirrorCheckBox;
        Mirrored *mirrored;
};

class GrayscaleWidget : public PreprocessingWidget
{
    public:
        GrayscaleWidget(QLayout *parentLayout, QWidget *parentWidget, Grayscale *grayscale);

        void displayUI();
    
    private:
        Grayscale *grayscale;
};


#endif // P_WIDGET_H