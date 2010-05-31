
#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#include "web.h"

#include "../common/utils.h"

CWeb::CWeb( int & argc, char ** argv ) :
    QCoreApplication ( argc, argv ),
    timer(),
    cnt(0)
{
    connect(this, SIGNAL(aboutToQuit()), SLOT(aboutToQuit()));
    connect(&timer, SIGNAL(timeout()), SLOT(timeout()));

    timer.start(1000);
}

void CWeb::timeout(){
    cnt++;

    cout << "timeout " << cnt << endl;

    if(cnt >= 5){
        QCoreApplication::quit();
    }
}

void CWeb::aboutToQuit(){
    cout << "about to quit" << endl;
}

#endif


