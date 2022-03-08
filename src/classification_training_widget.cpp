#include "classification_training_widget.h"

ClassificationTrainingWidget::ClassificationTrainingWidget(QVBoxLayout *parametersLayout, QVBoxLayout *trainingOutputLayout)
{
    this->parametersLayout = parametersLayout;
    this->trainingOutputLayout = trainingOutputLayout;

    this->formGroupBox = new QGroupBox(tr("Training parameters"));
    this->formLayout = new QFormLayout;

    this->launchTrainingClassifierButton = new QPushButton("Launch training");
    this->parametersLayout->insertWidget(this->parametersLayout->count()-1, this->launchTrainingClassifierButton);
}

void ClassificationTrainingWidget::readAndDisplayOutputTrainingFile()
{
    QFile outputTrainingFile("outputTraining.txt");
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

    this->trainingOutputLayout->insertWidget(this->trainingOutputLayout->count()-1, scrollArea);
}

void ClassificationTrainingWidget::handleWaitingClassification()
{
    QLabel *waitingCLassificationLabel = new QLabel(this);
    waitingCLassificationLabel->setText("Waiting for classification training");
    this->trainingOutputLayout->insertWidget(this->trainingOutputLayout->count()-1, waitingCLassificationLabel);
}

void ClassificationTrainingWidget::handleEndingClassification()
{
    QLabel *endingClassificationLabel = new QLabel(this);
    endingClassificationLabel->setText("Training it's done");
    this->trainingOutputLayout->insertWidget(this->trainingOutputLayout->count()-1, endingClassificationLabel);

    readAndDisplayOutputTrainingFile();
}

DeepLearningWidget::DeepLearningWidget(QVBoxLayout *parametersLayout, QVBoxLayout *trainingOutputLayout)
    : ClassificationTrainingWidget(parametersLayout, trainingOutputLayout)
{
    connect(this->launchTrainingClassifierButton, &QPushButton::released, this, &DeepLearningWidget::handleLaunchTrainingClassifierButton);

    this->addClassifierButton = new QPushButton("Add");
    this->classifierLineEdit = new QLineEdit();
    this->classifierLineEdit->setReadOnly(true);
    connect(this->addClassifierButton, &QPushButton::released, [=](){this->classifierLineEdit->setText(QFileDialog::getOpenFileName(this));});
    
    this->addTrainingSetButton = new QPushButton("Add");
    this->trainingSetLineEdit = new QLineEdit();
    this->trainingSetLineEdit->setReadOnly(true);
    connect(this->addTrainingSetButton, &QPushButton::released, [=](){this->trainingSetLineEdit->setText(QFileDialog::getExistingDirectory(this));});

    this->addTestingSetButton = new QPushButton("Add");
    this->testingSetLineEdit = new QLineEdit();
    this->testingSetLineEdit->setReadOnly(true);
    connect(this->addTestingSetButton, &QPushButton::released, [=](){this->testingSetLineEdit->setText(QFileDialog::getExistingDirectory(this));});
    
    this->numberOfEpochsLineEdit = new QLineEdit();
    this->numberOfEpochsLineEdit->setValidator(new QIntValidator(0,INT_MAX,this));

    this->heightOfImagesLineEdit = new QLineEdit();
    this->heightOfImagesLineEdit->setValidator(new QIntValidator(0,INT_MAX,this));

    this->widthOfImagesLineEdit = new QLineEdit();
    this->widthOfImagesLineEdit->setValidator(new QIntValidator(0,INT_MAX,this));

    this->formLayout->addRow(tr("&Classifier:"), this->addClassifierButton);
    this->formLayout->addRow(this->classifierLineEdit);
    this->formLayout->addRow(tr("&Training set :"), this->addTrainingSetButton);
    this->formLayout->addRow(this->trainingSetLineEdit);
    this->formLayout->addRow(tr("&Testing set :"), this->addTestingSetButton);
    this->formLayout->addRow(this->testingSetLineEdit);
    this->formLayout->addRow(tr("&Number of epochs :"), this->numberOfEpochsLineEdit);
    this->formLayout->addRow(tr("&Width of images :"), this->widthOfImagesLineEdit);
    this->formLayout->addRow(tr("&Height of images :"), this->heightOfImagesLineEdit);

    this->formGroupBox->setLayout(this->formLayout);
    this->parametersLayout->insertWidget(0, this->formGroupBox);
}

void DeepLearningWidget::handleLaunchTrainingClassifierButton()
{
    QString pathToClassifier = this->classifierLineEdit->text();
    QString pathToTrainingSet = this->trainingSetLineEdit->text();
    QString pathToTestingSet = this->testingSetLineEdit->text();
    QString numberOfEpochs = this->numberOfEpochsLineEdit->text();
    QString heightOfImages = this->heightOfImagesLineEdit->text();
    QString widthOfImages = this->widthOfImagesLineEdit->text();

    if(pathToClassifier != NULL)
    {
        DeepLearningThread *thread = new DeepLearningThread(pathToClassifier, pathToTrainingSet, pathToTestingSet, numberOfEpochs, heightOfImages, widthOfImages);
        connect(thread, &QThread::started, this, &DeepLearningWidget::handleWaitingClassification);
        connect(thread, &QThread::finished, this, &DeepLearningWidget::handleEndingClassification);
        thread->start();
    }
}

RandomForestWidget::RandomForestWidget(QVBoxLayout *parametersLayout, QVBoxLayout *trainingOutputLayout)
    : ClassificationTrainingWidget(parametersLayout, trainingOutputLayout)
{
    connect(this->launchTrainingClassifierButton, &QPushButton::released, this, &RandomForestWidget::handleLaunchTrainingClassifierButton);

    this->addClassifierButton = new QPushButton("Add");
    this->classifierLineEdit = new QLineEdit();
    this->classifierLineEdit->setReadOnly(true);
    connect(this->addClassifierButton, &QPushButton::released, [=](){this->classifierLineEdit->setText(QFileDialog::getOpenFileName(this));});
    
    this->addTrainingSetButton = new QPushButton("Add");
    this->trainingSetLineEdit = new QLineEdit();
    this->trainingSetLineEdit->setReadOnly(true);
    connect(this->addTrainingSetButton, &QPushButton::released, [=](){this->trainingSetLineEdit->setText(QFileDialog::getExistingDirectory(this));});

    this->numberOfTreesLineEdit = new QLineEdit();
    this->numberOfTreesLineEdit->setValidator(new QIntValidator(0,INT_MAX,this));

    this->heightOfImagesLineEdit = new QLineEdit();
    this->heightOfImagesLineEdit->setValidator(new QIntValidator(0,INT_MAX,this));

    this->widthOfImagesLineEdit = new QLineEdit();
    this->widthOfImagesLineEdit->setValidator(new QIntValidator(0,INT_MAX,this));

    this->formLayout->addRow(tr("&Classifier:"), this->addClassifierButton);
    this->formLayout->addRow(this->classifierLineEdit);
    this->formLayout->addRow(tr("&Training set :"), this->addTrainingSetButton);
    this->formLayout->addRow(this->trainingSetLineEdit);
    this->formLayout->addRow(tr("&Number of trees :"), this->numberOfTreesLineEdit);
    this->formLayout->addRow(tr("&Width of images :"), this->widthOfImagesLineEdit);
    this->formLayout->addRow(tr("&Height of images :"), this->heightOfImagesLineEdit);

    this->formGroupBox->setLayout(this->formLayout);
    this->parametersLayout->insertWidget(0, this->formGroupBox);
}

void RandomForestWidget::handleLaunchTrainingClassifierButton()
{
    QString pathToClassifier = this->classifierLineEdit->text();
    QString pathToTrainingSet = this->trainingSetLineEdit->text();
    QString numberOfTrees = this->numberOfTreesLineEdit->text();
    QString heightOfImages = this->heightOfImagesLineEdit->text();
    QString widthOfImages = this->widthOfImagesLineEdit->text();

    if(pathToClassifier != NULL)
    {
        RandomForestThread *thread = new RandomForestThread(pathToClassifier, pathToTrainingSet, numberOfTrees, heightOfImages, widthOfImages);
        connect(thread, &QThread::started, this, &RandomForestWidget::handleWaitingClassification);
        connect(thread, &QThread::finished, this, &RandomForestWidget::handleEndingClassification);
        thread->start();
    }
}