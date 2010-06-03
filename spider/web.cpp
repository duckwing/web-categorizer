

#include "web.h"

CWeb::CWeb() :
    QObject (),

    netman(0),
    netproxy(QNetworkProxy::Socks5Proxy, "127.0.0.1", 4000)

{
    netman = new QNetworkAccessManager(this);

    // setup network
    //netman->setProxy(netproxy);
    //netproxy.setCapabilities(QNetworkProxy::HostNameLookupCapability);
}

//
// slots
//

void CWeb::request(){
    cout << "incoming!!! " << endl;

}

void CWeb::die(){
    cout << "web die\n";

    this->thread()->quit();
    delete this;
}


