#include "bitmapwidget.h"

BitmapWidget::BitmapWidget(QWidget *parent) :
    QWidget(parent)
{
    numberOfPixel = 100;
    size = 3;
    matrix = NULL;

    timer = new QTimer(this);
    timer->setInterval(16);
    connect(timer, SIGNAL(timeout()) , this, SLOT(timerHit()));
    timer->start();
}

void BitmapWidget::setMatrix(unsigned char *mat) {
    matrix = mat;
}

void BitmapWidget::timerHit() {
    this->repaint();
}

int BitmapWidget::convert(unsigned char c) {
    switch (c) {
    case 3:
        return 255;
    case 2:
        return 192;
    case 1:
        return 88;
    case 0:
        return 0;
    default:
        return 0;
    }
}

void BitmapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen myPen(Qt::black, size, Qt::SolidLine);
    for (int x = 0; x < numberOfPixel; x++)
    for (int y = 0; y < numberOfPixel; y++) {
        if (matrix == NULL) {
            myPen.setColor(Qt::black);
        } else {
            unsigned char c = matrix[x*numberOfPixel + y];
            QColor color = QColor(convert((c>>6)&3), convert((c>>4)&3), convert((c>>2)&3));
            myPen.setColor(color);
        }
        painter.setPen(myPen);
        painter.drawPoint(x*size, y*size);
    }
}




