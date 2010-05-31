
#include <windows.h>
#include <sql.h>
#include <odbcinst.h>

#include <iostream>

using namespace std;


inline LPCSTR describe (RETCODE r){
    switch(r){
#define c(id)   case id: return #id
    c(SQL_SUCCESS);
    c(SQL_SUCCESS_WITH_INFO);
    c(SQL_NO_DATA);
    c(SQL_ERROR);
#undef c
    default:    return "<undef>";
    }
}



int main(){


    CHAR        buffer[256];
    WORD        cnt;
    DWORD       usage;

    if(0){
        strcpy(buffer, "d:\\Program Files\\ODBCng");

        if(SQLInstallDriverEx(
                    "ODBCng\0Driver=modbc.dll\0",
                    buffer, buffer, sizeof(buffer)/sizeof(buffer[0]),
                    &cnt, ODBC_INSTALL_COMPLETE, &usage))
        {
            cout << "TRUE" << endl;

            cout << "cnt: " << cnt << endl
                 << "usage: " << usage << endl
                 << buffer << endl;

            return 0;
        }else{
            cout << "FALSE" << endl;

            for(int i = 1; i <= 8; i++){
                CHAR    buf[256];
                DWORD   code;

                RETCODE r = SQLInstallerError(i, &code, buf, sizeof(buf)/sizeof(buf[0]), NULL);

                cout << i << ": " << describe(r) << ": " << buf << endl;
            }

            return -1;
        }
    }else{
        if(SQLRemoveDriver(
                    "ODBCng", TRUE, &usage))
        {
            cout << "TRUE" << endl;

            cout << "usage: " << usage << endl;

            return 0;
        }else{
            cout << "FALSE" << endl;

            for(int i = 1; i <= 8; i++){
                CHAR    buf[256];
                DWORD   code;

                RETCODE r = SQLInstallerError(i, &code, buf, sizeof(buf)/sizeof(buf[0]), NULL);

                cout << i << ": " << describe(r) << ": " << buf << endl;
            }

            return -1;
        }
    }
}

