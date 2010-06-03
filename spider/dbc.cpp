

#include "dbc.h"

CDbc::CDbc() :
    QObject ()
{
}

CDbc::~CDbc(){
    cout << "dbc died\n";
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

    deleteLater();
}

void CDbc::reply(CRequest* req){
    cout << "reply " << req->url.toString().toAscii().data()
        << "(" << req->http_status << " " << req->http_reason.toAscii().data() << ")" << endl;
}

void CDbc::scheduler(){
    static int cnt = 0;

    cnt++;

    cout << "timer" << cnt << endl;

    if(cnt == 3){
        CRequest    *req = new CRequest(this);

        req->url = QUrl("http://tut.by/");

        emit request(req);
    }

    if(cnt == 10) stop();
}


