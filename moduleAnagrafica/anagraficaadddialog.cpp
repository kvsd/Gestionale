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
    query.bindValue(anagrafica::PH_ID, id);
    query.exec();
    query.first();

    ui->le_rag_sociale->setText(query.value(anagrafica::COL_RAGIONE_SOCIALE).toString());
    ui->cliente_cb->setChecked(query.value(anagrafica::COL_CLIENTE).toBool());
    ui->fornitore_cb->setChecked(query.value(anagrafica::COL_FORNITORE).toBool());
    if (ui->fornitore_cb->isChecked()) {
        ui->lb_agente->show();
        ui->cb_agente->show();
    }

    ui->cb_tipo_ditta->setModelColumn(anagrafica::COL_TABLE_ID);
    int index = ui->cb_tipo_ditta->findText(query.value(anagrafica::COL_ID_TIPO_DITTA).toString());
    ui->cb_tipo_ditta->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cb_tipo_ditta->setCurrentIndex(index);

    ui->le_nome->setText(query.value(anagrafica::COL_NOME).toString());
    ui->le_cognome->setText(query.value(anagrafica::COL_COGNOME).toString());
    ui->le_piva->setText(query.value(anagrafica::COL_PARTITA_IVA).toString());
    ui->le_cod_fiscale->setText(query.value(anagrafica::COL_CODICE_FISCALE).toString());

    ui->cb_agente->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->cb_agente->findText(query.value(anagrafica::COL_ID_AGENTE).toString());
    ui->cb_agente->setModelColumn(anagrafica::COL_TABLE_COGNOME);
    ui->cb_agente->setCurrentIndex(index);

    ui->le_indirizzo->setText(query.value(anagrafica::COL_INDIRIZZO).toString());

    ui->cb_citta->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->cb_citta->findText(query.value(anagrafica::COL_ID_CITTA).toString());
    ui->cb_citta->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cb_citta->setCurrentIndex(index);

    ui->cb_provincia->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->cb_provincia->findText(query.value(anagrafica::COL_ID_PROVINCIA).toString());
    ui->cb_provincia->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cb_provincia->setCurrentIndex(index);

    ui->cb_cap->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->cb_cap->findText(query.value(anagrafica::COL_ID_CAP).toString());
    ui->cb_cap->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cb_cap->setCurrentIndex(index);

    ui->cb_stato->setModelColumn(anagrafica::COL_TABLE_ID);
    index = ui->cb_stato->findText(query.value(anagrafica::COL_ID_STATO).toString());
    ui->cb_stato->setModelColumn(anagrafica::COL_TABLE_DESCRIZIONE);
    ui->cb_stato->setCurrentIndex(index);

    ui->le_tel->setText(query.value(anagrafica::COL_TELEFONO).toString());
    ui->le_cel->setText(query.value(anagrafica::COL_CELLULARE).toString());
    ui->le_fax->setText(query.value(anagrafica::COL_FAX).toString());
    ui->le_email->setText(query.value(anagrafica::COL_EMAIL).toString());
    ui->le_web->setText(query.value(anagrafica::COL_SITO_WEB).toString());

    ui->le_banca->setText(query.value(anagrafica::COL_BANCA).toString());
    ui->le_agenzia->setText(query.value(anagrafica::COL_AGENZIA).toString());
    ui->le_conto->setText(query.value(anagrafica::COL_CONTO).toString());
    ui->le_swift->setText(query.value(anagrafica::COL_SWIFT).toString());
    ui->le_iban->setText(query.value(anagrafica::COL_IBAN).toString());

    ui->te_destinazione_merce->setText(query.value(anagrafica::COL_DESTINAZIONE_MERCE).toString());
    ui->te_note->setText(query.value(anagrafica::COL_NOTE).toString());

    mapPersona[anagrafica::PH_ID]=id;
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
    mapPersona[anagrafica::PH_RAG_SOCIALE] = ui->le_rag_sociale->text();

    int row = ui->cb_tipo_ditta->currentIndex();
    mapPersona[anagrafica::PH_TIPO_DITTA] = modelDitta->record(row).value(anagrafica::COL_ID).toString();

    mapPersona[anagrafica::PH_CLIENTE] = ui->cliente_cb->isChecked() ? "y" : "n";
    mapPersona[anagrafica::PH_FORNITORE] = ui->fornitore_cb->isChecked() ? "y" : "n";
    mapPersona[anagrafica::PH_NOME] = ui->le_nome->text();
    mapPersona[anagrafica::PH_COGNOME] = ui->le_cognome->text();
    mapPersona[anagrafica::PH_PRT_IVA] = ui->le_piva->text();
    mapPersona[anagrafica::PH_COD_FISCALE] = ui->le_cod_fiscale->text();

    row = ui->cb_agente->currentIndex();
    mapPersona[anagrafica::PH_AGENTE] = modelAgente->record(row).value(anagrafica::COL_ID).toString();

    mapPersona[anagrafica::PH_INDIRIZZO] = ui->le_indirizzo->text();

    row = ui->cb_citta->currentIndex();
    mapPersona[anagrafica::PH_CITTA] = modelCitta->record(row).value(anagrafica::COL_ID).toString();
    row = ui->cb_provincia->currentIndex();
    mapPersona[anagrafica::PH_PROVINCIA] = modelProvincia->record(row).value(anagrafica::COL_ID).toString();
    row = ui->cb_cap->currentIndex();
    mapPersona[anagrafica::PH_CAP]= modelCap->record(row).value(anagrafica::COL_ID).toString();
    row = ui->cb_stato->currentIndex();
    mapPersona[anagrafica::PH_STATO]= modelStato->record(row).value(anagrafica::COL_ID).toString();

    mapPersona[anagrafica::PH_TEL]= ui->le_tel->text();
    mapPersona[anagrafica::PH_CEL]= ui->le_cel->text();
    mapPersona[anagrafica::PH_FAX] = ui->le_fax->text();
    mapPersona[anagrafica::PH_EMAIL] = ui->le_email->text();
    mapPersona[anagrafica::PH_SITO_WEB] = ui->le_web->text();
    mapPersona[anagrafica::PH_BANCA] = ui->le_banca->text();
    mapPersona[anagrafica::PH_AGENZIA] = ui->le_agenzia->text();
    mapPersona[anagrafica::PH_CONTO] = ui->le_conto->text();
    mapPersona[anagrafica::PH_SWIFT] = ui->le_swift->text();
    mapPersona[anagrafica::PH_IBAN] = ui->le_iban->text();
    mapPersona[anagrafica::PH_DEST_MERCE] = ui->te_destinazione_merce->toPlainText();
    mapPersona[anagrafica::PH_NOTE] = ui->te_note->toPlainText();
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
    if (mapPersona.contains(anagrafica::PH_ID)) {
        query.prepare(anagrafica::UPDATE_QUERY);
        query.bindValue(anagrafica::PH_ID, mapPersona[anagrafica::PH_ID]);
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

    if (mapPersona[anagrafica::PH_RAG_SOCIALE].isEmpty()) {
        showDialogError(this, ERR020, MSG016); //NOTE codice errore 020
        ui->le_rag_sociale->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    else if (mapPersona[anagrafica::PH_CLIENTE] == "n" &&
             mapPersona[anagrafica::PH_FORNITORE] == "n") {
        showDialogError(this, ERR021, MSG017); //NOTE codice errore 021
        ui->cliente_cb->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        ui->fornitore_cb->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    else if (mapPersona[anagrafica::PH_COD_FISCALE].isEmpty() ||
             mapPersona[anagrafica::PH_PRT_IVA].isEmpty()) {
        showDialogError(this, ERR022, MSG018); //NOTE codice errore 022
        ui->le_cod_fiscale->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        ui->le_piva->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    if (!controlloPartitaIva(mapPersona[anagrafica::PH_PRT_IVA])) {
        if (!showDialogWarning(this, ERR023, MSG019)) //NOTE codice errore 023
            return;
    }

    if (mapPersona[anagrafica::PH_COD_FISCALE] != mapPersona[anagrafica::PH_PRT_IVA]) {
        if (!controlloCodiceFiscale(mapPersona[anagrafica::PH_COD_FISCALE])) {
            if (!showDialogWarning(this, ERR024, MSG020)) //NOTE codice errore 024
                return;
        }
    }

    QSqlQuery query = prepareQuery();
    if (!query.exec()) {
        if (mapPersona.contains(anagrafica::PH_ID)) {
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
