#include <opencv2/opencv.hpp>
#include <torch/script.h>
#include <torch/torch.h>

#include <iostream>
#include <fstream>
#include <chrono>

class ModelRunner
{
    public :
        ModelRunner(const char* cModel, const char* cLabels, const char* cImage);
        
        void run();

        std::string getLabelImageClassify();
        float getProbabilityImageClassify();

    private :
        std::vector<double> normMean = {0.485, 0.456, 0.406};
        std::vector<double> normStd = {0.229, 0.224, 0.225};

        const char* pathToModel;
        const char* pathToLabels;
        const char* pathToImage;
        std::string imageClassifylabel;
        float imageClassifyProbability;

        std::vector<std::string> loadLabels(const std::string& pathToLabels);
        torch::Tensor readImage(const std::string& pathToImage);
        cv::Mat cropCenter(const cv::Mat &image);
};