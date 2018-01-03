#include "moduleAnagrafica/anagraficawindow.h"
#include "ui_anagraficawindow.h"
#include "custommodel.h"

AnagraficaWindow::AnagraficaWindow(QWidget *parent) :
    CustomWindow(parent),
    ui(new Ui::AnagraficaWindow)
{
    qDebug() << "AnagraficaWindow()";
    ui->setupUi(this);

    initModel();
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
    anagraficaModel = new CustomModel(Qt::AlignLeft, this);
    ui->anagraficaView->setModel(anagraficaModel);

    cittaModel = new QSqlTableModel(this);
    cittaModel->setTable(table::CITTA);

    provinciaModel = new QSqlTableModel(this);
    provinciaModel->setTable(table::PROVINCIA);

    statoModel  = new QSqlTableModel(this);
    statoModel->setTable(table::STATO);

    agenteModel = new QSqlTableModel(this);
    agenteModel->setTable(table::AGENTI);
    agenteModel->setSort(2, Qt::AscendingOrder);

    updateModel();
}

void AnagraficaWindow::updateModel()
{
    qDebug() << "AnagraficaWindow::updateModel()";

    QString cittaText = ui->cittaComboBox->currentText();
    QString provinciaText = ui->provinciaComboBox->currentText();
    QString statoText = ui->statoComboBox->currentText();
    QString agenteText = ui->agenteComboBox->currentText();

    cittaModel->select();
    provinciaModel->select();
    statoModel->select();
    agenteModel->select();

    if (cittaText.isEmpty() || provinciaText.isEmpty() ||
            statoText.isEmpty() || agenteText.isEmpty())
        return;

    ui->cittaComboBox->setCurrentText(cittaText);
    ui->provinciaComboBox->setCurrentText(provinciaText);
    ui->statoComboBox->setCurrentText(statoText);
    ui->agenteComboBox->setCurrentText(agenteText);
}

void AnagraficaWindow::initComboBox()
{
    //Assegna i model ai combobox(filtri) e imposta le colonne da visualizzare.
    qDebug() << "AnagraficaWindow::initComboBox()";

    ui->cittaComboBox->setModel(cittaModel);
    ui->cittaComboBox->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cittaComboBox->setCurrentIndex(0);

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
    loadWindowGeometry();
    loadSplittersState();
    loadTableViewSettings();

    //legge il file file di configurazione e in base al valore
    //mostra o nasconde le colonne
    loadColumnVisibility(ui->anagraficaView, anagrafica::ANGRFC_STATUS);

    //imposta i colori delle colonne, questo viene fatto dal model
    //e non dalla view. MISTERI DI QT
    anagraficaModel->setBgMap(getBgSettings(anagrafica::ANGRFC_COLORS));

    //Carico le impostazioni del menu ricerca
    ui->actionRagioneSociale->setChecked(settings.value(anagrafica::SEARCH_RAGSOCL, true).toBool());
    ui->actionCognome->setChecked(settings.value(anagrafica::SEARCH_COGNOME, false).toBool());
    ui->actionCodiceFiscale->setChecked(settings.value(anagrafica::SEARCH_CODFISC, false).toBool());
    ui->actionPartitaIVA->setChecked(settings.value(anagrafica::SEARCH_PIVA, false).toBool());
}

void AnagraficaWindow::saveConfigSettings()
{
    qDebug() << "AnagraficaWindow::saveConfigSettings()";
    saveWindowGeometry();
    saveSplittersState();
    saveTableViewSettings();

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
    updateModel();
}

void AnagraficaWindow::updateRecord(void)
{
    qDebug() << "AnagraficaWindow::updateRecord()";
    QModelIndex index = ui->anagraficaView->currentIndex();
    if (!index.isValid()) {
        showDialogError(this, ERR026, MSG007, ""); //NOTE codice errore 026
        return;
    }
    QString id = anagraficaModel->record(index.row()).value(coldb::ID).toString();
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
    QString id = anagraficaModel->record(index.row()).value(coldb::ID).toString();

    QSqlQuery query;
    query.prepare(anagrafica::DELETE_QUERY);
    query.bindValue(ph::ID, id);
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
        list.append(pattern.arg(coldb::RAGIONE_SOCIALE));

    if (ui->actionCognome->isChecked())
        //WARNING CONFLITTO con la tabella agenti, campo cognome uguale.
        list.append(pattern.arg("anagrafica."+coldb::COGNOME));

    if (ui->actionCodiceFiscale->isChecked())
        list.append(pattern.arg(coldb::CODICE_FISCALE));

    if (ui->actionPartitaIVA->isChecked())
        list.append(pattern.arg(coldb::PARTITA_IVA));

    return list.join(" OR ").arg(value);

}

QString AnagraficaWindow::getFilterString1()
{
    qDebug() << "AnagraficaWindow::getFilterString1()";
    QStringList filter;
    QString pattern = "%1=%2";
    bool fornitore = ui->fornitoriCheckBox->isChecked();
    bool cliente = ui->clientiCheckBox->isChecked();

    filter.append(pattern.arg(coldb::CLIENTE, QVariant(cliente).toString()));
    filter.append(pattern.arg(coldb::FORNITORE, QVariant(fornitore).toString()));

    if (fornitore==true && cliente==true) {
        return filter.join(" OR ");
    }
    else if (fornitore==true) {
        return pattern.arg(coldb::FORNITORE, QVariant(fornitore).toString());
    }
    else if (cliente==true) {
        return pattern.arg(coldb::CLIENTE, QVariant(cliente).toString());
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
        filter.append(pattern.arg(coldb::ID_CITTA, id));
    }

    if (ui->provinciaEnabler->isChecked()) {
        int row = ui->provinciaComboBox->currentIndex();
        QString id = provinciaModel->record(row).value(anagrafica::COL_TABLE_ID).toString();
        filter.append(pattern.arg(coldb::ID_PROVINCIA, id));
    }

    if (ui->statoEnabler->isChecked()) {
        int row = ui->statoComboBox->currentIndex();
        QString id = statoModel->record(row).value(anagrafica::COL_TABLE_ID).toString();
        filter.append(pattern.arg(coldb::ID_STATO, id));
    }

    if (ui->agenteEnabler->isChecked()) {
        int row = ui->agenteComboBox->currentIndex();
        QString id = agenteModel->record(row).value(anagrafica::COL_TABLE_ID).toString();
        filter.append(pattern.arg(coldb::ID_AGENTE, id));
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
    saveConfigSettings();
    OptionsAnagraficaDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }

    loadConfigSettings();
}
