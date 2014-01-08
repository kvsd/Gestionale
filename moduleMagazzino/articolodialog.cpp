#include "articolodialog.h"
#include "ui_articolodialog.h"

const QString SELECT_FORNITORE = "SELECT \"Id\", \"Ragione sociale\" from vw_anagrafica_fornitori ORDER BY \"Ragione sociale\"";
const QString INSERT_ARTICOLO = "";
const QString INSERT_LISTINO = "";

enum columns {COL_ID,
              COL_DESCR = 1};

ArticoloDialog::ArticoloDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArticoloDialog)
{
    ui->setupUi(this);

    initModel();

    ui->le_data->setDate(QDate::currentDate());
}

ArticoloDialog::~ArticoloDialog()
{
    delete ui;
}

void ArticoloDialog::initModel(void)
{
    modelCatMerce = new QSqlTableModel(this);
    modelCatMerce->setTable("cat_merce");
    modelCatMerce->select();
    ui->cb_catmerce->setModel(modelCatMerce);
    ui->cb_catmerce->setModelColumn(COL_DESCR);

    modelCodIva = new QSqlTableModel(this);
    modelCodIva->setTable("cod_iva");
    modelCodIva->select();
    ui->cb_codiva->setModel(modelCodIva);
    ui->cb_codiva->setModelColumn(COL_DESCR);

    modelFornitore = new QSqlQueryModel(this);
    modelFornitore->setQuery(SELECT_FORNITORE);
    ui->cb_fornitore->setModel(modelFornitore);
    ui->cb_fornitore->setModelColumn(COL_DESCR);

    modelMarca = new QSqlTableModel(this);
    modelMarca->setTable("marca");
    modelMarca->select();
    ui->cb_marca->setModel(modelMarca);
    ui->cb_marca->setModelColumn(COL_DESCR);

    modelSede = new QSqlTableModel(this);
    modelSede->setTable("sede_magazzino");
    modelSede->select();
    ui->cb_sede->setModel(modelSede);
    ui->cb_sede->setModelColumn(COL_DESCR);

    modelUnita = new QSqlTableModel(this);
    modelUnita->setTable("unita_misura");
    modelUnita->select();
    ui->cb_unitamisura->setModel(modelUnita);
    ui->cb_unitamisura->setModelColumn(COL_DESCR);
}

void ArticoloDialog::prepareMap()
{
    articolo["descr"] = ui->le_descrizione->text();
    articolo["marca"] = modelMarca->index(ui->cb_marca->currentIndex(), COL_ID).data().toString();
    articolo["modello"] = ui->le_modello->text();
    articolo["cod_articolo"] = ui->le_cod_articolo->text();
    articolo["cod_barre"] = ui->le_cod_barre->text();
    articolo["catmerce"] = modelCatMerce->index(ui->cb_catmerce->currentIndex(), COL_ID).data().toString();
    articolo["unita"] = modelUnita->index(ui->cb_unitamisura->currentIndex(), COL_ID).data().toString();
    articolo["codiva"] = modelCodIva->index(ui->cb_codiva->currentIndex(), COL_ID).data().toString();
    articolo["scorta"] = ui->le_scorta->text();

    articolo["id_fornitore"] = modelFornitore->index(ui->cb_fornitore->currentIndex(), COL_ID).data().toString();
    articolo["cod_fornitore"] = ui->le_cod_fornitore->text();
    articolo["quantita"] = ui->le_quantita->text();
    articolo["prezzo_acquisto"] = ui->le_prezzo_acquisto->text();
    articolo["sconto"] = ui->le_sconto->text();
    articolo["imponibile"] = ui->le_imponibile->text();
    articolo["ricarico"] = ui->le_ricarico->text();
    articolo["iva"] = ui->le_iva->text();
    articolo["prezzo_vendita"] = ui->le_prezzo_vendita->text();
    articolo["prezzo_finito"] = ui->le_prezzo_finito->text();

    articolo["sede_magazzino"] = modelSede->index(ui->cb_sede->currentIndex(), COL_ID).data().toString();
    articolo["data"] = ui->le_data->date().toString();
    articolo["note"] = ui->te_note->toPlainText();
}

void ArticoloDialog::prepareQuery(void)
{
    prepareMap();
    QSqlQuery query_articolo;
    query_articolo.bindValue(":id", articolo["id"]);
    query_articolo.bindValue(":descr", articolo["descr"]);
    query_articolo.bindValue(":id_marca", articolo["marca"]);
    query_articolo.bindValue(":modello", articolo["modello"]);
    query_articolo.bindValue(":cod_articolo", articolo["cod_articolo"]);
    query_articolo.bindValue(":cod_barre", articolo["cod_barre"]);
    query_articolo.bindValue(":id_merce", articolo["catmerce"]);
    query_articolo.bindValue(":id_unita_merce", articolo["unita"]);
    query_articolo.bindValue(":scorta_minima", articolo["scorta"]);
    query_articolo.bindValue(":id_cod_iva", articolo["codiva"]);
    query_articolo.bindValue(":id_sede_magazzino", articolo["sede_magazzino"]);
    query_articolo.bindValue(":note", articolo["note"]);
    query_articolo.bindValue(":id_articolo", articolo[""]);
    query_articolo.bindValue(":id_fornitore", articolo["id_fornitore"]);
    query_articolo.bindValue(":cod_fornitore", articolo["cod_fornitore"]);
    query_articolo.bindValue(":data_arrivo", articolo["data"]);
    query_articolo.bindValue(":quantita", articolo["quantita"]);
    query_articolo.bindValue(":prezzo_acquisto", articolo["prezzo_acquisto"]);
    query_articolo.bindValue(":sconto_fornitore", articolo["sconto"]);
    query_articolo.bindValue(":imponibile", articolo["imponibile"]);
    query_articolo.bindValue(":ricarico", articolo["ricarico"]);
    query_articolo.bindValue(":iva", articolo["iva"]);
    query_articolo.bindValue(":prezzo_finito", articolo["prezzo_finito"]);
    query_articolo.bindValue(":prezzo_vendita", articolo["prezzo_vendita"]);
    query_articolo.bindValue(":fattura", articolo[""]);
}

void ArticoloDialog::updatePrezzoAcquisto(void)
{
    QString prezzo_str = ui->le_prezzo_acquisto->text();

    if (!prezzo_str.contains(locale().currencySymbol())) {
            ui->le_prezzo_acquisto->setText(locale().toCurrencyString(prezzo_str.toDouble()));
    }
    updateImponibile();
}

void ArticoloDialog::updateImponibile(void)
{
    QString prezzo_str = ui->le_prezzo_acquisto->text().replace(locale().currencySymbol(),"");
    if (prezzo_str.isEmpty()) {
        return;
    }

    QString sconto_str = ui->le_sconto->text().replace("%", "");

    double imponibile = prezzo_str.toDouble();
    double sconto = 0;

    if (sconto_str.contains("+")) {
        QStringList sconti = sconto_str.split("+");
        QString s;
        foreach(s, sconti) {
            sconto = s.toDouble()/100.0;
            imponibile -= imponibile*sconto;
        }
    }
    else {
        sconto = sconto_str.toDouble()/100.0;
        imponibile -= imponibile*sconto;
    }

    QString ricarico_str = ui->le_ricarico->text().replace("%","");
    double ricarico = 0;
    if (ricarico_str.contains("+")) {
        QStringList ricarichi = ricarico_str.split("+");
        QString s;
        foreach(s, ricarichi) {
            ricarico = s.toDouble()/100;
            imponibile += imponibile*ricarico;
        }
    }
    else {
        ricarico = ricarico_str.toDouble()/100;
        imponibile += imponibile*ricarico;
    }

    ui->le_imponibile->setText(locale().toCurrencyString(imponibile));
    updateIva();
}

void ArticoloDialog::updateIva(void)
{
    if (ui->le_prezzo_acquisto->text().isEmpty() || ui->le_ricarico->text().isEmpty()) {
        return;
    }

    double imponibile = ui->le_imponibile->text().replace(locale().currencySymbol(), "").toDouble();
    double codiva = ui->cb_codiva->currentText().toDouble()/100.0;

    double iva = imponibile*codiva;
    ui->le_iva->setText(locale().toCurrencyString(iva));

    double prezzo_vendita = imponibile+iva;
    ui->le_prezzo_vendita->setText(locale().toCurrencyString(prezzo_vendita));
    ui->le_prezzo_finito->setText(locale().toCurrencyString(prezzo_vendita));
}

void ArticoloDialog::updatePrezzoFinito(void)
{
    if (ui->le_prezzo_acquisto->text().isEmpty()) {
        return;
    }

    QString prezzo = ui->le_prezzo_finito->text();
    if (!prezzo.contains(locale().currencySymbol())) {
        ui->le_prezzo_finito->setText(locale().toCurrencyString(prezzo.toDouble()));
    }
}
