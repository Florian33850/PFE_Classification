#include <iostream>
#include <fstream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <torch/script.h>
#include <torch/torch.h>

class ModelRunner
{
    private :
    
    std::vector<std::string> load_labels(const std::string& fileName);
    torch::Tensor read_image(const std::string& imageName);
    cv::Mat crop_center(const cv::Mat &img);

    std::vector<double> norm_mean = {0.485, 0.456, 0.406};
    std::vector<double> norm_std = {0.229, 0.224, 0.225};

    std::string labelImageClassify;
    float probabilityImageClassify;

    const char* classificationModel;
    const char* classificationLabels;
    const char* classificationImage;

    public :

    ModelRunner(const char* cModel, const char* cLabels, const char* cImage);
    void run();
    std::string getLabelImageClassify();
    float getProbabilityImageClassify();
};