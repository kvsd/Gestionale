#include "tablesetupdialog.h"
#include "ui_tablesetupdialog.h"

const QString ADD_QUERY = "INSERT INTO %1(descr) VALUES(:value)";
const QString REMOVEQUERY = "DELETE FROM %1 WHERE id=:id";
const QString UPDATE_QUERY = "UPDATE %1 SET descr=:value WHERE id=:id";
const QString SELECT_QUERY = "SELECT id,descr AS Valori FROM %1 WHERE id>0 ORDER BY descr";

enum columns {COL_ID, COL_DESCR};

TableSetupDialog::TableSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableSetupDialog)
{
    ui->setupUi(this);
    model = new QSqlQueryModel(this);
    ui->tableView->setModel(model);

    /*Questo dialog gestisce tabelle con due colonne:
        id -> Serial
        descr -> TEXT UNIQUE NOT NULL
      Per aggiunge tabelle basta inserirle in mapTables*/

    mapTables["Categoria merceologica"] = "cat_merce";
    mapTables["Codice Iva"] = "cod_iva";
    mapTables["Unita di misura"] = "unita_misura";
    mapTables["Sedi magazzino"] = "sede_magazzino";
    mapTables["Marca"] = "marca";
    mapTables["Tipo di ditta"] = "tipo_ditta";
    mapTables["Citta"] = "citta";
    mapTables["Provincia"] = "provincia";
    mapTables["CAP"] = "cap";
    mapTables["Stato"] = "stato";
    mapTables["Banca"] = "banca";
    mapTables["Agenzia"] = "agenzia";
    mapTables["Tipo di pagamento"] = "tipo_pagamento";
    mapTables["Casuale di trasporto"] = "casuale_trasporto";
    mapTables["Vettore"] = "vettore";
    mapTables["Aspetto dei beni"] = "aspetto_beni";


    ui->comboBox->addItems(mapTables.keys());
    ui->comboBox->setCurrentIndex(0);
    changeTable(ui->comboBox->currentText());

    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeTable(QString)));
}

TableSetupDialog::~TableSetupDialog()
{
    delete ui;
}

void TableSetupDialog::changeTable(QString tbname)
{
    setWindowTitle(tbname);
    currentTable = mapTables.value(tbname);
    updateTable();
}

void TableSetupDialog::addRecord(void)
{
    bool ok;
    QString value = QInputDialog::getText(this, "Aggiungi record", "Inserisci il valore:", QLineEdit::Normal, "", &ok);
    if (ok) {
        if (value.isEmpty()) {
            showDialogError(this, ERR001, MSG001); //NOTE codice errore 001
            return;
        }
        QSqlQuery query;
        query.prepare(ADD_QUERY.arg(currentTable));
        query.bindValue(":value", value);
        if (!query.exec()) {
            showDialogError(this, ERR002, MSG002, query.lastError().text()); //NOTE codice errore 002
            return;
        }
        updateTable();
    }
}

void TableSetupDialog::removeRecord(void)
{
    QModelIndex index = ui->tableView->currentIndex();
    QString id = model->index(index.row(), COL_ID).data().toString();
    //Se non viene selezionato niente il valore e' uguale a una stringa vuota
    if (id != "") {
        QSqlQuery query;
        /*C'e' un bug nel driver x postgres, la query deve essere preparata e poi
          eseguita con exec. Se viene eseguita senza prepararla la query viene
          eseguita ma il valore ritornato da exec e' sempre falso e in caso di
          errore chiamando lasterror non viene ritornato l'ultimo errore. Eseguendo
          direttamente lastError senza prima aver usato exec sembra aggirare il
          problema almeno per postgres, non ho provato altri driver*/
        query.prepare(REMOVEQUERY.arg(currentTable));
        query.bindValue(":id", id);
        if (!query.exec()) {
            showDialogError(this, ERR003, MSG003, query.lastError().text()); //NOTE codice errore 003
            return;
        }
        updateTable();
    }
    else {
        showDialogError(this, ERR004, MSG004); //NOTE codice errore 004
    }
}

void TableSetupDialog::updateRecord(void)
{
    QModelIndex index = ui->tableView->currentIndex();
    QString id = model->index(index.row(), COL_ID).data().toString();
    QString old_value = model->index(index.row(), COL_DESCR).data().toString();
    if (id != "") {
        bool ok;
        QString value = QInputDialog::getText(this, "Modifica Record", "Modifica il valore:", QLineEdit::Normal,  old_value, &ok);
        if (ok) {
            if (!value.isEmpty()) {
                QSqlQuery query;
                query.prepare(UPDATE_QUERY.arg(currentTable));
                query.bindValue(":id", id);
                query.bindValue(":value", value);
                if (!query.exec()) {
                    showDialogError(this, ERR005, MSG005, query.lastError().text()); //NOTE codice errore 005
                    return;
                }
                updateTable();
            }
            else {
                showDialogError(this, ERR006, MSG006); //NOTE codice errore 006
                return;
            }
        }

    }
    else {
        showDialogError(this, ERR007, MSG007); //NOTE codice errore 007
    }
}

void TableSetupDialog::updateTable(void)
{
    QString query = SELECT_QUERY.arg(currentTable);
    model->setQuery(query);
    model->setHeaderData(COL_DESCR, Qt::Horizontal, "Descrizione");
    ui->tableView->hideColumn(COL_ID);
}
