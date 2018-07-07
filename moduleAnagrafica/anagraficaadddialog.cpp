#include "moduleAnagrafica/anagraficaadddialog.h"
#include "ui_anagraficaadddialog.h"

AnagraficaAddDialog::AnagraficaAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnagraficaAddDialog)
{
    qDebug() << "AnagraficaAddDialog()";
    ui->setupUi(this); 

    initModel();
    initComboBox();

    ui->agenteLB->hide();
    ui->agentiDlgPB->hide();
}

AnagraficaAddDialog::~AnagraficaAddDialog()
{
    qDebug() << "~AnagraficaAddDialog()";
    delete ui;
}

void AnagraficaAddDialog::setValue(QString id)
{
    //Recupera il record con l'id passato e assegna tutti i valori
    //ai widget corrispondenti. Chiamato subito dopo la creazione del
    //dialog per aggiornare il record.
    qDebug() << "AnagraficaAddDialog::setValue()";
    QSqlQuery query;
    query.prepare(anagrafica::SELECT_FROM_ID);
    query.bindValue(ph::ID, id);
    query.exec();
    query.first();

    ui->ragSocialeLE->setText(query.value(coldb::RAGIONE_SOCIALE).toString());
    ui->clienteCKB->setChecked(query.value(coldb::CLIENTE).toBool());
    ui->fornitoreCKB->setChecked(query.value(coldb::FORNITORE).toBool());
    if (ui->fornitoreCKB->isChecked()) {
        ui->agenteLB->show();
        ui->agenteCB->show();
    }

    ui->tipoDittaCB->setModelColumn(anagrafica::COL_TABLE_ID);
    int index = ui->tipoDittaCB->findText(query.value(coldb::ID_TIPO_DITTA).toString());
    ui->tipoDittaCB->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->tipoDittaCB->setCurrentIndex(index);

    ui->nomeLE->setText(query.value(coldb::NOME).toString());
    ui->cognomeLE->setText(query.value(coldb::COGNOME).toString());
    ui->pivaLE->setText(query.value(coldb::PARTITA_IVA).toString());
    ui->codFiscaleLE->setText(query.value(coldb::CODICE_FISCALE).toString());

    ui->agenteCB->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->agenteCB->findText(query.value(coldb::ID_AGENTE).toString());
    ui->agenteCB->setModelColumn(anagrafica::COL_TABLE_COGNOME);
    ui->agenteCB->setCurrentIndex(index);

    ui->indirizzoLE->setText(query.value(coldb::INDIRIZZO).toString());

    ui->cittaCB->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->cittaCB->findText(query.value(coldb::ID_CITTA).toString());
    ui->cittaCB->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cittaCB->setCurrentIndex(index);

    ui->provinciaCB->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->provinciaCB->findText(query.value(coldb::ID_PROVINCIA).toString());
    ui->provinciaCB->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->provinciaCB->setCurrentIndex(index);

    ui->capCB->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->capCB->findText(query.value(coldb::ID_CAP).toString());
    ui->capCB->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->capCB->setCurrentIndex(index);

    ui->statoCB->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->statoCB->findText(query.value(coldb::ID_STATO).toString());
    ui->statoCB->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->statoCB->setCurrentIndex(index);

    ui->telLE->setText(query.value(coldb::TEL).toString());
    ui->celLE->setText(query.value(coldb::CEL).toString());
    ui->faxLE->setText(query.value(coldb::FAX).toString());
    ui->emailLE->setText(query.value(coldb::EMAIL).toString());
    ui->sitoWebLE->setText(query.value(coldb::SITO_WEB).toString());

    ui->bancaLE->setText(query.value(coldb::BANCA).toString());
    ui->agenziaLE->setText(query.value(coldb::AGENZIA).toString());
    ui->contoLE->setText(query.value(coldb::CONTO).toString());
    ui->swiftLE->setText(query.value(coldb::SWIFT).toString());
    ui->ibanLE->setText(query.value(coldb::IBAN).toString());

    ui->destMerceTE->setText(query.value(coldb::DESTINAZIONE_MERCE).toString());
    ui->noteTE->setText(query.value(coldb::NOTE).toString());

    m_mapPersona[ph::ID]=id;
}

void AnagraficaAddDialog::initModel()
{
    qDebug() << "AnagraficaAddDialog::initModel()";
    m_modelDitta = new QSqlTableModel(this);
    m_modelDitta->setTable(table::TIPO_DITTA);
    m_modelDitta->setSort(1, Qt::AscendingOrder);
    m_modelDitta->select();

    m_modelCitta = new QSqlTableModel(this);
    m_modelCitta->setTable(table::CITTA);
    m_modelCitta->setSort(1, Qt::AscendingOrder);
    m_modelCitta->select();

    m_modelProvincia = new QSqlTableModel(this);
    m_modelProvincia->setTable(table::PROVINCIA);
    m_modelProvincia->setSort(1, Qt::AscendingOrder);
    m_modelProvincia->select();

    m_modelCap = new QSqlTableModel(this);
    m_modelCap->setTable(table::CAP);
    m_modelCap->setSort(1, Qt::AscendingOrder);
    m_modelCap->select();

    m_modelStato = new QSqlTableModel(this);
    m_modelStato->setTable(table::STATO);
    m_modelStato->setSort(1, Qt::AscendingOrder);
    m_modelStato->select();

    m_modelAgente = new QSqlTableModel(this);
    m_modelAgente->setTable(table::AGENTI);
    m_modelAgente->setSort(1, Qt::AscendingOrder);
    m_modelAgente->select();
}

void AnagraficaAddDialog::initComboBox()
{
    qDebug() << "AnagraficaAddDialog::initComboBox()";
    ui->tipoDittaCB->setModel(m_modelDitta);
    ui->tipoDittaCB->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->cittaCB->setModel(m_modelCitta);
    ui->cittaCB->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->provinciaCB->setModel(m_modelProvincia);
    ui->provinciaCB->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->capCB->setModel(m_modelCap);
    ui->capCB->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->statoCB->setModel(m_modelStato);
    ui->statoCB->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->agenteCB->setModel(m_modelAgente);
    ui->agenteCB->setModelColumn(anagrafica::COL_TABLE_COGNOME);
    ui->agenteCB->hide();
}

void AnagraficaAddDialog::prepareMap(void)
{
    //Popolo la mappa mapPersona<Qstring,QString> con i valori
    //dei vari widget. Verra usata in seguito nel metodo prepareQuery.
    qDebug() << "AnagraficaAddDialog::prepareMap()";
    m_mapPersona[ph::RAG_SOCIALE] = ui->ragSocialeLE->text();

    int row = ui->tipoDittaCB->currentIndex();
    m_mapPersona[ph::ID_TIPO_DITTA] = m_modelDitta->record(row).value(coldb::ID).toString();

    m_mapPersona[ph::CLIENTE] = ui->clienteCKB->isChecked() ? "y" : "n";
    m_mapPersona[ph::FORNITORE] = ui->fornitoreCKB->isChecked() ? "y" : "n";
    m_mapPersona[ph::NOME] = ui->nomeLE->text();
    m_mapPersona[ph::COGNOME] = ui->cognomeLE->text();
    m_mapPersona[ph::PRT_IVA] = ui->pivaLE->text();
    m_mapPersona[ph::COD_FISCALE] = ui->codFiscaleLE->text();

    row = ui->agenteCB->currentIndex();
    m_mapPersona[ph::ID_AGENTE] = m_modelAgente->record(row).value(coldb::ID).toString();

    m_mapPersona[ph::INDIRIZZO] = ui->indirizzoLE->text();

    row = ui->cittaCB->currentIndex();
    m_mapPersona[ph::ID_CITTA] = m_modelCitta->record(row).value(coldb::ID).toString();
    row = ui->provinciaCB->currentIndex();
    m_mapPersona[ph::PROVINCIA] = m_modelProvincia->record(row).value(coldb::ID).toString();
    row = ui->capCB->currentIndex();
    m_mapPersona[ph::ID_CAP]= m_modelCap->record(row).value(coldb::ID).toString();
    row = ui->statoCB->currentIndex();
    m_mapPersona[ph::ID_STATO]= m_modelStato->record(row).value(coldb::ID).toString();

    m_mapPersona[ph::TEL]= ui->telLE->text();
    m_mapPersona[ph::CEL]= ui->celLE->text();
    m_mapPersona[ph::FAX] = ui->faxLE->text();
    m_mapPersona[ph::EMAIL] = ui->emailLE->text();
    m_mapPersona[ph::SITO_WEB] = ui->sitoWebLE->text();
    m_mapPersona[ph::BANCA] = ui->bancaLE->text();
    m_mapPersona[ph::AGENZIA] = ui->agenziaLE->text();
    m_mapPersona[ph::CONTO] = ui->contoLE->text();
    m_mapPersona[ph::SWIFT] = ui->swiftLE->text();
    m_mapPersona[ph::IBAN] = ui->ibanLE->text();
    m_mapPersona[ph::DESTINAZIONE_MERCE] = ui->destMerceTE->toPlainText();
    m_mapPersona[ph::NOTE] = ui->noteTE->toPlainText();
}

QSqlQuery AnagraficaAddDialog::prepareQuery(void)
{
    //Seleziona la query da utilizzare, controllando se nella mappa
    //e' presente la chiave PH_ID, se e' presente il dialog è stato
    //chiamato per aggiornare un record, altrimenti usa la query di
    //insert.
    //Compila la query di insert/update effettuando un iterazione sulla
    //mappa mapPersona.
    qDebug() << "AnagraficaAddDialog::prepareQuery()";
    QSqlQuery query;
    if (m_mapPersona.contains(ph::ID)) {
        query.prepare(anagrafica::UPDATE_QUERY);
        query.bindValue(ph::ID, m_mapPersona[ph::ID]);
    }
    else
        query.prepare(anagrafica::INSERT_QUERY);

    for (auto key : m_mapPersona.keys())
        query.bindValue(key, m_mapPersona[key]);

    return query;
}

void AnagraficaAddDialog::save(void)
{
    //Effettua diversi controlli per verificare che i dati nel dialog
    //siano stati inseriti, se tutti i controlli vengono passati esegue
    //la query.
    qDebug() << "AnagraficaAddDialog::save()";
    prepareMap();

    if (m_mapPersona[ph::RAG_SOCIALE].isEmpty()) {
        showDialogError(this, ERR020, MSG016); //NOTE codice errore 020
        ui->ragSocialeLE->setStyleSheet(css::warning);
        return;
    }

    else if (m_mapPersona[ph::CLIENTE] == "n" &&
             m_mapPersona[ph::FORNITORE] == "n") {
        showDialogError(this, ERR021, MSG017); //NOTE codice errore 021
        ui->clienteCKB->setStyleSheet(css::warning_ckb);
        ui->fornitoreCKB->setStyleSheet(css::warning_ckb);
        return;
    }

    else if (m_mapPersona[ph::COD_FISCALE].isEmpty() ||
             m_mapPersona[ph::PRT_IVA].isEmpty()) {
        showDialogError(this, ERR022, MSG018); //NOTE codice errore 022
        ui->codFiscaleLE->setStyleSheet(css::warning);
        ui->pivaLE->setStyleSheet(css::warning);
        return;
    }

    if (!controlloPartitaIva(m_mapPersona[ph::PRT_IVA])) {
        if (!showDialogWarning(this, ERR023, MSG019)) //NOTE codice errore 023
            return;
    }

    if (m_mapPersona[ph::COD_FISCALE] != m_mapPersona[ph::PRT_IVA]) {
        if (!controlloCodiceFiscale(m_mapPersona[ph::COD_FISCALE])) {
            if (!showDialogWarning(this, ERR024, MSG020)) //NOTE codice errore 024
                return;
        }
    }

    QSqlQuery query = prepareQuery();
    if (!query.exec()) {
        if (m_mapPersona.contains(ph::ID))
            showDialogError(this, ERR011, MSG005, query.lastError().text()); //NOTE codice errore 011
        else
            showDialogError(this, ERR025, MSG002, query.lastError().text()); //NOTE codice errore 025

        return;
    }

    this->accept();
}


void AnagraficaAddDialog::openAddTipoditta(void)
{
    qDebug() << "AnagraficaAddDialog::openAddTipoDitta()";
    QString value = allDlg(this, m_modelDitta, ADD_DITTA_QUERY, "Tipologia Ditta", ERR015); //NOTE codice errore 015
    if (!value.isEmpty())
        ui->tipoDittaCB->setCurrentText(value);
}

void AnagraficaAddDialog::openAddCitta(void)
{
    qDebug() << "AnagraficaAddDialog::openAddCitta()";
    QString value = allDlg(this, m_modelCitta, ADD_CITTA_QUERY, "Città", "ERRORE DA DEFINIRE"); //NOTE codice errore
    if (!value.isEmpty())
        ui->cittaCB->setCurrentText(value);
}

void AnagraficaAddDialog::openAddProvincia(void)
{
    qDebug() << "AnagraficaAddDialog::openAddProvincia";
    QString value = allDlg(this, m_modelProvincia, ADD_PROVINCIA_QUERY, "Provincia", ERR017); //NOTE codice errore 017
    if (!value.isEmpty())
        ui->provinciaCB->setCurrentText(value);
}

void AnagraficaAddDialog::openAddCap(void)
{
    qDebug() << "AnagraficaAddDialog::openAddCap()";
    QString value = allDlg(this, m_modelCap, ADD_CAP_QUERY, "CAP", ERR018); //NOTE codice errore 018
    if (!value.isEmpty())
        ui->capCB->setCurrentText(value);
}

void AnagraficaAddDialog::openAddStato(void)
{
    qDebug() << "AnagraficaAddDialog::openAddStato()";
    QString value = allDlg(this, m_modelStato, ADD_STATO_QUERY, "Stato", ERR019); //NOTE codice errore 019
    if (!value.isEmpty())
        ui->statoCB->setCurrentText(value);
}

void AnagraficaAddDialog::openAddAgente(void)
{
    qDebug() << "AnagraficaAddDialog::openAddAgente()";
    AgentiAddDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok)
        return;

    m_modelAgente->select();
    QString id = dlg.getId();
    //Seleziono il valore immesso
    ui->agenteCB->setModelColumn(anagrafica::COL_TABLE_ID);
    ui->agenteCB->setCurrentText(id);
    ui->agenteCB->setModelColumn(anagrafica::COL_TABLE_COGNOME);
}

void AnagraficaAddDialog::copyPrtIva(void)
{
    qDebug() << "AnagraficaAddDialog::copyPrtIva()";
    ui->codFiscaleLE->setText(ui->pivaLE->text());
}
