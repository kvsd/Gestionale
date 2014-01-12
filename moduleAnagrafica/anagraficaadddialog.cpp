#include "moduleAnagrafica/anagraficaadddialog.h"
#include "ui_anagraficaadddialog.h"

const QString INSERT_QUERY = "INSERT INTO anagrafica(fornitore, cliente, rag_sociale, id_tipo_ditta, nome, cognome, indirizzo, id_citta, id_provincia, id_cap, id_stato, cod_fisc, prt_iva, id_agente, tel, fax, cel, email, sito_web, banca, agenzia, conto, swift, iban, dest_merce, note) VALUES(:fornitore, :cliente, :rag_sociale, :id_tipo_ditta, :nome, :cognome, :indirizzo, :id_citta, :id_provincia, :id_cap, :id_stato, :cod_fisc, :prt_iva, :id_agente, :tel, :fax, :cel, :email, :sito_web, :banca, :agenzia, :conto, :swift, :iban, :dest_merce, :note)";
const QString UPDATE_QUERY = "UPDATE anagrafica SET fornitore=:fornitore, cliente=:cliente, rag_sociale=:rag_sociale, id_tipo_ditta=:id_tipo_ditta, nome=:nome, cognome=:cognome, indirizzo=:indirizzo, id_citta=:id_citta, id_provincia=:id_provincia, id_cap=:id_cap, id_stato=:id_stato, cod_fisc=:cod_fisc, prt_iva=:prt_iva, id_agente=:id_agente, tel=:tel, fax=:fax, cel=:cel, email=:email, sito_web=:sito_web, banca=:banca, agenzia=:agenzia, conto=:conto, swift=:swift, iban=:iban, dest_merce=:dest_merce, note=:note WHERE id=:id";
const QString SELECT_QUERY = "SELECT * FROM anagrafica WHERE id=:id";

const QString CSS_WARNING_STYLE = "background-color:yellow";

AnagraficaAddDialog::AnagraficaAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnagraficaAddDialog)
{
    ui->setupUi(this); 

    model_tipo_ditta = new QSqlTableModel(this);
    model_tipo_ditta->setTable("tipo_ditta");
    model_tipo_ditta->select();
    ui->cb_tipo_ditta->setModel(model_tipo_ditta);
    ui->cb_tipo_ditta->setModelColumn(anagrafica::COL_MODEL_DESCR);

    model_citta = new QSqlTableModel(this);
    model_citta->setTable("citta");
    model_citta->select();
    ui->cb_citta->setModel(model_citta);
    ui->cb_citta->setModelColumn(anagrafica::COL_MODEL_DESCR);

    model_provincia = new QSqlTableModel(this);
    model_provincia->setTable("provincia");
    model_provincia->select();
    ui->cb_provincia->setModel(model_provincia);
    ui->cb_provincia->setModelColumn(anagrafica::COL_MODEL_DESCR);

    model_cap = new QSqlTableModel(this);
    model_cap->setTable("cap");
    model_cap->select();
    ui->cb_cap->setModel(model_cap);
    ui->cb_cap->setModelColumn(anagrafica::COL_MODEL_DESCR);

    model_stato = new QSqlTableModel(this);
    model_stato->setTable("stato");
    model_stato->select();
    ui->cb_stato->setModel(model_stato);
    ui->cb_stato->setModelColumn(anagrafica::COL_MODEL_DESCR);

    model_agente = new QSqlTableModel(this);
    model_agente->setTable("agenti");
    model_agente->select();
    ui->cb_agente->setModel(model_agente);
    ui->cb_agente->setModelColumn(anagrafica::COL_MODEL_COGNOME);

    ui->cb_agente->setShown(false);
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
    query.prepare(SELECT_QUERY);
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

    persona["id"]=id;

}

void AnagraficaAddDialog::prepareMap(void)
{
    persona["rag_soc"] = ui->le_rag_sociale->text();
    persona["tipo_ditta"] = model_tipo_ditta->index(ui->cb_tipo_ditta->currentIndex(), anagrafica::COL_ID).data().toString();
    persona["cliente"] = ui->cliente_cb->isChecked() ? "y" : "n";
    persona["fornitore"] = ui->fornitore_cb->isChecked() ? "y" : "n";
    persona["nome"] = ui->le_nome->text();
    persona["cognome"] = ui->le_cognome->text();
    persona["prt_iva"] = ui->le_piva->text();
    persona["cod_fiscale"] = ui->le_cod_fiscale->text();
    persona["agente"] = model_agente->index(ui->cb_agente->currentIndex(), anagrafica::COL_ID).data().toString();
    persona["indirizzo"] = ui->le_indirizzo->text();
    persona["id_citta"] = model_citta->index(ui->cb_citta->currentIndex(), anagrafica::COL_ID).data().toString();
    persona["id_provincia"] = model_provincia->index(ui->cb_provincia->currentIndex(), anagrafica::COL_ID).data().toString();
    persona["id_cap"]= model_cap->index(ui->cb_cap->currentIndex(), anagrafica::COL_ID).data().toString();
    persona["id_stato"]= model_stato->index(ui->cb_stato->currentIndex(), anagrafica::COL_ID).data().toString();
    persona["tel"]= ui->le_tel->text();
    persona["cel"]= ui->le_cel->text();
    persona["fax"] = ui->le_fax->text();
    persona["email"] = ui->le_email->text();
    persona["web"] = ui->le_web->text();
    persona["banca"] = ui->le_banca->text();
    persona["agenzia"] = ui->le_agenzia->text();
    persona["conto"] = ui->le_conto->text();
    persona["swift"] = ui->le_swift->text();
    persona["iban"] = ui->le_iban->text();
    persona["dest_merce"] = ui->te_destinazione_merce->toPlainText();
    persona["note"] = ui->te_note->toPlainText();
}

QSqlQuery AnagraficaAddDialog::prepareQuery(void)
{
    QSqlQuery query;
    if (persona.contains("id")) {
        query.prepare(UPDATE_QUERY);
        query.bindValue(":id", persona["id"]);
    }
    else {
        query.prepare(INSERT_QUERY);
    }

    query.bindValue(":fornitore",persona["fornitore"]);
    query.bindValue(":cliente",persona["cliente"]);
    query.bindValue(":rag_sociale",persona["rag_soc"]);
    query.bindValue(":id_tipo_ditta",persona["tipo_ditta"]);
    query.bindValue(":nome",persona["nome"]);
    query.bindValue(":cognome",persona["cognome"]);
    query.bindValue(":indirizzo",persona["indirizzo"]);
    query.bindValue(":id_citta",persona["id_citta"]);
    query.bindValue(":id_provincia",persona["id_provincia"]);
    query.bindValue(":id_cap",persona["id_cap"]);
    query.bindValue(":id_stato",persona["id_stato"]);
    query.bindValue(":cod_fisc",persona["cod_fiscale"]);
    query.bindValue(":prt_iva",persona["prt_iva"]);
    query.bindValue(":id_agente",persona["agente"]);
    query.bindValue(":tel",persona["tel"]);
    query.bindValue(":fax",persona["fax"]);
    query.bindValue(":cel",persona["cel"]);
    query.bindValue(":email",persona["email"]);
    query.bindValue(":sito_web",persona["web"]);
    query.bindValue(":banca",persona["banca"]);
    query.bindValue(":agenzia",persona["agenzia"]);
    query.bindValue(":conto",persona["conto"]);
    query.bindValue(":swift",persona["swift"]);
    query.bindValue(":iban",persona["iban"]);
    query.bindValue(":dest_merce",persona["dest_merce"]);
    query.bindValue(":note",persona["note"]);
    return query;
}

void AnagraficaAddDialog::save(void)
{
    prepareMap();

    if (persona["rag_soc"].isEmpty()) {
        showDialogError(this, ERR020, MSG016); //NOTE codice errore 020
        ui->le_rag_sociale->setStyleSheet(CSS_WARNING_STYLE);
        return;
    }

    else if (persona["cliente"] == "n" && persona["fornitore"] == "n") {
        showDialogError(this, ERR021, MSG017); //NOTE codice errore 021
        ui->cliente_cb->setStyleSheet(CSS_WARNING_STYLE);
        ui->fornitore_cb->setStyleSheet(CSS_WARNING_STYLE);
        return;
    }

    else if (persona["cod_fiscale"].isEmpty() || persona["prt_iva"].isEmpty()) {
        showDialogError(this, ERR022, MSG018); //NOTE codice errore 022
        ui->le_cod_fiscale->setStyleSheet(CSS_WARNING_STYLE);
        ui->le_piva->setStyleSheet(CSS_WARNING_STYLE);
        return;
    }

    if (!controlloPartitaIva(persona["prt_iva"])) {
        if (!showDialogWarning(this, ERR023, MSG019)) //NOTE codice errore 023
            return;
    }

    if (persona["cod_fiscale"] != persona["prt_iva"]) {
        if (!controlloCodiceFiscale(persona["cod_fiscale"])) {
            if (!showDialogWarning(this, ERR024, MSG020)) //NOTE codice errore 024
                return;
        }
    }

    QSqlQuery query = prepareQuery();
    if (!query.exec()) {
        if (persona.contains("id")) {
            showDialogError(this, ERR011, MSG005, query.lastError().text()); //NOTE codice errore 011
        }
        else {
            showDialogError(this, ERR025, MSG002, query.lastError().text()); //NOTE codice errore 025
        }
        return;
    }

    this->accept();
}


void AnagraficaAddDialog::open_add_tipoditta(void)
{
    allDlg(this, model_tipo_ditta, ADD_DITTA_QUERY, "Tipologia Ditta", ERR015); //NOTE codice errore 015
}

void AnagraficaAddDialog::open_add_citta(void)
{
    allDlg(this, model_citta, ADD_CITTA_QUERY, "Città", ERR016); //NOTE codice errore 016
}

void AnagraficaAddDialog::open_add_provincia(void)
{
    allDlg(this, model_provincia, ADD_PROVINCIA_QUERY, "Provincia", ERR017); //NOTE codice errore 017
}

void AnagraficaAddDialog::open_add_cap(void)
{
    allDlg(this, model_cap, ADD_CAP_QUERY, "CAP", ERR018); //NOTE codice errore 018
}

void AnagraficaAddDialog::open_add_stato(void)
{
    allDlg(this, model_stato, ADD_STATO_QUERY, "Stato", ERR019); //NOTE codice errore 019
}

void AnagraficaAddDialog::open_add_agente(void)
{
    AgentiAddDialog dlg(this);
    bool ok = dlg.exec();
    if (ok) {
        model_agente->select();
    }
}

void AnagraficaAddDialog::copy_prt_iva(void)
{
    ui->le_cod_fiscale->setText(ui->le_piva->text());
}
