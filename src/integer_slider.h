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

        void initializeIntegerSlider(int minValue, int maxValue);
        void initializeSizePolicy();
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
};
#endif // INTEGER_SLIDER_H
