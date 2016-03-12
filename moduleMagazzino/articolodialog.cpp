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
    modelCatMerce->setSort(magazzino::COL_TABLE_DESCRIZIONE, Qt::AscendingOrder);
    modelCatMerce->select();

    modelCodIva = new QSqlTableModel(this);
    modelCodIva->setTable(table::CODICE_IVA);
    modelCodIva->setSort(magazzino::COL_TABLE_DESCRIZIONE, Qt::AscendingOrder);
    modelCodIva->select();

    modelFornitore = new QSqlQueryModel(this);
    modelFornitore->setQuery(magazzino::SELECT_FORNITORE);

    modelMarca = new QSqlTableModel(this);
    modelMarca->setTable(table::MARCA);
    modelMarca->setSort(magazzino::COL_TABLE_DESCRIZIONE, Qt::AscendingOrder);
    modelMarca->select();

    modelSede = new QSqlTableModel(this);
    modelSede->setTable(table::SEDE_MAGAZZINO);
    modelSede->setSort(magazzino::COL_TABLE_DESCRIZIONE, Qt::AscendingOrder);
    modelSede->select();

    modelUnita = new QSqlTableModel(this);
    modelUnita->setTable(table::UNITA_MISURA);
    modelUnita->setSort(magazzino::COL_TABLE_DESCRIZIONE, Qt::AscendingOrder);
    modelUnita->select();
}

void ArticoloDialog::initComboBox(void)
{
    qDebug() << "ArticoloDialog::initComboBox()";
    ui->cb_catmerce->setModel(modelCatMerce);
    ui->cb_catmerce->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    //cb_codiva è collegato a updateiva tramite il segnale currentIndexChanged
    //devo bloccare il segnale prima di configurarlo, altrimenti a ogni impostazione
    //genera un segnale.
    ui->cb_codiva->blockSignals(true);
    ui->cb_codiva->setModel(modelCodIva);
    ui->cb_codiva->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);
    int index = ui->cb_codiva->findText(settings.value(magazzino::DEFAULT_IVA).toString());
    ui->cb_codiva->setCurrentIndex(index);
    ui->cb_codiva->blockSignals(false);

    ui->cb_fornitore->setModel(modelFornitore);
    ui->cb_fornitore->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->cb_marca->setModel(modelMarca);
    ui->cb_marca->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->cb_sede->setModel(modelSede);
    ui->cb_sede->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->cb_unitamisura->setModel(modelUnita);
    ui->cb_unitamisura->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);
}

void ArticoloDialog::setValue(QString id, bool update)
{
    qDebug() << "ArticoloDialog::setValue()";
    QSqlQuery query;
    query.prepare(magazzino::SELECT_FROM_ID);
    query.bindValue(magazzino::PH_ID, id);
    if (!query.exec()) {
        showDialogError(this, ERR038, MSG010, query.lastError().text()); //NOTE codice errore 038
    }

    query.first();
    if (update)
        articoloMap[magazzino::PH_ID] = id;
    ui->le_descrizione->setText(query.value(magazzino::COL_DESCRIZIONE).toString());

    ui->cb_fornitore->setModelColumn(magazzino::COL_TABLE_ID);
    ui->cb_fornitore->setCurrentText(query.value(magazzino::COL_ID_FORNITORE).toString());
    ui->cb_fornitore->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->cb_marca->setModelColumn(magazzino::COL_TABLE_ID);
    ui->cb_marca->setCurrentText(query.value(magazzino::COL_ID_MARCA).toString());
    ui->cb_marca->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->le_modello->setText(query.value(magazzino::COL_MODELLO).toString());
    ui->le_cod_articolo->setText(query.value(magazzino::COL_CODICE_ARTICOLO).toString());
    ui->le_cod_fornitore->setText(query.value(magazzino::COL_CODICE_FORNITORE).toString());
    ui->le_cod_barre->setText(query.value(magazzino::COL_CODICE_BARRE).toString());

    ui->cb_catmerce->setModelColumn(magazzino::COL_TABLE_ID);
    ui->cb_catmerce->setCurrentText(query.value(magazzino::COL_ID_MERCE).toString());
    ui->cb_catmerce->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->cb_codiva->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);
    ui->cb_codiva->setCurrentText(query.value(magazzino::COL_CODICE_IVA).toString());

    ui->cb_unitamisura->setModelColumn(magazzino::COL_TABLE_ID);
    ui->cb_unitamisura->setCurrentText(query.value(magazzino::COL_ID_UNITA).toString());
    ui->cb_unitamisura->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->le_scorta->setText(query.value(magazzino::COL_SCORTA_MINIMA).toString());
    ui->le_quantita->setText(query.value(magazzino::COL_QUANTITA).toString());
    ui->le_prezzo_fattura->setText(locale().toCurrencyString(query.value(magazzino::COL_PREZZO_FATTURA).toDouble()));
    ui->le_sconto->setText(query.value(magazzino::COL_SCONTO_FORNITORE).toString());
    ui->le_ricarico->setText(query.value(magazzino::COL_RICARICO).toString());
    ui->le_prezzo_acquisto->setText(locale().toCurrencyString(query.value(magazzino::COL_PREZZO_ACQUISTO).toDouble()));
    ui->le_iva->setText(locale().toCurrencyString(query.value(magazzino::COL_IVA).toDouble()));

    ui->le_prezzo_finito->setText(locale().toCurrencyString(query.value(magazzino::COL_PREZZO_FINITO).toDouble()));
    ui->le_prezzo_vendita->setText(locale().toCurrencyString(query.value(magazzino::COL_PREZZO_VENDITA).toDouble()));
    ui->le_fattura->setText(query.value(magazzino::COL_FATTURA).toString());
    ui->le_data->setDate(QDate::currentDate());

    ui->cb_sede->setModelColumn(magazzino::COL_TABLE_ID);
    ui->cb_sede->setCurrentText(query.value(magazzino::COL_ID_SEDE_MAGAZZINO).toString());
    ui->cb_sede->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->te_note->setText(query.value(magazzino::COL_NOTE).toString());
}

void ArticoloDialog::prepareMap()
{
    qDebug() << "ArticoloDialog::prepareMap";
    articoloMap[magazzino::PH_DESCR] = ui->le_descrizione->text();
    articoloMap[magazzino::PH_ID_MARC] = modelMarca->index(ui->cb_marca->currentIndex(), magazzino::COL_TABLE_ID).data().toString();
    articoloMap[magazzino::PH_MODELLO] = ui->le_modello->text();
    articoloMap[magazzino::PH_COD_ART] = ui->le_cod_articolo->text();
    articoloMap[magazzino::PH_COD_EAN] = ui->le_cod_barre->text();
    articoloMap[magazzino::PH_ID_MERC] = modelCatMerce->index(ui->cb_catmerce->currentIndex(), magazzino::COL_TABLE_ID).data().toString();
    articoloMap[magazzino::PH_ID_UM] = modelUnita->index(ui->cb_unitamisura->currentIndex(), magazzino::COL_TABLE_ID).data().toString();

    //Per i tipi numeri devo usare il locale C. Maledetto postgresql
    double scorta = stringToDouble(ui->le_scorta->text());
    articoloMap[magazzino::PH_SCORTA] = QString().setNum(scorta);

    articoloMap[magazzino::PH_ID_FORN] = modelFornitore->index(ui->cb_fornitore->currentIndex(), magazzino::COL_TABLE_ID).data().toString();
    articoloMap[magazzino::PH_COD_FRN] = ui->le_cod_fornitore->text();

    double quantita = stringToDouble(ui->le_quantita->text());
    articoloMap[magazzino::PH_QUANTIT] = QString().setNum(quantita);

    double prezzo_fattura = stringToDouble(ui->le_prezzo_fattura->text());
    articoloMap[magazzino::PH_PRZ_FAT] = QString().setNum(prezzo_fattura);

    QString sconto = ui->le_sconto->text();
    articoloMap[magazzino::PH_SCONTO] = sconto.isEmpty() ? "0" : sconto;
    QString ricarico = ui->le_ricarico->text();
    articoloMap[magazzino::PH_RICARIC] = ricarico.isEmpty() ? "0" : ricarico;

    double prezzo_acquisto = stringToDouble(ui->le_prezzo_acquisto->text());
    articoloMap[magazzino::PH_PRZ_ACQ] = QString().setNum(prezzo_acquisto);
    articoloMap[magazzino::PH_COD_IVA] = ui->cb_codiva->currentText();
    double iva = stringToDouble(ui->le_iva->text());
    articoloMap[magazzino::PH_IVA] = QString().setNum(iva);
    double prezzo_vend = stringToDouble(ui->le_prezzo_vendita->text());
    articoloMap[magazzino::PH_PRZ_VEN] = QString().setNum(prezzo_vend);
    double prezzo_fin = stringToDouble(ui->le_prezzo_finito->text());
    articoloMap[magazzino::PH_PRZ_FIN] = QString().setNum(prezzo_fin);

    articoloMap[magazzino::PH_ID_SEDE] = modelSede->index(ui->cb_sede->currentIndex(), magazzino::COL_TABLE_ID).data().toString();
    articoloMap[magazzino::PH_DATA] = ui->le_data->date().toString("dd/MM/yyyy");
    articoloMap[magazzino::PH_FATTURA] = ui->le_fattura->text();
    articoloMap[magazzino::PH_NOTE] = ui->te_note->toPlainText();
}

QSqlQuery ArticoloDialog::prepareQueryArticolo(void)
{
    qDebug() << "ArticoloDialog::prepareQueryArticolo()";
    QSqlQuery query_articolo;
    if (articoloMap.contains(magazzino::PH_ID)) {
        query_articolo.prepare(magazzino::UPDATE_ARTICOLO);
    }
    else {
        query_articolo.prepare(magazzino::INSERT_ARTICOLO);
    }

    QMapIterator <QString, QString> it(articoloMap);
    while(it.hasNext()) {
        it.next();
        query_articolo.bindValue(it.key(), it.value());
    }

    return query_articolo;
}

QSqlQuery ArticoloDialog::prepareQueryStorico(void)
{
    qDebug() << "ArticoloDialog::prepareQueryStorico()";
    articoloMap[magazzino::PH_ID_ART] = articoloMap[magazzino::PH_ID];

    QSqlQuery query_check_storico;
    query_check_storico.prepare(magazzino::CHECK_STORICO);
    query_check_storico.bindValue(magazzino::PH_ID_ART, articoloMap[magazzino::PH_ID_ART]);
    query_check_storico.bindValue(magazzino::PH_DATA, articoloMap[magazzino::PH_DATA]);
    query_check_storico.exec();

    QSqlQuery query_storico;
    if (query_check_storico.first()) {
        query_storico.prepare(magazzino::UPDATE_STORICO);
    }
    else {
        query_storico.prepare(magazzino::INSERT_STORICO);
    }

    QMapIterator <QString, QString> it(articoloMap);
    while (it.hasNext()) {
        it.next();
        query_storico.bindValue(it.key(), it.value());
    }

    return query_storico;
}

void ArticoloDialog::save(void)
{
    qDebug() << "ArticoloDialog::save()";
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();
    prepareMap();

    if (articoloMap[magazzino::PH_DESCR].isEmpty()) {
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
        if (!articoloMap.contains(magazzino::PH_ID)) {
            QSqlQuery query_id;
            query_id.prepare("SELECT * FROM lastval();");
            if (!query_id.exec()) {
                showDialogError(this, ERR040, MSG010, query_id.lastError().text()); //NOTE codice errore 040
                db.rollback();
                return;
            }
            query_id.first();
            articoloMap[magazzino::PH_ID] = query_id.value(0).toString();
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
    if (prezzo_str.isEmpty()) {
        ui->le_prezzo_acquisto->setReadOnly(false);
        ui->le_prezzo_acquisto->setStyleSheet("");
        return;
    }

    prezzo_str = locale().toCurrencyString(stringToDouble(prezzo_str));
    ui->le_prezzo_fattura->setText(prezzo_str);

    calculatePrezzoAcquisto();
    ui->le_prezzo_acquisto->setReadOnly(true);
    ui->le_prezzo_acquisto->setStyleSheet("background:yellow");
}

void ArticoloDialog::calculatePrezzoAcquisto(void)
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

void ArticoloDialog::updatePrezzoAcquisto(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoAcquisto()";
    ui->le_prezzo_fattura->clear();
    ui->le_sconto->clear();
    QString prezzo = ui->le_prezzo_acquisto->text();
    if (!prezzo.contains(locale().currencySymbol()))
        ui->le_prezzo_acquisto->setText((locale().toCurrencyString(stringToDouble(prezzo))));
    updateIva();
}

void ArticoloDialog::updateIva(void)
{
    qDebug() << "ArticoloDialog::updateIva()";
    if (ui->le_prezzo_acquisto->text().isEmpty() || ui->le_ricarico->text().isEmpty()) {
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
    ui->cb_fornitore->setModelColumn(magazzino::COL_TABLE_ID);
    ui->cb_fornitore->setCurrentText(id);
    ui->cb_fornitore->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);
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

void ArticoloDialog::copyCodArt()
{
    qDebug() << "ArticoloDialog::copyCodArt()";
    QString codArticolo = ui->le_cod_articolo->text();
    ui->le_cod_fornitore->setText(codArticolo);
}
