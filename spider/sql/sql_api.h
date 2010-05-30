
#ifndef __SQL_API_H__
#define __SQL_API_H__


#include <windows.h>
#include <sqlext.h>


#define PSQL_CONN_STRING        L"DRIVER=ODBCng;SERVER=localhost;UID=spider;PORT=5432;DATABASE=postgres"



#define SQLAPI(api, params, handle)    \
    switch(rc = sql_api. api params){        \
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
    void init();

#define C(api, params)      SQLRETURN (SQL_API * api) params;
#include "sqlapi.in"
#undef C

};

extern SqlApi       sql_api;

#endif // __SQL_API_H__

