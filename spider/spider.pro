
####### general configuration
TEMPLATE = app
TARGET = spider

CLASSES *= web/entry
CLASSES *= web/utils
CLASSES *= web/web
CLASSES *= web/dbc

CLASSES *= sql/sql_api
CLASSES *= sql/sql_handle
CLASSES *= sql/sql_exc
CLASSES *= sql/sql_env
CLASSES *= sql/sql_conn
CLASSES *= sql/sql_stmt

HEADER *= sql/sqlapi.in

#error($$CONFIG)

QT -= gui
QT += network

QMAKE_LIBS += libodbc32

CONFIG = debug warn_on
CONFIG *= console qt
CONFIG *= exceptions stl mmx sse

####### output files
OBJECTS_DIR = obj

MOC_DIR = $${OBJECTS_DIR}

DESTDIR = ..

####### the option for generating the map file
QMAKE_LFLAGS_DEBUG += -Wl,-Map,../src.map
#QMAKE_CXXFLAGS_DEBUG += -Wa,-D

####### classes processor

for(class, CLASSES){
    exists($${class}.cpp):SOURCES *= $${class}.cpp
    exists($${class}.h):HEADERS *= $${class}.h
}

#message(SOURCES: $$SOURCES)
#message(HEADERS: $$HEADERS)

