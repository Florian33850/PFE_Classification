#include "classification_training_tab.h"

ClassificationTrainingTab::ClassificationTrainingTab(Tab *parent)
    : Tab(parent)
{
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    testAndTrainCheckBox = new QCheckBox("Load training and testing set", this);
    mainLayout->addWidget(testAndTrainCheckBox);

    QPushButton *loadTrainingClassifierButton = new QPushButton("Load classifier training");
    connect(loadTrainingClassifierButton, &QPushButton::released, this, &ClassificationTrainingTab::handleLoadTrainingClassifierButton);
    mainLayout->addWidget(loadTrainingClassifierButton);

    QPushButton *launchTrainingClassifierButton = new QPushButton("Launch training");
    connect(launchTrainingClassifierButton, &QPushButton::released, this, &ClassificationTrainingTab::handleLaunchTrainingClassifierButton);
    mainLayout->addWidget(launchTrainingClassifierButton);

    mainLayout->addStretch();
    
    isTrainingClassifierLoad = false;
    isTrainingSetLoad = false;
    isTestingSetLoad = false;
}

void ClassificationTrainingTab::handleLoadTrainingClassifierButton()
{
    QLabel *label = new QLabel(this);

    pathToClassifier = QFileDialog::getOpenFileName(this, tr("Select CLASSIFIER TRAINING to LOAD"), "../data/code/training", tr("PY (*.py)"));
    if(pathToClassifier == NULL)
    {
        printf("classifier loading problem\n");
        return;
    }
    isTrainingClassifierLoad = true;

    label->setText("Classification file : " + pathToClassifier + "\n"); 

    if(testAndTrainCheckBox->checkState() == Qt::Checked)
    {
        pathToTrainingSet = QFileDialog::getExistingDirectory(this, tr("Select TRAINING DATASET"), "../data/images");
        if(pathToClassifier == NULL)
        {
            printf("classifier loading problem\n");
            return;
        }
        isTrainingSetLoad = true;

        pathToTestingSet = QFileDialog::getExistingDirectory(this, tr("Select TESTING DATASET"), "../data/images");
        if(pathToClassifier == NULL)
        {
            printf("classifier loading problem\n");
            return;
        }
        isTestingSetLoad = true;
        
        label->setText(label->text() + "Training set directory : " + pathToTrainingSet + "\n" + "Testing set directory" + pathToTestingSet);
    }

    mainLayout->insertWidget(mainLayout->count()-1, label);
}
void ClassificationTrainingTab::handleLaunchTrainingClassifierButton()
{
    mainLayout->setStretch(2, mainLayout->stretch(1));
    if(isTrainingClassifierLoad == true && isTrainingSetLoad == true && isTestingSetLoad == true && testAndTrainCheckBox->checkState() == Qt::Checked)
    {
        ClassificationThread *thread = new ClassificationThread(pathToClassifier, pathToTrainingSet, pathToTestingSet);
        connect(thread, &QThread::started, this, &ClassificationTrainingTab::handleWaitingClassification);
        connect(thread, &QThread::finished, this, &ClassificationTrainingTab::handleEndingClassification);
        thread->start();
    }
    else if(isTrainingClassifierLoad == true && testAndTrainCheckBox->checkState() == Qt::Unchecked)
    {
        ClassificationThread *thread = new ClassificationThread(pathToClassifier);
        connect(thread, &QThread::started, this, &ClassificationTrainingTab::handleWaitingClassification);
        connect(thread, &QThread::finished, this, &ClassificationTrainingTab::handleEndingClassification);
        thread->start();
    }
}

void ClassificationTrainingTab::handleWaitingClassification()
{
    QLabel *label = new QLabel(this);
    label->setText("Waiting for classification training");
    mainLayout->insertWidget(mainLayout->count()-1, label);
}

void ClassificationTrainingTab::handleEndingClassification()
{
    QLabel *label = new QLabel(this);
    label->setText("Training it's done");
    mainLayout->insertWidget(mainLayout->count()-1, label);
}