

#include "utils.h"

#include "../sql/sql_api.h"

int main(){

    try {

        sql_api.init();

        SqlEnv      env;
        SqlConn     dbc(env);

        SqlStmt     st(dbc);

        st.direct(L"SELECT id FROM pages");

        {
            SQLINTEGER      id;
            SQLLEN          id_ind;

            st.bindcol(1, SQL_C_SLONG, &id, 0, &id_ind);

            cout << "data:";

            while(st.fetch() != SQL_NO_DATA){
                if(id_ind == SQL_NULL_DATA){
                    cout << " NULL";
                }else{
                    cout << " " << id;
                }
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

