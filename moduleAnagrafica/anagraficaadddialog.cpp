#include "moduleAnagrafica/anagraficaadddialog.h"
#include "ui_anagraficaadddialog.h"

AnagraficaAddDialog::AnagraficaAddDialog(QWidget *parent) :
    CustomInsertDialog(parent),
    ui(new Ui::AnagraficaAddDialog)
{
    qDebug() << "AnagraficaAddDialog()";
    ui->setupUi(this); 

    initForm();
    initComboBox();

    ui->agenteLB->hide();
    ui->agenteCB->hide();
    ui->agentiDlgPB->hide();
}

AnagraficaAddDialog::~AnagraficaAddDialog()
{
    qDebug() << "~AnagraficaAddDialog()";
    delete ui;
}

void AnagraficaAddDialog::initForm(void)
{
    qDebug() << "AnagraficaAddDialog::initForm()";
    ui->ragSocialeLE->setProperty(m_property, coldb::RAGIONE_SOCIALE);
    ui->nomeLE->setProperty(m_property, coldb::NOME);
    ui->cognomeLE->setProperty(m_property, coldb::COGNOME);
    ui->clienteCKB->setProperty(m_property, coldb::CLIENTE);
    ui->fornitoreCKB->setProperty(m_property, coldb::FORNITORE);
    ui->tipoDittaCB->setProperty(m_property, coldb::ID_TIPO_DITTA);
    ui->pivaLE->setProperty(m_property, coldb::PARTITA_IVA);
    ui->codFiscaleLE->setProperty(m_property, coldb::CODICE_FISCALE);
    ui->agenteCB->setProperty(m_property, coldb::ID_AGENTE);
    ui->indirizzoLE->setProperty(m_property, coldb::INDIRIZZO);
    ui->cittaCB->setProperty(m_property, coldb::ID_CITTA);
    ui->provinciaCB->setProperty(m_property, coldb::ID_PROVINCIA);
    ui->capCB->setProperty(m_property, coldb::ID_CAP);
    ui->statoCB->setProperty(m_property, coldb::ID_STATO);
    ui->telLE->setProperty(m_property, coldb::TEL);
    ui->celLE->setProperty(m_property, coldb::CEL);
    ui->faxLE->setProperty(m_property, coldb::FAX);
    ui->emailLE->setProperty(m_property, coldb::EMAIL);
    ui->sitoWebLE->setProperty(m_property, coldb::SITO_WEB);
    ui->bancaLE->setProperty(m_property, coldb::BANCA);
    ui->agenziaLE->setProperty(m_property, coldb::AGENZIA);
    ui->contoLE->setProperty(m_property, coldb::CONTO);
    ui->swiftLE->setProperty(m_property, coldb::SWIFT);
    ui->ibanLE->setProperty(m_property, coldb::IBAN);
    ui->destMerceTE->setProperty(m_property, coldb::DESTINAZIONE_MERCE);
    ui->noteTE->setProperty(m_property, coldb::NOTE);
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

    for (auto *le : findChildren<QLineEdit *>()) {
        QString colName = le->property(m_property).toString();
        QString value = query.value(colName).toString();
        le->setText(value);
    }

    for (auto *cb : findChildren<QComboBox *>()) {
        QString colName = cb->property(m_property).toString();
        QString value = query.value(colName).toString();
        setValueCB(cb, value, int(modelCols::id));
    }

    ui->clienteCKB->setChecked(query.value(coldb::CLIENTE).toBool());
    ui->fornitoreCKB->setChecked(query.value(coldb::FORNITORE).toBool());
    if (ui->fornitoreCKB->isChecked()) {
        ui->agenteLB->show();
        ui->agenteCB->show();
        ui->agentiDlgPB->show();
    }

    ui->destMerceTE->setText(query.value(coldb::DESTINAZIONE_MERCE).toString());
    ui->noteTE->setText(query.value(coldb::NOTE).toString());

    m_mapPersona[ph::ID]=id;
}

void AnagraficaAddDialog::initComboBox()
{
    qDebug() << "AnagraficaAddDialog::initComboBox()";
    m_modelDitta = setupComboBox(table::TIPO_DITTA, ui->tipoDittaCB, int(modelCols::descr));
    m_modelCitta = setupComboBox(table::CITTA, ui->cittaCB, int(modelCols::descr));
    m_modelProvincia = setupComboBox(table::PROVINCIA, ui->provinciaCB, int(modelCols::descr));
    m_modelCap = setupComboBox(table::CAP, ui->capCB, int(modelCols::descr));
    m_modelStato = setupComboBox(table::STATO, ui->statoCB, int(modelCols::descr));
    m_modelAgente = setupComboBox(table::AGENTI, ui->agenteCB, int(colsAgenti::COGNOME));
}

void AnagraficaAddDialog::prepareMap(void)
{
    //Popolo la mappa mapPersona<Qstring,QString> con i valori
    //dei vari widget. Verra usata in seguito nel metodo prepareQuery.
    qDebug() << "AnagraficaAddDialog::prepareMap()";
    CustomInsertDialog::prepareMap(m_mapPersona, int(modelCols::id));

    m_mapPersona[ph::CLIENTE] = ui->clienteCKB->isChecked() ? "y" : "n";
    m_mapPersona[ph::FORNITORE] = ui->fornitoreCKB->isChecked() ? "y" : "n";
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

bool AnagraficaAddDialog::checkValues(void)
{
    qDebug() << "AnagraficaAddDialog::checkValues()";
    if (m_mapPersona[ph::RAG_SOCIALE].isEmpty()) {
        showDialogError(this, ERR020, MSG016); //NOTE codice errore 020
        ui->ragSocialeLE->setStyleSheet(css::warning);
        return false;
    }

    else if (m_mapPersona[ph::CLIENTE] == "n" &&
             m_mapPersona[ph::FORNITORE] == "n") {
        showDialogError(this, ERR021, MSG017); //NOTE codice errore 021
        ui->clienteCKB->setStyleSheet(css::warning_ckb);
        ui->fornitoreCKB->setStyleSheet(css::warning_ckb);
        return false;
    }

    else if (m_mapPersona[ph::COD_FISCALE].isEmpty() ||
             m_mapPersona[ph::PRT_IVA].isEmpty()) {
        showDialogError(this, ERR022, MSG018); //NOTE codice errore 022
        ui->codFiscaleLE->setStyleSheet(css::warning);
        ui->pivaLE->setStyleSheet(css::warning);
        return false;
    }

    if (!controlloPartitaIva(m_mapPersona[ph::PRT_IVA])) {
        if (!showDialogWarning(this, ERR023, MSG019)) //NOTE codice errore 023
            return false;
    }

    if (m_mapPersona[ph::COD_FISCALE] != m_mapPersona[ph::PRT_IVA]) {
        if (!controlloCodiceFiscale(m_mapPersona[ph::COD_FISCALE])) {
            if (!showDialogWarning(this, ERR024, MSG020)) //NOTE codice errore 024
                return false;
        }
    }

    return true;
}


void AnagraficaAddDialog::save(void)
{
    //Effettua diversi controlli per verificare che i dati nel dialog
    //siano stati inseriti, se tutti i controlli vengono passati esegue
    //la query.
    qDebug() << "AnagraficaAddDialog::save()";
    prepareMap();
    if (!checkValues())
        return;

    QSqlQuery query = prepareQuery();
    if (!query.exec()) {
        if (m_mapPersona.contains(ph::ID))
            showDialogError(this, ERR011, MSG005, query.lastError().text()); //NOTE codice errore 011
        else
            showDialogError(this, ERR025, MSG002, query.lastError().text()); //NOTE codice errore 025

        return;
    }

    while (query.next())
       setId(query.value("id").toString());

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
    setValueCB(ui->agenteCB, id, int(modelCols::id));
}

void AnagraficaAddDialog::copyPrtIva(void)
{
    qDebug() << "AnagraficaAddDialog::copyPrtIva()";
    ui->codFiscaleLE->setText(ui->pivaLE->text());
}
//353
