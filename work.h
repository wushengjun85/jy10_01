#ifndef WORK_H
#define WORK_H

#include <QDialog>
#include"findlook.h"
#include"timesetup.h"
#include"camera_thread.h"

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

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();


    void show_picture(QImage *img);
    void start_thread(void);
    void stop_thread();




    void on_pushButton_5_clicked();

private:
    Ui::Work *ui;
    FindLook *findlokk_work;
    Timesetup *time_work;


    Camera_thread *video;



protected:
    void paintEvent(QPaintEvent *event);


signals:
        void camerastartsignal();
};

#endif // WORK_H
