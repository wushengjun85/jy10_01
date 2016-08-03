#include "signalcan.h"


SignalCan::SignalCan(QObject *parent) :
    QThread(parent)
{
}

void SignalCan::run()
{
    int master;
    int mycanid;
    Canread canread;
    canread.initcan(&mycanid);
    canread.test_can_rw(mycanid,master);
    canread.shutdownfd(mycanid);
}




