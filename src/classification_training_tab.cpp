#include "classification_training_tab.h"

ClassificationTrainingTab::ClassificationTrainingTab(Tab *parent)
    : Tab(parent)
{
    this->mainLayout = new QVBoxLayout;
    this->setLayout(this->mainLayout);

    addTestAndTrainCheckBox();
    addLoadTrainingClassifierButton();
    addLaunchTrainingClassifierButton();

    this->mainLayout->addStretch();
    
    this->isTrainingClassifierLoad = false;
    this->isTrainingSetLoad = false;
    this->isTestingSetLoad = false;
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

void ClassificationTrainingTab::addTestAndTrainCheckBox()
{
    this->testAndTrainCheckBox = new QCheckBox("Select training and testing set when the training classifier will be loaded", this);
    this->mainLayout->addWidget(this->testAndTrainCheckBox);
}

void ClassificationTrainingTab::addLoadTrainingClassifierButton()
{
    this->loadTrainingClassifierButton = new QPushButton("Load training classifier");
    connect(loadTrainingClassifierButton, &QPushButton::released, this, &ClassificationTrainingTab::handleLoadTrainingClassifierButton);
    this->mainLayout->addWidget(this->loadTrainingClassifierButton);
}

void ClassificationTrainingTab::addLaunchTrainingClassifierButton()
{
    this->launchTrainingClassifierButton = new QPushButton("Launch training");
    connect(this->launchTrainingClassifierButton, &QPushButton::released, this, &ClassificationTrainingTab::handleLaunchTrainingClassifierButton);
    this->mainLayout->addWidget(this->launchTrainingClassifierButton);
}

void ClassificationTrainingTab::handleLoadTrainingClassifierButton()
{
    QLabel *informationClassifierLabel = new QLabel(this);

    this->pathToClassifier = QFileDialog::getOpenFileName(this, tr("Select CLASSIFIER TRAINING to LOAD"), tr("PY (*.py)"));
    if(this->pathToClassifier == NULL)
    {
        printf("classifier loading problem\n");
        return;
    }
    this->isTrainingClassifierLoad = true;

    informationClassifierLabel->setText("Classification file : " + this->pathToClassifier + "\n"); 

    if(testAndTrainCheckBox->checkState() == Qt::Checked)
    {
        this->pathToTrainingSet = QFileDialog::getExistingDirectory(this, tr("Select TRAINING DATASET"));
        if(this->pathToClassifier == NULL)
        {
            printf("classifier loading problem\n");
            return;
        }
        this->isTrainingSetLoad = true;

        this->pathToTestingSet = QFileDialog::getExistingDirectory(this, tr("Select TESTING DATASET"));
        if(this->pathToClassifier == NULL)
        {
            printf("classifier loading problem\n");
            return;
        }
        this->isTestingSetLoad = true;
        
        informationClassifierLabel->setText(informationClassifierLabel->text() + "Training set directory : " + this->pathToTrainingSet + "\n" + "Testing set directory : " + pathToTestingSet);
    }

    this->mainLayout->insertWidget(this->mainLayout->count()-1, informationClassifierLabel);
}

void ClassificationTrainingTab::handleLaunchTrainingClassifierButton()
{
    if(this->isTrainingClassifierLoad == true && this->isTrainingSetLoad == true && this->isTestingSetLoad == true && this->testAndTrainCheckBox->checkState() == Qt::Checked)
    {
        ClassificationThread *thread = new ClassificationThread(this->pathToClassifier, this->pathToTrainingSet, this->pathToTestingSet);
        connect(thread, &QThread::started, this, &ClassificationTrainingTab::handleWaitingClassification);
        connect(thread, &QThread::finished, this, &ClassificationTrainingTab::handleEndingClassification);
        thread->start();
    }
    else if(this->isTrainingClassifierLoad == true && this->testAndTrainCheckBox->checkState() == Qt::Unchecked)
    {
        ClassificationThread *thread = new ClassificationThread(this->pathToClassifier);
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