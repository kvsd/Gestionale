#include "aziendadialog.h"
#include "ui_aziendadialog.h"

const QString SELECT_QUERY = "SELECT * FROM azienda WHERE id=0";
const QString UPDATE_QUERY = "UPDATE azienda SET rag_sociale=:rag_sociale, \
                                                 nome=:nome, \
                                                 cognome=:cognome,\
                                                 indirizzo=:indirizzo, \
                                                 id_citta=:id_citta, \
                                                 id_provincia=:id_provincia, \
                                                 id_cap=:id_cap, \
                                                 id_stato=:stato, \
                                                 tel=:tel, \
                                                 fax=:fax, \
                                                 email=:email, \
                                                 prt_iva=:prt_iva,\
                                                 cod_fisc=:cod_fisc,\
                                                 iscr_trib=:iscr_trib,\
                                                 cciaa=:cciaa WHERE id=0";

const QString CSS_WARNING_STYLE = "background-color:yellow";

AziendaDialog::AziendaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AziendaDialog)
{
    ui->setupUi(this);

    modelCitta = new QSqlTableModel(this);
    modelCitta->setTable(table::CITTA);
    modelCitta->select();
    ui->cb_citta->setModel(modelCitta);
    ui->cb_citta->setModelColumn(azienda::COL_DESCR);

    modelProvincia = new QSqlTableModel(this);
    modelProvincia->setTable(table::PROVINCIA);
    modelProvincia->select();
    ui->cb_provincia->setModel(modelProvincia);
    ui->cb_provincia->setModelColumn(azienda::COL_DESCR);

    modelCap = new QSqlTableModel(this);
    modelCap->setTable(table::CAP);
    modelCap->select();
    ui->cb_cap->setModel(modelCap);
    ui->cb_cap->setModelColumn(azienda::COL_DESCR);

    modelStato = new QSqlTableModel(this);
    modelStato->setTable(table::STATO);
    modelStato->select();
    ui->cb_stato->setModel(modelStato);
    ui->cb_stato->setModelColumn(azienda::COL_DESCR);

    setValue();
}

AziendaDialog::~AziendaDialog()
{
    delete ui;
}

void AziendaDialog::open_add_citta(void)
{
    allDlg(this, modelCitta, ADD_CITTA_QUERY, "Città", ERR016); //NOTE codice errore 016.1
}

void AziendaDialog::open_add_provincia(void)
{
    allDlg(this, modelProvincia, ADD_PROVINCIA_QUERY, "Provincia", ERR017); //NOTE codice errore 017.1
}

void AziendaDialog::open_add_cap(void)
{
    allDlg(this, modelCap, ADD_CAP_QUERY, "CAP", ERR018); //NOTE codice errore 018.1
}

void AziendaDialog::open_add_stato(void)
{
    allDlg(this, modelStato, ADD_STATO_QUERY, "Stato", ERR019); //NOTE codice errore 019.1
}

void AziendaDialog::setValue(QString id)
{
    QSqlQuery query;
    query.prepare(SELECT_QUERY);
    query.bindValue(":id", id);
    query.exec();
    query.first();

    ui->le_rag_sociale->setText(query.value(azienda::COL_RAG_SOC).toString());
    ui->le_nome->setText(query.value(azienda::COL_NOME).toString());
    ui->le_cognome->setText(query.value(azienda::COL_COGNOME).toString());
    ui->le_prtiva->setText(query.value(azienda::COL_PRT_IVA).toString());
    ui->le_codfisc->setText(query.value(azienda::COL_COD_FISC).toString());
    ui->le_indirizzo->setText(query.value(azienda::COL_INDIRIZZO).toString());

    ui->cb_citta->setModelColumn(azienda::COL_ID);
    int index = ui->cb_citta->findText(query.value(azienda::COL_CITTA).toString());
    ui->cb_citta->setModelColumn(azienda::COL_DESCR);
    ui->cb_citta->setCurrentIndex(index);

    ui->cb_provincia->setModelColumn(azienda::COL_ID);
    index = ui->cb_provincia->findText(query.value(azienda::COL_PROVINCIA).toString());
    ui->cb_provincia->setModelColumn(azienda::COL_DESCR);
    ui->cb_provincia->setCurrentIndex(index);

    ui->cb_cap->setModelColumn(azienda::COL_ID);
    index = ui->cb_cap->findText(query.value(azienda::COL_CAP).toString());
    ui->cb_cap->setModelColumn(azienda::COL_DESCR);
    ui->cb_cap->setCurrentIndex(index);

    ui->cb_stato->setModelColumn(azienda::COL_ID);
    index = ui->cb_stato->findText(query.value(azienda::COL_STATO).toString());
    ui->cb_stato->setModelColumn(azienda::COL_DESCR);
    ui->cb_stato->setCurrentIndex(index);

    ui->le_tel->setText(query.value(azienda::COL_TEL).toString());
    ui->le_fax->setText(query.value(azienda::COL_FAX).toString());
    ui->le_email->setText(query.value(azienda::COL_EMAIL).toString());

    ui->le_cciaa->setText(query.value(azienda::COL_CCIAA).toString());
    ui->le_iscr_trib->setText(query.value(azienda::COL_TRIB).toString());
}

void AziendaDialog::prepareMap(void)
{
    azienda["rag_sociale"] = ui->le_rag_sociale->text();
    azienda["nome"] = ui->le_nome->text();
    azienda["cognome"] = ui->le_cognome->text();
    azienda["indirizzo"] = ui->le_indirizzo->text();
    azienda["id_citta"] = modelCitta->index(ui->cb_citta->currentIndex(), azienda::COL_ID).data().toString();
    azienda["id_provincia"] = modelProvincia->index(ui->cb_provincia->currentIndex(), azienda::COL_ID).data().toString();
    azienda["id_cap"] = modelCap->index(ui->cb_cap->currentIndex(), azienda::COL_ID).data().toString();
    azienda["id_stato"] = modelStato->index(ui->cb_stato->currentIndex(), azienda::COL_ID).data().toString();
    azienda["tel"] = ui->le_tel->text();
    azienda["fax"] = ui->le_fax->text();
    azienda["email"] = ui->le_email->text();
    azienda["prt_iva"] = ui->le_prtiva->text();
    azienda["cod_fisc"] = ui->le_codfisc->text();
    azienda["iscr_trib"] = ui->le_iscr_trib->text();
    azienda["cciaa"] = ui->le_cciaa->text();
}

void AziendaDialog::save(void)
{
    prepareMap();    

    if (azienda["rag_sociale"].isEmpty()) {
        showDialogError(this, ERR029, MSG016); //NOTE codice errore 029
        ui->le_rag_sociale->setStyleSheet(CSS_WARNING_STYLE);
        return;
    }
    else if (azienda["indirizzo"].isEmpty()) {
        showDialogError(this, ERR030, MSG014); //NOTE codice errore 030
        ui->le_indirizzo->setStyleSheet(CSS_WARNING_STYLE);
        return;
    }
    else if (azienda["prt_iva"].isEmpty() || azienda["cod_fisc"].isEmpty()) {
        showDialogError(this, ERR031, MSG018); //NOTE codice errore 031
        ui->le_prtiva->setStyleSheet(CSS_WARNING_STYLE);
        ui->le_codfisc->setStyleSheet(CSS_WARNING_STYLE);
        return;
    }



    if (!controlloPartitaIva(azienda["prt_iva"])) {
        if (!showDialogWarning(this, ERR032, MSG019)) //NOTE codice errore 032
            return;
    }

    if (azienda["cod_fisc"] != azienda["prt_iva"]) {
        if (!controlloCodiceFiscale(azienda["cod_fisc"])) {
            if (!showDialogWarning(this, ERR033, MSG020)) //NOTE codice errore 033
                return;
        }
    }

    QSqlQuery query;
    query.prepare(UPDATE_QUERY);
    query.bindValue(":rag_sociale", azienda["rag_sociale"]);
    query.bindValue(":nome", azienda["nome"]);
    query.bindValue(":cognome", azienda["cognome"]);
    query.bindValue(":indirizzo", azienda["indirizzo"]);
    query.bindValue(":id_citta", azienda["id_citta"]);
    query.bindValue(":id_provincia", azienda["id_provincia"]);
    query.bindValue(":id_cap", azienda["id_cap"]);
    query.bindValue(":id_stato", azienda["id_stato"]);
    query.bindValue(":tel", azienda["tel"]);
    query.bindValue(":fax", azienda["fax"]);
    query.bindValue(":email", azienda["email"]);
    query.bindValue(":prt_iva", azienda["prt_iva"]);
    query.bindValue(":cod_fisc", azienda["cod_fisc"]);
    query.bindValue(":iscr_trib", azienda["iscr_trib"]);
    query.bindValue(":cciaa", azienda["cciaa"]);

    if (!query.exec()) {
        showDialogError(this, ERR012, MSG005, query.lastError().text()); //NOTE codice errore 012
        return;
    }
    this->accept();
}

void AziendaDialog::clearCombobox(void)
{
    ui->cb_citta->setCurrentIndex(0);
    ui->cb_provincia->setCurrentIndex(0);
    ui->cb_cap->setCurrentIndex(0);
    ui->cb_stato->setCurrentIndex(0);
}

void AziendaDialog::copy_prt_iva(void)
{
    QString prtiva = ui->le_prtiva->text();
    ui->le_codfisc->setText(prtiva);
}
