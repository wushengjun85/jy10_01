#ifndef CAMERA_THREAD_H
#define CAMERA_THREAD_H

#include <QThread>
#include <QImage>
#include"camera.h"

class Camera_thread : public QThread
{
    Q_OBJECT
public:
    explicit Camera_thread(QObject *parent = 0);

    void run();
    
signals:
   void image_data(QImage *img);
    
public slots:

private:
    Camera camera_hw;
    
};

#endif // CAMERA_THREAD_H
