#ifndef ERROR_H
#define ERROR_H

#include <QMessageBox>
#include <QDebug>
#include <QPushButton>

#define ERR000 "Codice Errore 000" //LoginDialog
#define ERR001 "Codice Errore 001" //TableSetupDialog
#define ERR002 "Codice Errore 002" //*
#define ERR003 "Codice Errore 003" //*
#define ERR004 "Codice Errore 004" //*
#define ERR005 "Codice Errore 005" //*
#define ERR006 "Codice Errore 006" //*
#define ERR007 "Codice Errore 007" //*
#define ERR008 "Codice Errore 008" //LoginDialog
#define ERR009 "Codice Errore 009" //AgentiAddDialog
#define ERR010 "Codice Errore 010" //AgentiViewDialog
#define ERR011 "Codice Errore 011" //AnagraficaAddDialog
#define ERR012 "Codice Errore 012" //AziendaDialog
#define ERR013 "Codice Errore 013" //AgentiViewDialog
#define ERR014 "Codice Errore 014" //*
#define ERR015 "Codice Errore 015" //Non usato
#define ERR016 "Codice Errore 016" //Non usato
#define ERR017 "Codice Errore 017" //AnagraficaAddDialog
#define ERR018 "Codice Errore 018" //*
#define ERR019 "Codice Errore 019" //*
#define ERR020 "Codice Errore 020" //*
#define ERR021 "Codice Errore 021" //Non Usato
#define ERR022 "Codice Errore 022" //Non Usato
#define ERR023 "Codice Errore 023" //AnagraficaAddDialog
#define ERR024 "Codice Errore 024" //*
#define ERR025 "Codice Errore 025" //*
#define ERR026 "Codice Errore 026" //AnagraficaWindow
#define ERR027 "Codice Errore 027" //*
#define ERR028 "Codice Errore 028" //*
#define ERR029 "Codice Errore 029" //AziendaDialog
#define ERR030 "Codice Errore 030" //*
#define ERR031 "Codice Errore 031" //*
#define ERR032 "Codice Errore 032" //*
#define ERR033 "Codice Errore 033" //*
#define ERR034 "Codice Errore 034" //*
#define ERR035 "Codice Errore 035" //*
#define ERR036 "Codice Errore 036" //MagazzinoWindow
#define ERR037 "Codice Errore 037" //*
#define ERR038 "Codice Errore 038" //ArticoloDialog
#define ERR039 "Codice Errore 039" //*
#define ERR040 "Codice Errore 040" //Non Usato
#define ERR041 "Codice Errore 041" //ArticoloDialog
#define ERR042 "Codice Errore 042" //*
#define ERR043 "Codice Errore 043" //*
#define ERR044 "Codice Errore 044" //*
#define ERR045 "Codice Errore 045" //*
#define ERR046 "Codice Errore 046" //*
#define ERR047 "Codice Errore 047" //MagazzinoWindow
#define ERR048 "Codice Errore 048" //PrimaNotaWindow
#define ERR049 "Codice Errore 049" //*
#define ERR050 "Codice Errore 050" //ArticoloDialog
#define ERR051 "Codice Errore 051" //PrimaNotaAddDlg
#define ERR052 "Codice Errore 052" //*
#define ERR053 "Codice Errore 053" //*
#define ERR054 "Codice Errore 054" //Collissione: MainWindow e PrimaNotaWindow
#define ERR055 "Codice Errore 055" //MainWindow
#define ERR056 "Codice Errore 056" //MagazzinoWindow
#define ERR057 "Codice Errore 057" //CodIvaUpdateDialog


const QString MSG000 = QString::fromUtf8("Si è verificato un errore nella connessione al database.");
const QString MSG001 = QString::fromUtf8("Non è possibile inserire stringhe di testo vuote.");
const QString MSG002 = QString::fromUtf8("Si è verificato un errore nell'inserimento del record. Probrabilmente è stato inserito un record già presente nella tabella.");
const QString MSG003 = QString::fromUtf8("Si è verificato un errore nella cancellazione del record. Probabilmente il record è referenziato da un altro record.");
const QString MSG004 = QString::fromUtf8("Per poter cancellare un record bisogna prima selezionarlo dalla lista a lato.");
const QString MSG005 = QString::fromUtf8("Si è verificato un errore nell'aggiornamento del record.");
const QString MSG006 = QString::fromUtf8("Non è permesso aggiornare il record con una stringa di testo vuota.");
const QString MSG007 = QString::fromUtf8("Per poter aggiornare un record bisogna prima selezionarlo dalla lista a lato.");
const QString MSG008 = QString::fromUtf8("Devi selezionare il fornitore dal filtro fornitore a lato.");
const QString MSG009 = QString::fromUtf8("Per poter cancellare un articolo bisogna prima selezionarlo dalla lista articoli.");
const QString MSG010 = QString::fromUtf8("Si è verificato un errore imprevisto.");
const QString MSG011 = QString::fromUtf8("Per poter aggiornare un articolo bisogna prima selezionarlo dalla lista articoli.");
const QString MSG012 = QString::fromUtf8("Prima di cancellare una nota bisogna selezionarla dalla lista in alto");
const QString MSG013 = QString::fromUtf8("Il campo descrizione è obbligatorio");
const QString MSG014 = QString::fromUtf8("L'indirizzo è un campo obbligatorio, deve essere specificato.");
const QString MSG015 = QString::fromUtf8("Il record è già presente.");
const QString MSG016 = QString::fromUtf8("La Ragione sociale non è stata inserita.");
const QString MSG017 = QString::fromUtf8("Non è stato specificato se il nuovo record è un cliente o un fornitore.");
const QString MSG018 = QString::fromUtf8("La partita IVA e il codice fiscale sono campi obbligatori.");
const QString MSG019 = QString::fromUtf8("La partita IVA immessa potrebbe essere sbagliata. Si vuole continuare lo stesso?");
const QString MSG020 = QString::fromUtf8("Il codice fiscale immesso potrebbe essere sbagliato. Si vuole continuare lo stesso?");
const QString MSG021 = QString::fromUtf8("Il cognome dell'agente è obbligatorio.");
const QString MSG022 = QString::fromUtf8("Si è verificato un errore nell'inserimento del record.");
const QString MSG023 = QString::fromUtf8("Sto per aggiornare gli articoli con iva al %1% al %2%.");
const QString MSG024 = QString::fromUtf8("Errore conversione.\nInserire un numero valido");
const QString MSG025 = QString::fromUtf8("Prima di modificare una nota bisogna selezionarla dalla lista in alto");
const QString MSG026 = QString::fromUtf8("Non è stata effettuata la connessione al database");
const QString MSG027 = QString::fromUtf8("Per poter gestire gli utenti devi usare l'utente postgres");
const QString MSG028 = QString::fromUtf8("Per poter clonare un articolo bisogna prima selezionarlo dalla lista articoli.");
const QString MSG030 = QString::fromUtf8("I codici IVA sono uguali.");
const QString MSG031 = QString::fromUtf8("Il campo %1 deve essere compilato");
const QString MSG032 = QString::fromUtf8("Bisogna selezionare un valore dal campo %1");
const QString MSG033 = QString::fromUtf8("I campi Nome e cognome sono obbligatori");
const QString MSG034 = QString::fromUtf8("L'untente non è autorizzato, contattare l'amministratore del database.");
const QString MSG035 = QString::fromUtf8("Password o nome utente errato, se l'errore persiste contattare l'amministratore del database.");

void showDialogError(QWidget *parent, QString title, QString informative="", QString details="");
bool showDialogWarning(QWidget *parent, QString title, QString informative="", QString details="");
void showDialogInfo(QWidget *parent, QString title, QString informative="");

#endif // ERROR_H
