#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "image_label.h"

class Preprocessing
{
    public:
        virtual void runPreprocess(std::vector<ImageLabel*> *imagePreviewList) = 0;
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
        void runPreprocess(std::vector<ImageLabel*> *imagePreviewList);
};

class GrayscalePreprocess : public Preprocessing
{
    public:
        GrayscalePreprocess();
    
    private:
        void runPreprocess(std::vector<ImageLabel*> *imagePreviewList);
};

#endif // PREPROCESSING_H