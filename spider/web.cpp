

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

    emit start();
}

void CWeb::send_start(){
    cout << "web send start\n";
    emit start();
}


//
// slots
//

void CWeb::request(){
    cout << "incoming!!! " << endl;

}

void CWeb::stop(){
    cout << "web stop\n";
    this->thread()->quit();
    //QCoreApplication::quit();
}


