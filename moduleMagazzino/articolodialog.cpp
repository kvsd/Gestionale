#include "articolodialog.h"
#include "ui_articolodialog.h"

ArticoloDialog::ArticoloDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArticoloDialog)
{
    qDebug() << "ArticoloDialog()";
    ui->setupUi(this);

    initModel();
    initComboBox();

    ui->le_data->setDate(QDate::currentDate());
}

ArticoloDialog::~ArticoloDialog()
{
    qDebug() << "~ArticoloDialog()";
    delete ui;
}

void ArticoloDialog::initModel(void)
{
    qDebug() << "ArticoloDialog::initModel()";
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
    qDebug() << "ArticoloDialog::initComboBox()";
    ui->cb_catmerce->setModel(modelCatMerce);
    ui->cb_catmerce->setModelColumn(magazzino::COL_MG_DESCR);

    //cb_codiva è collegato a updateiva tramite il segnale currentIndexChanged
    //devo bloccare il segnale prima di configurarlo, altrimenti a ogni impostazione
    //genera un segnale.
    ui->cb_codiva->blockSignals(true);
    ui->cb_codiva->setModel(modelCodIva);
    ui->cb_codiva->setModelColumn(magazzino::COL_MG_DESCR);
    int index = ui->cb_codiva->findText(settings.value(magazzino::DEFAULT_IVA).toString());
    ui->cb_codiva->setCurrentIndex(index);
    ui->cb_codiva->blockSignals(false);

    ui->cb_fornitore->setModel(modelFornitore);
    ui->cb_fornitore->setModelColumn(magazzino::COL_MG_DESCR);

    ui->cb_marca->setModel(modelMarca);
    ui->cb_marca->setModelColumn(magazzino::COL_MG_DESCR);

    ui->cb_sede->setModel(modelSede);
    ui->cb_sede->setModelColumn(magazzino::COL_MG_DESCR);

    ui->cb_unitamisura->setModel(modelUnita);
    ui->cb_unitamisura->setModelColumn(magazzino::COL_MG_DESCR);
}

void ArticoloDialog::setValue(QString id)
{
    qDebug() << "ArticoloDialog::setValue()";
    QSqlQuery query;
    query.prepare(magazzino::SELECT_FROM_ID);
    query.bindValue(magazzino::PH_ID, id);
    if (!query.exec()) {
        showDialogError(this, ERR038, MSG010, query.lastError().text()); //NOTE codice errore 038
    }

    query.first();
    articolo[keymap::KEY_ID] = id;
    ui->le_descrizione->setText(query.value(magazzino::COL_MG_DESCR).toString());

    ui->cb_fornitore->setModelColumn(magazzino::COL_MG_ID);
    ui->cb_fornitore->setCurrentText(query.value(magazzino::COL_MG_ID_FORN).toString());
    ui->cb_fornitore->setModelColumn(magazzino::COL_MG_DESCR);

    ui->cb_marca->setModelColumn(magazzino::COL_MG_ID);
    ui->cb_marca->setCurrentText(query.value(magazzino::COL_MG_ID_MARCA).toString());
    ui->cb_marca->setModelColumn(magazzino::COL_MG_DESCR);

    ui->le_modello->setText(query.value(magazzino::COL_MG_MODELLO).toString());
    ui->le_cod_articolo->setText(query.value(magazzino::COL_MG_COD_ART).toString());
    ui->le_cod_fornitore->setText(query.value(magazzino::COL_MG_COD_FOR).toString());
    ui->le_cod_barre->setText(query.value(magazzino::COL_MG_COD_EAN).toString());

    ui->cb_catmerce->setModelColumn(magazzino::COL_MG_ID);
    ui->cb_catmerce->setCurrentText(query.value(magazzino::COL_MG_ID_MERCE).toString());
    ui->cb_catmerce->setModelColumn(magazzino::COL_MG_DESCR);

    ui->cb_codiva->setModelColumn(magazzino::COL_MG_DESCR);
    ui->cb_codiva->setCurrentText(query.value(magazzino::COL_MG_COD_IVA).toString());

    ui->cb_unitamisura->setModelColumn(magazzino::COL_MG_ID);
    ui->cb_unitamisura->setCurrentText(query.value(magazzino::COL_MG_ID_UM).toString());
    ui->cb_unitamisura->setModelColumn(magazzino::COL_MG_DESCR);

    ui->le_scorta->setText(query.value(magazzino::COL_MG_SCORTA).toString());
    ui->le_quantita->setText(query.value(magazzino::COL_MG_QT).toString());
    ui->le_prezzo_fattura->setText(locale().toCurrencyString(query.value(magazzino::COL_MG_PRZ_FAT).toDouble()));
    ui->le_sconto->setText(query.value(magazzino::COL_MG_SCONTO).toString());
    ui->le_ricarico->setText(query.value(magazzino::COL_MG_RICARICO).toString());
    ui->le_prezzo_acquisto->setText(locale().toCurrencyString(query.value(magazzino::COL_MG_PRZ_ACQ).toDouble()));
    ui->le_iva->setText(locale().toCurrencyString(query.value(magazzino::COL_MG_IVA).toDouble()));

    ui->le_prezzo_finito->setText(locale().toCurrencyString(query.value(magazzino::COL_MG_PRZ_FIN).toDouble()));
    ui->le_prezzo_vendita->setText(locale().toCurrencyString(query.value(magazzino::COL_MG_PRZ_VEN).toDouble()));
    ui->le_fattura->setText(query.value(magazzino::COL_MG_FATTURA).toString());
    ui->le_data->setDate(QDate::currentDate());

    ui->cb_sede->setModelColumn(magazzino::COL_MG_ID);
    ui->cb_sede->setCurrentText(query.value(magazzino::COL_MG_ID_SEDE).toString());
    ui->cb_sede->setModelColumn(magazzino::COL_MG_DESCR);

    ui->te_note->setText(query.value(magazzino::COL_MG_NOTE).toString());
}

void ArticoloDialog::prepareMap()
{
    qDebug() << "ArticoloDialog::prepareMap";
    articolo[keymap::KEY_DESCRIZIONE] = ui->le_descrizione->text();
    articolo[keymap::KEY_MARCA] = modelMarca->index(ui->cb_marca->currentIndex(), magazzino::COL_MG_ID).data().toString();
    articolo[keymap::KEY_MODELLO] = ui->le_modello->text();
    articolo[keymap::KEY_COD_ARTICOLO] = ui->le_cod_articolo->text();
    articolo[keymap::KEY_COD_BARRE] = ui->le_cod_barre->text();
    articolo[keymap::KEY_CATMERCE] = modelCatMerce->index(ui->cb_catmerce->currentIndex(), magazzino::COL_MG_ID).data().toString();
    articolo[keymap::KEY_UNITA] = modelUnita->index(ui->cb_unitamisura->currentIndex(), magazzino::COL_MG_ID).data().toString();

    //Per i tipi numeri devo usare il locale C. Maledetto postgresql
    double scorta = stringToDouble(ui->le_scorta->text());
    articolo[keymap::KEY_SCORTA] = QString().setNum(scorta);

    articolo[keymap::KEY_ID_FORNITORE] = modelFornitore->index(ui->cb_fornitore->currentIndex(), magazzino::COL_MG_ID).data().toString();
    articolo[keymap::KEY_COD_FORNITORE] = ui->le_cod_fornitore->text();

    double quantita = stringToDouble(ui->le_quantita->text());
    articolo[keymap::KEY_QUANTITA] = QString().setNum(quantita);

    double prezzo_fattura = stringToDouble(ui->le_prezzo_fattura->text());
    articolo[keymap::KEY_PRZ_FATTURA] = QString().setNum(prezzo_fattura);

    articolo[keymap::KEY_SCONTO] =  ui->le_sconto->text();
    articolo[keymap::KEY_RICARICO] = ui->le_ricarico->text();

    double prezzo_acquisto = stringToDouble(ui->le_prezzo_acquisto->text());
    articolo[keymap::KEY_PRZ_ACQUISTO] = QString().setNum(prezzo_acquisto);
    articolo[keymap::KEY_COD_IVA] = ui->cb_codiva->currentText();
    double iva = stringToDouble(ui->le_iva->text());
    articolo[keymap::KEY_IVA] = QString().setNum(iva);
    double prezzo_vend = stringToDouble(ui->le_prezzo_vendita->text());
    articolo[keymap::KEY_PRZ_VENDITA] = QString().setNum(prezzo_vend);
    double prezzo_fin = stringToDouble(ui->le_prezzo_finito->text());
    articolo[keymap::KEY_PRZ_FINITO] = QString().setNum(prezzo_fin);

    articolo[keymap::KEY_SEDE] = modelSede->index(ui->cb_sede->currentIndex(), magazzino::COL_MG_ID).data().toString();
    articolo[keymap::KEY_DATA] = ui->le_data->date().toString("dd/MM/yyyy");
    articolo[keymap::KEY_NR_FATTURA] = ui->le_fattura->text();
    articolo[keymap::KEY_NOTE] = ui->te_note->toPlainText();
}

QSqlQuery ArticoloDialog::prepareQueryArticolo(void)
{
    qDebug() << "ArticoloDialog::prepareQueryArticolo()";
    QSqlQuery query_articolo;
    if (articolo.contains(keymap::KEY_ID)) {
        query_articolo.prepare(magazzino::UPDATE_ARTICOLO);
        query_articolo.bindValue(magazzino::PH_ID, articolo[keymap::KEY_ID]);
    }
    else {
        query_articolo.prepare(magazzino::INSERT_ARTICOLO);
    }

    query_articolo.bindValue(magazzino::PH_DESCR, articolo[keymap::KEY_DESCRIZIONE]);
    query_articolo.bindValue(magazzino::PH_ID_MARC, articolo[keymap::KEY_MARCA]);
    query_articolo.bindValue(magazzino::PH_MODELLO, articolo[keymap::KEY_MODELLO]);
    query_articolo.bindValue(magazzino::PH_COD_ART, articolo[keymap::KEY_COD_ARTICOLO]);
    query_articolo.bindValue(magazzino::PH_COD_EAN, articolo[keymap::KEY_COD_BARRE]);
    query_articolo.bindValue(magazzino::PH_ID_MERC, articolo[keymap::KEY_CATMERCE]);
    query_articolo.bindValue(magazzino::PH_ID_UM, articolo[keymap::KEY_UNITA]);
    query_articolo.bindValue(magazzino::PH_SCORTA, articolo[keymap::KEY_SCORTA]);

    query_articolo.bindValue(magazzino::PH_ID_FORN, articolo[keymap::KEY_ID_FORNITORE]);
    query_articolo.bindValue(magazzino::PH_COD_FRN, articolo[keymap::KEY_COD_FORNITORE]);
    query_articolo.bindValue(magazzino::PH_QUANTIT, articolo[keymap::KEY_QUANTITA]);
    query_articolo.bindValue(magazzino::PH_PRZ_FAT, articolo[keymap::KEY_PRZ_FATTURA]);
    query_articolo.bindValue(magazzino::PH_SCONTO, articolo[keymap::KEY_SCONTO]);
    query_articolo.bindValue(magazzino::PH_PRZ_ACQ, articolo[keymap::KEY_PRZ_ACQUISTO]);
    query_articolo.bindValue(magazzino::PH_RICARIC, articolo[keymap::KEY_RICARICO]);
    query_articolo.bindValue(magazzino::PH_COD_IVA, articolo[keymap::KEY_COD_IVA]);
    query_articolo.bindValue(magazzino::PH_IVA, articolo[keymap::KEY_IVA]);
    query_articolo.bindValue(magazzino::PH_PRZ_FIN, articolo[keymap::KEY_PRZ_FINITO]);
    query_articolo.bindValue(magazzino::PH_PRZ_VEN, articolo[keymap::KEY_PRZ_VENDITA]);

    query_articolo.bindValue(magazzino::PH_ID_SEDE, articolo[keymap::KEY_SEDE]);
    query_articolo.bindValue(magazzino::PH_DATA, articolo[keymap::KEY_DATA]);
    query_articolo.bindValue(magazzino::PH_FATTURA, articolo[keymap::KEY_NR_FATTURA]);
    query_articolo.bindValue(magazzino::PH_NOTE, articolo[keymap::KEY_NOTE]);
    return query_articolo;
}

QSqlQuery ArticoloDialog::prepareQueryStorico(void)
{
    qDebug() << "ArticoloDialog::prepareQueryStorico()";
    QString id_articolo = articolo[keymap::KEY_ID];
    QString data_articolo = articolo[keymap::KEY_DATA];

    QSqlQuery query_storico;

    QSqlQuery query_check_storico;
    query_check_storico.prepare(magazzino::CHECK_STORICO);
    query_check_storico.bindValue(magazzino::PH_ID_ART, id_articolo);
    query_check_storico.bindValue(magazzino::PH_DATA, data_articolo);
    query_check_storico.exec();
    if (query_check_storico.first()) {
        qDebug() << "run update;";
        query_storico.prepare(magazzino::UPDATE_STORICO);
    }
    else {
        query_storico.prepare(magazzino::INSERT_STORICO);
        qDebug() << "run insert;";
    }

    query_storico.bindValue(magazzino::PH_ID_ART, articolo[keymap::KEY_ID]);
    query_storico.bindValue(magazzino::PH_DATA, articolo[keymap::KEY_DATA]);
    query_storico.bindValue(magazzino::PH_QUANTIT, articolo[keymap::KEY_QUANTITA]);
    query_storico.bindValue(magazzino::PH_PRZ_FAT, articolo[keymap::KEY_PRZ_FATTURA]);
    query_storico.bindValue(magazzino::PH_SCONTO, articolo[keymap::KEY_SCONTO]);
    query_storico.bindValue(magazzino::PH_RICARIC, articolo[keymap::KEY_RICARICO]);
    query_storico.bindValue(magazzino::PH_PRZ_ACQ, articolo[keymap::KEY_PRZ_ACQUISTO]);
    query_storico.bindValue(magazzino::PH_IVA, articolo[keymap::KEY_IVA]);
    query_storico.bindValue(magazzino::PH_PRZ_FIN, articolo[keymap::KEY_PRZ_FINITO]);
    query_storico.bindValue(magazzino::PH_PRZ_VEN, articolo[keymap::KEY_PRZ_VENDITA]);
    query_storico.bindValue(magazzino::PH_FATTURA, articolo[keymap::KEY_NR_FATTURA]);

    return query_storico;
}

void ArticoloDialog::save(void)
{
    qDebug() << "ArticoloDialog::save()";
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();
    prepareMap();

    if (articolo[keymap::KEY_DESCRIZIONE].isEmpty()) {
        showDialogError(this, ERR050, MSG013); //NOTE codice errore 050
        ui->le_descrizione->setStyleSheet(magazzino::CSS_WARNING_STYLE);
        return;
    }

    QSqlQuery query_articolo = prepareQueryArticolo();
    if (!query_articolo.exec()) {
        showDialogError(this, ERR039, MSG010, query_articolo.lastError().text()); //NOTE codice errore 039
        db.rollback();
        return;
    }
    if (ui->updateStoricoCheckBox->isChecked()) {
        if (!articolo.contains(keymap::KEY_ID)) {
            QSqlQuery query_id;
            query_id.prepare("SELECT * FROM lastval();");
            if (!query_id.exec()) {
                showDialogError(this, ERR040, MSG010, query_id.lastError().text()); //NOTE codice errore 040
                db.rollback();
                return;
            }
            query_id.first();
            articolo[keymap::KEY_ID] = query_id.value(0).toString();
        }

        QSqlQuery query_storico = prepareQueryStorico();

        if (!query_storico.exec()) {
            showDialogError(this, ERR041, MSG010, query_storico.lastError().text()); //NOTE codice errore 041
            db.rollback();
            return;
        }
    }

    db.commit();
    this->accept();
}

void ArticoloDialog::updatePrezzoFattura(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoFattura()";
    QString prezzo_str = ui->le_prezzo_fattura->text();

    if (!prezzo_str.contains(locale().currencySymbol())) {
            ui->le_prezzo_fattura->setText(locale().toCurrencyString(stringToDouble(prezzo_str)));
    }
    else {
        prezzo_str = locale().toCurrencyString(stringToDouble(prezzo_str));
        ui->le_prezzo_fattura->setText(prezzo_str);
    }

    updatePrezzoAcquisto();
}

void ArticoloDialog::updatePrezzoAcquisto(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoAcquisto()";
    QString prezzo_str = ui->le_prezzo_fattura->text();
    if (prezzo_str.isEmpty()) {
        return;
    }

    QString sconto_str = ui->le_sconto->text().replace("%", "");

    double prezzo_acquisto = stringToDouble(prezzo_str);
    double sconto = 0;

    if (sconto_str.contains("+")) {
        QStringList sconti = sconto_str.split("+");
        QString s;
        foreach(s, sconti) {
            sconto = stringToDouble(s)/100.0;
            prezzo_acquisto -= prezzo_acquisto*sconto;
        }
    }
    else {
        sconto = stringToDouble(sconto_str)/100.0;
        prezzo_acquisto -= prezzo_acquisto*sconto;
    }

    ui->le_prezzo_acquisto->setText(locale().toCurrencyString(prezzo_acquisto));
    updateIva();
}

void ArticoloDialog::updateIva(void)
{
    qDebug() << "ArticoloDialog::updateIva()";
    if (ui->le_prezzo_fattura->text().isEmpty() || ui->le_ricarico->text().isEmpty()) {
        return;
    }

    double prezzo_acquisto = stringToDouble(ui->le_prezzo_acquisto->text());
    double ricarico = 0;

    QString ricarico_str = ui->le_ricarico->text().replace("%","");
    if (ricarico_str.contains("+")) {
        QStringList ricarichi = ricarico_str.split("+");
        QString s;
        foreach(s, ricarichi) {
            ricarico = stringToDouble(s)/100;
            prezzo_acquisto += prezzo_acquisto*ricarico;
        }
    }
    else {
        ricarico = stringToDouble(ricarico_str)/100;
        prezzo_acquisto += prezzo_acquisto*ricarico;
    }

    double codiva = stringToDouble(ui->cb_codiva->currentText())/100.0;
    double iva = prezzo_acquisto*codiva;
    ui->le_iva->setText(locale().toCurrencyString(iva));

    double prezzo_vendita = prezzo_acquisto+iva;
    ui->le_prezzo_vendita->setText(locale().toCurrencyString(prezzo_vendita));
    ui->le_prezzo_finito->setText(locale().toCurrencyString(prezzo_vendita));
}

void ArticoloDialog::updatePrezzoFinito(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoFinito()";
    if (ui->le_prezzo_fattura->text().isEmpty()) {
        return;
    }

    QString prezzo = ui->le_prezzo_finito->text();
    if (!prezzo.contains(locale().currencySymbol())) {
        ui->le_prezzo_finito->setText(locale().toCurrencyString(stringToDouble(prezzo)));
    }
}

void ArticoloDialog::updatePrezzoVendita(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoVendita()";
    QString prezzo_str = ui->le_prezzo_vendita->text();

    if (!prezzo_str.contains(locale().currencySymbol())) {
            ui->le_prezzo_vendita->setText(locale().toCurrencyString(stringToDouble(prezzo_str)));
    }
}

void ArticoloDialog::openAddMarca()
{
    qDebug() << "ArticoloDialog::openAddMarca()";
    QString newValue = allDlg(this, modelMarca, ADD_MARCA_QUERY, "Marca", ERR042); //NOTE codice errore 042
    if (!newValue.isEmpty()) {
        ui->cb_marca->setCurrentText(newValue);
    }
}

void ArticoloDialog::openAddCategoria()
{
    qDebug() << "ArticoloDialog::openAddCategoria()";
    QString newValue = allDlg(this, modelCatMerce, ADD_CAT_MERCE_QUERY, "Categoria merce", ERR043); //NOTE codice errore 043
    if (!newValue.isEmpty()) {
        ui->cb_catmerce->setCurrentText(newValue);
    }
}

void ArticoloDialog::openAddMisura()
{
    qDebug() << "ArticoloDialog::openAddMisura()";
    QString newValue = allDlg(this, modelUnita, ADD_UM_QUERY, "Unita di misura", ERR044); //NOTE codice errore 044
    if (!newValue.isEmpty()) {
        ui->cb_unitamisura->setCurrentText(newValue);
    }
}

void ArticoloDialog::openAddFornitore()
{
    qDebug() << "ArticoloDialog::openAddFornitore()";
    AnagraficaAddDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }

    //Trovo l'ultimo id inserito nel database
    QSqlQuery query;
    query.prepare("select * from lastval();");
    query.exec();
    query.first();
    QString id = query.value(0).toString();

    //Ricarico la query e seleziono il valore immesso
    modelFornitore->setQuery(magazzino::SELECT_FORNITORE);
    ui->cb_fornitore->setModelColumn(0);
    ui->cb_fornitore->setCurrentText(id);
    ui->cb_fornitore->setModelColumn(1);
}

void ArticoloDialog::openAddIVA()
{
    qDebug() << "ArticoloDialog::openAddIVA()";
    QString newValue = allDlg(this, modelCodIva, ADD_IVA_QUERY, "Codice IVA", ERR045); //NOTE codice errore 045
    if (!newValue.isEmpty()) {
        ui->cb_codiva->setCurrentText(newValue);
    }
}

void ArticoloDialog::openAddSede()
{
    qDebug() << "ArticoloDialog::openAddSede()";
    QString newValue = allDlg(this, modelSede, ADD_SEDE_QUERY, "Sede magazzino", ERR046); //NOTE codice errore 046
    if (!newValue.isEmpty()) {
        ui->cb_sede->setCurrentText(newValue);
    }
}
