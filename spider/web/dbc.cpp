

#include "dbc.h"

#include "utils.h"

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#include <QtCore/QFile>

#define USER_EVENT_TYPE         QEvent::User

CDbc::CDbc( int & argc, char ** argv ) :
    QCoreApplication ( argc, argv ),

    timer()
{
    // schedule the init event
    QCoreApplication::postEvent(this, new QEvent(USER_EVENT_TYPE));
}

void CDbc::scheduler(){
    // check for exit file
    {
        QFile       efile("spider_stop");

        if(efile.exists()){
            QCoreApplication::quit();
        }
    }

    cout << "timer" << endl;


    /*
    cout << "Error: " << netreply->error() << " " <<
        netreply->errorString().toAscii().data() << endl;

    cout << "Code: " << netreply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() << endl;

    cout << netreply->readAll().data() << endl;
    */
}

bool CDbc::event(QEvent* e){
    // other events are handled by the default
    // QCoreApplication event processor
    if(e->type() != USER_EVENT_TYPE){
        return QCoreApplication::event(e);
    }

    // set up timer
    connect(&timer, SIGNAL(timeout()), SLOT(scheduler()));
    timer.start(2000);

    // accept the event
    e->accept();
    return true;
}


#endif


