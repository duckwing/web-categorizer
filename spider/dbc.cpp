

#include "dbc.h"

CDbc::CDbc() :
    QObject ()
{
}

CDbc::~CDbc(){
    cout << "dbc died\n";
}

bool CDbc::open_db(){
    // open the database connection
    QSqlDatabase    db = QSqlDatabase::database();

    if(db.isOpenError()){
        cerr << "ERROR: failed to open database: " << db.lastError().text().toAscii().data() << endl;
        return false;
    }

    if(q1 == 0){
        q1 = new QSqlQuery(db);
        if(!q1->prepare("SELECT id, url FROM urls WHERE NOT EXISTS (SELECT 1 FROM pagedata WHERE urls.id = pagedata.page_id)")){
            cerr << "ERROR: failed to prepare the 1st query: " << q1->lastError().text().toAscii().data() << endl;

            delete q1;
            q1 = 0;
            return false;
        }
    }

    if(q2 == 0){
        q2 = new QSqlQuery(db);
        if(!q2->prepare("SELECT id, url FROM urls WHERE NOT EXISTS (SELECT 1 FROM pagedata WHERE urls.id = pagedata.page_id)")){
            cerr << "ERROR: failed to prepare the 2nd query: " << q2->lastError().text().toAscii().data() << endl;

            delete q2;
            q2 = 0;
            return false;
        }
    }

    return true;
}


//
// slots
//

void CDbc::start(){
    // setup timer
    QTimer* timer = new QTimer(this);
    DIRECT_CONNECT(timer, timeout, this, scheduler, ());
    timer->start(1000);

    // setup the database
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("spider");
    db.setPassword("");
}

void CDbc::reply(CRequest* req){
    cout << "reply " << req->url.toString().toAscii().data()
        << "(" << req->http_status << " " << req->http_reason.toAscii().data() << ")" << endl;

    delete req;
}

void CDbc::scheduler(){
    {
        QFile       file("spider_stop.bat");
        if(file.exists()){
            cout << "dbc die\n";
            deleteLater();
            return;
        }
    }

    if(!open_db()){
        return;
    }

    q1->exec();
    while(q1->next()){
        int         id = q1->value(0).toInt();
        QString     url = q1->value(1).toString();

        cout << id << ": " << url.toAscii().data() << endl;
    }
}


