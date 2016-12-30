#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include "tablemodel.h"
#include "process.h"
#include <QTableView>
#include "formain.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0, Arg *arg = NULL);
    ~Widget();

private:
    Ui::Widget *ui;
    QTimer *timer;
    SharedMem *sharedMem;

private slots:
    void slotButtonRun();
    void slotButtonStopReset();
    void slotButtonStep();
    void slotUpdateRegister();
    //void userclicked(QTableViewItem *item);
};


#endif // WIDGET_H
