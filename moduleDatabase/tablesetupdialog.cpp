#include "tablesetupdialog.h"
#include "ui_tablesetupdialog.h"

const QString ADD_QUERY = "INSERT INTO %1(descr) VALUES(:value)";
const QString REMOVEQUERY = "DELETE FROM %1 WHERE id=:id";
const QString UPDATE_QUERY = "UPDATE %1 SET descr=:value WHERE id=:id";
const QString SELECT_QUERY = "SELECT id,descr AS Valori FROM %1 WHERE id>0 ORDER BY descr";

TableSetupDialog::TableSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableSetupDialog)
{
    qDebug() << "TableSetupDialog()";
    ui->setupUi(this);
    m_model = new QSqlQueryModel(this);
    ui->tableView->setModel(m_model);

    /*Questo dialog gestisce tabelle con due colonne:
        id -> Serial
        descr -> TEXT UNIQUE NOT NULL
      Per aggiunge tabelle basta inserirle in mapTables*/

    m_mapTables["Categoria merceologica"] = table::CATEGORIA_MERCE;
    m_mapTables["Codice Iva"] = table::CODICE_IVA;
    m_mapTables["Unita di misura"] = table::UNITA_MISURA;
    m_mapTables["Sedi magazzino"] = table::SEDE_MAGAZZINO;
    m_mapTables["Marca"] = table::MARCA;
    m_mapTables["Citta"] = table::CITTA;
    m_mapTables["CAP"] = table::CAP;
    //mapTables["Stato"] = table::STATO;
    m_mapTables["Banca"] = table::BANCA;
    m_mapTables["Agenzia"] = table::AGENZIA;
    //m_mapTables["Tipo di pagamento"] = table::TIPO_PAGAMENTO;
    m_mapTables["Casuale di trasporto"] = table::CASUALE_TRASPORTO;
    m_mapTables["Vettore"] = table::VETTORE;
    m_mapTables["Aspetto dei beni"] = table::ASPETTO_BENI;

    m_tableModel = new QStringListModel(m_mapTables.keys(), this);
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
    m_currentTable = m_mapTables.value(tbname);
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
        query.prepare(ADD_QUERY.arg(m_currentTable));
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
    QString id = m_model->index(index.row(), ID).data().toString();
    //Se non viene selezionato niente il valore e' uguale a una stringa vuota
    if (id != "") {
        QSqlQuery query;
        query.prepare(REMOVEQUERY.arg(m_currentTable));
        query.bindValue(":id", id);
        if (!query.exec()) {
            showDialogError(this, ERR003, MSG003, query.lastError().text()); //NOTE codice errore 003
            return;
        }
        updateView();
    }
    else
        showDialogError(this, ERR004, MSG004); //NOTE codice errore 004
}

void TableSetupDialog::updateRecord(void)
{
    qDebug() << "TableSetupDialog::updateRecord()";
    QModelIndex index = ui->tableView->currentIndex();
    QString id = m_model->index(index.row(), ID).data().toString();
    QString old_value = m_model->index(index.row(), DESCR).data().toString();
    if (id != "") {
        bool ok;
        QString value = QInputDialog::getText(this, "Modifica Record", "Modifica il valore:", QLineEdit::Normal,  old_value, &ok);
        if (ok) {
            if (!value.isEmpty()) {
                QSqlQuery query;
                query.prepare(UPDATE_QUERY.arg(m_currentTable));
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
    else
        showDialogError(this, ERR007, MSG007); //NOTE codice errore 007
}

void TableSetupDialog::updateView(void)
{
    qDebug() << "TableSetupDialog::updateView()";
    QString query = SELECT_QUERY.arg(m_currentTable);
    m_model->setQuery(query);
    m_model->setHeaderData(DESCR, Qt::Horizontal, "Descrizione");
    ui->tableView->hideColumn(ID);
}
