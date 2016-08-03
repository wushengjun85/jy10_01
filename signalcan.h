#ifndef SIGNALCAN_H
#define SIGNALCAN_H
#include <QThread>
#include <QObject>


#include"canread.h"

typedef struct hwe
{
    int id;
    int data[8];
}CanData;

class SignalCan : public QThread
{
    Q_OBJECT
public:
    explicit SignalCan(QObject *parent = 0);
    CanData candata;
    void run();
    
signals:
    void sendcansignal(CanData);
    
public slots:
    
};

#endif // SIGNALCAN_H
