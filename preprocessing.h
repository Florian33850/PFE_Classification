#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "image_collection.h"
#include "image_label.h"

class Preprocessing
{
    public:
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

    private:
        void runPreprocess(ImageCollection *imageCollection);
};

class Grayscale : public Preprocessing
{
    public:
        explicit Grayscale(Preprocessing *parent = nullptr);
    
    private:
        void runPreprocess(ImageCollection *imageCollection);
};

#endif // PREPROCESSING_H