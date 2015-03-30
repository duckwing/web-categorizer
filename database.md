The database serves as a mediator for all other modules. The commands are issued by adding new entries to the appropriate tables.

Currently, I use [PostgreSQL](http://www.postgresql.org/). The QSql module of Qt4 is used as a connector.

The download section below provides some links to download the Qt4 libraries. However, the default QSql4.dll binary didn't provide the QPSQL intrface and had to be recompiled. See the recompilation procedure below.

## Data model ##

_to be added later_

## Downloads ##

  * [PostgreSQL](http://www.postgresql.org/) -> [Downloads](http://www.postgresql.org/download/windows) -> [zip archive](http://www.enterprisedb.com/products/pgbindownload.do)
  * [Qt downloads](http://qt.nokia.com/downloads) -> [Qt libraries 4.6.2 for Windows (minGW 4.4, 278 MB)](http://qt.nokia.com/downloads/windows-cpp)

_See older versions of this page for other downloads._

## Qt SQL module recompilation ##

  1. Download the qt-library package.
  1. Install it. _(Actually, there were some issues with the installation, since that process required almost 2GB of free space for temporary files. Changing TEMP/TMP enviro variables to something more appropriate saved the day.)_
    * **Note:** qmake is almost ready for work. Simply add the qt bin dir to the PATH. Then you will have to run cmd and run qtvars.bat there.
  1. Download the PostgreSQL zip archive and unzip it somewhere closer to the root of the fs _(whitespaces in paths suck)._
  1. Execute `configure.exe -debug-and-release -opensource -shared -fast -qt-sql-psql -no-qmake -no-rtti`
    * `-fast` -- create makefile stubs instead of actually creating all the makefiles
    * `-no-qmake` -- don't compile qmake _(we already have it)._
    * `-qt-sql-psql` -- compile psql driver into the QSql module _(I couldn't get it working as a plugin)._
    * `-no-rtti` -- why not?
  1. Descend into `src/sql`.
  1. Run the following stuff: `qmake "INCLUDEPATH+=d:\psql\include" "LIBS+=d:\psql\lib\libpq.lib"`.
  1. Now `make release`.
    * It should compile and install everything. _(Check it with `QSqlDatabase::drivers()`.)_
    * You may now move or delete the PostgreSQL.

Useful code snippets:
```
configure.exe -debug-and-release -opensource -shared -fast -qt-sql-psql -no-qmake -no-rtti
```
```
call qtvars
qmake "INCLUDEPATH+=d:\psql\include" "LIBS+=d:\psql\lib\libpq.lib"
make release
```