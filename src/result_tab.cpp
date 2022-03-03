#include "result_tab.h"

ResultTab::ResultTab(Tab *parent): Tab(parent)
{
    this->mainLayout = new QVBoxLayout;
    this->setLayout(this->mainLayout);

    addClassificationParametersFormLayout();
    addLaunchModelButton();

    this->mainLayout->addStretch();
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

    this->mainLayout->insertWidget(this->mainLayout->count()-1, scrollArea);
}

void ResultTab::addClassificationParametersFormLayout()
{
    this->formGroupBox = new QGroupBox(tr("Training parameters"));
    this->formLayout = new QFormLayout;

    this->addPredicitonFileButton = new QPushButton("Add");
    this->predictionFileLineEdit = new QLineEdit();
    this->predictionFileLineEdit->setReadOnly(true);
    connect(addPredicitonFileButton, &QPushButton::released, [=](){this->handleAddFileToQlineEdit(predictionFileLineEdit);});
    
    this->addModelClassifierButton = new QPushButton("Add");
    this->modelClassifierLineEdit = new QLineEdit();
    this->modelClassifierLineEdit->setReadOnly(true);
    connect(addModelClassifierButton, &QPushButton::released, [=](){this->handleAddFileToQlineEdit(modelClassifierLineEdit);});
    
    this->addLabelsButton = new QPushButton("Add");
    this->labelsLineEdit = new QLineEdit();
    this->labelsLineEdit->setReadOnly(true);
    connect(addLabelsButton, &QPushButton::released, [=](){this->handleAddFileToQlineEdit(labelsLineEdit);});

    this->addImageButton = new QPushButton("Add");
    this->imageLineEdit = new QLineEdit();
    this->imageLineEdit->setReadOnly(true);
    connect(addImageButton, &QPushButton::released, [=](){this->handleAddFileToQlineEdit(imageLineEdit);});

    this->formLayout->addRow(tr("&File for prediction :"), addPredicitonFileButton);
    this->formLayout->addRow(predictionFileLineEdit);
    this->formLayout->addRow(tr("&Model of classification:"), addModelClassifierButton);
    this->formLayout->addRow(modelClassifierLineEdit);
    this->formLayout->addRow(tr("&File of labels :"), addLabelsButton);
    this->formLayout->addRow(labelsLineEdit);
    this->formLayout->addRow(tr("&Image to classify :"), addImageButton);
    this->formLayout->addRow(imageLineEdit);

    this->formGroupBox->setLayout(formLayout);
    this->mainLayout->addWidget(formGroupBox);
}

void ResultTab::addLaunchModelButton()
{
    this->launchModelButton = new QPushButton("Launch classification model");
    connect(this->launchModelButton, &QPushButton::released, this, &ResultTab::handleLaunchModelButton);
    this->mainLayout->addWidget(this->launchModelButton);
}

void ResultTab::handleLaunchModelButton()
{
    QString pathToPredictionFile = predictionFileLineEdit->text();
    QString pathToModel = modelClassifierLineEdit->text();
    QString pathToLabels = labelsLineEdit->text();
    QString pathToImage = imageLineEdit->text();

    if(pathToPredictionFile != NULL && pathToModel != NULL && pathToImage != NULL)
    {
        QImage image;
        image.load(pathToImage);
        ImageLabel *imageLabel = new ImageLabel();
        imageLabel->setImage(image);
        this->mainLayout->insertWidget(this->mainLayout->count()-1, imageLabel);

        ResultThread *thread = new ResultThread(pathToPredictionFile, pathToModel, pathToLabels, pathToImage);
        connect(thread, &QThread::started, this, &ResultTab::handleWaitingResult);
        connect(thread, &QThread::finished, this, &ResultTab::handleEndingResult);
        thread->start();
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

    readAndDisplayOutputResultFile();
}