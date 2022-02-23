#include "result_tab.h"

ResultTab::ResultTab(Tab *parent): Tab(parent)
{
    this->mainLayout = new QVBoxLayout;
    this->setLayout(this->mainLayout);

    addModelGroupBox();
    addLoadModelButton();
    addLaunchModelButton();

    this->mainLayout->addStretch();

    this->isModelLoad = false;
}

void ResultTab::printClassificationResults(ModelRunner model)
{
    QLabel *classificationResultsLabel = new QLabel(this);
    classificationResultsLabel->setText("Image label : " + QString::fromUtf8(model.getLabelImageClassify().c_str()) + " Classification probability : " + QString::number(model.getProbabilityImageClassify()));
    this->mainLayout->insertWidget(this->mainLayout->count()-1, classificationResultsLabel);
}

void ResultTab::addModelGroupBox()
{
    this->modelH5CheckBox = new QCheckBox("Model (*.h5)", this);
    this->modelH5CheckBox->setCheckState(Qt::Checked);
    this->modelPtCheckBox = new QCheckBox("Model (*.pt)", this);

    this->modelButtonGroup = new QButtonGroup(this);
    this->modelButtonGroup->setExclusive(true);
    this->modelButtonGroup->addButton(this->modelH5CheckBox);
    this->modelButtonGroup->addButton(this->modelPtCheckBox);

    this->typeOfModelLayout = new QVBoxLayout;
    this->typeOfModelLayout->addWidget(this->modelH5CheckBox);
    this->typeOfModelLayout->addWidget(this->modelPtCheckBox);

    this->modelGroupBox = new QGroupBox("Type of classification model");

    this->modelGroupBox->setLayout(this->typeOfModelLayout);
    this->mainLayout->addWidget(this->modelGroupBox);
}

void ResultTab::addLoadModelButton()
{
    this->loadModelButton = new QPushButton("Load classification model");
    connect(this->loadModelButton, &QPushButton::released, this, &ResultTab::handleLoadModelButton);
    this->mainLayout->addWidget(this->loadModelButton);
}

void ResultTab::addLaunchModelButton()
{
    this->launchModelButton = new QPushButton("Launch classification model");
    connect(this->launchModelButton, &QPushButton::released, this, &ResultTab::handleLaunchModelButton);
    this->mainLayout->addWidget(this->launchModelButton);
}

void ResultTab::handleLoadModelButton()
{
    this->pathToModel = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION MODEL to LOAD"), "../data/models");
    if (this->pathToModel == NULL)
    {
        printf("model loading problem\n");
        return;
    }

    if(this->modelPtCheckBox->checkState() == Qt::Checked)
    {
        this->pathToLabels = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION LABELS to LOAD"), "../data/labels", tr("TXT (*.txt)"));
        if (this->pathToLabels == NULL)
        {
            printf("labels loading problem\n");
            return;
        }
    }
    else if(this->modelH5CheckBox->checkState() == Qt::Checked)
    {
        this->pathToPredictionFile = QFileDialog::getOpenFileName(this, tr("Select PREDICTION PYTHON FILE"), "../data/code/prediction", tr("PY (*.py)"));
        if (this->pathToPredictionFile == NULL)
        {
            printf("prediction file loading problem\n");
            return;
        }
    }

    this->pathToImage = QFileDialog::getOpenFileName(this, tr("Select IMAGE to CLASSIFY"), "../data/images", tr("JPEG (*.jpeg, *.jpg);;PNG (*.png)"));
    if (this->pathToImage == NULL)
    {
        printf("image loading problem\n");
        return;
    }

    QImage image;
    image.load(this->pathToImage);
    ImageLabel *imageLabel = new ImageLabel();
    imageLabel->setImage(image);
    this->mainLayout->insertWidget(this->mainLayout->count()-1, imageLabel);

    this->isModelLoad = true;
}

void ResultTab::handleLaunchModelButton()
{
    if(this->isModelLoad == true)
    {
        if(this->modelPtCheckBox->checkState() == Qt::Checked)
        {
            QByteArray ba_pathToModel = this->pathToModel.toLocal8Bit();
            const char *c_pathToModel = ba_pathToModel.data();

            QByteArray ba_pathToLabels = this->pathToLabels.toLocal8Bit();
            const char *c_pathToLabels = ba_pathToLabels.data();

            QByteArray ba_pathToImage = this->pathToImage.toLocal8Bit();
            const char *c_pathToImage = ba_pathToImage.data();

            ModelRunner model(c_pathToModel, c_pathToLabels, c_pathToImage);
            model.run();
            printClassificationResults(model);
        }
        else if(this->modelH5CheckBox->checkState() == Qt::Checked)
        {
            ResultThread *thread = new ResultThread(this->pathToPredictionFile, this->pathToModel, this->pathToImage);
            connect(thread, &QThread::started, this, &ResultTab::handleWaitingResult);
            connect(thread, &QThread::finished, this, &ResultTab::handleEndingResult);
            thread->start();
        }
    }
}

void ResultTab::handleWaitingResult()
{
    QLabel *waitingResultsLabel = new QLabel(this);
    waitingResultsLabel->setText("Waiting for the classification of the image");
    this->mainLayout->insertWidget(this->mainLayout->count()-1, waitingResultsLabel);
}

void ResultTab::handleEndingResult()
{
    QLabel *endingResultsLabel = new QLabel(this);
    endingResultsLabel->setText("Classification of the image is done");
    this->mainLayout->insertWidget(this->mainLayout->count()-1, endingResultsLabel);
}