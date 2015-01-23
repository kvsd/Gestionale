#include "moduleAnagrafica/anagraficawindow.h"
#include "ui_anagraficawindow.h"
#include "custommodel.h"

AnagraficaWindow::AnagraficaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnagraficaWindow)
{
    qDebug() << "AnagraficaWindow()";
    ui->setupUi(this);

    anagraficaModel = new CustomModel(anagrafica::ANGRFC_COLORS);
    ui->anagraficaView->setModel(anagraficaModel);

    this->move(parent->pos());

    str_search = " AND \"Ragione sociale\" ILIKE '\%%1\%'";

    //ui->docView->setShown(false);
    ui->docView->hide();

    loadConfigSettings();
}

AnagraficaWindow::~AnagraficaWindow()
{
    qDebug() << "~AnagraficaWindow()";
    delete ui;
}

void AnagraficaWindow::loadConfigSettings()
{
    qDebug() << "AnagraficaWindow::loadConfigSettings()";
    this->setGeometry(settings.value(anagrafica::ANGRFC_SIZE, anagrafica::DEFAULT_SIZE).toRect());

    //Carica la disposizione delle colonne. Il ripristino dello stato delle colonne
    //salva anche lo stato delle colonne (mostra/nascondi), quindi bisogna caricarle
    //prima di leggere lo stato mostra nascondi.
    //ui->anagraficaView->horizontalHeader()->setMovable(true);
    ui->anagraficaView->horizontalHeader()->setSectionsMovable(true);
    if (settings.contains(anagrafica::ANGRFC_HEADER)) {
        QByteArray array = settings.value(anagrafica::ANGRFC_HEADER).toByteArray();
        ui->anagraficaView->horizontalHeader()->restoreState(array);
    }

    //legge il file file di configurazione e in base al valore
    //mostra o nasconde le colonne
    settings.beginGroup(anagrafica::ANGRFC_STATUS);
    QStringList cols = settings.allKeys();
    if (!cols.isEmpty()) {
        for (QStringList::Iterator i=cols.begin(); i!=cols.end(); i++) {
            int col = QVariant((*i)).toInt();
            bool value = settings.value((*i)).toBool();
            ui->anagraficaView->setColumnHidden(col, !value);
        }
    }
    settings.endGroup();

    //imposta i colori delle colonne, questo viene fatto dal model
    //e non dalla view. MISTERI DI QT
    anagraficaModel->loadSettings();

    //Carico le impostazioni del menu ricerca
    ui->actionRagioneSociale->setChecked(settings.value(anagrafica::SEARCH_RAGSOCL, true).toBool());
    ui->actionCognome->setChecked(settings.value(anagrafica::SEARCH_COGNOME, false).toBool());
    ui->actionCodiceFiscale->setChecked(settings.value(anagrafica::SEARCH_CODFISC, false).toBool());
    ui->actionPartitaIVA->setChecked(settings.value(anagrafica::SEARCH_PIVA, false).toBool());
}

void AnagraficaWindow::saveConfigSettings()
{
    qDebug() << "AnagraficaWindow::saveConfigSettings()";
    settings.setValue(anagrafica::ANGRFC_SIZE, this->geometry());
    settings.setValue(anagrafica::ANGRFC_HEADER, ui->anagraficaView->horizontalHeader()->saveState());
    //Salvo le impostazioni del menu ricerca
    settings.setValue(anagrafica::SEARCH_RAGSOCL, ui->actionRagioneSociale->isChecked());
    settings.setValue(anagrafica::SEARCH_COGNOME, ui->actionCognome->isChecked());
    settings.setValue(anagrafica::SEARCH_CODFISC, ui->actionCodiceFiscale->isChecked());
    settings.setValue(anagrafica::SEARCH_PIVA, ui->actionPartitaIVA->isChecked());
}

void AnagraficaWindow::showEvent(QShowEvent *event)
{
    qDebug() << "AnagraficaWindow::showEvent()";
    updateViewAnagrafica();
    event->accept();
}

void AnagraficaWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "AnagraficaWindow::closeEvent()";
    this->parentWidget()->show();
    saveConfigSettings();
    event->accept();
}

void AnagraficaWindow::addRecord(void)
{
    qDebug() << "AnagraficaWindow::addRecord()";
    AnagraficaAddDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    updateViewAnagrafica();
}

void AnagraficaWindow::updateRecord(void)
{
    qDebug() << "AnagraficaWindow::updateRecord()";
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

void AnagraficaWindow::removeRecord(void)
{
    qDebug() << "AnagraficaWindow::removeRecord()";
    QModelIndex index = ui-> anagraficaView->currentIndex();
    if (!index.isValid()) {
        showDialogError(this, ERR027, MSG004, ""); //NOTE codice errore 027
        return;
    }
    QString id = anagraficaModel->index(index.row(), anagrafica::COL_ID).data().toString();

    QSqlQuery query;
    query.prepare(anagrafica::DELETE_QUERY);
    query.bindValue(anagrafica::PH_ID, id);
    if (!query.exec()) {
        showDialogError(this, ERR028, MSG003, query.lastError().text()); //NOTE codice errore 028
    }
    updateViewAnagrafica();
}

void AnagraficaWindow::searchRecord(void)
{
    qDebug() << "AnagraficaWindow::searchRecord()";
    QString s = ui->searchLineEdit->text();

    if (s.isEmpty()) {
        updateViewAnagrafica();
        return;
    }

    QString query;
    if (ui->clientiCheckBox->isChecked() && ui->fornitoriCheckBox->isChecked()) {
        query.append(anagrafica::SELECT_ALL);
    }
    else if (ui->clientiCheckBox->isChecked()) {
        query.append(anagrafica::SELECT_CLNT);
    }
    else if (ui->fornitoriCheckBox->isChecked()) {
        query.append(anagrafica::SELECT_FORN);
    }
    else {
        return;
    }

    query.append(str_search);
    anagraficaModel->setQuery(query.arg(s));
}

void AnagraficaWindow::updateViewAnagrafica(void)
{
    qDebug() << "AnagraficaWindow::updateViewAnagrafica()";
    ui->searchLineEdit->clear();

    if (ui->clientiCheckBox->isChecked() && ui->fornitoriCheckBox->isChecked()) {
        anagraficaModel->setQuery(anagrafica::SELECT_ALL);
    }
    else if (ui->clientiCheckBox->isChecked()) {
        anagraficaModel->setQuery(anagrafica::SELECT_CLNT);
    }
    else if (ui->fornitoriCheckBox->isChecked()) {
        anagraficaModel->setQuery(anagrafica::SELECT_FORN);
    }
    else {
        anagraficaModel->setQuery("");
    }

    ui->anagraficaView->resizeColumnsToContents();
    ui->anagraficaView->horizontalHeader()->setStretchLastSection(true);
}

void AnagraficaWindow::openConfigDialog(void)
{
    qDebug() << "AnagraficaWindow::openConfigDialog()";
    OptionsAnagraficaDialog dlg(anagraficaModel, this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }

    loadConfigSettings();
}

void AnagraficaWindow::updateStringSearch(void)
{
    qDebug() << "AnagraficaWindow::updateStringSearch()";
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
}
