#include "articolodialog.h"
#include "ui_articolodialog.h"

const QString SELECT_FORNITORE = "SELECT \"Id\", \"Ragione sociale\" from vw_anagrafica_fornitori ORDER BY \"Ragione sociale\"";
const QString INSERT_ARTICOLO = "INSERT INTO magazzino (descr, id_fornitore, id_marca, modello, cod_articolo, cod_fornitore, cod_barre ,id_merce ,id_cod_iva, id_unita_misura, scorta_minima, quantita, prezzo_acquisto, sconto_fornitore, ricarico, imponibile, iva, prezzo_finito, prezzo_vendita, fattura, data_arrivo, id_sede_magazzino, note) VALUES (:descr, :id_fornitore, :id_marca, :modello, :cod_articolo, :cod_fornitore, :cod_barre, :id_merce, :id_cod_iva, :id_unita_merce, :scorta_minima, :quantita, :prezzo_acquisto, :sconto_fornitore, :ricarico, :imponibile, :iva, :prezzo_finito, :prezzo_vendita, :fattura, :data_arrivo, :id_sede_magazzino, :note)";
const QString INSERT_STORICO = "INSERT INTO listino_storico (id_articolo, data_arrivo, quantita, prezzo_acquisto, sconto_fornitore, ricarico, imponibile, iva, prezzo_finito, prezzo_vendita, fattura) VALUES (:id_articolo, :data_arrivo, :quantita, :prezzo_acquisto, :sconto_fornitore, :ricarico, :imponibile, :iva, :prezzo_finito, :prezzo_vendita, :fattura)";
const QString SELECT_FROM_ID = "SELECT * FROM magazzino WHERE id = :id";
const QString UPDATE_ARTICOLO = "UPDATE magazzino SET descr=:descr, id_fornitore=:id_fornitore, id_marca=:id_marca, modello=:modello, cod_articolo=:cod_articolo, cod_fornitore=:cod_fornitore, cod_barre=:cod_barre, id_merce=:id_merce, id_cod_iva=:id_cod_iva, id_unita_misura=:id_unita_merce, scorta_minima=:scorta_minima, quantita=:quantita, prezzo_acquisto=:prezzo_acquisto, sconto_fornitore=:sconto_fornitore, ricarico=:ricarico, imponibile=:imponibile, iva=:iva, prezzo_finito=:prezzo_finito, prezzo_vendita=:prezzo_vendita, fattura=:fattura, data_arrivo=:data_arrivo, id_sede_magazzino=:id_sede_magazzino, note=:note WHERE id=:id";


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
    ui->cb_catmerce->setModelColumn(magazzino::COL_DESCR);

    modelCodIva = new QSqlTableModel(this);
    modelCodIva->setTable("cod_iva");
    modelCodIva->select();
    ui->cb_codiva->setModel(modelCodIva);
    ui->cb_codiva->setModelColumn(magazzino::COL_DESCR);

    modelFornitore = new QSqlQueryModel(this);
    modelFornitore->setQuery(SELECT_FORNITORE);
    ui->cb_fornitore->setModel(modelFornitore);
    ui->cb_fornitore->setModelColumn(magazzino::COL_DESCR);

    modelMarca = new QSqlTableModel(this);
    modelMarca->setTable("marca");
    modelMarca->select();
    ui->cb_marca->setModel(modelMarca);
    ui->cb_marca->setModelColumn(magazzino::COL_DESCR);

    modelSede = new QSqlTableModel(this);
    modelSede->setTable("sede_magazzino");
    modelSede->select();
    ui->cb_sede->setModel(modelSede);
    ui->cb_sede->setModelColumn(magazzino::COL_DESCR);

    modelUnita = new QSqlTableModel(this);
    modelUnita->setTable("unita_misura");
    modelUnita->select();
    ui->cb_unitamisura->setModel(modelUnita);
    ui->cb_unitamisura->setModelColumn(magazzino::COL_DESCR);
}

void ArticoloDialog::setValue(QString id)
{
    QSqlQuery query;
    query.prepare(SELECT_FROM_ID);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "ERRORE: " << query.lastError().text(); //TODO definire codice errore
    }

    query.first();
    articolo["id"] = id;
    ui->le_descrizione->setText(query.value(magazzino::COL_DESCR).toString());

    ui->cb_fornitore->setModelColumn(magazzino::COL_ID);
    int index = ui->cb_fornitore->findText(query.value(magazzino::COL_ID_FORN).toString());
    ui->cb_fornitore->setModelColumn(magazzino::COL_DESCR);
    ui->cb_fornitore->setCurrentIndex(index);

    ui->cb_marca->setModelColumn(magazzino::COL_ID);
    index = ui->cb_marca->findText(query.value(magazzino::COL_ID_MARCA).toString());
    ui->cb_marca->setModelColumn(magazzino::COL_DESCR);
    ui->cb_marca->setCurrentIndex(index);

    ui->le_modello->setText(query.value(magazzino::COL_MODELLO).toString());
    ui->le_cod_articolo->setText(query.value(magazzino::COL_COD_ART).toString());
    ui->le_cod_fornitore->setText(query.value(magazzino::COL_COD_FOR).toString());
    ui->le_cod_barre->setText(query.value(magazzino::COL_COD_EAN).toString());

    ui->cb_catmerce->setModelColumn(magazzino::COL_ID);
    index = ui->cb_catmerce->findText(query.value(magazzino::COL_ID_MERCE).toString());
    ui->cb_catmerce->setModelColumn(magazzino::COL_DESCR);
    ui->cb_catmerce->setCurrentIndex(index);

    ui->cb_codiva->setModelColumn(magazzino::COL_ID);
    index = ui->cb_codiva->findText(query.value(magazzino::COL_ID_COD_IVA).toString());
    ui->cb_codiva->setModelColumn(magazzino::COL_DESCR);
    ui->cb_codiva->setCurrentIndex(index);

    ui->cb_unitamisura->setModelColumn(magazzino::COL_ID);
    index = ui->cb_unitamisura->findText(query.value(magazzino::COL_ID_UM).toString());
    ui->cb_unitamisura->setModelColumn(magazzino::COL_DESCR);
    ui->cb_unitamisura->setCurrentIndex(index);

    ui->le_scorta->setText(query.value(magazzino::COL_SCORTA).toString());
    ui->le_quantita->setText(query.value(magazzino::COL_QUANTITA).toString());
    ui->le_prezzo_acquisto->setText(locale().toCurrencyString(query.value(magazzino::COL_PREZZO_ACQ).toDouble()));
    ui->le_sconto->setText(query.value(magazzino::COL_SCONTO).toString());
    ui->le_ricarico->setText(query.value(magazzino::COL_RICARICO).toString());
    ui->le_imponibile->setText(locale().toCurrencyString(query.value(magazzino::COL_IMPONIBILE).toDouble()));
    ui->le_iva->setText(locale().toCurrencyString(query.value(magazzino::COL_IVA).toDouble()));

    ui->le_prezzo_finito->setText(locale().toCurrencyString(query.value(magazzino::COL_PREZZO_FIN).toDouble()));
    ui->le_prezzo_vendita->setText(locale().toCurrencyString(query.value(magazzino::COL_PREZZO_VEN).toDouble()));
    ui->le_fattura->setText(query.value(magazzino::COL_FATTURA).toString());
    ui->le_data->setDate(QDate::currentDate());

    ui->cb_sede->setModelColumn(magazzino::COL_ID);
    index = ui->cb_sede->findText(query.value(magazzino::COL_ID_SEDE).toString());
    ui->cb_sede->setModelColumn(magazzino::COL_DESCR);
    ui->cb_sede->setCurrentIndex(index);

    ui->te_note->setText(query.value(magazzino::COL_NOTE).toString());
}

void ArticoloDialog::prepareMap()
{
    articolo["descr"] = ui->le_descrizione->text();
    articolo["marca"] = modelMarca->index(ui->cb_marca->currentIndex(), magazzino::COL_ID).data().toString();
    articolo["modello"] = ui->le_modello->text();
    articolo["cod_articolo"] = ui->le_cod_articolo->text();
    articolo["cod_barre"] = ui->le_cod_barre->text();
    articolo["catmerce"] = modelCatMerce->index(ui->cb_catmerce->currentIndex(), magazzino::COL_ID).data().toString();
    articolo["unita"] = modelUnita->index(ui->cb_unitamisura->currentIndex(), magazzino::COL_ID).data().toString();

    //Per i tipi numeri devo usare il locale C. Maledetto postgresql
    double scorta = ui->le_scorta->text().toDouble();
    articolo["scorta"] = QString().setNum(scorta);

    articolo["id_fornitore"] = modelFornitore->index(ui->cb_fornitore->currentIndex(), magazzino::COL_ID).data().toString();
    articolo["cod_fornitore"] = ui->le_cod_fornitore->text();

    double quantita = ui->le_quantita->text().toDouble();
    articolo["quantita"] = QString().setNum(quantita);

    double prezzo_acq = ui->le_prezzo_acquisto->text().replace(locale().currencySymbol(),"").toDouble();
    articolo["prezzo_acquisto"] = QString().setNum(prezzo_acq);

    articolo["sconto"] =  ui->le_sconto->text();
    articolo["ricarico"] = ui->le_ricarico->text();

    double imponibile = ui->le_imponibile->text().replace(locale().currencySymbol(),"").toDouble();
    articolo["imponibile"] = QString().setNum(imponibile);
    articolo["codiva"] = modelCodIva->index(ui->cb_codiva->currentIndex(), magazzino::COL_ID).data().toString();
    double iva = ui->le_iva->text().replace(locale().currencySymbol(),"").toDouble();
    articolo["iva"] = QString().setNum(iva);
    double prezzo_vend = ui->le_prezzo_vendita->text().replace(locale().currencySymbol(),"").toDouble();
    articolo["prezzo_vendita"] = QString().setNum(prezzo_vend);
    double prezzo_fin = ui->le_prezzo_finito->text().replace(locale().currencySymbol(),"").toDouble();
    articolo["prezzo_finito"] = QString().setNum(prezzo_fin);

    articolo["sede_magazzino"] = modelSede->index(ui->cb_sede->currentIndex(), magazzino::COL_ID).data().toString();
    articolo["data"] = ui->le_data->date().toString("dd/MM/yyyy");
    articolo["nr_fattura"] = ui->le_fattura->text();
    articolo["note"] = ui->te_note->toPlainText();
}

QSqlQuery ArticoloDialog::prepareQueryArticolo(void)
{
    QSqlQuery query_articolo;
    if (articolo.contains("id")) {
        query_articolo.prepare(UPDATE_ARTICOLO);
        query_articolo.bindValue(":id", articolo["id"]);
    }
    else {
        query_articolo.prepare(INSERT_ARTICOLO);
    }

    query_articolo.bindValue(":descr", articolo["descr"]);
    query_articolo.bindValue(":id_marca", articolo["marca"]);
    query_articolo.bindValue(":modello", articolo["modello"]);
    query_articolo.bindValue(":cod_articolo", articolo["cod_articolo"]);
    query_articolo.bindValue(":cod_barre", articolo["cod_barre"]);
    query_articolo.bindValue(":id_merce", articolo["catmerce"]);
    query_articolo.bindValue(":id_unita_merce", articolo["unita"]);
    query_articolo.bindValue(":scorta_minima", articolo["scorta"]);

    query_articolo.bindValue(":id_fornitore", articolo["id_fornitore"]);
    query_articolo.bindValue(":cod_fornitore", articolo["cod_fornitore"]);
    query_articolo.bindValue(":quantita", articolo["quantita"]);
    query_articolo.bindValue(":prezzo_acquisto", articolo["prezzo_acquisto"]);
    query_articolo.bindValue(":sconto_fornitore", articolo["sconto"]);
    query_articolo.bindValue(":imponibile", articolo["imponibile"]);
    query_articolo.bindValue(":ricarico", articolo["ricarico"]);
    query_articolo.bindValue(":id_cod_iva", articolo["codiva"]);
    query_articolo.bindValue(":iva", articolo["iva"]);
    query_articolo.bindValue(":prezzo_finito", articolo["prezzo_finito"]);
    query_articolo.bindValue(":prezzo_vendita", articolo["prezzo_vendita"]);

    query_articolo.bindValue(":id_sede_magazzino", articolo["sede_magazzino"]);
    query_articolo.bindValue(":data_arrivo", articolo["data"]);
    query_articolo.bindValue(":fattura", articolo["nr_fattura"]);
    query_articolo.bindValue(":note", articolo["note"]);
    return query_articolo;
}

QSqlQuery ArticoloDialog::prepareQueryStorico(void)
{
    QSqlQuery query_storico;
    query_storico.prepare(INSERT_STORICO);

    query_storico.bindValue(":data_arrivo", articolo["data"]);
    query_storico.bindValue(":quantita", articolo["quantita"]);
    query_storico.bindValue(":prezzo_acquisto", articolo["prezzo_acquisto"]);
    query_storico.bindValue(":sconto_fornitore", articolo["sconto"]);
    query_storico.bindValue(":ricarico", articolo["ricarico"]);
    query_storico.bindValue(":imponibile", articolo["imponibile"]);
    query_storico.bindValue(":iva", articolo["iva"]);
    query_storico.bindValue(":prezzo_finito", articolo["prezzo_finito"]);
    query_storico.bindValue(":prezzo_vendita", articolo["prezzo_vendita"]);
    query_storico.bindValue(":fattura", articolo["nr_fattura"]);

    return query_storico;
}

void ArticoloDialog::save(void)
{
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();
    prepareMap();
    QSqlQuery query_articolo = prepareQueryArticolo();
    if (!query_articolo.exec()) {
        qDebug() << "errore: " << query_articolo.lastError();
        db.rollback();
        return;
    }
    if (!articolo.contains("id")) {
        QSqlQuery query_id;
        query_id.prepare("SELECT * FROM lastval();");
        if (!query_id.exec()) {
            qDebug() << "errore: " << query_id.lastError();
            db.rollback();
            return;
        }
        query_id.first();
        articolo["id"] = query_id.value(0).toString();
    }

    QSqlQuery query_storico = prepareQueryStorico();
    query_storico.bindValue(":id_articolo", articolo["id"]);
    if (!query_storico.exec()) {
        qDebug() << "errore storico: " << articolo["id"] << query_storico.lastError();
        db.rollback();
        return;
    }

    db.commit();
    this->accept();
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

void ArticoloDialog::openAddMarca()
{
    allDlg(this, modelMarca, ADD_MARCA_QUERY, "Marca", ""); //TODO definire codice errore
}

void ArticoloDialog::openAddCategoria()
{
    allDlg(this, modelCatMerce, ADD_CAT_MERCE_QUERY, "Categoria merce", ""); //TODO definire codice errore
}

void ArticoloDialog::openAddMisura()
{
    allDlg(this, modelUnita, ADD_UM_QUERY, "Unita di misura", ""); //TODO definire codice errore
}

void ArticoloDialog::openAddFornitore()
{
    qDebug() << "open fornitore dialog";  //TODO richiamare dialog fornitore
}

void ArticoloDialog::openAddIVA()
{
    allDlg(this, modelCodIva, ADD_IVA_QUERY, "Codice IVA", ""); //TODO definire codice errore
}

void ArticoloDialog::openAddSede()
{
    allDlg(this, modelSede, ADD_SEDE_QUERY, "Sede magazzino", ""); //TODO definire codice errore
}
