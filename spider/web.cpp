

#include "web.h"
#include "utils.h"

CWeb::CWeb(int & argc, char ** argv) :
    QCoreApplication (argc, argv),

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

    this->quit();
    delete this;
}


