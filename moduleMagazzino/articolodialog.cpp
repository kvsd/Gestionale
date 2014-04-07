#include "articolodialog.h"
#include "ui_articolodialog.h"

ArticoloDialog::ArticoloDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArticoloDialog)
{
    ui->setupUi(this);

    initModel();
    initComboBox();

    ui->le_data->setDate(QDate::currentDate());
}

ArticoloDialog::~ArticoloDialog()
{
    delete ui;
}

void ArticoloDialog::initModel(void)
{
    modelCatMerce = new QSqlTableModel(this);
    modelCatMerce->setTable(table::CATEGORIA_MERCE);
    modelCatMerce->select();

    modelCodIva = new QSqlTableModel(this);
    modelCodIva->setTable(table::CODICE_IVA);
    modelCodIva->select();

    modelFornitore = new QSqlQueryModel(this);
    modelFornitore->setQuery(magazzino::SELECT_FORNITORE);

    modelMarca = new QSqlTableModel(this);
    modelMarca->setTable(table::MARCA);
    modelMarca->select();

    modelSede = new QSqlTableModel(this);
    modelSede->setTable(table::SEDE_MAGAZZINO);
    modelSede->select();

    modelUnita = new QSqlTableModel(this);
    modelUnita->setTable(table::UNITA_MISURA);
    modelUnita->select();

}

void ArticoloDialog::initComboBox(void)
{
    ui->cb_catmerce->setModel(modelCatMerce);
    ui->cb_catmerce->setModelColumn(magazzino::COL_DESCR);

    ui->cb_codiva->setModel(modelCodIva);
    ui->cb_codiva->setModelColumn(magazzino::COL_DESCR);
    int index = ui->cb_codiva->findText(settings.value(magazzino::DEFAULT_IVA).toString());
    ui->cb_codiva->setCurrentIndex(index);

    ui->cb_fornitore->setModel(modelFornitore);
    ui->cb_fornitore->setModelColumn(magazzino::COL_DESCR);

    ui->cb_marca->setModel(modelMarca);
    ui->cb_marca->setModelColumn(magazzino::COL_DESCR);

    ui->cb_sede->setModel(modelSede);
    ui->cb_sede->setModelColumn(magazzino::COL_DESCR);

    ui->cb_unitamisura->setModel(modelUnita);
    ui->cb_unitamisura->setModelColumn(magazzino::COL_DESCR);
}

void ArticoloDialog::setValue(QString id)
{
    QSqlQuery query;
    query.prepare(magazzino::SELECT_FROM_ID);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "ERRORE: " << query.lastError().text(); //TODO definire codice errore
    }

    query.first();
    articolo[keymap::KEY_ID] = id;
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
    ui->le_prezzo_fattura->setText(locale().toCurrencyString(query.value(magazzino::COL_PREZZO_FATTURA).toDouble()));
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
    articolo[keymap::KEY_DESCRIZIONE] = ui->le_descrizione->text();
    articolo[keymap::KEY_MARCA] = modelMarca->index(ui->cb_marca->currentIndex(), magazzino::COL_ID).data().toString();
    articolo[keymap::KEY_MODELLO] = ui->le_modello->text();
    articolo[keymap::KEY_COD_ARTICOLO] = ui->le_cod_articolo->text();
    articolo[keymap::KEY_COD_BARRE] = ui->le_cod_barre->text();
    articolo[keymap::KEY_CATMERCE] = modelCatMerce->index(ui->cb_catmerce->currentIndex(), magazzino::COL_ID).data().toString();
    articolo[keymap::KEY_UNITA] = modelUnita->index(ui->cb_unitamisura->currentIndex(), magazzino::COL_ID).data().toString();

    //Per i tipi numeri devo usare il locale C. Maledetto postgresql
    double scorta = ui->le_scorta->text().toDouble();
    articolo[keymap::KEY_SCORTA] = QString().setNum(scorta);

    articolo[keymap::KEY_ID_FORNITORE] = modelFornitore->index(ui->cb_fornitore->currentIndex(), magazzino::COL_ID).data().toString();
    articolo[keymap::KEY_COD_FORNITORE] = ui->le_cod_fornitore->text();

    double quantita = ui->le_quantita->text().toDouble();
    articolo[keymap::KEY_QUANTITA] = QString().setNum(quantita);

    double prezzo_fattura = ui->le_prezzo_fattura->text().replace(locale().currencySymbol(),"").toDouble();
    articolo[keymap::KEY_PRZ_FATTURA] = QString().setNum(prezzo_fattura);

    articolo[keymap::KEY_SCONTO] =  ui->le_sconto->text();
    articolo[keymap::KEY_RICARICO] = ui->le_ricarico->text();

    double imponibile = ui->le_imponibile->text().replace(locale().currencySymbol(),"").toDouble();
    articolo[keymap::KEY_IMPONIBILE] = QString().setNum(imponibile);
    articolo[keymap::KEY_COD_IVA] = modelCodIva->index(ui->cb_codiva->currentIndex(), magazzino::COL_ID).data().toString();
    double iva = ui->le_iva->text().replace(locale().currencySymbol(),"").toDouble();
    articolo[keymap::KEY_IVA] = QString().setNum(iva);
    double prezzo_vend = ui->le_prezzo_vendita->text().replace(locale().currencySymbol(),"").toDouble();
    articolo[keymap::KEY_PRZ_VENDITA] = QString().setNum(prezzo_vend);
    double prezzo_fin = ui->le_prezzo_finito->text().replace(locale().currencySymbol(),"").toDouble();
    articolo[keymap::KEY_PRZ_FINITO] = QString().setNum(prezzo_fin);

    articolo[keymap::KEY_SEDE] = modelSede->index(ui->cb_sede->currentIndex(), magazzino::COL_ID).data().toString();
    articolo[keymap::KEY_DATA] = ui->le_data->date().toString("dd/MM/yyyy");
    articolo[keymap::KEY_NR_FATTURA] = ui->le_fattura->text();
    articolo[keymap::KEY_NOTE] = ui->te_note->toPlainText();
}

QSqlQuery ArticoloDialog::prepareQueryArticolo(void)
{
    QSqlQuery query_articolo;
    if (articolo.contains(keymap::KEY_ID)) {
        query_articolo.prepare(magazzino::UPDATE_ARTICOLO);
        query_articolo.bindValue(":id", articolo[keymap::KEY_ID]);
    }
    else {
        query_articolo.prepare(magazzino::INSERT_ARTICOLO);
    }

    query_articolo.bindValue(":descr", articolo[keymap::KEY_DESCRIZIONE]);
    query_articolo.bindValue(":id_marca", articolo[keymap::KEY_MARCA]);
    query_articolo.bindValue(":modello", articolo[keymap::KEY_MODELLO]);
    query_articolo.bindValue(":cod_articolo", articolo[keymap::KEY_COD_ARTICOLO]);
    query_articolo.bindValue(":cod_barre", articolo[keymap::KEY_COD_BARRE]);
    query_articolo.bindValue(":id_merce", articolo[keymap::KEY_CATMERCE]);
    query_articolo.bindValue(":id_unita_merce", articolo[keymap::KEY_UNITA]);
    query_articolo.bindValue(":scorta_minima", articolo[keymap::KEY_SCORTA]);

    query_articolo.bindValue(":id_fornitore", articolo[keymap::KEY_ID_FORNITORE]);
    query_articolo.bindValue(":cod_fornitore", articolo[keymap::KEY_COD_FORNITORE]);
    query_articolo.bindValue(":quantita", articolo[keymap::KEY_QUANTITA]);
    query_articolo.bindValue(":prezzo_fattura", articolo[keymap::KEY_PRZ_FATTURA]);
    query_articolo.bindValue(":sconto_fornitore", articolo[keymap::KEY_SCONTO]);
    query_articolo.bindValue(":imponibile", articolo[keymap::KEY_IMPONIBILE]);
    query_articolo.bindValue(":ricarico", articolo[keymap::KEY_RICARICO]);
    query_articolo.bindValue(":id_cod_iva", articolo[keymap::KEY_COD_IVA]);
    query_articolo.bindValue(":iva", articolo[keymap::KEY_IVA]);
    query_articolo.bindValue(":prezzo_finito", articolo[keymap::KEY_PRZ_FINITO]);
    query_articolo.bindValue(":prezzo_vendita", articolo[keymap::KEY_PRZ_VENDITA]);

    query_articolo.bindValue(":id_sede_magazzino", articolo[keymap::KEY_SEDE]);
    query_articolo.bindValue(":data_arrivo", articolo[keymap::KEY_DATA]);
    query_articolo.bindValue(":fattura", articolo[keymap::KEY_NR_FATTURA]);
    query_articolo.bindValue(":note", articolo[keymap::KEY_NOTE]);
    return query_articolo;
}

QSqlQuery ArticoloDialog::prepareQueryStorico(void)
{
    QSqlQuery query_storico;
    query_storico.prepare(magazzino::INSERT_STORICO);

    query_storico.bindValue(":data_arrivo", articolo[keymap::KEY_DATA]);
    query_storico.bindValue(":quantita", articolo[keymap::KEY_QUANTITA]);
    query_storico.bindValue(":prezzo_fattura", articolo[keymap::KEY_PRZ_FATTURA]);
    query_storico.bindValue(":sconto_fornitore", articolo[keymap::KEY_SCONTO]);
    query_storico.bindValue(":ricarico", articolo[keymap::KEY_RICARICO]);
    query_storico.bindValue(":imponibile", articolo[keymap::KEY_IMPONIBILE]);
    query_storico.bindValue(":iva", articolo[keymap::KEY_IVA]);
    query_storico.bindValue(":prezzo_finito", articolo[keymap::KEY_PRZ_FINITO]);
    query_storico.bindValue(":prezzo_vendita", articolo[keymap::KEY_PRZ_VENDITA]);
    query_storico.bindValue(":fattura", articolo[keymap::KEY_NR_FATTURA]);

    return query_storico;
}

void ArticoloDialog::save(void)
{
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();
    prepareMap();
    QSqlQuery query_articolo = prepareQueryArticolo();
    if (!query_articolo.exec()) {
        qDebug() << "errore: " << query_articolo.lastError(); //TODO definire codice errore
        db.rollback();
        return;
    }
    if (ui->updateStoricoCheckBox->isChecked()) {
        if (!articolo.contains(keymap::KEY_ID)) {
            QSqlQuery query_id;
            query_id.prepare("SELECT * FROM lastval();");
            if (!query_id.exec()) {
                qDebug() << "errore: " << query_id.lastError(); //TODO definire codice errore
                db.rollback();
                return;
            }
            query_id.first();
            articolo[keymap::KEY_ID] = query_id.value(0).toString();
        }

        QSqlQuery query_storico = prepareQueryStorico();
        query_storico.bindValue(":id_articolo", articolo[keymap::KEY_ID]);
        if (!query_storico.exec()) {
            qDebug() << "errore storico: " << articolo[keymap::KEY_ID] << query_storico.lastError(); //TODO definire codice errore
            db.rollback();
            return;
        }
    }

    db.commit();
    this->accept();
}

void ArticoloDialog::updatePrezzoAcquisto(void)
{
    QString prezzo_str = ui->le_prezzo_fattura->text();

    if (!prezzo_str.contains(locale().currencySymbol())) {
            ui->le_prezzo_fattura->setText(locale().toCurrencyString(prezzo_str.toDouble()));
    }

    updateImponibile();
}

void ArticoloDialog::updateImponibile(void)
{
    QString prezzo_str = ui->le_prezzo_fattura->text().replace(locale().currencySymbol(),"");
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
    if (ui->le_prezzo_fattura->text().isEmpty() || ui->le_ricarico->text().isEmpty()) {
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
    if (ui->le_prezzo_fattura->text().isEmpty()) {
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
