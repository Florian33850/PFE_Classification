#include "classification_training_tab.h"

ClassificationTrainingTab::ClassificationTrainingTab(Tab *parent): Tab(parent)
{
    mainLayout = new QVBoxLayout;
    
    QPushButton *loadModelButton = new QPushButton("Load classification model");
    connect(loadModelButton, &QPushButton::released, this, &ClassificationTrainingTab::handleLoadModelButton);
    mainLayout->addWidget(loadModelButton);

    QPushButton *launchModelButton = new QPushButton("Launch classification model");
    connect(launchModelButton, &QPushButton::released, this, &ClassificationTrainingTab::handleLaunchModelButton);
    mainLayout->addWidget(launchModelButton);

    setLayout(mainLayout);
}

void ClassificationTrainingTab::handleLoadModelButton()
{
    pathToModel = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION MODEL to LOAD"), "../data", tr("PT (*.pt)"));
    if (pathToModel == NULL)
    {
        printf("model loading problem\n");
        return;
    }

    pathToLabels = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION LABELS to LOAD"), "../data", tr("TXT (*.txt)"));
    if (pathToLabels == NULL)
    {
        printf("labels loading problem\n");
        return;
    }

    pathToImage = QFileDialog::getOpenFileName(this, tr("Select IMAGE to CLASSIFY"), "../data", tr("JPEG (*.jpeg, *.jpg);;PNG(*.png)"));
    if (pathToImage == NULL)
    {
        printf("image loading problem\n");
        return;
    }

    QImage qImg;
    qImg.load(pathToImage);
    ImageLabel *imageLabel = new ImageLabel();
    imageLabel->setImage(qImg);
    mainLayout->addWidget(imageLabel);

    modelLoad = true;
}

void ClassificationTrainingTab::handleLaunchModelButton()
{
    if(modelLoad == true)
    {
        QByteArray ba_pathToModel = pathToModel.toLocal8Bit();
        const char *c_pathToModel = ba_pathToModel.data();

        QByteArray ba_pathToLabels = pathToLabels.toLocal8Bit();
        const char *c_pathToLabels = ba_pathToLabels.data();

        QByteArray ba_pathToImage = pathToImage.toLocal8Bit();
        const char *c_pathToImage = ba_pathToImage.data();

        ModelRunner model(c_pathToModel, c_pathToLabels, c_pathToImage);
        model.run();
        printClassificationResults(model);
    }
}

void ClassificationTrainingTab::printClassificationResults(ModelRunner model)
{
    QLabel *label = new QLabel(this);
    label->setText("Image label : " + QString::fromUtf8(model.getLabelImageClassify().c_str()) + " Classification probability : " + QString::number(model.getProbabilityImageClassify()));
    mainLayout->addWidget(label);
}