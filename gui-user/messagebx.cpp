#include "messagebx.h"
#include "ui_messagebx.h"

MessageBx::MessageBx(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageBx)
{
    ui->setupUi(this);
}

MessageBx::~MessageBx()
{
    delete ui;
}

void MessageBx::setTitle (const QString & value)
{
    ui->title_bar->setText (value);
}

void MessageBx::setContent (const QString & value)
{
    ui->title_bar->setText (value);
}
