#include "widget.h"
#include "ui_widget.h"
#include "formain.h"
#include "cpu_api.h"


Widget::Widget(QWidget *parent, Arg *arg) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    pthread_mutex_lock(arg->mutex);
    sharedMem = arg->sharedMem;
    pthread_mutex_unlock(arg->mutex);

    printf("sharedMem in widget = %p:\n vidio_mem = %p\t asmCommand = %p\n",
           sharedMem, sharedMem->vidio_memory, sharedMem->asmCommand);
    for (int i = 0; i < 8; i++)
        printf("command[%d] = \"%s\"\n", i, sharedMem->asmCommand[i].command);

    TableModel *myModel = new TableModel();
    myModel->setSharedMem(sharedMem);
    ui->tableCommand->setModel(myModel);
    ui->tableCommand->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableCommand->resizeColumnsToContents();

    ui->bitmap->setMatrix(sharedMem->vidio_memory);

    connect(ui->buttonRun,       SIGNAL(clicked()), this, SLOT(slotButtonRun()));
    connect(ui->buttonStopReset, SIGNAL(clicked()), this, SLOT(slotButtonStopReset()));
    connect(ui->buttonStep,      SIGNAL(clicked()), this, SLOT(slotButtonStep()));
    //connect(ui->tableCommand, SIGNAL(itemActivated (QTableWidgetItem *), this, SLOT(userclicked(QTableWidgetItem *)));

    timer = new QTimer(this);
    timer->setInterval(16);
    connect(timer, SIGNAL(timeout()) , this, SLOT(slotUpdateRegister()));
    timer->start();

}
/*
void Widget::userclicked(QTableWidgetItem *item) {

}
*/
void Widget::slotUpdateRegister() {
    char strtmp[100];
    sprintf(strtmp, "0x%x", sharedMem->registers[0]);
    ui->val_R_0->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[1]);
    ui->val_R_1->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[2]);
    ui->val_R_2->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[3]);
    ui->val_R_3->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[4]);
    ui->val_R_4->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[5]);
    ui->val_R_5->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[6]);
    ui->val_R_6->setText(strtmp);
    sprintf(strtmp, "0x%x", sharedMem->registers[7]);
    ui->val_R_7->setText(strtmp);

    sprintf(strtmp, "x%x", sharedMem->flags);
    ui->val_flags->setText(strtmp);
}

void Widget::slotButtonRun() {
    //process.run();
    //cpu_emulation(&vcpu);
}

void Widget::slotButtonStopReset() {
    //process.stopReset();
}

void Widget::slotButtonStep() {
    //process.step();
}

Widget::~Widget()
{
    delete ui;
}
