#ifndef WORK_H
#define WORK_H

#include <QDialog>

namespace Ui {
class Work;
}

class Work : public QDialog
{
    Q_OBJECT
    
public:
    explicit Work(QWidget *parent = 0);
    ~Work();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::Work *ui;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WORK_H
