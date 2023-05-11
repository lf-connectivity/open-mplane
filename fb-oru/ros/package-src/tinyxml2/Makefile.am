ACLOCAL_AMFLAGS = -I m4

## Flags
AM_CPPFLAGS = -I./libtinyxml2
AM_LDFLAGS =


## Library
lib_LTLIBRARIES = libtinyxml2.la 
nobase_include_HEADERS = libtinyxml2/tinyxml2.h

libtinyxml2_la_SOURCES = src/tinyxml2.cpp

## Install documentation
WORKSPACE ?= $(HOME)
DOC_ROOT ?= $(WORKSPACE)/htmldoc_ALL

DOC_DIR = $(DOC_ROOT)/tinyxml2

install-data-local:
	@ if [ ! -d $(DOC_DIR) ] ; then mkdir -p $(DOC_DIR) ; fi
	@ echo Installing tinxml2 documentation into $(DOC_DIR)
	@ cp -r docs/* $(DOC_DIR)