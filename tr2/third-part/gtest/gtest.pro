######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 24 11:04:10 2015
######################################################################

TEMPLATE = lib
TARGET = gtest
CONFIG(x64){
TARGET = $$TARGET"64"
}
DEPENDPATH += . src
INCLUDEPATH += ./include

CONFIG += staticlib

dir = ../..
include($$dir/common.pri)

DEFINES += _CRT_SECURE_NO_WARNINGS

SOURCES += src/gtest-all.cc src/gtest_main.cc
