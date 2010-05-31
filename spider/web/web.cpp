

#include "web.h"

#include "../common/utils.h"

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

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

    // about-to-quit signal
    connect(this, SIGNAL(aboutToQuit()), SLOT(aboutToQuit()));

    //
    netreply = netman.get(QNetworkRequest(QUrl("http://tut.by/")));

    connect(netreply, SIGNAL(finished()), SLOT(timeout()));
}

void CWeb::timeout(){
    cout << "Error: " << netreply->error() << " " <<
        netreply->errorString().toAscii().data() << endl;

    cout << "Code: " << netreply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() << endl;

    cout << netreply->readAll().data() << endl;

    QCoreApplication::quit();
}

void CWeb::aboutToQuit(){
}

#endif


