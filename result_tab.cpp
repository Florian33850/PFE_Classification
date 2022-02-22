#include "result_tab.h"

ResultTab::ResultTab(Tab *parent): Tab(parent)
{
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    modelH5CheckBox = new QCheckBox("Model (*.h5)", this);
    modelH5CheckBox->setCheckState(Qt::Checked);
    modelPtCheckBox = new QCheckBox("Model (*.pt)", this);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);
    buttonGroup->addButton(modelH5CheckBox);
    buttonGroup->addButton(modelPtCheckBox);
    typeOfModelLayout = new QVBoxLayout;
    typeOfModelLayout->addWidget(modelH5CheckBox);
    typeOfModelLayout->addWidget(modelPtCheckBox);
    QGroupBox *groupBox = new QGroupBox("Type of classification model");
    groupBox->setLayout(typeOfModelLayout);
    mainLayout->addWidget(groupBox);

    loadModelButton = new QPushButton("Load classification model");
    connect(loadModelButton, &QPushButton::released, this, &ResultTab::handleLoadModelButton);
    mainLayout->addWidget(loadModelButton);

    launchModelButton = new QPushButton("Launch classification model");
    connect(launchModelButton, &QPushButton::released, this, &ResultTab::handleLaunchModelButton);
    mainLayout->addWidget(launchModelButton);

    mainLayout->addStretch();

    isModelLoad = false;
}
 
void ResultTab::handleLoadModelButton()
{
    pathToModel = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION MODEL to LOAD"), "../data/models");
    if (pathToModel == NULL)
    {
        printf("model loading problem\n");
        return;
    }

    if(modelPtCheckBox->checkState() == Qt::Checked)
    {
        pathToLabels = QFileDialog::getOpenFileName(this, tr("Select CLASSIFICATION LABELS to LOAD"), "../data/labels", tr("TXT (*.txt)"));
        if (pathToLabels == NULL)
        {
            printf("labels loading problem\n");
            return;
        }
    }
    else if(modelH5CheckBox->checkState() == Qt::Checked)
    {
        pathToPredictionFile = QFileDialog::getOpenFileName(this, tr("Select PREDICTION PYTHON FILE"), "../data/code/prediction", tr("PY (*.py)"));
        if (pathToPredictionFile == NULL)
        {
            printf("prediction file loading problem\n");
            return;
        }
    }

    pathToImage = QFileDialog::getOpenFileName(this, tr("Select IMAGE to CLASSIFY"), "../data/images", tr("JPEG (*.jpeg, *.jpg);;PNG (*.png)"));
    if (pathToImage == NULL)
    {
        printf("image loading problem\n");
        return;
    }

    QImage qImg;
    qImg.load(pathToImage);
    ImageLabel *imageLabel = new ImageLabel();
    imageLabel->setImage(qImg);
    mainLayout->insertWidget(mainLayout->count()-1, imageLabel);

    isModelLoad = true;
}

void ResultTab::handleLaunchModelButton()
{
    if(isModelLoad == true && modelPtCheckBox->checkState() == Qt::Checked)
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
    else if(isModelLoad == true && modelH5CheckBox->checkState() == Qt::Checked)
    {
        ResultThread *thread = new ResultThread(pathToPredictionFile, pathToModel, pathToImage);
        connect(thread, &QThread::started, this, &ResultTab::handleWaitingResult);
        connect(thread, &QThread::finished, this, &ResultTab::handleEndingResult);
        thread->start();
    }
}

void ResultTab::printClassificationResults(ModelRunner model)
{
    QLabel *label = new QLabel(this);
    label->setText("Image label : " + QString::fromUtf8(model.getLabelImageClassify().c_str()) + " Classification probability : " + QString::number(model.getProbabilityImageClassify()));
    mainLayout->insertWidget(mainLayout->count()-1, label);
}

void ResultTab::handleWaitingResult()
{
    QLabel *label = new QLabel(this);
    label->setText("Waiting for the classification of the image");
    mainLayout->insertWidget(mainLayout->count()-1, label);
}

void ResultTab::handleEndingResult()
{
    QLabel *label = new QLabel(this);
    label->setText("Classification of the image is done");
    mainLayout->insertWidget(mainLayout->count()-1, label);
}