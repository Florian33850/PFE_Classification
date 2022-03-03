#include "classification_training_tab.h"

ClassificationTrainingTab::ClassificationTrainingTab(Tab *parent)
    : Tab(parent)
{
    this->mainLayout = new QVBoxLayout;
    this->setLayout(this->mainLayout);

    addTrainingParametersFormLayout();
    addLaunchTrainingClassifierButton();

    this->mainLayout->addStretch();
}

void ClassificationTrainingTab::readAndDisplayOutputTrainingFile()
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

void ClassificationTrainingTab::addTrainingParametersFormLayout()
{
    this->formGroupBox = new QGroupBox(tr("Training parameters"));
    this->formLayout = new QFormLayout;

    this->addClassifierButton = new QPushButton("Add");
    this->classifierLineEdit = new QLineEdit();
    this->classifierLineEdit->setReadOnly(true);
    connect(addClassifierButton, &QPushButton::released, [=](){this->handleAddFileToQlineEdit(classifierLineEdit);});
    
    this->addTrainingSetButton = new QPushButton("Add");
    this->trainingSetLineEdit = new QLineEdit();
    this->trainingSetLineEdit->setReadOnly(true);
    connect(addTrainingSetButton, &QPushButton::released, [=](){this->handleAddDirectoryToQlineEdit(trainingSetLineEdit);});

    this->addTestingSetButton = new QPushButton("Add");
    this->testingSetLineEdit = new QLineEdit();
    this->testingSetLineEdit->setReadOnly(true);
    connect(addTestingSetButton, &QPushButton::released, [=](){this->handleAddDirectoryToQlineEdit(testingSetLineEdit);});
    
    this->numberOfepochsLineEdit = new QLineEdit();
    this->numberOfepochsLineEdit->setValidator(new QIntValidator(0,INT_MAX,this));

    this->heightOfImagesLineEdit = new QLineEdit();
    this->heightOfImagesLineEdit->setValidator(new QIntValidator(0,INT_MAX,this));

    this->widthOfImagesLineEdit = new QLineEdit();
    this->widthOfImagesLineEdit->setValidator(new QIntValidator(0,INT_MAX,this));

    this->formLayout->addRow(tr("&Classifier:"), addClassifierButton);
    this->formLayout->addRow(classifierLineEdit);
    this->formLayout->addRow(tr("&Training set :"), addTrainingSetButton);
    this->formLayout->addRow(trainingSetLineEdit);
    this->formLayout->addRow(tr("&Testing set :"), addTestingSetButton);
    this->formLayout->addRow(testingSetLineEdit);
    this->formLayout->addRow(tr("&Number of epochs :"), numberOfepochsLineEdit);
    this->formLayout->addRow(tr("&Height of images :"), heightOfImagesLineEdit);
    this->formLayout->addRow(tr("&Width of images :"), widthOfImagesLineEdit);

    this->formGroupBox->setLayout(formLayout);
    this->mainLayout->addWidget(formGroupBox);
}

void ClassificationTrainingTab::addLaunchTrainingClassifierButton()
{
    this->launchTrainingClassifierButton = new QPushButton("Launch training");
    connect(this->launchTrainingClassifierButton, &QPushButton::released, this, &ClassificationTrainingTab::handleLaunchTrainingClassifierButton);
    this->mainLayout->addWidget(this->launchTrainingClassifierButton);
}

void ClassificationTrainingTab::handleAddDirectoryToQlineEdit(QLineEdit *qLineEdit)
{
    qLineEdit->setText(QFileDialog::getExistingDirectory(this));
}

void ClassificationTrainingTab::handleAddFileToQlineEdit(QLineEdit *qLineEdit)
{
    qLineEdit->setText(QFileDialog::getOpenFileName(this));
}

void ClassificationTrainingTab::handleLaunchTrainingClassifierButton()
{
    QString pathToClassifier = classifierLineEdit->text();
    QString pathToTrainingSet = trainingSetLineEdit->text();
    QString pathToTestingSet = testingSetLineEdit->text();
    QString numberOfEpochs = numberOfepochsLineEdit->text();
    QString heightOfImages = heightOfImagesLineEdit->text();
    QString widthOfImages = widthOfImagesLineEdit->text();

    if(pathToClassifier != NULL)
    {
        ClassificationThread *thread = new ClassificationThread(pathToClassifier, pathToTrainingSet, pathToTestingSet, numberOfEpochs, heightOfImages, widthOfImages);
        connect(thread, &QThread::started, this, &ClassificationTrainingTab::handleWaitingClassification);
        connect(thread, &QThread::finished, this, &ClassificationTrainingTab::handleEndingClassification);
        thread->start();
    }
}

void ClassificationTrainingTab::handleWaitingClassification()
{
    QLabel *waitingCLassificationLabel = new QLabel(this);
    waitingCLassificationLabel->setText("Waiting for classification training");
    this->mainLayout->insertWidget(this->mainLayout->count()-1, waitingCLassificationLabel);
}

void ClassificationTrainingTab::handleEndingClassification()
{
    QLabel *endingClassificationLabel = new QLabel(this);
    endingClassificationLabel->setText("Training it's done");
    this->mainLayout->insertWidget(this->mainLayout->count()-1, endingClassificationLabel);

    readAndDisplayOutputTrainingFile();
}