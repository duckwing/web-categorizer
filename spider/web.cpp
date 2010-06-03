

#include "web.h"

#include "utils.h"

#include "../sql/sql_api.h"

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

CWeb::CWeb() :
    QObject (),

    netman(0),
    netproxy(QNetworkProxy::Socks5Proxy, "127.0.0.1", 4000)

{
    netman = new QNetworkAccessManager(this);

    // setup network
    netman->setProxy(netproxy);
    //netproxy.setCapabilities(QNetworkProxy::HostNameLookupCapability);
}

//
// public
//

QNetworkAccessManager& CWeb::manager(){
    return *netman;
}

void CWeb::request_completed(SReq* req){
    // FIXME: move to the app thread instead
    req->reply = 0;

    // emit reply
    emit reply(req);
}

//
// slots
//

void CWeb::request(SReq* req){
    cout << "incoming!!! " << req->url << endl;

    CRequest* r = new CRequest(this, req);
    r->finished();
}

void CWeb::die(){
    cout << "web die\n";

    this->thread()->quit();
    cout << "web die\n";
    delete this;
}

#endif


