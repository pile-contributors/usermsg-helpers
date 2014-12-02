#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "messagebx.h"

#include <usermsg/usermsg.h>
#include <usermsg/usermsgman.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->use_class->setChecked (true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onShowMessage (const UserMsg &um)
{
    MessageBx mx ;
    int i_max = um.count ();
    for (int i = 0; i < i_max; ++i) {
        const UserMsgEntry & e = um.at (i);
        if (e.isEnabled()) {
            mx.setTitle (QString("%1 %2")
                         .arg(e.typeNameCap ())
                         .arg(e.moment ().toString ()));
            mx.setContent (e.message ());
            mx.exec ();
        }
    }
}

void MainWindow::on_error_message_clicked()
{
    if (ui->use_class->isChecked ()) {
        UserMsg um;
        um.addErr ("Test error");
        um.show ();
    } else {
        UserMsg::err ("Test error shared");
    }
}

void MainWindow::on_warning_message_clicked()
{
    if (ui->use_class->isChecked ()) {
        UserMsg um;
        um.addErr ("Test warning");
        um.show ();
    } else {
        UserMsg::err ("Test warning shared");
    }
}

void MainWindow::on_info_massage_clicked()
{
    if (ui->use_class->isChecked ()) {
        UserMsg um;
        um.addErr ("Test info");
        um.show ();
    } else {
        UserMsg::err ("Test info shared");
    }
}

void MainWindow::on_debug_error_message_clicked()
{
    if (ui->use_class->isChecked ()) {
        UserMsg um;
        um.addErr ("Test debug error");
        um.show ();
    } else {
        UserMsg::err ("Test debug error shared");
    }
}

void MainWindow::on_debug_warning_message_clicked()
{
    if (ui->use_class->isChecked ()) {
        UserMsg um;
        um.addErr ("Test debug warning");
        um.show ();
    } else {
        UserMsg::err ("Test debug warning shared");
    }
}

void MainWindow::on_debug_info_message_clicked()
{
    if (ui->use_class->isChecked ()) {
        UserMsg um;
        um.addErr ("Test debug info");
        um.show ();
    } else {
        UserMsg::err ("Test debug info shared");
    }
}

void MainWindow::on_enabled_message_toggled(bool checked)
{
    if (checked) {
        UserMsgMan::enable (ui->collapse_on_enable->isChecked ());
    } else {
        UserMsgMan::disable ();
    }
}
