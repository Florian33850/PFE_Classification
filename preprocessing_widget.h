#ifndef PPREPROCESSING_WIDGET_H
#define PREPROCESSING_WIDGET_H

#include "preprocessing.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QGroupBox>
#include <QUuid>


class PreprocessingWidget : public QWidget
{
    public:
        QUuid *quuid;
        
        virtual void displayUI() = 0;
        QPushButton* getDeletePreprocessingWidgetButton();
        
        void deleteMainWidgetGroupBox();
        
    protected:
        QGroupBox *mainWidgetGroupBox;
        QPushButton *deletePreprocessingWidgetButton;
        QLayout *parentLayout;
        QWidget *parentWidget;

        void connectWidgetDeleteButton();
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