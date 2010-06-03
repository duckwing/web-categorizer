

#include "dbc.h"
#include "utils.h"

#include <QtCore/QTimer>
#include <QtCore/QThread>

CDbc::CDbc() :
    QObject ()
{
}

//
// slots
//

void CDbc::start(){
    // setup timer
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(scheduler()));
    timer->start(1000);
}

void CDbc::stop(){
    this->thread()->quit();
    delete this;
}

void CDbc::reply(){
    cout << "reply " << endl;
}

void CDbc::scheduler(){
    static int cnt = 0;

    cnt++;

    cout << "timer" << cnt << endl;

    if(cnt == 2) emit request();
}


