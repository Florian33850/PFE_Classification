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

#include "image_label.h"

ImageLabel::ImageLabel(QWidget *parent) : QLabel(parent) {
    QSizePolicy size_policy;
    size_policy.setVerticalPolicy(QSizePolicy::Minimum);
    size_policy.setHorizontalPolicy(QSizePolicy::Minimum);
    this->setSizePolicy(size_policy);
    this->setMinimumSize(MINIMUM_IMAGE_WIDTH_IMAGE_LABEL, MINIMUM_IMAGE_HEIGHT_IMAGE_LABEL);
}

ImageLabel::~ImageLabel() {}

void ImageLabel::updateContent()
{
    if (this->qImage.isNull())
    {
        return;
    }
    this->pixmap = QPixmap::fromImage(this->qImage);
    this->pixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatio);
    this->setPixmap(this->pixmap);
}

void ImageLabel::resizeEvent(QResizeEvent *event)
{
    (void)event;
    updateContent();
}
