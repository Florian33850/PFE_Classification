#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "image_collection.h"

class Preprocessing
{
    public:
        virtual void runPreprocess(ImageCollection *imageCollection) = 0;
};

class MirrorPreprocess : public Preprocessing
{   
    public:
        MirrorPreprocess();

        bool horizontalMirror;
        bool verticalMirror;
        
        void changeHorizontalMirrorMode();
        void changeVerticalMirrorMode();

    private:
        void runPreprocess(ImageCollection *imageCollection);
};

class GrayscalePreprocess : public Preprocessing
{
    public:
        GrayscalePreprocess();
    
    private:
        void runPreprocess(ImageCollection *imageCollection);
};

#endif // PREPROCESSING_H