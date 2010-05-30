
####### general configuration
TEMPLATE = app
TARGET = spider

CLASSES *= common/utils
CLASSES *= common/entry

CLASSES *= sql/sql_api
CLASSES *= sql/sql_handle
CLASSES *= sql/sql_exc
CLASSES *= sql/sql_env
CLASSES *= sql/sql_conn
CLASSES *= sql/sql_stmt

CLASSES *= web/web

HEADER *= sql/sqlapi.in

#error($$CONFIG)

QT -= gui
QT += network

CONFIG = debug warn_on
CONFIG *= console qt
CONFIG *= exceptions stl mmx sse

####### output files
OBJECTS_DIR = obj

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

