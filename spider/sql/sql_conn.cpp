
#include "sql_conn.h"

#include "../common/utils.h"

#define PSQL_CONN_STRING        L"DRIVER=PostgreSQL;SERVER=localhost;UID=spider;PORT=5432;DATABASE=postgres"


SqlConn::SqlConn(const SqlEnv& env) : SqlHandle(0, SQL_HANDLE_DBC), connected(false) {
    SQLRETURN   rc;

    SQLAPI(SQLAllocHandle, (SQL_HANDLE_DBC, env, &handle), this);
}

SqlConn::~SqlConn(){
    if(connected){
        SQLRETURN   rc;
        SQLAPI(SQLDisconnect, (*this), this);
    }
}

void SqlConn::connect(){
    SQLRETURN   rc;

    SQLWCHAR        buffer[1024] = L"";
    SQLSMALLINT     sz;

    SQLAPI(SQLDriverConnectW, (*this, NULL, (SQLWCHAR*)PSQL_CONN_STRING, SQL_NTS, buffer, sizeof_a(buffer), &sz, SQL_DRIVER_NOPROMPT), this);

    if(0) wprintf(L"Connection string: %s\n", buffer);

    connected = true;
}

