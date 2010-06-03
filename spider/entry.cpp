

#include "utils.h"
#include "dbc.h"

#include "../sql/sql_api.h"

#include <QtCore/QStringList>

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

        

#if 0
        CDbc        dbc(argc, argv);

        QCoreApplication::exec();


        SqlEnv      env;
        SqlConn     dbc(env);

        try {
            dbc.connect();
        }catch(SqlException e){
            if(e[0] && (e[1] == 0) && !strcmp(e[0], "08001")){
                cout << "Cannot connect" << endl;
                return -1;
            }
            throw e;
        }

        SqlStmt     st(dbc);

        st.direct(L"SELECT id, url FROM urls2");

        {
            SQLINTEGER      id;

            st.bindcol(1, SQL_C_SLONG, &id, 0, NULL);

            cout << "data:" << endl;

            while(st.fetch() != SQL_NO_DATA){
                string      str;

                SQLCHAR     buf[3];
                SQLINTEGER  len;
                SQLRETURN   rc;

                while((rc = st.get_data(2, SQL_C_CHAR, buf, sizeof(buf), &len)) != SQL_NO_DATA){
                    SQLINTEGER  lenmax = sizeof_a(buf) - 1;
                    if((len > lenmax) || (len == SQL_NO_TOTAL)) len = lenmax;

                    //cout << len << endl;
                    str.append(buf, buf + lenmax);
                }

                cout << id << " " << str << endl;
            }

        }
#endif
    }
    catch(SqlException e){
        cout << "ERROR: " << e.message() << endl;
    }
    catch(const char* msg){
        cout << "FATAL: " << msg << endl;
    }

    return 0;
}

