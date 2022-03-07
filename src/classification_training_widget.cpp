#include "classification_training_widget.h"

ClassificationTrainingWidget::ClassificationTrainingWidget(QVBoxLayout *mainLayout)
{
    this->mainLayout = mainLayout;
    this->formGroupBox = new QGroupBox(tr("Training parameters"));
    this->formLayout = new QFormLayout;

    this->launchTrainingClassifierButton = new QPushButton("Launch training");
    this->mainLayout->insertWidget(this->mainLayout->count()-1, this->launchTrainingClassifierButton);
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

    this->mainLayout->insertWidget(this->mainLayout->count()-1, scrollArea);
}

void ClassificationTrainingWidget::handleAddDirectoryToQlineEdit(QLineEdit *qLineEdit)
{
    qLineEdit->setText(QFileDialog::getExistingDirectory(this));
}

void ClassificationTrainingWidget::handleAddFileToQlineEdit(QLineEdit *qLineEdit)
{
    qLineEdit->setText(QFileDialog::getOpenFileName(this));
}

void ClassificationTrainingWidget::handleWaitingClassification()
{
    QLabel *waitingCLassificationLabel = new QLabel(this);
    waitingCLassificationLabel->setText("Waiting for classification training");
    this->mainLayout->insertWidget(this->mainLayout->count()-1, waitingCLassificationLabel);
}

void ClassificationTrainingWidget::handleEndingClassification()
{
    QLabel *endingClassificationLabel = new QLabel(this);
    endingClassificationLabel->setText("Training it's done");
    this->mainLayout->insertWidget(this->mainLayout->count()-1, endingClassificationLabel);

    readAndDisplayOutputTrainingFile();
}

DeepLearningWidget::DeepLearningWidget(QVBoxLayout *mainLayout)
    : ClassificationTrainingWidget(mainLayout)
{
    connect(this->launchTrainingClassifierButton, &QPushButton::released, this, &DeepLearningWidget::handleLaunchTrainingClassifierButton);

    this->addClassifierButton = new QPushButton("Add");
    this->classifierLineEdit = new QLineEdit();
    this->classifierLineEdit->setReadOnly(true);
    connect(this->addClassifierButton, &QPushButton::released, [=](){this->handleAddFileToQlineEdit(this->classifierLineEdit);});
    
    this->addTrainingSetButton = new QPushButton("Add");
    this->trainingSetLineEdit = new QLineEdit();
    this->trainingSetLineEdit->setReadOnly(true);
    connect(this->addTrainingSetButton, &QPushButton::released, [=](){this->handleAddDirectoryToQlineEdit(this->trainingSetLineEdit);});

    this->addTestingSetButton = new QPushButton("Add");
    this->testingSetLineEdit = new QLineEdit();
    this->testingSetLineEdit->setReadOnly(true);
    connect(this->addTestingSetButton, &QPushButton::released, [=](){this->handleAddDirectoryToQlineEdit(this->testingSetLineEdit);});
    
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
    this->formLayout->addRow(tr("&Height of images :"), this->heightOfImagesLineEdit);
    this->formLayout->addRow(tr("&Width of images :"), this->widthOfImagesLineEdit);

    this->formGroupBox->setLayout(this->formLayout);
    this->mainLayout->insertWidget(this->mainLayout->count()-1, this->formGroupBox);
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
        ClassificationThread *thread = new ClassificationThread(pathToClassifier, pathToTrainingSet, pathToTestingSet, numberOfEpochs, heightOfImages, widthOfImages);
        connect(thread, &QThread::started, [=](){this->handleWaitingClassification();});
        connect(thread, &QThread::finished, [=](){this->handleEndingClassification();});
        thread->start();
    }
}