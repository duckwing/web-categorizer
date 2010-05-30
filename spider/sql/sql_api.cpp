
#include "sql_api.h"


SqlApi       sql_api;





void SqlApi::init(){
    HMODULE m = LoadLibraryW(L"modbc.dll");
    //LPVOID  p, *pp;

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

