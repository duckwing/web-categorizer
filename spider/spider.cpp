

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

#if 0

    QSqlDatabase   db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName("127.0.0.1");
    db.setDatabaseName("postgres");

    bool op = db.open("spider", "");

    cout << op << endl;

    {
        QSqlQuery q = db.exec("SELECT id, url FROM urls");

        while(q.next()){
            cout << q.value(0).toInt() << ": " << q.value(1).toString().toAscii().data() << endl;
        }
    }

    db.close();
#endif

    return 0;
}

