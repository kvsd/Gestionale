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
    updateModel();

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
    //Configura il model che verrano usati in anagraficaView
    qDebug() << "AnagraficaWindow::initModel()";
    m_anagraficaModel = new CustomModel(Qt::AlignLeft, this);
    ui->anagraficaView->setModel(m_anagraficaModel);
}

void AnagraficaWindow::updateModel()
{
    qDebug() << "AnagraficaWindow::updateModel()";

    QString cittaText = ui->cittaComboBox->currentText();
    QString provinciaText = ui->provinciaComboBox->currentText();
    QString statoText = ui->statoComboBox->currentText();
    QString agenteText = ui->agenteComboBox->currentText();

    m_cittaModel->select();
    m_provinciaModel->select();
    m_statoModel->select();
    m_agenteModel->select();

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
    //Inizializza i model e i QComboBox utilizzati per i filtri.
    qDebug() << "AnagraficaWindow::initComboBox()";

    m_cittaModel = setupComboBox(table::CITTA, ui->cittaComboBox, int(anagrafica::cols::descr));
    m_provinciaModel = setupComboBox(table::PROVINCIA, ui->provinciaComboBox, int(anagrafica::cols::descr));
    m_statoModel = setupComboBox(table::STATO, ui->statoComboBox, int(anagrafica::cols::descr));
    m_agenteModel = setupComboBox(table::AGENTI, ui->agenteComboBox, int(anagrafica::cols::cognome));
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
    m_anagraficaModel->setBgMap(getBgSettings(anagrafica::ANGRFC_COLORS));

    //Carico le impostazioni del menu ricerca
    ui->actionDenominazione->setChecked(m_settings.value(anagrafica::SEARCH_DENOM, true).toBool());
    ui->actionCognome->setChecked(m_settings.value(anagrafica::SEARCH_COGNOME, false).toBool());
    ui->actionCodiceFiscale->setChecked(m_settings.value(anagrafica::SEARCH_CODFISC, false).toBool());
    ui->actionPartitaIVA->setChecked(m_settings.value(anagrafica::SEARCH_PIVA, false).toBool());
}

void AnagraficaWindow::saveConfigSettings()
{
    qDebug() << "AnagraficaWindow::saveConfigSettings()";
    saveWindowGeometry();
    saveSplittersState();
    saveTableViewSettings();

    //Salvo le impostazioni del menu ricerca
    m_settings.setValue(anagrafica::SEARCH_DENOM, ui->actionDenominazione->isChecked());
    m_settings.setValue(anagrafica::SEARCH_COGNOME, ui->actionCognome->isChecked());
    m_settings.setValue(anagrafica::SEARCH_CODFISC, ui->actionCodiceFiscale->isChecked());
    m_settings.setValue(anagrafica::SEARCH_PIVA, ui->actionPartitaIVA->isChecked());
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
    QString id = m_anagraficaModel->record(index.row()).value(coldb::ID).toString();
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
    QString id = m_anagraficaModel->record(index.row()).value(coldb::ID).toString();

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
    if (ui->actionDenominazione->isChecked())
        list.append(pattern.arg(coldb::DENOMINAZIONE));

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

    bool azienda = ui->aziendaCKB->isChecked();
    bool cliente = ui->clientiCKB->isChecked();
    bool fornitore = ui->fornitoriCKB->isChecked();
    bool pa = ui->paCKB->isChecked();

    if (azienda)
        filter.append(pattern.arg(coldb::AZIENDA, QVariant(azienda).toString()));
    if (cliente)
        filter.append(pattern.arg(coldb::CLIENTE, QVariant(cliente).toString()));
    if (fornitore)
        filter.append(pattern.arg(coldb::FORNITORE, QVariant(fornitore).toString()));
    if (pa)
        filter.append(pattern.arg(coldb::PA, QVariant(pa).toString()));

    return filter.join(" OR ");
}

QString AnagraficaWindow::getFilterString2()
{
    qDebug() << "AnagraficaWindow::getFilterString2()";
    QStringList filter;
    QString pattern = "%1=%2";

    if (ui->cittaEnabler->isChecked()) {
        int row = ui->cittaComboBox->currentIndex();
        QString id = m_cittaModel->record(row).value(int(anagrafica::cols::id)).toString();
        filter.append(pattern.arg(coldb::ID_CITTA, id));
    }

    if (ui->provinciaEnabler->isChecked()) {
        int row = ui->provinciaComboBox->currentIndex();
        QString id = m_provinciaModel->record(row).value(int(anagrafica::cols::id)).toString();
        filter.append(pattern.arg(coldb::ID_PROVINCIA, id));
    }

    if (ui->statoEnabler->isChecked()) {
        int row = ui->statoComboBox->currentIndex();
        QString id = m_statoModel->record(row).value(int(anagrafica::cols::id)).toString();
        filter.append(pattern.arg(coldb::ID_STATO, id));
    }

    if (ui->agenteEnabler->isChecked()) {
        int row = ui->agenteComboBox->currentIndex();
        QString id = m_agenteModel->record(row).value(int(anagrafica::cols::id)).toString();
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
    if (filter2.isEmpty())
        //Se il selettore per tipo anagrafica non e' selezionato
        //non mostro risultati
        query.append(" LIMIT 0");
    m_anagraficaModel->setQuery(query);
    ui->anagraficaView->resizeColumnsToContents();
    ui->anagraficaView->horizontalHeader()->setStretchLastSection(true);
}

void AnagraficaWindow::openConfigDialog(void)
{
    qDebug() << "AnagraficaWindow::openConfigDialog()";
    saveConfigSettings();
    OptionsAnagraficaDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok)
        return;

    loadConfigSettings();
}
