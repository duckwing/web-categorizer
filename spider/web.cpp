

#include "web.h"

CWeb::CWeb() :
    QObject (),

    netman(0),
    netproxy(QNetworkProxy::Socks5Proxy, "127.0.0.1", 4000)

{
}

CWeb::~CWeb(){
    cout << "web dies\n";

    cout << "netman: " << (void*)netman << endl;
    cout << "netman parent: " << (void*)netman->parent() << " vs " << (void*)this << endl;

    {
        map<QNetworkReply*, CRequest*>::iterator    it, it2;

        for(it = reply_map.begin(), it2 = reply_map.end(); it != it2; it++){
            QNetworkReply* rep = it->first;

            cout << "rep " << (void*)rep << " " << (void*)rep->parent() << endl;
        }
    }


    netman->setParent(0);
    delete netman;
}

void CWeb::request_finished(QNetworkReply * r){
    map<QNetworkReply*, CRequest*>::iterator    it = reply_map.find(r);

    if(it == reply_map.end()){
        cout << "map error\n";
        return;
    }

    CRequest *req = it->second;

    reply_map.erase(it);

    // do something

    r->deleteLater();

    emit reply(req);
}

void CWeb::start(){
    netman = new QNetworkAccessManager(this);

    DIRECT_CONNECT(netman, finished, this, request_finished, (QNetworkReply*));

    // setup network
    //netman->setProxy(netproxy);
    //netproxy.setCapabilities(QNetworkProxy::HostNameLookupCapability);

    cout << "web send start\n";
    emit started();
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


