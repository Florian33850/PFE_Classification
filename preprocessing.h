#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "image_collection.h"
#include "image_label.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QGroupBox>


class Preprocessing
{
    public:
        void displayUI(QLayout *layout, QWidget *parent);
        virtual void runPreprocess(ImageCollection *imageCollection) = 0;
    private:
};

class Mirrored : public Preprocessing
{   
    public:
        explicit Mirrored(Preprocessing *parent = nullptr);

        bool horizontalMirror;
        bool verticalMirror;
        
        void changeHorizontalMirrorMode();
        void changeVerticalMirrorMode();

        void displayUI(QLayout *layout, QWidget *parent);

    private:
        void runPreprocess(ImageCollection *imageCollection);
};

class Grayscale : public Preprocessing
{
    public:
        explicit Grayscale(Preprocessing *parent = nullptr);

        void displayUI(QLayout *layout, QWidget *parent);
    
    private:
        void runPreprocess(ImageCollection *imageCollection);
};

#endif // PREPROCESSING_H