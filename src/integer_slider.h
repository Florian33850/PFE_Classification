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

#ifndef INTEGER_SLIDER_H
#define INTEGER_SLIDER_H

#include <QLabel>
#include <QSlider>
#include <QWidget>
#include <QHBoxLayout>
#include <cmath>
#include <sstream>

class IntegerSlider : public QWidget
{
    Q_OBJECT
    public:
        IntegerSlider(const QString &sliderName, int minValue, int maxValue, QWidget *parentWidget = nullptr);
        ~IntegerSlider();

        int value();

    public Q_SLOTS:
        void setValue(int newValue);
        void onValueChange(int newValue);
        void setRange(int minValue, int maxValue);

    Q_SIGNALS:
        void valueChanged(int newValue);

    private:
        QLayout *mainLayout;
        QLabel *nameLabel;
        QSlider *integerSlider;
        QLabel *valueLabel;
        QSizePolicy sizePolicy;

        void updateValueLabel();
        void initializeIntegerSlider(int minValue, int maxValue);
        void initializeSizePolicy();
};
#endif // INTEGER_SLIDER_H
