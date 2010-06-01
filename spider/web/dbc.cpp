

#include "dbc.h"

#include "utils.h"

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#include "web.h"

#include <QtCore/QFile>

#define USER_EVENT_TYPE         QEvent::User

CDbc::CDbc( int & argc, char ** argv ) :
    QCoreApplication ( argc, argv ),

    timer()
{
    // schedule the init event
    QCoreApplication::postEvent(this, new QEvent(USER_EVENT_TYPE));
}

bool CDbc::event(QEvent* e){
    // other events are handled by the default
    // QCoreApplication event processor
    if(e->type() != USER_EVENT_TYPE){
        return QCoreApplication::event(e);
    }

    // start the worker
    worker.start();
    connect(&worker, SIGNAL(finished()), SLOT(worker_finished()));

    // create the web object
    {
        CWeb* web = new CWeb();

        web->moveToThread(&worker);

        connect(this, SIGNAL(worker_send(SReq*)), web, SLOT(request(SReq*)));
        connect(this, SIGNAL(worker_die()),       web, SLOT(die()));

        connect(web, SIGNAL(reply(SReq*)), SLOT(worker_reply(SReq*)));
    }

    // set up timer
    connect(&timer, SIGNAL(timeout()), SLOT(scheduler()));
    timer.start(2000);

    // accept the event
    e->accept();
    return true;
}

void CDbc::scheduler(){
    // check for exit file
    {
        QFile       efile("spider_stop");

        if(efile.exists()){
            emit worker_die();
            return ;
        }
    }

    static int cnt = 0;

    cnt++;

    cout << "timer" << cnt << endl;

    SReq*   req = new SReq;

    req->url = "http://tut.by/";

    if(cnt == 2) emit worker_send(req);

    if(cnt >= 10) emit worker_die();

}

void CDbc::worker_reply(SReq* req){
    cout << "reply " << req->url << endl;
}

void CDbc::worker_finished(){
    cout << "app die\n";
    QCoreApplication::quit();
}

#endif


