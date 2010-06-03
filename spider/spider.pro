
####### general configuration
TEMPLATE = app
TARGET = spider

CLASSES *= spider
CLASSES *= web
CLASSES *= dbc
CLASSES *= request

PRECOMPILED_HEADER = spider.h

#error($$CONFIG)

QT -= gui
QT += network sql

CONFIG = debug warn_on
CONFIG *= console qt precompile_header
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

