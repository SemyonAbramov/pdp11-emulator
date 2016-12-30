#ifndef BITMAPWIDGET_H
#define BITMAPWIDGET_H

#include <QWidget>
#include <QtGui>

class BitmapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BitmapWidget(QWidget *parent = 0);
    int numberOfPixel; // read only

    void setMatrix(unsigned char *matrix);

signals:

protected:
    void paintEvent(QPaintEvent *event);

private:
    int size;
    QTimer *timer;
    unsigned char *matrix;
    int convert(unsigned char c);

private slots:
    void timerHit();
};

#endif // BITMAPWIDGET_H
