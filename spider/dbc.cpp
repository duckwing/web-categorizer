

#include "dbc.h"
#include "utils.h"

#if defined(QT_CORE_LIB)

#include <QtCore/QTimer>

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

void CDbc::reply(SReq* req){
    cout << "reply " << req->url << endl;
}

void CDbc::scheduler(){
    static int cnt = 0;

    cnt++;

    cout << "timer" << cnt << endl;

    SReq*   req = new SReq;

    req->url = "http://tut.by/";

    if(cnt == 2) emit request(req);
}

#endif


