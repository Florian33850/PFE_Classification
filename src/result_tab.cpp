#include "result_tab.h"

ResultTab::ResultTab() : Tab()
{
    this->classificationParametersLayout = new QVBoxLayout;
    this->classificationParametersLayout->addStretch();
    this->mainLayout->addLayout(this->classificationParametersLayout, 0, 0);
    this->resultOutputLayout = new QVBoxLayout;
    this->resultOutputLayout->addStretch();
    this->mainLayout->addLayout(this->resultOutputLayout, 1, 0);

    addClassificationParametersFormLayout();
    addLaunchModelButton();
}

void ResultTab::readAndDisplayOutputResultFile()
{
    QFile outputTrainingFile("outputResult.txt");
    QLabel *outputTrainingFileLabel = new QLabel(this);
    outputTrainingFileLabel->setText("Standard output : ");

    QString line;
    if (outputTrainingFile.open(QIODevice::ReadWrite | QIODevice::Text)){
        QTextStream stream(&outputTrainingFile);
        while (!stream.atEnd()){

            line = stream.readLine();
            outputTrainingFileLabel->setText(outputTrainingFileLabel->text()+"\n"+line);
        }
    }
    outputTrainingFile.close();

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(outputTrainingFileLabel);

    this->resultOutputLayout->insertWidget(this->resultOutputLayout->count()-1, scrollArea);
}

void ResultTab::addClassificationParametersFormLayout()
{
    this->formGroupBox = new QGroupBox(tr("Training parameters"));
    this->formLayout = new QFormLayout;

    this->addPredicitonFileButton = new QPushButton("Add");
    this->predictionFileLineEdit = new QLineEdit();
    this->predictionFileLineEdit->setReadOnly(true);
    connect(addPredicitonFileButton, &QPushButton::released, [=](){this->predictionFileLineEdit->setText(QFileDialog::getOpenFileName(this));});

    this->addModelClassifierButton = new QPushButton("Add");
    this->modelClassifierLineEdit = new QLineEdit();
    this->modelClassifierLineEdit->setReadOnly(true);
    connect(addModelClassifierButton, &QPushButton::released, [=](){this->modelClassifierLineEdit->setText(QFileDialog::getOpenFileName(this));});

    this->addImageButton = new QPushButton("Add");
    this->imageLineEdit = new QLineEdit();
    this->imageLineEdit->setReadOnly(true);
    connect(addImageButton, &QPushButton::released, [=](){this->imageLineEdit->setText(QFileDialog::getOpenFileName(this));});

    this->addLabelsButton = new QPushButton("Add");
    this->labelsLineEdit = new QLineEdit();
    this->labelsLineEdit->setReadOnly(true);
    connect(addLabelsButton, &QPushButton::released, [=](){this->labelsLineEdit->setText(QFileDialog::getOpenFileName(this));});

    this->formLayout->addRow(tr("&File for prediction :"), addPredicitonFileButton);
    this->formLayout->addRow(predictionFileLineEdit);
    this->formLayout->addRow(tr("&Model of classification:"), addModelClassifierButton);
    this->formLayout->addRow(modelClassifierLineEdit);
    this->formLayout->addRow(tr("&Image to classify :"), addImageButton);
    this->formLayout->addRow(imageLineEdit);
    this->formLayout->addRow(tr("&File of labels :"), addLabelsButton);
    this->formLayout->addRow(labelsLineEdit);

    this->formGroupBox->setLayout(this->formLayout);
    this->classificationParametersLayout->insertWidget(this->classificationParametersLayout->count()-1, this->formGroupBox);
}

void ResultTab::addLaunchModelButton()
{
    this->launchModelButton = new QPushButton("Launch classification model");
    connect(this->launchModelButton, &QPushButton::released, this, &ResultTab::handleLaunchModelButton);
    this->classificationParametersLayout->insertWidget(this->classificationParametersLayout->count()-1, this->launchModelButton);
}

void ResultTab::handleLaunchModelButton()
{
    QString pathToPredictionFile = predictionFileLineEdit->text();
    QString pathToModel = modelClassifierLineEdit->text();
    QString pathToImage = imageLineEdit->text();
    QString pathToLabels = labelsLineEdit->text();

    if(!pathToPredictionFile.isEmpty() && !pathToModel.isEmpty() && !pathToImage.isEmpty())
    {
        QImage image;
        image.load(pathToImage);
        ImageLabel *imageLabel = new ImageLabel();
        imageLabel->qImage = image;
        this->resultOutputLayout->insertWidget(this->resultOutputLayout->count()-1, imageLabel);

        this->resultThread = new ResultThread(pathToPredictionFile, pathToModel, pathToImage, pathToLabels);
        connect(resultThread, &QThread::started, this, &ResultTab::handleWaitingResult);
        connect(resultThread, &QThread::finished, this, &ResultTab::handleEndingResult);
        resultThread->start();
    }
}

void ResultTab::handleWaitingResult()
{
    QLabel *waitingResultsLabel = new QLabel(this);
    waitingResultsLabel->setText("Waiting for the classification of the image");
    this->resultOutputLayout->insertWidget(this->resultOutputLayout->count()-1, waitingResultsLabel);
}

void ResultTab::handleEndingResult()
{
    QLabel *endingResultsLabel = new QLabel(this);
    endingResultsLabel->setText("Classification of the image is done");
    this->resultOutputLayout->insertWidget(this->resultOutputLayout->count()-1, endingResultsLabel);

    readAndDisplayOutputResultFile();
}