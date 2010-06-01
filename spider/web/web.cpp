

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

//
// public
//

QNetworkAccessManager& CWeb::manager(){
    return netman;
}

void request_completed(SReq* req){
    // FIXME: move to the app thread instead
    delete req->reply;
    req->reply = 0;

    // emit reply
    emit reply(req);
}

//
// signals
//

void CWeb::request(SRequest* data){
    cout << "incoming!!! " << data->url << endl;

    delete data;
}

void CWeb::die(){
    cout << "web die\n";

    this->thread()->quit();
    delete this;
}

#endif


