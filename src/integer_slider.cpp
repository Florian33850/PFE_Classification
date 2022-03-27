//     PFE_Classification --- Generic classification software
//     Copyright © <2022> Florian Dayre <florian.dayre33850@gmail.com>
//     Copyright © <2022> Élodie Gaudry <elodie.gaudry@etu.u-bordeaux.fr>
//     Copyright © <2022> Hugo Lecomte <hugolecomte932@protonmail.com>
//     Copyright © <2022> Hugo Trarieux <htrarieux@gmail.com>

//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
    this->sizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
    this->sizePolicy.setHorizontalPolicy(QSizePolicy::Minimum);
    this->setSizePolicy(this->sizePolicy);
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
