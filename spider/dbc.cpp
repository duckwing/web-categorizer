

#include "dbc.h"

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
    DIRECT_CONNECT(timer, timeout, this, scheduler, ());
    timer->start(1000);
}

void CDbc::stop(){

    cout << "dbc stop\n";

    this->thread()->quit();
}

void CDbc::reply(){
    cout << "reply " << endl;
}

void CDbc::scheduler(){
    static int cnt = 0;

    cnt++;

    cout << "timer" << cnt << endl;

    if(cnt % 4 == 0){
        CRequest    *req = new CRequest(this);

        emit request();
    }
}


