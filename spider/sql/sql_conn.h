
#include <windows.h>
#include <sqlext.h>

#include <string>
#include <algorithm>
#include <iostream>

using namespace std;


#define sizeof_a(a)     (sizeof(a)/sizeof(a[0]))


#define PSQL_CONN_STRING        L"DRIVER=ODBCng;SERVER=localhost;UID=spider;PORT=5432;DATABASE=postgres"



#define API(api, params, handle)    \
    switch(rc = sapi. api params){        \
    case SQL_INVALID_HANDLE:        \
        throw SqlException(#api #params ": invalid handle");    \
    case SQL_ERROR:                 \
        throw SqlException(#api #params, handle);               \
    default:                        \
        break;                      \
    }



//////////////////////////////////
// api
//


class SqlApi {
public:
    void init(){
        HMODULE m = LoadLibrary("modbc.dll");
        LPVOID  p, *pp;

        if(m == NULL){
            throw "LoadLibrary(modbc.dll) failed";
        }

#define C(api, params)      \
        if((this->api = (SQLRETURN (SQL_API*) params)GetProcAddress(m, #api)) == NULL){                  \
            throw "GetProcAddress(" #api ") failed";                \
        }
#include "sqlapi.in"
#undef C
    }

#define C(api, params)      SQLRETURN (SQL_API * api) params;
#include "sqlapi.in"
#undef C

} sapi;


//////////////////////////////
// handles
//

class SqlHandle {
protected:
    SQLHANDLE       handle;
    SQLSMALLINT     type;

public:
    SqlHandle(SQLHANDLE h, SQLSMALLINT t): handle(h), type(t) {}
    ~SqlHandle();

    inline operator SQLHANDLE () const {
        return handle;
    }

    inline operator SQLSMALLINT () const {
        return type;
    }
};



//////////////////////////////
// exceptions
//


class SqlException {
private:
    SQLCHAR     *buffer;
public:
    SqlException(const char* msg){
        int l = strlen(msg) + 1;

        buffer = new SQLCHAR [l];

        memcpy(buffer, msg, sizeof(SQLCHAR) * l);
    }

    SqlException(const char* msg, const SqlHandle& exc){
        // locals
        SQLSMALLINT cnt;

        SQLINTEGER  num;

        // query the number of diag records
        switch(sapi.SQLGetDiagFieldW(exc, exc, 0, SQL_DIAG_NUMBER, &num, SQL_IS_INTEGER, &cnt)){
        case SQL_SUCCESS:
        //case SQL_SUCCESS_WITH_INFO:
            break;
        default:
            throw "SQLGetDiagField error (1)";
        }

        basic_string<SQLCHAR>       buf1;
        basic_string<SQLWCHAR>      buf2;

        for(int i = 1; i <= num; i++){
            SQLWCHAR        state[6] = {0, 0, 0, 0, 0, 0};
            SQLINTEGER      native;
            SQLWCHAR        buf3[1024];
            SQLSMALLINT     sz;

            switch(sapi.SQLGetDiagRecW(exc, exc, i, state, &native, buf3, sizeof_a(buf3), &sz)){
            case SQL_SUCCESS:
            //case SQL_SUCCESS_WITH_INFO:
                break;
            default:
                throw "SQLGetDiagField error (2)";
            }

            basic_string<SQLWCHAR>  b_state(state);
            basic_string<SQLWCHAR>  b_buf(buf3);

            buf2.append(L"\n  ");
            buf2.append(b_state);
            buf2.append(L"  ");
            buf2.append(b_buf);
        }

        string      m(msg);
        m.append(": ");

        buf1.append(m.begin(), m.end());
        buf1.append(buf2.begin(), buf2.end());

        int l = buf1.size() + 1;
        buffer = new SQLCHAR [l];
        std::copy(buf1.begin(), buf1.end(), buffer);

        buffer[l-1] = '\0';
    }

    SQLCHAR* message() const {
        return buffer;
    }

    ~SqlException(){
        delete [] buffer;
    }
};



SqlHandle::~SqlHandle() {
    SQLRETURN   rc;
    API(SQLFreeHandle, (type, handle), *this);
}



//////////////////////////////
// sql
//


class SqlEnv : public SqlHandle {
public:
    SqlEnv() : SqlHandle(0, SQL_HANDLE_ENV) {
        SQLHANDLE   h;

        switch (sapi.SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &handle)){
            case SQL_SUCCESS: case SQL_SUCCESS_WITH_INFO: break;
            default: throw "SQLAllocHandle(SQL_HANDLE_ENV) failed";
        }

        set_attr(SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3);
    }

    // methods

    SQLRETURN set_attr(SQLINTEGER attr, SQLPOINTER value, SQLINTEGER len = 0){
        SQLRETURN rc;

        API(SQLSetEnvAttr, (*this, attr, value, len), *this);

        return rc;
    }

};


class SqlConn : public SqlHandle {
public:
    SqlConn(const SqlEnv& env) : SqlHandle(0, SQL_HANDLE_DBC) {
        SQLRETURN   rc;

        API(SQLAllocHandle, (SQL_HANDLE_DBC, env, &handle), *this);

        SQLWCHAR        buffer[1024] = L"";
        SQLSMALLINT     sz;

        API(SQLDriverConnectW, (*this, NULL, (SQLWCHAR*)PSQL_CONN_STRING, SQL_NTS, buffer, sizeof_a(buffer), &sz, SQL_DRIVER_NOPROMPT), *this);

        wprintf(L"Connection string: %s\n", buffer);

    }

    ~SqlConn(){
        SQLRETURN   rc;

        API(SQLDisconnect, (*this), *this);
    }

};

class SqlStmt : public SqlHandle {
public:
    SqlStmt(const SqlConn& conn) : SqlHandle(0, SQL_HANDLE_STMT) {
        SQLRETURN   rc;

        API(SQLAllocHandle, (SQL_HANDLE_STMT, conn, &handle), *this);
    }

    // bind

    SQLRETURN bindcol(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValuePtr, SQLINTEGER BufferLength, SQLLEN *StrLen_or_Ind){
        SQLRETURN   rc;
        API(SQLBindCol, (*this, ColumnNumber, TargetType, TargetValuePtr, BufferLength, StrLen_or_Ind), *this);
        return rc;
    }

    // statement

    SQLRETURN fetch(){
        SQLRETURN   rc;
        API(SQLFetch, (*this), *this);
        return rc;
    }

    SQLRETURN direct(SQLWCHAR* text){
        SQLRETURN   rc;
        API(SQLExecDirectW, (*this, text, SQL_NTS), *this);
        return rc;
    }


};




////////////////////////////////
// main
//

void show_drivers(SqlEnv& env);


int main(){

    try {

        sapi.init();

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

