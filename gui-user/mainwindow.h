#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <usermsg/usermsg.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void
    onShowMessage (
            const UserMsg & um);

private slots:
    void on_error_message_clicked();

    void on_warning_message_clicked();

    void on_info_massage_clicked();

    void on_debug_error_message_clicked();

    void on_debug_warning_message_clicked();

    void on_debug_info_message_clicked();

    void on_enabled_message_toggled(bool checked);

    void on_clear_log_clicked();

    void onCheckType();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
