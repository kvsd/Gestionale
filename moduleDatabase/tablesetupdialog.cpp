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
    qDebug() << "TableSetupDialog()";
    ui->setupUi(this);
    model = new QSqlQueryModel(this);
    ui->tableView->setModel(model);

    /*Questo dialog gestisce tabelle con due colonne:
        id -> Serial
        descr -> TEXT UNIQUE NOT NULL
      Per aggiunge tabelle basta inserirle in mapTables*/

    mapTables["Categoria merceologica"] = table::CATEGORIA_MERCE;
    mapTables["Codice Iva"] = table::CODICE_IVA;
    mapTables["Unita di misura"] = table::UNITA_MISURA;
    mapTables["Sedi magazzino"] = table::SEDE_MAGAZZINO;
    mapTables["Marca"] = table::MARCA;
    mapTables["Tipo di ditta"] = table::TIPO_DITTA;
    mapTables["Citta"] = table::CITTA;
    mapTables["Provincia"] = table::PROVINCIA;
    mapTables["CAP"] = table::CAP;
    mapTables["Stato"] = table::STATO;
    mapTables["Banca"] = table::BANCA;
    mapTables["Agenzia"] = table::AGENZIA;
    mapTables["Tipo di pagamento"] = table::TIPO_PAGAMENTO;
    mapTables["Casuale di trasporto"] = table::CASUALE_TRASPORTO;
    mapTables["Vettore"] = table::VETTORE;
    mapTables["Aspetto dei beni"] = table::ASPETTO_BENI;

    m_tableModel = new QStringListModel(mapTables.keys(), this);
    m_tableModel->sort(0);
    ui->comboBox->setModel(m_tableModel);
    changeTable(ui->comboBox->currentText());

    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeTable(QString)));
}

TableSetupDialog::~TableSetupDialog()
{
    qDebug() << "~TableSetupDialog()";
    delete ui;
}

void TableSetupDialog::changeTable(QString tbname)
{
    qDebug() << "TableSetupDialog::changeTable()";
    setWindowTitle(tbname);
    currentTable = mapTables.value(tbname);
    updateView();
}

void TableSetupDialog::addRecord(void)
{
    qDebug() << "TableSetupDialog::addRecord()";
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
        updateView();
    }
}

void TableSetupDialog::removeRecord(void)
{
    qDebug() << "TableSetupDialog::removeRecord()";
    QModelIndex index = ui->tableView->currentIndex();
    QString id = model->index(index.row(), COL_ID).data().toString();
    //Se non viene selezionato niente il valore e' uguale a una stringa vuota
    if (id != "") {
        QSqlQuery query;
        query.prepare(REMOVEQUERY.arg(currentTable));
        query.bindValue(":id", id);
        if (!query.exec()) {
            showDialogError(this, ERR003, MSG003, query.lastError().text()); //NOTE codice errore 003
            return;
        }
        updateView();
    }
    else {
        showDialogError(this, ERR004, MSG004); //NOTE codice errore 004
    }
}

void TableSetupDialog::updateRecord(void)
{
    qDebug() << "TableSetupDialog::updateRecord()";
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
                updateView();
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

void TableSetupDialog::updateView(void)
{
    qDebug() << "TableSetupDialog::updateView()";
    QString query = SELECT_QUERY.arg(currentTable);
    model->setQuery(query);
    model->setHeaderData(COL_DESCR, Qt::Horizontal, "Descrizione");
    ui->tableView->hideColumn(COL_ID);
}
