


#include "utils.h"

#include "../sql/sql_api.h"

#include "../web/web.h"

int main(int argc, char** argv){

    try {

#if 0
        CWeb                web(argc, argv);

        QCoreApplication::exec();

        cout << "leave" << endl;
#endif


        //sql_api.init();

        cout << "env" << endl;

        SqlEnv      env;

        cout << "dbc" << endl;

        SqlConn     dbc(env);

        cout << "st" << endl;

        SqlStmt     st(dbc);

        st.direct(L"SELECT id, url FROM urls");

        {
            SQLINTEGER      id;

            st.bindcol(1, SQL_C_SLONG, &id, 0, NULL);

            cout << "data:";

            while(st.fetch() != SQL_NO_DATA){
                string      str;

                cout << "out" << endl;

                SQLCHAR     buf[5];
                SQLINTEGER  len;
                SQLRETURN   rc;

                while((rc = st.get_data(2, SQL_C_CHAR, buf, sizeof(buf), &len)) != SQL_NO_DATA){
                    str.append((char*)buf);
                }

                cout << id << " " << str << endl;
            }

            cout << endl;
        }
    }
    catch(SqlException e){
        cout << "ERROR: " << e.message() << endl;
    }
    catch(const char* msg){
        cout << "FATAL: " << msg << endl;
    }

    return 0;
}

