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

    ui->lb_agente->hide();
    ui->pb_agenti_dlg->hide();
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

    ui->le_rag_sociale->setText(query.value(col::RAGIONE_SOCIALE).toString());
    ui->cliente_cb->setChecked(query.value(col::CLIENTE).toBool());
    ui->fornitore_cb->setChecked(query.value(col::FORNITORE).toBool());
    if (ui->fornitore_cb->isChecked()) {
        ui->lb_agente->show();
        ui->cb_agente->show();
    }

    ui->cb_tipo_ditta->setModelColumn(anagrafica::COL_TABLE_ID);
    int index = ui->cb_tipo_ditta->findText(query.value(col::ID_TIPO_DITTA).toString());
    ui->cb_tipo_ditta->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cb_tipo_ditta->setCurrentIndex(index);

    ui->le_nome->setText(query.value(col::NOME).toString());
    ui->le_cognome->setText(query.value(col::COGNOME).toString());
    ui->le_piva->setText(query.value(col::PARTITA_IVA).toString());
    ui->le_cod_fiscale->setText(query.value(col::CODICE_FISCALE).toString());

    ui->cb_agente->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->cb_agente->findText(query.value(col::ID_AGENTE).toString());
    ui->cb_agente->setModelColumn(anagrafica::COL_TABLE_COGNOME);
    ui->cb_agente->setCurrentIndex(index);

    ui->le_indirizzo->setText(query.value(col::INDIRIZZO).toString());

    ui->cb_citta->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->cb_citta->findText(query.value(col::ID_CITTA).toString());
    ui->cb_citta->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cb_citta->setCurrentIndex(index);

    ui->cb_provincia->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->cb_provincia->findText(query.value(col::ID_PROVINCIA).toString());
    ui->cb_provincia->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cb_provincia->setCurrentIndex(index);

    ui->cb_cap->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->cb_cap->findText(query.value(col::ID_CAP).toString());
    ui->cb_cap->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cb_cap->setCurrentIndex(index);

    ui->cb_stato->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->cb_stato->findText(query.value(col::ID_STATO).toString());
    ui->cb_stato->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cb_stato->setCurrentIndex(index);

    ui->le_tel->setText(query.value(col::TEL).toString());
    ui->le_cel->setText(query.value(col::CEL).toString());
    ui->le_fax->setText(query.value(col::FAX).toString());
    ui->le_email->setText(query.value(col::EMAIL).toString());
    ui->le_web->setText(query.value(col::SITO_WEB).toString());

    ui->le_banca->setText(query.value(col::BANCA).toString());
    ui->le_agenzia->setText(query.value(col::AGENZIA).toString());
    ui->le_conto->setText(query.value(col::CONTO).toString());
    ui->le_swift->setText(query.value(col::SWIFT).toString());
    ui->le_iban->setText(query.value(col::IBAN).toString());

    ui->te_destinazione_merce->setText(query.value(col::DESTINAZIONE_MERCE).toString());
    ui->te_note->setText(query.value(col::NOTE).toString());

    mapPersona[ph::ID]=id;
}

void AnagraficaAddDialog::initModel()
{
    qDebug() << "AnagraficaAddDialog::initModel()";
    modelDitta = new QSqlTableModel(this);
    modelDitta->setTable(table::TIPO_DITTA);
    modelDitta->select();

    modelCitta = new QSqlTableModel(this);
    modelCitta->setTable(table::CITTA);
    modelCitta->select();

    modelProvincia = new QSqlTableModel(this);
    modelProvincia->setTable(table::PROVINCIA);
    modelProvincia->select();

    modelCap = new QSqlTableModel(this);
    modelCap->setTable(table::CAP);
    modelCap->select();

    modelStato = new QSqlTableModel(this);
    modelStato->setTable(table::STATO);
    modelStato->select();

    modelAgente = new QSqlTableModel(this);
    modelAgente->setTable(table::AGENTI);
    modelAgente->select();
}

void AnagraficaAddDialog::initComboBox()
{
    qDebug() << "AnagraficaAddDialog::initComboBox()";
    ui->cb_tipo_ditta->setModel(modelDitta);
    ui->cb_tipo_ditta->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->cb_citta->setModel(modelCitta);
    ui->cb_citta->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->cb_provincia->setModel(modelProvincia);
    ui->cb_provincia->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->cb_cap->setModel(modelCap);
    ui->cb_cap->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->cb_stato->setModel(modelStato);
    ui->cb_stato->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);

    ui->cb_agente->setModel(modelAgente);
    ui->cb_agente->setModelColumn(anagrafica::COL_TABLE_COGNOME);
    ui->cb_agente->hide();
}

void AnagraficaAddDialog::prepareMap(void)
{
    //Popolo la mappa mapPersona<Qstring,QString> con i valori
    //dei vari widget. Verra usata in seguito nel metodo prepareQuery.
    qDebug() << "AnagraficaAddDialog::prepareMap()";
    mapPersona[ph::RAG_SOCIALE] = ui->le_rag_sociale->text();

    int row = ui->cb_tipo_ditta->currentIndex();
    mapPersona[ph::TIPO_DITTA] = modelDitta->record(row).value(col::ID).toString();

    mapPersona[ph::CLIENTE] = ui->cliente_cb->isChecked() ? "y" : "n";
    mapPersona[ph::FORNITORE] = ui->fornitore_cb->isChecked() ? "y" : "n";
    mapPersona[ph::NOME] = ui->le_nome->text();
    mapPersona[ph::COGNOME] = ui->le_cognome->text();
    mapPersona[ph::PRT_IVA] = ui->le_piva->text();
    mapPersona[ph::COD_FISCALE] = ui->le_cod_fiscale->text();

    row = ui->cb_agente->currentIndex();
    mapPersona[ph::AGENTE] = modelAgente->record(row).value(col::ID).toString();

    mapPersona[ph::INDIRIZZO] = ui->le_indirizzo->text();

    row = ui->cb_citta->currentIndex();
    mapPersona[ph::CITTA] = modelCitta->record(row).value(col::ID).toString();
    row = ui->cb_provincia->currentIndex();
    mapPersona[ph::PROVINCIA] = modelProvincia->record(row).value(col::ID).toString();
    row = ui->cb_cap->currentIndex();
    mapPersona[ph::CAP]= modelCap->record(row).value(col::ID).toString();
    row = ui->cb_stato->currentIndex();
    mapPersona[ph::STATO]= modelStato->record(row).value(col::ID).toString();

    mapPersona[ph::TEL]= ui->le_tel->text();
    mapPersona[ph::CEL]= ui->le_cel->text();
    mapPersona[ph::FAX] = ui->le_fax->text();
    mapPersona[ph::EMAIL] = ui->le_email->text();
    mapPersona[ph::SITO_WEB] = ui->le_web->text();
    mapPersona[ph::BANCA] = ui->le_banca->text();
    mapPersona[ph::AGENZIA] = ui->le_agenzia->text();
    mapPersona[ph::CONTO] = ui->le_conto->text();
    mapPersona[ph::SWIFT] = ui->le_swift->text();
    mapPersona[ph::IBAN] = ui->le_iban->text();
    mapPersona[ph::DEST_MERCE] = ui->te_destinazione_merce->toPlainText();
    mapPersona[ph::NOTE] = ui->te_note->toPlainText();
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
    if (mapPersona.contains(ph::ID)) {
        query.prepare(anagrafica::UPDATE_QUERY);
        query.bindValue(ph::ID, mapPersona[ph::ID]);
    }
    else {
        query.prepare(anagrafica::INSERT_QUERY);
    }

    QMapIterator <QString, QString> it(mapPersona);
    while (it.hasNext()) {
        it.next();
        query.bindValue(it.key(), it.value());
    }

    return query;
}

void AnagraficaAddDialog::save(void)
{
    //Effettua diversi controlli per verificare che i dati nel dialog
    //siano stati inseriti, se tutti i controlli vengono passati esegue
    //la query.
    qDebug() << "AnagraficaAddDialog::save()";
    prepareMap();

    if (mapPersona[ph::RAG_SOCIALE].isEmpty()) {
        showDialogError(this, ERR020, MSG016); //NOTE codice errore 020
        ui->le_rag_sociale->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    else if (mapPersona[ph::CLIENTE] == "n" &&
             mapPersona[ph::FORNITORE] == "n") {
        showDialogError(this, ERR021, MSG017); //NOTE codice errore 021
        ui->cliente_cb->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        ui->fornitore_cb->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    else if (mapPersona[ph::COD_FISCALE].isEmpty() ||
             mapPersona[ph::PRT_IVA].isEmpty()) {
        showDialogError(this, ERR022, MSG018); //NOTE codice errore 022
        ui->le_cod_fiscale->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        ui->le_piva->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    if (!controlloPartitaIva(mapPersona[ph::PRT_IVA])) {
        if (!showDialogWarning(this, ERR023, MSG019)) //NOTE codice errore 023
            return;
    }

    if (mapPersona[ph::COD_FISCALE] != mapPersona[ph::PRT_IVA]) {
        if (!controlloCodiceFiscale(mapPersona[ph::COD_FISCALE])) {
            if (!showDialogWarning(this, ERR024, MSG020)) //NOTE codice errore 024
                return;
        }
    }

    QSqlQuery query = prepareQuery();
    if (!query.exec()) {
        if (mapPersona.contains(ph::ID)) {
            showDialogError(this, ERR011, MSG005, query.lastError().text()); //NOTE codice errore 011
        }
        else {
            showDialogError(this, ERR025, MSG002, query.lastError().text()); //NOTE codice errore 025
        }
        return;
    }

    this->accept();
}


void AnagraficaAddDialog::openAddTipoditta(void)
{
    qDebug() << "AnagraficaAddDialog::openAddTipoDitta()";
    QString value = allDlg(this, modelDitta, ADD_DITTA_QUERY, "Tipologia Ditta", ERR015); //NOTE codice errore 015
    if (!value.isEmpty())
        ui->cb_tipo_ditta->setCurrentText(value);
}

void AnagraficaAddDialog::openAddCitta(void)
{
    qDebug() << "AnagraficaAddDialog::openAddCitta()";
    QString value = allDlg(this, modelCitta, ADD_CITTA_QUERY, "Città", ERR016); //NOTE codice errore 016
    if (!value.isEmpty())
        ui->cb_citta->setCurrentText(value);

}

void AnagraficaAddDialog::openAddProvincia(void)
{
    qDebug() << "AnagraficaAddDialog::openAddProvincia";
    QString value = allDlg(this, modelProvincia, ADD_PROVINCIA_QUERY, "Provincia", ERR017); //NOTE codice errore 017
    if (!value.isEmpty())
        ui->cb_provincia->setCurrentText(value);
}

void AnagraficaAddDialog::openAddCap(void)
{
    qDebug() << "AnagraficaAddDialog::openAddCap()";
    QString value = allDlg(this, modelCap, ADD_CAP_QUERY, "CAP", ERR018); //NOTE codice errore 018
    if (!value.isEmpty())
        ui->cb_cap->setCurrentText(value);
}

void AnagraficaAddDialog::openAddStato(void)
{
    qDebug() << "AnagraficaAddDialog::openAddStato()";
    QString value = allDlg(this, modelStato, ADD_STATO_QUERY, "Stato", ERR019); //NOTE codice errore 019
    if (!value.isEmpty())
        ui->cb_stato->setCurrentText(value);
}

void AnagraficaAddDialog::openAddAgente(void)
{
    qDebug() << "AnagraficaAddDialog::openAddAgente()";
    AgentiAddDialog dlg(this);
    bool ok = dlg.exec();
    if (ok) {
        modelAgente->select();
    }

    //Trovo l'ultimo id inserito nel database
    QSqlQuery query;
    query.prepare("SELECT * FROM lastval();");
    query.exec();
    query.first();
    QString id = query.value(anagrafica::COL_TABLE_ID).toString();

    //Seleziono il valore immesso
    ui->cb_agente->setModelColumn(anagrafica::COL_TABLE_ID);
    ui->cb_agente->setCurrentText(id);
    ui->cb_agente->setModelColumn(anagrafica::COL_TABLE_COGNOME);
}

void AnagraficaAddDialog::copyPrtIva(void)
{
    qDebug() << "AnagraficaAddDialog::copyPrtIva()";
    ui->le_cod_fiscale->setText(ui->le_piva->text());
}
