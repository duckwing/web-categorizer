

#include "dbc.h"

#include "utils.h"

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#include <QtCore/QFile>

CDbc::CDbc( int & argc, char ** argv ) :
    QCoreApplication ( argc, argv )

{
}

void CDbc::scheduler(){
    // check for exit file
    {
        QFile       efile("spider_stop");

        if(efile.exists()){
            QCoreApplication::quit();
        }
    }

    cout << "timer" << endl;

    SqlEnv      env;

    SqlConn     dbc(env);

    /*
    cout << "Error: " << netreply->error() << " " <<
        netreply->errorString().toAscii().data() << endl;

    cout << "Code: " << netreply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() << endl;

    cout << netreply->readAll().data() << endl;
    */
}

#endif


