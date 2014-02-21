#include "moduleAnagrafica/anagraficaadddialog.h"
#include "ui_anagraficaadddialog.h"

AnagraficaAddDialog::AnagraficaAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnagraficaAddDialog)
{
    ui->setupUi(this); 

    initModel();
    initComboBox();

    ui->lb_agente->setShown(false);
    ui->pb_agenti_dlg->setShown(false);
}

AnagraficaAddDialog::~AnagraficaAddDialog()
{
    delete ui;
}

void AnagraficaAddDialog::setValue(QString id)
{
    QSqlQuery query;
    query.prepare(anagrafica::SELECT_FROM_ID);
    query.bindValue(":id", id);
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

    mapPersona["id"]=id;

}

void AnagraficaAddDialog::initModel()
{
    modelDitta = new QSqlTableModel(this);
    modelDitta->setTable("tipo_ditta");
    modelDitta->select();

    modelCitta = new QSqlTableModel(this);
    modelCitta->setTable("citta");
    modelCitta->select();

    modelProvincia = new QSqlTableModel(this);
    modelProvincia->setTable("provincia");
    modelProvincia->select();

    modelCap = new QSqlTableModel(this);
    modelCap->setTable("cap");
    modelCap->select();


    modelStato = new QSqlTableModel(this);
    modelStato->setTable("stato");
    modelStato->select();

    modelAgente = new QSqlTableModel(this);
    modelAgente->setTable("agenti");
    modelAgente->select();
}

void AnagraficaAddDialog::initComboBox()
{
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
    ui->cb_agente->setShown(false);
}

void AnagraficaAddDialog::prepareMap(void)
{
    mapPersona["rag_soc"] = ui->le_rag_sociale->text();
    mapPersona["tipo_ditta"] = modelDitta->index(ui->cb_tipo_ditta->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona["cliente"] = ui->cliente_cb->isChecked() ? "y" : "n";
    mapPersona["fornitore"] = ui->fornitore_cb->isChecked() ? "y" : "n";
    mapPersona["nome"] = ui->le_nome->text();
    mapPersona["cognome"] = ui->le_cognome->text();
    mapPersona["prt_iva"] = ui->le_piva->text();
    mapPersona["cod_fiscale"] = ui->le_cod_fiscale->text();
    mapPersona["agente"] = modelAgente->index(ui->cb_agente->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona["indirizzo"] = ui->le_indirizzo->text();
    mapPersona["id_citta"] = modelCitta->index(ui->cb_citta->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona["id_provincia"] = modelProvincia->index(ui->cb_provincia->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona["id_cap"]= modelCap->index(ui->cb_cap->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona["id_stato"]= modelStato->index(ui->cb_stato->currentIndex(), anagrafica::COL_ID).data().toString();
    mapPersona["tel"]= ui->le_tel->text();
    mapPersona["cel"]= ui->le_cel->text();
    mapPersona["fax"] = ui->le_fax->text();
    mapPersona["email"] = ui->le_email->text();
    mapPersona["web"] = ui->le_web->text();
    mapPersona["banca"] = ui->le_banca->text();
    mapPersona["agenzia"] = ui->le_agenzia->text();
    mapPersona["conto"] = ui->le_conto->text();
    mapPersona["swift"] = ui->le_swift->text();
    mapPersona["iban"] = ui->le_iban->text();
    mapPersona["dest_merce"] = ui->te_destinazione_merce->toPlainText();
    mapPersona["note"] = ui->te_note->toPlainText();
}

QSqlQuery AnagraficaAddDialog::prepareQuery(void)
{
    QSqlQuery query;
    if (mapPersona.contains("id")) {
        query.prepare(anagrafica::UPDATE_QUERY);
        query.bindValue(":id", mapPersona["id"]);
    }
    else {
        query.prepare(anagrafica::INSERT_QUERY);
    }

    query.bindValue(":fornitore",mapPersona["fornitore"]);
    query.bindValue(":cliente",mapPersona["cliente"]);
    query.bindValue(":rag_sociale",mapPersona["rag_soc"]);
    query.bindValue(":id_tipo_ditta",mapPersona["tipo_ditta"]);
    query.bindValue(":nome",mapPersona["nome"]);
    query.bindValue(":cognome",mapPersona["cognome"]);
    query.bindValue(":indirizzo",mapPersona["indirizzo"]);
    query.bindValue(":id_citta",mapPersona["id_citta"]);
    query.bindValue(":id_provincia",mapPersona["id_provincia"]);
    query.bindValue(":id_cap",mapPersona["id_cap"]);
    query.bindValue(":id_stato",mapPersona["id_stato"]);
    query.bindValue(":cod_fisc",mapPersona["cod_fiscale"]);
    query.bindValue(":prt_iva",mapPersona["prt_iva"]);
    query.bindValue(":id_agente",mapPersona["agente"]);
    query.bindValue(":tel",mapPersona["tel"]);
    query.bindValue(":fax",mapPersona["fax"]);
    query.bindValue(":cel",mapPersona["cel"]);
    query.bindValue(":email",mapPersona["email"]);
    query.bindValue(":sito_web",mapPersona["web"]);
    query.bindValue(":banca",mapPersona["banca"]);
    query.bindValue(":agenzia",mapPersona["agenzia"]);
    query.bindValue(":conto",mapPersona["conto"]);
    query.bindValue(":swift",mapPersona["swift"]);
    query.bindValue(":iban",mapPersona["iban"]);
    query.bindValue(":dest_merce",mapPersona["dest_merce"]);
    query.bindValue(":note",mapPersona["note"]);
    return query;
}

void AnagraficaAddDialog::save(void)
{
    prepareMap();

    if (mapPersona["rag_soc"].isEmpty()) {
        showDialogError(this, ERR020, MSG016); //NOTE codice errore 020
        ui->le_rag_sociale->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    else if (mapPersona["cliente"] == "n" && mapPersona["fornitore"] == "n") {
        showDialogError(this, ERR021, MSG017); //NOTE codice errore 021
        ui->cliente_cb->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        ui->fornitore_cb->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    else if (mapPersona["cod_fiscale"].isEmpty() || mapPersona["prt_iva"].isEmpty()) {
        showDialogError(this, ERR022, MSG018); //NOTE codice errore 022
        ui->le_cod_fiscale->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        ui->le_piva->setStyleSheet(anagrafica::CSS_WARNING_STYLE);
        return;
    }

    if (!controlloPartitaIva(mapPersona["prt_iva"])) {
        if (!showDialogWarning(this, ERR023, MSG019)) //NOTE codice errore 023
            return;
    }

    if (mapPersona["cod_fiscale"] != mapPersona["prt_iva"]) {
        if (!controlloCodiceFiscale(mapPersona["cod_fiscale"])) {
            if (!showDialogWarning(this, ERR024, MSG020)) //NOTE codice errore 024
                return;
        }
    }

    QSqlQuery query = prepareQuery();
    if (!query.exec()) {
        if (mapPersona.contains("id")) {
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
    allDlg(this, modelDitta, ADD_DITTA_QUERY, "Tipologia Ditta", ERR015); //NOTE codice errore 015
}

void AnagraficaAddDialog::openAddCitta(void)
{
    allDlg(this, modelCitta, ADD_CITTA_QUERY, "Città", ERR016); //NOTE codice errore 016
}

void AnagraficaAddDialog::openAddProvincia(void)
{
    allDlg(this, modelProvincia, ADD_PROVINCIA_QUERY, "Provincia", ERR017); //NOTE codice errore 017
}

void AnagraficaAddDialog::openAddCap(void)
{
    allDlg(this, modelCap, ADD_CAP_QUERY, "CAP", ERR018); //NOTE codice errore 018
}

void AnagraficaAddDialog::openAddStato(void)
{
    allDlg(this, modelStato, ADD_STATO_QUERY, "Stato", ERR019); //NOTE codice errore 019
}

void AnagraficaAddDialog::openAddAgente(void)
{
    AgentiAddDialog dlg(this);
    bool ok = dlg.exec();
    if (ok) {
        modelAgente->select();
    }
}

void AnagraficaAddDialog::copyPrtIva(void)
{
    ui->le_cod_fiscale->setText(ui->le_piva->text());
}
