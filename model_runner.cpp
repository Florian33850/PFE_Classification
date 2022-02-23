#include "model_runner.h"

ModelRunner::ModelRunner(const char* pathToModel, const char* pathToLabels, const char* pathToImage)
{
    this->pathToModel = pathToModel;
    this->pathToLabels = pathToLabels;
    this->pathToImage = pathToImage;
}

void ModelRunner::run()
{
    auto model = torch::jit::load(pathToModel);
    model.eval();

    std::vector<std::string> labels = loadLabels(pathToLabels);

    std::vector<torch::jit::IValue> images;
    torch::Tensor imageTensor = readImage(pathToImage);
    images.push_back(imageTensor);

    torch::Tensor outputTensor = torch::softmax(model.forward(images).toTensor(), 1);

    std::tuple<torch::Tensor, torch::Tensor> classificationResult = torch::max(outputTensor, 1);

    torch::Tensor classificationProbabilityTensor = std::get<0>(classificationResult);
    torch::Tensor imageIndexTensor = std::get<1>(classificationResult);

    auto classificationProbabilityIndex = classificationProbabilityTensor.accessor<float,1>();
    auto imageIndex = imageIndexTensor.accessor<long,1>();

    this->imageClassifylabel = labels[imageIndex[0]];
    this->imageClassifyProbability = classificationProbabilityIndex[0];
}

std::vector<std::string> ModelRunner::loadLabels(const std::string& pathToLabels)
{
    std::ifstream file(pathToLabels);
    if (!file.is_open())
    {
        printf("Couldn't open labels file\n");
            abort();
    }

    std::vector<std::string> labels;
    std::string line;

    while (getline(file, line))
    {
        labels.push_back(line);
    }

    file.close();

    return labels;
}

torch::Tensor ModelRunner::readImage(const std::string& pathToImage)
{
    cv::Mat imageMat = cv::imread(pathToImage);
    imageMat = cropCenter(imageMat);

    imageMat.convertTo(imageMat, CV_32FC3, 1/255.0);

    torch::Tensor imageTensor = torch::from_blob(imageMat.data, {imageMat.rows, imageMat.cols, 3}, c10::kFloat);
    imageTensor = imageTensor.permute({2, 0, 1});
    imageTensor.unsqueeze_(0);

    imageTensor = torch::data::transforms::Normalize<>(normMean, normStd)(imageTensor);

    return imageTensor.clone();
    return torch::Tensor();
}

cv::Mat ModelRunner::cropCenter(const cv::Mat &imageMat)
{
    const int rows = imageMat.rows;
    const int cols = imageMat.cols;

    const int cropSize = std::min(rows,cols);
    const int offsetWidth = (cols - cropSize) / 2;
    const int offsetHeight = (rows - cropSize) / 2;
    const cv::Rect imageRect(offsetWidth, offsetHeight, cropSize, cropSize);

    return imageMat(imageRect);
}

std::string ModelRunner::getLabelImageClassify()
{
    return imageClassifylabel;
}

float ModelRunner::getProbabilityImageClassify()
{
    return imageClassifyProbability;
}