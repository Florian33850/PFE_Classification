#include "integer_slider.h"

#include "integer_slider.h"

IntegerSlider::IntegerSlider(const QString &sliderName, int minValue, int maxValue, QWidget *parentWidget) : QWidget(parentWidget) {
    this->mainLayout = new QHBoxLayout(this);
    this->nameLabel = new QLabel(sliderName);

    initializeIntegerSlider(minValue, maxValue);
    initializeSizePolicy();

    this->valueLabel = new QLabel("value");
    this->mainLayout->addWidget(this->nameLabel);
    this->mainLayout->addWidget(this->integerSlider);
    this->mainLayout->addWidget(this->valueLabel);

    connect(this->integerSlider, SIGNAL(valueChanged(int)), this, SLOT(onValueChange(int)));
    updateValueLabel();
}

IntegerSlider::~IntegerSlider(){}

void IntegerSlider::initializeIntegerSlider(int minValue, int maxValue)
{
    this->integerSlider = new QSlider(Qt::Horizontal);
    this->integerSlider->setMinimum(minValue);
    this->integerSlider->setMaximum(maxValue);
    this->integerSlider->setRange(minValue, maxValue);
}

void IntegerSlider::initializeSizePolicy()
{
    this->size_policy.setVerticalPolicy(QSizePolicy::Fixed);
    this->size_policy.setHorizontalPolicy(QSizePolicy::Minimum);
    this->setSizePolicy(this->size_policy);
}

int IntegerSlider::value()
{ 
    return this->integerSlider->value(); 
}

void IntegerSlider::setValue(int newValue)
{ 
    this->integerSlider->setValue(newValue);
}

void IntegerSlider::setRange(int minValue, int maxValue)
{ 
    this->integerSlider->setRange(minValue, maxValue);
}

void IntegerSlider::onValueChange(int newValue)
{
    updateValueLabel();
    valueChanged(newValue);
}

void IntegerSlider::updateValueLabel()
{
    std::ostringstream oss;
    oss << this->integerSlider->value() << " [" << this->integerSlider->minimum() << "," << this->integerSlider->maximum() << "]";
    this->valueLabel->setText(QString(oss.str().c_str()));
}