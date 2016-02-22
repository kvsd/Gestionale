#include "moduleAnagrafica/anagraficawindow.h"
#include "ui_anagraficawindow.h"
#include "custommodel.h"

AnagraficaWindow::AnagraficaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnagraficaWindow)
{
    qDebug() << "AnagraficaWindow()";
    ui->setupUi(this);

    initModel();
    updateModel();
    initComboBox();
    this->move(parent->pos());
    loadConfigSettings();
}

AnagraficaWindow::~AnagraficaWindow()
{
    qDebug() << "~AnagraficaWindow()";
    delete ui;
}

void AnagraficaWindow::initModel()
{
    //Configura i model che verrano usati nei combobox (pannello dei filtri)
    qDebug() << "AnagraficaWindow::initModel()";
    anagraficaModel = new CustomModel(anagrafica::ANGRFC_COLORS, Qt::AlignLeft, this);
    ui->anagraficaView->setModel(anagraficaModel);

    cittaModel = new QSqlTableModel(this);
    cittaModel->setTable(table::CITTA);
    //cittaModel->select();

    provinciaModel = new QSqlTableModel(this);
    provinciaModel->setTable(table::PROVINCIA);
    //provinciaModel->select();

    statoModel  = new QSqlTableModel(this);
    statoModel->setTable(table::STATO);
    //statoModel->select();

    agenteModel = new QSqlTableModel(this);
    agenteModel->setTable(table::AGENTI);
    //agenteModel->select();
}

void AnagraficaWindow::updateModel()
{
    cittaModel->select();
    provinciaModel->select();
    statoModel->select();
    agenteModel->select();
}

void AnagraficaWindow::initComboBox()
{
    //Assegna i model ai combobox(filtri) e imposta le colonne da visualizzare.
    qDebug() << "AnagraficaWindow::initComboBox()";

    ui->cittaComboBox->setModel(cittaModel);
    ui->cittaComboBox->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->provinciaComboBox->setModel(provinciaModel);
    ui->provinciaComboBox->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->statoComboBox->setModel(statoModel);
    ui->statoComboBox->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->agenteComboBox->setModel(agenteModel);
    ui->agenteComboBox->setModelColumn(anagrafica::COL_TABLE_COGNOME);
}

void AnagraficaWindow::loadConfigSettings()
{
    qDebug() << "AnagraficaWindow::loadConfigSettings()";
    this->setGeometry(settings.value(anagrafica::GEOMETRY, anagrafica::DEFAULT_GEOMETRY).toRect());
    ui->splitter_filtri->restoreState(settings.value(anagrafica::SPLITTER_FILTRI_STATE).toByteArray());
    ui->splitter_docs->restoreState(settings.value(anagrafica::SPLITTER_DOCS_STATE).toByteArray());
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
    settings.setValue(anagrafica::GEOMETRY, this->geometry());
    settings.setValue(anagrafica::ANGRFC_HEADER, ui->anagraficaView->horizontalHeader()->saveState());
    settings.setValue(anagrafica::SPLITTER_FILTRI_STATE, ui->splitter_filtri->saveState());
    settings.setValue(anagrafica::SPLITTER_DOCS_STATE, ui->splitter_docs->saveState());

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
    updateModel();
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
    QString id = anagraficaModel->record(index.row()).value(anagrafica::COL_ID).toString();
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
    QString id = anagraficaModel->record(index.row()).value(anagrafica::COL_ID).toString();

    QSqlQuery query;
    query.prepare(anagrafica::DELETE_QUERY);
    query.bindValue(anagrafica::PH_ID, id);
    if (!query.exec()) {
        showDialogError(this, ERR028, MSG003, query.lastError().text()); //NOTE codice errore 028
    }
    updateViewAnagrafica();
}

QString AnagraficaWindow::getSearchString()
{
    qDebug() << "AnagraficaWindow::getSearchString()";
    QString value= ui->searchLineEdit->text();
    if (value.isEmpty()) {
        return value;
    }

    QString pattern = "%1 ILIKE '%%2%'";
    QStringList list;
    if (ui->actionRagioneSociale->isChecked())
        list.append(pattern.arg(anagrafica::COL_RAGIONE_SOCIALE));

    if (ui->actionCognome->isChecked())
        //WARNING CONFLITTO con la tabella agenti, campo cognome uguale.
        list.append(pattern.arg("anagrafica."+anagrafica::COL_COGNOME));

    if (ui->actionCodiceFiscale->isChecked())
        list.append(pattern.arg(anagrafica::COL_CODICE_FISCALE));

    if (ui->actionPartitaIVA->isChecked())
        list.append(pattern.arg(anagrafica::COL_PARTITA_IVA));

    return list.join(" OR ").arg(value);

}

QString AnagraficaWindow::getFilterString1()
{
    qDebug() << "AnagraficaWindow::getFilterString1()";
    QStringList filter;
    QString pattern = "%1=%2";
    bool fornitore = ui->fornitoriCheckBox->isChecked();
    bool cliente = ui->clientiCheckBox->isChecked();

    filter.append(pattern.arg(anagrafica::COL_CLIENTE, QVariant(cliente).toString()));
    filter.append(pattern.arg(anagrafica::COL_FORNITORE, QVariant(fornitore).toString()));

    if (fornitore==true && cliente==true) {
        return filter.join(" OR ");
    }
    else if (fornitore==true) {
        return pattern.arg(anagrafica::COL_FORNITORE, QVariant(fornitore).toString());
    }
    else if (cliente==true) {
        return pattern.arg(anagrafica::COL_CLIENTE, QVariant(cliente).toString());
    }
    else
        return filter.join(" AND ");
}

QString AnagraficaWindow::getFilterString2()
{
    qDebug() << "AnagraficaWindow::getFilterString2()";
    QStringList filter;
    QString pattern = "%1=%2";

    if (ui->cittaEnabler->isChecked()) {
        int row = ui->cittaComboBox->currentIndex();
        QString id = cittaModel->record(row).value(anagrafica::COL_TABLE_ID).toString();
        filter.append(pattern.arg(anagrafica::COL_ID_CITTA, id));
    }

    if (ui->provinciaEnabler->isChecked()) {
        int row = ui->provinciaComboBox->currentIndex();
        QString id = provinciaModel->record(row).value(anagrafica::COL_TABLE_ID).toString();
        filter.append(pattern.arg(anagrafica::COL_ID_PROVINCIA, id));
    }

    if (ui->statoEnabler->isChecked()) {
        int row = ui->statoComboBox->currentIndex();
        QString id = statoModel->record(row).value(anagrafica::COL_TABLE_ID).toString();
        filter.append(pattern.arg(anagrafica::COL_ID_STATO, id));
    }

    if (ui->agenteEnabler->isChecked()) {
        int row = ui->agenteComboBox->currentIndex();
        QString id = agenteModel->record(row).value(anagrafica::COL_TABLE_ID).toString();
        filter.append(pattern.arg(anagrafica::COL_ID_AGENTE, id));
    }

    return filter.join(" AND ");
}

void AnagraficaWindow::updateViewAnagrafica(void)
{
    qDebug() << "AnagraficaWindow::updateViewAnagrafica()";

    QString filter1 = getSearchString();
    QString filter2 = getFilterString1();
    QString filter3 = getFilterString2();

    QStringList test;
    test.append(anagrafica::SELECT_ALL);
    if (!filter1.isEmpty())
        test.append("("+filter1+")");
    if (!filter2.isEmpty())
        test.append("("+filter2+")");
    if (!filter3.isEmpty())
        test.append("("+filter3+")");

    QString query = test.join(" AND ");
    query.append(anagrafica::ORDER_CLAUSE);

    anagraficaModel->setQuery(query);
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
