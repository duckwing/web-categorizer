

#include "utils.h"

#include <QtCore/QVariant>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

int main(int argc, char** argv){

    try {

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
    }
    catch(const char* msg){
        cout << "FATAL: " << msg << endl;
    }

    return 0;
}

