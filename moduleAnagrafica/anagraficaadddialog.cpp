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

    toggleAgente(false);
    ui->aziendaRB->setChecked(true);
    checkAzienda();
}

AnagraficaAddDialog::~AnagraficaAddDialog()
{
    qDebug() << "~AnagraficaAddDialog()";
    delete ui;
}

void AnagraficaAddDialog::initForm(void)
{
    qDebug() << "AnagraficaAddDialog::initForm()";
    ui->aziendaRB->setProperty(m_property, coldb::AZIENDA);
    ui->clienteRB->setProperty(m_property, coldb::CLIENTE);
    ui->fornitoreRB->setProperty(m_property, coldb::FORNITORE);
    ui->paRB->setProperty(m_property, coldb::PA);

    ui->ragSocialeLE->setProperty(m_property, coldb::RAGIONE_SOCIALE);
    ui->nomeLE->setProperty(m_property, coldb::NOME);
    ui->cognomeLE->setProperty(m_property, coldb::COGNOME);
    ui->trasmissioneCB->setProperty(m_property, coldb::ID_TRASMISSIONE);
    ui->codSdiLE->setProperty(m_property, coldb::COD_SDI);
    ui->pecLE->setProperty(m_property, coldb::PEC);
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
        cb->blockSignals(true);
        setValueCB(cb, value, int(modelCols::id));
        cb->blockSignals(false);
    }

    for (auto *rb : findChildren<QRadioButton *>()) {
        QString colName = rb->property(m_property).toString();
        bool value = query.value(colName).toBool();
        if (value) {
            rb->setChecked(value);
            rb->click();
        }
    }

    ui->destMerceTE->setText(query.value(coldb::DESTINAZIONE_MERCE).toString());
    ui->noteTE->setText(query.value(coldb::NOTE).toString());
    if (ui->trasmissioneCB->currentText() == "PEC") {
        ui->codSdiLE->setVisible(false);
        ui->codSdiLb->setVisible(false);
    }

    m_mapPersona[ph::ID]=id;
}

void AnagraficaAddDialog::initComboBox()
{
    qDebug() << "AnagraficaAddDialog::initComboBox()";
    m_modelCitta = setupComboBox(table::CITTA, ui->cittaCB, int(modelCols::descr));
    m_modelProvincia = setupComboBox(table::PROVINCIA, ui->provinciaCB, int(modelCols::descr));
    m_modelCap = setupComboBox(table::CAP, ui->capCB, int(modelCols::descr));
    m_modelStato = setupComboBox(table::STATO, ui->statoCB, int(modelCols::descr));
    m_modelAgente = setupComboBox(table::AGENTI, ui->agenteCB, int(colsAgenti::COGNOME));
    m_modelTrasmissione = setupComboBox(table::TIPO_TRASMISSIONE, ui->trasmissioneCB, int(modelCols::descr));
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

    //Controllo ragione sociale
    if ((ui->aziendaRB->isChecked() || ui->fornitoreRB->isChecked() ||
            ui->paRB->isChecked()) && ui->ragSocialeLE->text().isEmpty()) {
        ui->ragSocialeLE->setStyleSheet(css::warning);
        showDialogError(this, ERR019, MSG016);
        return false;
    }

    //Controllo nome e cognome
    if (ui->clienteRB->isChecked() && (ui->nomeLE->text().isEmpty() ||
            ui->cognomeLE->text().isEmpty())) {
        ui->nomeLE->setStyleSheet(css::warning);
        ui->cognomeLE->setStyleSheet(css::warning);
        showDialogError(this, ERR020, MSG033);
        return false;
    }

    //Controllo se i campi obbligatori sono stati inseriti.
    if (!checkLineEdit(ui->pivaLE, "partita IVA") ||
            !checkLineEdit(ui->codFiscaleLE, "codice fiscale") ||
            !checkLineEdit(ui->indirizzoLE, "indirizzo") ||
            !checkComboBox(ui->cittaCB, "citta") ||
            !checkComboBox(ui->provinciaCB, "provincia") ||
            !checkComboBox(ui->capCB, "CAP") ||
            !checkComboBox(ui->statoCB, "stato"))
        return false;

    if (!controlloPartitaIva(m_mapPersona[ph::PRT_IVA]))
        if (!showDialogWarning(this, ERR023, MSG019)) //NOTE codice errore 023
            return false;

    if (m_mapPersona[ph::COD_FISCALE] != m_mapPersona[ph::PRT_IVA])
        if (!controlloCodiceFiscale(m_mapPersona[ph::COD_FISCALE]))
            if (!showDialogWarning(this, ERR024, MSG020)) //NOTE codice errore 024
                return false;

    return true;
}

void AnagraficaAddDialog::save(void)
{
    //Effettua diversi controlli per verificare che i dati nel dialog
    //siano stati inseriti, se tutti i controlli vengono passati esegue
    //la query.
    qDebug() << "AnagraficaAddDialog::save()";
    prepareMap(m_mapPersona, int(modelCols::id));
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
    //ui->codFiscaleLE
    if (ui->pivaLE->text().isEmpty()) {
        QString nullIVA = "00000000000";
        ui->pivaLE->setText(nullIVA);
        ui->codFiscaleLE->setText(nullIVA);
    }
    else
        ui->codFiscaleLE->setText(ui->pivaLE->text());
}

void AnagraficaAddDialog::checkAzienda()
{
    qDebug() << "AnagraficaAddDialog::checkAzienda()";
    ui->ragSocialeLB->setVisible(true);
    ui->ragSocialeLE->setVisible(true);
    ui->nomeLB->setVisible(false);
    ui->nomeLE->setVisible(false);
    ui->nomeLE->clear();
    ui->cognomeLB->setVisible(false);
    ui->cognomeLE->setVisible(false);
    ui->cognomeLE->clear();
}

void AnagraficaAddDialog::checkCliente()
{
    qDebug() << "AnagraficaAddDialog::checkCliente()";
    ui->ragSocialeLB->setVisible(false);
    ui->ragSocialeLE->setVisible(false);
    ui->ragSocialeLE->clear();
    ui->nomeLB->setVisible(true);
    ui->nomeLE->setVisible(true);
    ui->cognomeLB->setVisible(true);
    ui->cognomeLE->setVisible(true);
}

void AnagraficaAddDialog::checkFornitore()
{
    qDebug() << "AnagraficaAddDialog::checkFornitore()";
    checkAzienda();
}

void AnagraficaAddDialog::checkPA()
{
    qDebug() << "AnagraficaAddDialog::checkPA()";
    checkAzienda();
}

void AnagraficaAddDialog::toggleAgente(bool status)
{
    qDebug() << "AnagraficaAddDialog::toggleAgente";
    ui->agenteLB->setVisible(status);
    ui->agenteCB->setVisible(status);
    ui->agentiDlgPB->setVisible(status);
}

void AnagraficaAddDialog::checkSDI(QString string)
{
    qDebug() << "AnagraficaAddDialog::checkSDI()";
    if (string == "PEC") {
        ui->codSdiLb->setVisible(false);
        ui->codSdiLE->setVisible(false);
        ui->codSdiLE->setText("0000000"); //default value PEC
        ui->pecLb->setVisible(true);
        ui->pecLE->setVisible(true);
    }
    else {
        ui->codSdiLb->setVisible(true);
        ui->codSdiLE->setVisible(true);
        ui->codSdiLE->clear();
        ui->pecLb->setVisible(true);
        ui->pecLE->setVisible(true);
    }
}
