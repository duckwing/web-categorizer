
#ifndef __SQL_API_H__
#define __SQL_API_H__


#include <windows.h>
#include <sqlext.h>



#define SQLAPI(api, params, handle)    \
    switch(rc = api params){        \
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

//extern SqlApi       sql_api;

class SqlHandle;
class SqlException;
class SqlEnv;
class SqlConn;
class SqlStmt;

#include "sql_handle.h"
#include "sql_exc.h"
#include "sql_env.h"
#include "sql_conn.h"
#include "sql_stmt.h"

#endif // __SQL_API_H__

