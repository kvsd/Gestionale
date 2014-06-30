######################################################################
# Automatically generated by qmake (2.01a) ven gen 3 11:46:43 2014
######################################################################

TEMPLATE = app
TARGET = Gestionale
QT += core gui sql

DEPENDPATH += . \
              moduleAgenti \
              moduleAnagrafica \
              moduleAzienda \
              moduleMagazzino \
              moduleDatabase \
              libs
INCLUDEPATH += . \
               moduleAgenti \
               moduleAnagrafica \
               libs \
               moduleAzienda \
               moduleMagazzino \
               moduleDatabase

# Input
HEADERS += moduleDatabase/connectionsetupdialog.h \
           libs/error.h \
           moduleDatabase/logindialog.h \
           mainwindow.h \
           moduleDatabase/tablesetupdialog.h \
           moduleAgenti/agentiadddialog.h \
           moduleAgenti/agentiviewdialog.h \
           moduleAnagrafica/anagraficaadddialog.h \
           moduleAnagrafica/anagraficawindow.h \
           moduleAnagrafica/optionsanagraficadialog.h \
           moduleAzienda/aziendadialog.h \
           moduleMagazzino/articolodialog.h \
           moduleMagazzino/magazzinowindow.h \
           libs/controllodati.h \
           libs/simpledialogs.h \
           libs/custommodel.h \
           moduleMagazzino/optionsmagazzinodialog.h \
    moduleMagazzino/magazzino_const.h \
    moduleAnagrafica/anagrafica_const.h \
    libs/gestionale_const.h \
    moduleMagazzino/codivaupdatedialog.h \
    moduleMagazzino/configprintdialog.h \
    moduleAgenti/agenti_const.h \
    moduleMagazzino/printreport.h
FORMS += moduleDatabase/connectionsetupdialog.ui \
         moduleDatabase/logindialog.ui \
         mainwindow.ui \
         moduleDatabase/tablesetupdialog.ui \
         moduleAgenti/agentiadddialog.ui \
         moduleAgenti/agentiviewdialog.ui \
         moduleAnagrafica/anagraficaadddialog.ui \
         moduleAnagrafica/anagraficawindow.ui \
         moduleAnagrafica/optionsanagraficadialog.ui \
         moduleAzienda/aziendadialog.ui \
         moduleMagazzino/articolodialog.ui \
         moduleMagazzino/magazzinowindow.ui \
         moduleMagazzino/optionsmagazzinodialog.ui \
    moduleMagazzino/codivaupdatedialog.ui \
    moduleMagazzino/configprintdialog.ui \
    moduleMagazzino/printreport.ui
SOURCES += moduleDatabase/connectionsetupdialog.cpp \
           libs/error.cpp \
           moduleDatabase/logindialog.cpp \
           main.cpp \
           mainwindow.cpp \
           moduleDatabase/tablesetupdialog.cpp \
           moduleAgenti/agentiadddialog.cpp \
           moduleAgenti/agentiviewdialog.cpp \
           moduleAnagrafica/anagraficaadddialog.cpp \
           moduleAnagrafica/anagraficawindow.cpp \
           moduleAnagrafica/optionsanagraficadialog.cpp \
           moduleAzienda/aziendadialog.cpp \
           moduleMagazzino/articolodialog.cpp \
           moduleMagazzino/magazzinowindow.cpp \
           libs/controllodati.cpp \
           libs/simpledialogs.cpp \
           libs/custommodel.cpp \
           moduleMagazzino/optionsmagazzinodialog.cpp \
    moduleMagazzino/magazzino_const.cpp \
    moduleMagazzino/codivaupdatedialog.cpp \
    moduleMagazzino/configprintdialog.cpp \
    moduleMagazzino/printreport.cpp
