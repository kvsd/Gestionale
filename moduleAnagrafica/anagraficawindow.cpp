#include "moduleAnagrafica/anagraficawindow.h"
#include "ui_anagraficawindow.h"
#include "custommodel.h"

const QString SELECT_ALL = "SELECT * FROM vw_anagrafica WHERE \"Id\">0";
const QString SELECT_CLNT = "SELECT * FROM vw_anagrafica_clienti WHERE \"Id\">0";
const QString SELECT_FORN = "SELECT * FROM vw_anagrafica_fornitori WHERE \"Id\">0";
const QString DELETE_QUERY = "DELETE FROM anagrafica WHERE id = :id";

anagraficaWindow::anagraficaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::anagraficaWindow)
{
    ui->setupUi(this);

    this->move(parent->pos());
    anagraficaModel = new CustomModel("AnagraficaColsColors");
    ui->anagraficaView->setModel(anagraficaModel);

    updateViewAnagrafica();

    str_search = " AND \"Ragione sociale\" ILIKE '\%%1\%'";

    ui->docView->setShown(false);
    this->setGeometry(settings.value("AnagraficaWindow.size", QRect(0, 0, 700, 500)).toRect());
    loadConfigSettings();
}

anagraficaWindow::~anagraficaWindow()
{
    delete ui;
}

void anagraficaWindow::loadConfigSettings()
{
    //legge il file file di configurazione e in base al valore
    //mostra o nasconde le colonne
    settings.beginGroup("AnagraficaColsStatus");
    QStringList cols = settings.allKeys();
    if (cols.isEmpty()) {
        return;
    }
    for (QStringList::Iterator i=cols.begin(); i!=cols.end(); i++) {
        int col = QVariant((*i)).toInt();
        bool value = settings.value((*i)).toBool();
        ui->anagraficaView->setColumnHidden(col, !value);

    }
    settings.endGroup();

    //imposta i colori delle colonne, questo viene fatto dal model
    //e non dalla view. MISTERI DI QT
    anagraficaModel->loadSettings();
}

void anagraficaWindow::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->show();
    settings.setValue("AnagraficaWindow.size", this->geometry());
    event->accept();
}

void anagraficaWindow::addRecord(void)
{
    AnagraficaAddDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    updateViewAnagrafica();
}

void anagraficaWindow::updateRecord(void)
{
    QModelIndex index = ui->anagraficaView->currentIndex();
    if (!index.isValid()) {
        showDialogError(this, ERR026, MSG007, ""); //NOTE codice errore 026
        return;
    }
    QString id = anagraficaModel->index(index.row(), anagrafica::COL_ID).data().toString();
    AnagraficaAddDialog dlg(this);
    dlg.setValue(id);
    dlg.setWindowTitle("Modifica Cliente Fornitore");
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    updateViewAnagrafica();
}

void anagraficaWindow::removeRecord(void)
{
    QModelIndex index = ui-> anagraficaView->currentIndex();
    if (!index.isValid()) {
        showDialogError(this, ERR027, MSG004, ""); //NOTE codice errore 027
        return;
    }
    QString id = anagraficaModel->index(index.row(), anagrafica::COL_ID).data().toString();

    QSqlQuery query;
    query.prepare(DELETE_QUERY);
    query.bindValue(":id", id);
    if (!query.exec()) {
        showDialogError(this, ERR028, MSG003, query.lastError().text()); //NOTE codice errore 028
    }
    updateViewAnagrafica();
}

void anagraficaWindow::searchRecord(void)
{
    QString s = ui->searchLineEdit->text();

    if (s.isEmpty()) {
        updateViewAnagrafica();
        return;
    }

    QString query;
    if (ui->clientiCheckBox->isChecked() && ui->fornitoriCheckBox->isChecked()) {
        query.append(SELECT_ALL);
    }
    else if (ui->clientiCheckBox->isChecked()) {
        query.append(SELECT_CLNT);
    }
    else if (ui->fornitoriCheckBox->isChecked()) {
        query.append(SELECT_FORN);
    }
    else {
        return;
    }

    query.append(str_search);
    anagraficaModel->setQuery(query.arg(s));
}

void anagraficaWindow::updateViewAnagrafica(void)
{
    ui->searchLineEdit->clear();

    if (ui->clientiCheckBox->isChecked() && ui->fornitoriCheckBox->isChecked()) {
        anagraficaModel->setQuery(SELECT_ALL);
    }
    else if (ui->clientiCheckBox->isChecked()) {
        anagraficaModel->setQuery(SELECT_CLNT);
    }
    else if (ui->fornitoriCheckBox->isChecked()) {
        anagraficaModel->setQuery(SELECT_FORN);
    }
    else {
        anagraficaModel->setQuery("");
    }

    ui->anagraficaView->hideColumn(anagrafica::COL_ID); //FIXME se nelle impostazioni viene specificato di visualizzare l'id questo lo
                                                        //scavalca. Possibile soluzione è impostare al primo avvio un file di configurazione
                                                        //preimpostato. Poi sara' l'utente a decidere cosa visualizzare
    ui->anagraficaView->resizeColumnsToContents();
    ui->anagraficaView->horizontalHeader()->setStretchLastSection(true);
}

void anagraficaWindow::openConfigDialog(void)
{
    OptionsAnagraficaDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }

    loadConfigSettings();
}

void anagraficaWindow::modifyStringSearch(void)
{
    if (!ui->actionRagioneSociale->isChecked() && !ui->actionCognome->isChecked() &&
        !ui->actionPartitaIVA->isChecked() && !ui->actionCodiceFiscale->isChecked()) {
        //Niente selezionato Ragione sociale di default;
        str_search = " WHERE \"Ragione sociale\" ILIKE '\%%1\%'";
        ui->actionRagioneSociale->setChecked(true);
    }
    else {
        QStringList test;
        if (ui->actionRagioneSociale->isChecked()) {
            test.append(QString("\"Ragione sociale\" ILIKE '\%%1\%'"));
        }

        if (ui->actionCognome->isChecked()) {
            test.append(QString("\"Cognome\" ILIKE '\%%1\%'"));
        }

        if (ui->actionCodiceFiscale->isChecked()) {
            test.append(QString("\"Codice fiscale\" ILIKE '\%%1\%'"));
        }

        if (ui->actionPartitaIVA->isChecked()) {
            test.append(QString("\"Partita Iva\" ILIKE '\%%1\%'"));
        }

        str_search = " WHERE " + test.join(" OR ");
    }
    //TODO salvare le impostazioni di ricerca nei settaggi;
}
