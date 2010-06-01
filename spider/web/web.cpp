

#include "web.h"

#include "utils.h"

#include "../sql/sql_api.h"

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#include <QtCore/QThread>

CWeb::CWeb() :
    QObject (),

    netman(),
    netproxy(QNetworkProxy::Socks5Proxy, "127.0.0.1", 4000)

{
    // setup network
    netman.setProxy(netproxy);
    //netproxy.setCapabilities(QNetworkProxy::HostNameLookupCapability);
}

void CWeb::incoming(){
    cout << "incoming!!!\n";
}

void CWeb::die(){
    cout << "web die\n";

    this->thread()->quit();
    delete this;
}

#endif


