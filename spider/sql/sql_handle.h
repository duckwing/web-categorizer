
#ifndef __SQL_HANDLE_H__
#define __SQL_HANDLE_H__

#include "sql_api.h"

#include "sql_exc.h"

//////////////////////////////
// handles
//

class SqlHandle {
protected:
    SQLHANDLE       handle;
    SQLSMALLINT     type;

public:
    inline SqlHandle(SQLHANDLE h, SQLSMALLINT t): handle(h), type(t) {}

    inline ~SqlHandle(){
        SQLRETURN   rc;
        SQLAPI(SQLFreeHandle, (type, handle), this);
    }

    inline operator SQLHANDLE () const {
        return handle;
    }

    inline operator SQLSMALLINT () const {
        return type;
    }
};


#endif // __SQL_HANDLE_H__

