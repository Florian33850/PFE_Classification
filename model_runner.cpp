#include "model_runner.h"

ModelRunner::ModelRunner(const char* cModel, const char* cLabels, const char* cImage)
{
    classificationModel = cModel;
    classificationLabels = cLabels;
    classificationImage = cImage;
}

void ModelRunner::run()
{
    auto model = torch::jit::load(classificationModel);
    model.eval();

    std::vector<std::string> labels = load_labels(classificationLabels);

    std::vector<torch::jit::IValue> inputs;
    torch::Tensor in = read_image(classificationImage);
    inputs.push_back(in);

    torch::Tensor output = torch::softmax(model.forward(inputs).toTensor(), 1);

    std::tuple<torch::Tensor, torch::Tensor> result = torch::max(output, 1);

    torch::Tensor prob = std::get<0>(result);
    torch::Tensor index = std::get<1>(result);

    auto probability = prob.accessor<float,1>();
    auto idx = index.accessor<long,1>();

    labelImageClassify = labels[idx[0]];
    probabilityImageClassify = probability[0];
}

std::vector<std::string> ModelRunner::load_labels(const std::string& fileName)
{
    std::ifstream ins(fileName);
    if (!ins.is_open())
    {
        std::cerr << "Couldn't open " << fileName << std::endl;
        abort();
    }

    std::vector<std::string> labels;
    std::string line;

    while (getline(ins, line))
        labels.push_back(line);

    ins.close();

    return labels;
}

torch::Tensor ModelRunner::read_image(const std::string& imageName)
{
    cv::Mat img = cv::imread(imageName);
    img = crop_center(img);
    // cv::resize(img, img, cv::Size(224,224));
    
    // if (img.channels()==1)
    //     cv::cvtColor(img, img, cv::COLOR_GRAY2RGB);
    // else
    //     cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

    img.convertTo( img, CV_32FC3, 1/255.0 );

    torch::Tensor img_tensor = torch::from_blob(img.data, {img.rows, img.cols, 3}, c10::kFloat);
    img_tensor = img_tensor.permute({2, 0, 1});
    img_tensor.unsqueeze_(0);

    img_tensor = torch::data::transforms::Normalize<>(norm_mean, norm_std)(img_tensor);

    return img_tensor.clone();
    return torch::Tensor();
}

cv::Mat ModelRunner::crop_center(const cv::Mat &img)
{
    const int rows = img.rows;
     const int cols = img.cols;

    const int cropSize = std::min(rows,cols);
    const int offsetW = (cols - cropSize) / 2;
    const int offsetH = (rows - cropSize) / 2;
    const cv::Rect roi(offsetW, offsetH, cropSize, cropSize);

    return img(roi);
}

std::string ModelRunner::getLabelImageClassify()
{
    return labelImageClassify;
}

float ModelRunner::getProbabilityImageClassify()
{
    return probabilityImageClassify;
}