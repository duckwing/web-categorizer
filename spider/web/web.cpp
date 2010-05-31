

#include "web.h"

#include "utils.h"

#include "../sql/sql_api.h"

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#include <QtCore/QFile>

CWeb::CWeb( int & argc, char ** argv ) :
    QCoreApplication ( argc, argv ),

    netman(),
    netproxy(QNetworkProxy::Socks5Proxy, "127.0.0.1", 4000),

    timer(),
    cnt(0)

{
    // setup network
    netman.setProxy(netproxy);
    //netproxy.setCapabilities(QNetworkProxy::HostNameLookupCapability);

    // setup timer
    timer.start(2000);
    connect(&timer, SIGNAL(timeout()), SLOT(scheduler()));

    // about-to-quit signal
    connect(this, SIGNAL(aboutToQuit()), SLOT(aboutToQuit()));

    //
    //netreply = netman.get(QNetworkRequest(QUrl("http://tut.by/")));
}

void CWeb::scheduler(){
    // check for exit file
    {
        QFile       efile("spider_stop");

        if(efile.exists()){
            QCoreApplication::quit();
        }
    }

    cout << "timer" << endl;

    SqlEnv      env;

    SqlConn     dbc(env);

    /*
    cout << "Error: " << netreply->error() << " " <<
        netreply->errorString().toAscii().data() << endl;

    cout << "Code: " << netreply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() << endl;

    cout << netreply->readAll().data() << endl;
    */
}

void CWeb::aboutToQuit(){
    cout << "quit" << endl;
}

#endif


