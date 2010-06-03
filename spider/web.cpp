

#include "web.h"

CWeb::CWeb() :
    QObject (),

    netman(0),
    netproxy(QNetworkProxy::Socks5Proxy, "127.0.0.1", 4000)

{
    netman = new QNetworkAccessManager(this);

    DIRECT_CONNECT(netman, finished, this, request_finished, (QNetworkReply*));

    // setup network
    //netman->setProxy(netproxy);
    //netproxy.setCapabilities(QNetworkProxy::HostNameLookupCapability);
}

void CWeb::request_finished(QNetworkReply * r){
    map<QNetworkReply*, CRequest*>::iterator    it = reply_map.find(r);

    if(it == reply_map.end()){
        cout << "map error\n";
        return;
    }

    CRequest *req = it->second;

    // do something

    r->deleteLater();

    emit reply(req);
}

void CWeb::send_start(){
    cout << "web send start\n";
    emit start();
}


//
// slots
//

void CWeb::request(CRequest *req){
    cout << "incoming: " << req->url.toString().toAscii().data() << endl;

    QNetworkReply *r = netman->get(QNetworkRequest(req->url));

    pair<QNetworkReply*, CRequest*>     p(r, req);
    reply_map.insert(p);
}

void CWeb::stop(){
    cout << "web stop\n";
    this->thread()->quit();
    //QCoreApplication::quit();
}


