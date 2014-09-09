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

    //ui->lb_agente->setShown(false);
    ui->lb_agente->hide();
    //ui->pb_agenti_dlg->setShown(false);
    ui->pb_agenti_dlg->hide();
}

AnagraficaAddDialog::~AnagraficaAddDialog()
{
    qDebug() << "~AnagraficaAddDialog()";
    delete ui;
}

void AnagraficaAddDialog::setValue(QString id)
{
    qDebug() << "AnagraficaAddDialog::setValue()";
    QSqlQuery query;
    query.prepare(anagrafica::SELECT_FROM_ID);
    query.bindValue(anagrafica::PH_ID, id);
    query.exec();
    query.first();

    ui->le_rag_sociale->setText(query.value(anagrafica::COL_RAG_SOC).toString());
    ui->cliente_cb->setChecked(query.value(anagrafica::COL_CLIENTE).toBool());
    ui->fornitore_cb->setChecked(query.value(anagrafica::COL_FORNITORE).toBool());
    if (ui->fornitore_cb->isChecked()) {
        ui->lb_agente->show();
        ui->cb_agente->show();
    }

    ui->cb_tipo_ditta->setModelColumn(anagrafica::COL_ID);
    int index = ui->cb_tipo_ditta->findText(query.value(anagrafica::COL_TIPO_DITTA).toString());
    ui->cb_tipo_ditta->setModelColumn(anagrafica::COL_MODEL_DESCR);
    ui->cb_tipo_ditta->setCurrentIndex(index);

    ui->le_nome->setText(query.value(anagrafica::COL_NOME).toString());
    ui->le_cognome->setText(query.value(anagrafica::COL_COGNOME).toString());
    ui->le_piva->setText(query.value(anagrafica::COL_PRT_IVA).toString());
    ui->le_cod_fiscale->setText(query.value(anagrafica::COL_COD_FISC).toString());

    ui->cb_agente->setModelColumn(anagrafica::COL_ID);
    index = ui->cb_agente->findText(query.value(anagrafica::COL_AGENTE).toString());
    ui->cb_agente->setModelColumn(anagrafica::COL_MODEL_COGNOME);
    ui->cb_agente->setCurrentIndex(index);

    ui->le_indirizzo->setText(query.value(anagrafica::COL_INDIRIZZO).toString());

    ui->cb_citta->setModelColumn(anagrafica::COL_ID);
    index = ui->cb_citta->findText(query.value(anagrafica::COL_CITTA).toString());
    ui->cb_citta->setModelColumn(anagrafica::COL_MODEL_DESCR);
    ui->cb_citta->setCurrentIndex(index);

    ui->cb_provincia->setModelColumn(anagrafica::COL_ID);
    index = ui->cb_provincia->findText(query.value(anagrafica::COL_PROVINCIA).toString());
    ui->cb_provincia->setModelColumn(anagrafica::COL_MODEL_DESCR);
    ui->cb_provincia->setCurrentIndex(index);

    ui->cb_cap->setModelColumn(anagrafica::COL_ID);
    index = ui->cb_cap->findText(query.value(anagrafica::COL_CAP).toString());
    ui->cb_cap->setModelColumn(anagrafica::COL_MODEL_DESCR);
    ui->cb_cap->setCurrentIndex(index);

    ui->cb_stato->setModelColumn(anagrafica::COL_ID);
    index = ui->cb_stato->findText(query.value(anagrafica::COL_STATO).toString());
    ui->cb_stato->setModelColumn(anagrafica::COL_MODEL_DESCR);
    ui->cb_stato->setCurrentIndex(index);

    ui->le_tel->setText(query.value(anagrafica::COL_TEL).toString());
    ui->le_cel->setText(query.value(anagrafica::COL_CEL).toString());
    ui->le_fax->setText(query.value(anagrafica::COL_FAX).toString());
    ui->le_email->setText(query.value(anagrafica::COL_EMAIL).toString());
    ui->le_web->setText(query.value(anagrafica::COL_WEB).toString());

    ui->le_banca->setText(query.value(anagrafica::COL_BANCA).toString());
    ui->le_agenzia->setText(query.value(anagrafica::COL_AGENZIA).toString());
    ui->le_conto->setText(query.value(anagrafica::COL_CONTO).toString());
    ui->le_swift->setText(query.value(anagrafica::COL_SWIFT).toString());
    ui->le_iban->setText(query.value(anagrafica::COL_IBAN).toString());

    ui->te_destinazione_merce->setText(query.value(anagrafica::COL_MERCE).toString());
    ui->te_note->setText(query.value(anagrafica::COL_NOTE).toString());

    mapPersona[keymap::KEY_ID]=id;

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
    ui->cb_tipo_ditta->setModelColumn(anagrafica::COL_MODEL_DESCR);

    ui->cb_citta->setModel(modelCitta);
    ui->cb_citta->setModelColumn(anagrafica::COL_MODEL_DESCR);

    ui->cb_provincia->setModel(modelProvincia);
    ui->cb_provincia->setModelColumn(anagrafica::COL_MODEL_DESCR);

    ui->cb_cap->setModel(modelCap);
    ui->cb_cap->setModelColumn(anagrafica::COL_MODEL_DESCR);

    ui->cb_stato->setModel(modelStato);
    ui->cb_stato->setModelColumn(anagrafica::COL_MODEL_DESCR);

    ui->cb_agente->setModel(modelAgente);
    ui->cb_agente->setModelColumn(anagrafica::COL_MODEL_COGNOME);
    //ui->cb_agente->setShown(false);
    ui->cb_agente->hide();
}

void AnagraficaAddDialog::prepareMap(void)
{
    qDebug() << "AnagraficaAddDialog::prepareMap()";
    mapPersona[keymap::KEY_RAGSOC] = ui->le_rag_sociale->text();
    mapPersona[keymap::KEY_TIPO_DITTA] = modelDitta->index(ui->cb_tipo_ditta->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona[keymap::KEY_CLIENTE] = ui->cliente_cb->isChecked() ? "y" : "n";
    mapPersona[keymap::KEY_FORNITORE] = ui->fornitore_cb->isChecked() ? "y" : "n";
    mapPersona[keymap::KEY_NOME] = ui->le_nome->text();
    mapPersona[keymap::KEY_COGNOME] = ui->le_cognome->text();
    mapPersona[keymap::KEY_PRT_IVA] = ui->le_piva->text();
    mapPersona[keymap::KEY_COD_FISCALE] = ui->le_cod_fiscale->text();
    mapPersona[keymap::KEY_AGENTE] = modelAgente->index(ui->cb_agente->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona[keymap::KEY_INDIRIZZO] = ui->le_indirizzo->text();
    mapPersona[keymap::KEY_ID_CITTA] = modelCitta->index(ui->cb_citta->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona[keymap::KEY_ID_PROVINCIA] = modelProvincia->index(ui->cb_provincia->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona[keymap::KEY_ID_CAP]= modelCap->index(ui->cb_cap->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona[keymap::KEY_ID_STATO]= modelStato->index(ui->cb_stato->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona[keymap::KEY_TEL]= ui->le_tel->text();
    mapPersona[keymap::KEY_CEL]= ui->le_cel->text();
    mapPersona[keymap::KEY_FAX] = ui->le_fax->text();
    mapPersona[keymap::KEY_EMAIL] = ui->le_email->text();
    mapPersona[keymap::KEY_WEB] = ui->le_web->text();
    mapPersona[keymap::KEY_BANCA] = ui->le_banca->text();
    mapPersona[keymap::KEY_AGENZIA] = ui->le_agenzia->text();
    mapPersona[keymap::KEY_CONTO] = ui->le_conto->text();
    mapPersona[keymap::KEY_SWIFT] = ui->le_swift->text();
    mapPersona[keymap::KEY_IBAN] = ui->le_iban->text();
    mapPersona[keymap::KEY_DESTMERCE] = ui->te_destinazione_merce->toPlainText();
    mapPersona[keymap::KEY_NOTE] = ui->te_note->toPlainText();
}

QSqlQuery AnagraficaAddDialog::prepareQuery(void)
{
    qDebug() << "AnagraficaAddDialog::prepareQuery()";
    QSqlQuery query;
    if (mapPersona.contains(keymap::KEY_ID)) {
        query.prepare(anagrafica::UPDATE_QUERY);
        query.bindValue(anagrafica::PH_ID, mapPersona[keymap::KEY_ID]);
    }
    else {
        query.prepare(anagrafica::INSERT_QUERY);
    }

    query.bindValue(anagrafica::PH_FORNITORE, mapPersona[keymap::KEY_FORNITORE]);
    query.bindValue(anagrafica::PH_CLIENTE, mapPersona[keymap::KEY_CLIENTE]);
    query.bindValue(anagrafica::PH_RAG_SOCIALE, mapPersona[keymap::KEY_RAGSOC]);
    query.bindValue(anagrafica::PH_TIPO_DITTA, mapPersona[keymap::KEY_TIPO_DITTA]);
    query.bindValue(anagrafica::PH_NOME, mapPersona[keymap::KEY_NOME]);
    query.bindValue(anagrafica::PH_COGNOME, mapPersona[keymap::KEY_COGNOME]);
    query.bindValue(anagrafica::PH_INDIRIZZO, mapPersona[keymap::KEY_INDIRIZZO]);
    query.bindValue(anagrafica::PH_CITTA, mapPersona[keymap::KEY_ID_CITTA]);
    query.bindValue(anagrafica::PH_PROVINCIA, mapPersona[keymap::KEY_ID_PROVINCIA]);
    query.bindValue(anagrafica::PH_CAP, mapPersona[keymap::KEY_ID_CAP]);
    query.bindValue(anagrafica::PH_STATO, mapPersona[keymap::KEY_ID_STATO]);
    query.bindValue(anagrafica::PH_COD_FISCALE, mapPersona[keymap::KEY_COD_FISCALE]);
    query.bindValue(anagrafica::PH_PRT_IVA, mapPersona[keymap::KEY_PRT_IVA]);
    query.bindValue(anagrafica::PH_AGENTE, mapPersona[keymap::KEY_AGENTE]);
    query.bindValue(anagrafica::PH_TEL, mapPersona[keymap::KEY_TEL]);
    query.bindValue(anagrafica::PH_FAX, mapPersona[keymap::KEY_FAX]);
    query.bindValue(anagrafica::PH_CEL, mapPersona[keymap::KEY_CEL]);
    query.bindValue(anagrafica::PH_EMAIL, mapPersona[keymap::KEY_EMAIL]);
    query.bindValue(anagrafica::PH_SITO_WEB, mapPersona[keymap::KEY_WEB]);
    query.bindValue(anagrafica::PH_BANCA, mapPersona[keymap::KEY_BANCA]);
    query.bindValue(anagrafica::PH_AGENZIA, mapPersona[keymap::KEY_AGENZIA]);
    query.bindValue(anagrafica::PH_CONTO, mapPersona[keymap::KEY_CONTO]);
    query.bindValue(anagrafica::PH_SWIFT, mapPersona[keymap::KEY_SWIFT]);
    query.bindValue(anagrafica::PH_IBAN, mapPersona[keymap::KEY_IBAN]);
    query.bindValue(anagrafica::PH_DEST_MERCE, mapPersona[keymap::KEY_DESTMERCE]);
    query.bindValue(anagrafica::PH_NOTE, mapPersona[keymap::KEY_NOTE]);
    return query;
}

void AnagraficaAddDialog::save(void)
{
    qDebug() << "AnagraficaAddDialog::save()";
    prepareMap();

    if (mapPersona[keymap::KEY_RAGSOC].isEmpty()) {
        showDialogError(this, ERR020, MSG016); //NOTE codice errore 020
        ui->le_rag_sociale->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    else if (mapPersona[keymap::KEY_CLIENTE] == "n" && mapPersona[keymap::KEY_FORNITORE] == "n") {
        showDialogError(this, ERR021, MSG017); //NOTE codice errore 021
        ui->cliente_cb->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        ui->fornitore_cb->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    else if (mapPersona[keymap::KEY_COD_FISCALE].isEmpty() || mapPersona[keymap::KEY_PRT_IVA].isEmpty()) {
        showDialogError(this, ERR022, MSG018); //NOTE codice errore 022
        ui->le_cod_fiscale->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        ui->le_piva->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    if (!controlloPartitaIva(mapPersona[keymap::KEY_PRT_IVA])) {
        if (!showDialogWarning(this, ERR023, MSG019)) //NOTE codice errore 023
            return;
    }

    if (mapPersona[keymap::KEY_COD_FISCALE] != mapPersona[keymap::KEY_PRT_IVA]) {
        if (!controlloCodiceFiscale(mapPersona[keymap::KEY_COD_FISCALE])) {
            if (!showDialogWarning(this, ERR024, MSG020)) //NOTE codice errore 024
                return;
        }
    }

    QSqlQuery query = prepareQuery();
    if (!query.exec()) {
        if (mapPersona.contains(keymap::KEY_ID)) {
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
    allDlg(this, modelDitta, ADD_DITTA_QUERY, "Tipologia Ditta", ERR015); //NOTE codice errore 015
}

void AnagraficaAddDialog::openAddCitta(void)
{
    qDebug() << "AnagraficaAddDialog::openAddCitta()";
    allDlg(this, modelCitta, ADD_CITTA_QUERY, "Città", ERR016); //NOTE codice errore 016
}

void AnagraficaAddDialog::openAddProvincia(void)
{
    qDebug() << "AnagraficaAddDialog::openAddProvincia";
    allDlg(this, modelProvincia, ADD_PROVINCIA_QUERY, "Provincia", ERR017); //NOTE codice errore 017
}

void AnagraficaAddDialog::openAddCap(void)
{
    qDebug() << "AnagraficaAddDialog::openAddCap()";
    allDlg(this, modelCap, ADD_CAP_QUERY, "CAP", ERR018); //NOTE codice errore 018
}

void AnagraficaAddDialog::openAddStato(void)
{
    qDebug() << "AnagraficaAddDialog::openAddStato()";
    allDlg(this, modelStato, ADD_STATO_QUERY, "Stato", ERR019); //NOTE codice errore 019
}

void AnagraficaAddDialog::openAddAgente(void)
{
    qDebug() << "AnagraficaAddDialog::openAddAgente()";
    AgentiAddDialog dlg(this);
    bool ok = dlg.exec();
    if (ok) {
        modelAgente->select();
    }
}

void AnagraficaAddDialog::copyPrtIva(void)
{
    qDebug() << "AnagraficaAddDialog::copyPrtIva()";
    ui->le_cod_fiscale->setText(ui->le_piva->text());
}
