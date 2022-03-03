#include "result_tab.h"

ResultTab::ResultTab(Tab *parent): Tab(parent)
{
    addModelGroupBox();
    addLoadModelButton();
    addLaunchModelButton();

    this->isModelLoad = false;
}

void ResultTab::addModelGroupBox()
{
    this->modelH5CheckBox = new QCheckBox("Select classification model (*.h5) with prediction file and an image to classify", this);
    this->modelH5CheckBox->setCheckState(Qt::Checked);
    this->modelPtCheckBox = new QCheckBox("Select classification model (*.pt) with labels file and an image to classify", this);

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
    this->pathToModel = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION MODEL to LOAD"));
    if (this->pathToModel == NULL)
    {
        printf("model loading problem\n");
        return;
    }

    if(this->modelPtCheckBox->checkState() == Qt::Checked)
    {
        this->pathToLabels = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION LABELS to LOAD"), tr("TXT (*.txt)"));
        if (this->pathToLabels == NULL)
        {
            printf("labels loading problem\n");
            return;
        }
    }
    else if(this->modelH5CheckBox->checkState() == Qt::Checked)
    {
        this->pathToPredictionFile = QFileDialog::getOpenFileName(this, tr("Select PREDICTION PYTHON FILE"), tr("PY (*.py)"));
        if (this->pathToPredictionFile == NULL)
        {
            printf("prediction file loading problem\n");
            return;
        }
    }

    this->pathToImage = QFileDialog::getOpenFileName(this, tr("Select IMAGE to CLASSIFY"), tr("JPEG (*.jpeg, *.jpg);;PNG (*.png)"));
    if (this->pathToImage == NULL)
    {
        printf("image loading problem\n");
        return;
    }

    QImage image;
    image.load(this->pathToImage);
    ImageLabel *imageLabel = new ImageLabel();
    imageLabel->setImage(image);
    this->mainLayout->addWidget(imageLabel);

    this->isModelLoad = true;
}

void ResultTab::handleLaunchModelButton()
{
    if(this->isModelLoad == true)
    {
        if(this->modelH5CheckBox->checkState() == Qt::Checked)
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
    this->mainLayout->addWidget(waitingResultsLabel);
}

void ResultTab::handleEndingResult()
{
    QLabel *endingResultsLabel = new QLabel(this);
    endingResultsLabel->setText("Classification of the image is done");
    this->mainLayout->addWidget(endingResultsLabel);
}