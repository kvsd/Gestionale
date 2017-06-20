######################################################################
# Automatically generated by qmake (2.01a) ven gen 3 11:46:43 2014
######################################################################

TEMPLATE = app
TARGET = Gestionale
QT += core gui sql
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

DEPENDPATH += . \
              moduleAgenti \
              moduleAnagrafica \
              moduleAzienda \
              moduleMagazzino \
              moduleDatabase \
			  moduleReport \
              libs
INCLUDEPATH += . \
               moduleAgenti \
               moduleAnagrafica \
               libs \
               moduleAzienda \
               moduleMagazzino \
			   moduleReport \
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
           libs/simpledialogs.h \
           libs/custommodel.h \
           moduleMagazzino/optionsmagazzinodialog.h \
           moduleMagazzino/magazzino_const.h \
           moduleAnagrafica/anagrafica_const.h \
           libs/gestionale_const.h \
           moduleMagazzino/codivaupdatedialog.h \
           moduleReport/configprintdialog.h \
           moduleAgenti/agenti_const.h \
           moduleReport/reportdlg.h \
		   moduleReport/report_const.h \
    moduleAzienda/azienda_const.h \
    libs/utils.h \
    modulePrimaNota/primanotawindow.h \
    modulePrimaNota/primanota_const.h \
	modulePrimaNota/primanotaadddlg.h \
    moduleDatabase/db_const.h \
    moduleDatabase/userdbdialog.h \
    libs/optionsdialog.h \
    libs/customwindow.h \
    moduleReport/report.h
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
         moduleReport/configprintdialog.ui \
         moduleReport/reportdlg.ui \
    modulePrimaNota/primanotawindow.ui \
    modulePrimaNota/primanotaadddlg.ui \
    moduleDatabase/userdbdialog.ui
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
           libs/simpledialogs.cpp \
           libs/custommodel.cpp \
           moduleMagazzino/optionsmagazzinodialog.cpp \
           moduleMagazzino/codivaupdatedialog.cpp \
           moduleReport/configprintdialog.cpp \
           moduleReport/reportdlg.cpp \
    libs/utils.cpp \
    modulePrimaNota/primanotawindow.cpp \
    modulePrimaNota/primanotaadddlg.cpp \
    moduleDatabase/userdbdialog.cpp \
    libs/optionsdialog.cpp \
    libs/customwindow.cpp \
    moduleReport/report.cpp
