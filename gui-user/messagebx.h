#ifndef MESSAGEBX_H
#define MESSAGEBX_H

#include <QDialog>

namespace Ui {
class MessageBx;
}

class MessageBx : public QDialog
{
    Q_OBJECT

public:
    explicit MessageBx(QWidget *parent = 0);
    ~MessageBx();

    void setTitle (const QString & value);
    void setContent (const QString & value);
private:
    Ui::MessageBx *ui;
};

#endif // MESSAGEBX_H
