#include "integer_slider.h"

#include "integer_slider.h"

IntegerSlider::IntegerSlider(const QString &sliderName, int minValue, int maxValue, QWidget *parentWidget) : QWidget(parentWidget) {
    QSizePolicy size_policy;
    size_policy.setVerticalPolicy(QSizePolicy::Fixed);
    size_policy.setHorizontalPolicy(QSizePolicy::Minimum);
    setSizePolicy(size_policy);
    this->mainLayout = new QHBoxLayout(this);
    this->nameLabel = new QLabel(sliderName);
    this->integerSlider = new QSlider(Qt::Horizontal);
    this->integerSlider->setMinimum(minValue);
    this->integerSlider->setMaximum(maxValue);
    this->integerSlider->setRange(minValue, maxValue);
    this->valueLabel = new QLabel("value");
    this->mainLayout->addWidget(this->nameLabel);
    this->mainLayout->addWidget(this->integerSlider);
    this->mainLayout->addWidget(this->valueLabel);

    connect(this->integerSlider, SIGNAL(valueChanged(int)), this, SLOT(onValueChange(int)));
    updateValueLabel();
}

IntegerSlider::~IntegerSlider(){}

int IntegerSlider::value()
{ 
    return this->integerSlider->value(); 
}

void IntegerSlider::setValue(int new_value)
{ 
    this->integerSlider->setValue(new_value);
}

void IntegerSlider::setRange(int min, int max)
{ 
    this->integerSlider->setRange(min, max);
}

void IntegerSlider::onValueChange(int new_value)
{
  updateValueLabel();
  valueChanged(new_value);
}

void IntegerSlider::updateValueLabel()
{
    std::ostringstream oss;
    oss << this->integerSlider->value() << " [" << this->integerSlider->minimum() << "," << this->integerSlider->maximum() << "]";
    this->valueLabel->setText(QString(oss.str().c_str()));
}
