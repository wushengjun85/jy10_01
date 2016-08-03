#ifndef FINDLOOK_H
#define FINDLOOK_H

#include <QDialog>

namespace Ui {
class FindLook;
}

class FindLook : public QDialog
{
    Q_OBJECT
    
public:
    explicit FindLook(QWidget *parent = 0);
    ~FindLook();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::FindLook *ui;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // FINDLOOK_H
