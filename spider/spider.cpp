

#include "spider.h"

#include "web.h"
#include "dbc.h"


int main(int argc, char** argv){

    QCoreApplication        app(argc, argv);

    QThread                 worker;

    CWeb                    *web = new CWeb();
    CDbc                    *dbc = new CDbc();

    // connect
    QUEUED_CONNECT(web, started, dbc, start, ());
    QUEUED_CONNECT(&worker, finished, web, deleteLater, ());

    DIRECT_CONNECT(dbc, destroyed, &worker, quit, ());
    DIRECT_CONNECT(web, destroyed, &app, quit, ());

    QUEUED_CONNECT(dbc, request, web, request, (CRequest*));
    QUEUED_CONNECT(web, reply  , dbc, reply  , (CRequest*));

    // move dbc to another thread
    dbc->moveToThread(&worker);

    // start the thread
    worker.start();

    // send the start signal to dbc
    web->start();

    // exec local event loop
    QCoreApplication::exec();

    cout << "bye\n";

    return 0;
}

