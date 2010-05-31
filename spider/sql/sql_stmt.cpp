
#include "sql_stmt.h"


SqlStmt::SqlStmt(const SqlConn& conn) : SqlHandle(0, SQL_HANDLE_STMT) {
    SQLRETURN   rc;

    SQLAPI(SQLAllocHandle, (SQL_HANDLE_STMT, conn, &handle), this);
}

// bind

SQLRETURN SqlStmt::bindcol(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValuePtr, SQLINTEGER BufferLength, SQLLEN *StrLen_or_Ind){
    SQLRETURN   rc;
    SQLAPI(SQLBindCol, (*this, ColumnNumber, TargetType, TargetValuePtr, BufferLength, StrLen_or_Ind), this);
    return rc;
}

// attributes

SQLRETURN SqlStmt::set_attr(SQLINTEGER attr, SQLPOINTER ptr, SQLINTEGER len){
    SQLRETURN   rc;
    SQLAPI(SQLSetStmtAttr, (*this, attr, ptr, len), this);
    return rc;
}

// statement

SQLRETURN SqlStmt::fetch(){
    SQLRETURN   rc;
    SQLAPI(SQLFetch, (*this), this);
    return rc;
}

SQLRETURN SqlStmt::direct(SQLWCHAR* text){
    SQLRETURN   rc;
    SQLAPI(SQLExecDirectW, (*this, text, SQL_NTS), this);
    return rc;
}

// utils

SQLRETURN SqlStmt::bind_param_offset(SQLINTEGER* ptr){
    return this->set_attr(SQL_ATTR_PARAM_BIND_OFFSET_PTR, ptr, SQL_IS_POINTER);
}

SQLRETURN SqlStmt::bind_row_offset(SQLINTEGER* ptr){
    return this->set_attr(SQL_ATTR_ROW_BIND_OFFSET_PTR, ptr, SQL_IS_POINTER);
}

