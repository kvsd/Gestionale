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
    m_modelCatMerce = new QSqlTableModel(this);
    m_modelCatMerce->setTable(table::CATEGORIA_MERCE);
    m_modelCatMerce->setSort(CBM::DESCR, Qt::AscendingOrder);
    m_modelCatMerce->select();

    m_modelCodIva = new QSqlTableModel(this);
    m_modelCodIva->setTable(table::CODICE_IVA);
    m_modelCodIva->setSort(CBM::DESCR, Qt::AscendingOrder);
    m_modelCodIva->select();

    m_modelFornitore = new QSqlQueryModel(this);
    m_modelFornitore->setQuery(sql::SELECT_CB_FORNITORE);

    m_modelMarca = new QSqlTableModel(this);
    m_modelMarca->setTable(table::MARCA);
    m_modelMarca->setSort(CBM::DESCR, Qt::AscendingOrder);
    m_modelMarca->select();

    m_modelSede = new QSqlTableModel(this);
    m_modelSede->setTable(table::SEDE_MAGAZZINO);
    m_modelSede->setSort(CBM::DESCR, Qt::AscendingOrder);
    m_modelSede->select();

    m_modelUnita = new QSqlTableModel(this);
    m_modelUnita->setTable(table::UNITA_MISURA);
    m_modelUnita->setSort(CBM::DESCR, Qt::AscendingOrder);
    m_modelUnita->select();
}

void ArticoloDialog::initComboBox(void)
{
    qDebug() << "ArticoloDialog::initComboBox()";
    ui->cb_catmerce->setModel(m_modelCatMerce);
    ui->cb_catmerce->setModelColumn(CBM::DESCR);

    //cb_codiva è collegato a updateiva tramite il segnale currentIndexChanged
    //devo bloccare il segnale prima di configurarlo, altrimenti a ogni impostazione
    //genera un segnale.
    ui->cb_codiva->blockSignals(true);
    ui->cb_codiva->setModel(m_modelCodIva);
    ui->cb_codiva->setModelColumn(CBM::DESCR);
    int index = ui->cb_codiva->findText(m_settings.value(settings::DEFAULT_IVA).toString());
    ui->cb_codiva->setCurrentIndex(index);
    ui->cb_codiva->blockSignals(false);

    ui->cb_fornitore->setModel(m_modelFornitore);
    ui->cb_fornitore->setModelColumn(CBM::DESCR);

    ui->cb_marca->setModel(m_modelMarca);
    ui->cb_marca->setModelColumn(CBM::DESCR);

    ui->cb_sede->setModel(m_modelSede);
    ui->cb_sede->setModelColumn(CBM::DESCR);

    ui->cb_unitamisura->setModel(m_modelUnita);
    ui->cb_unitamisura->setModelColumn(CBM::DESCR);
}

void ArticoloDialog::setValue(QString id, bool update)
{
    qDebug() << "ArticoloDialog::setValue()";
    QSqlQuery query;
    query.prepare(sql::SELECT_ARTICOLO_FROM_ID);
    query.bindValue(ph::ID, id);
    if (!query.exec())
        showDialogError(this, ERR038, MSG010, query.lastError().text()); //NOTE codice errore 038

    query.first();
    if (update)
        m_articoloMap[ph::ID] = id;
    ui->le_descrizione->setText(query.value(coldb::DESCRIZIONE).toString());

    ui->cb_fornitore->setModelColumn(CBM::ID);
    ui->cb_fornitore->setCurrentText(query.value(coldb::ID_FORNITORE).toString());
    ui->cb_fornitore->setModelColumn(CBM::DESCR);

    ui->cb_marca->setModelColumn(CBM::ID);
    ui->cb_marca->setCurrentText(query.value(coldb::ID_MARCA).toString());
    ui->cb_marca->setModelColumn(CBM::DESCR);

    ui->le_modello->setText(query.value(coldb::MODELLO).toString());
    ui->le_cod_articolo->setText(query.value(coldb::CODICE_ARTICOLO).toString());
    ui->le_cod_fornitore->setText(query.value(coldb::CODICE_FORNITORE).toString());
    ui->le_cod_barre->setText(query.value(coldb::CODICE_BARRE).toString());

    ui->cb_catmerce->setModelColumn(CBM::ID);
    ui->cb_catmerce->setCurrentText(query.value(coldb::ID_MERCE).toString());
    ui->cb_catmerce->setModelColumn(CBM::DESCR);

    ui->cb_codiva->setModelColumn(CBM::DESCR);
    ui->cb_codiva->setCurrentText(query.value(coldb::CODICE_IVA).toString());

    ui->cb_unitamisura->setModelColumn(CBM::ID);
    ui->cb_unitamisura->setCurrentText(query.value(coldb::ID_UNITA).toString());
    ui->cb_unitamisura->setModelColumn(CBM::DESCR);

    ui->le_scorta->setText(query.value(coldb::SCORTA_MINIMA).toString());
    ui->le_quantita->setText(query.value(coldb::QUANTITA).toString());
    ui->le_prezzo_fattura->setText(locale().toCurrencyString(query.value(coldb::PREZZO_FATTURA).toDouble()));
    freezeLineEdit(ui->le_prezzo_acquisto, !ui->le_prezzo_fattura->text().isEmpty());
    ui->le_sconto->setText(query.value(coldb::SCONTO_FORNITORE).toString());
    ui->le_ricarico->setText(query.value(coldb::RICARICO).toString());
    ui->le_prezzo_acquisto->setText(locale().toCurrencyString(query.value(coldb::PREZZO_ACQUISTO).toDouble()));
    ui->le_iva->setText(locale().toCurrencyString(query.value(coldb::IVA).toDouble()));
    ui->le_prezzo_finito->setText(locale().toCurrencyString(query.value(coldb::PREZZO_FINITO).toDouble()));
    ui->le_prezzo_vendita->setText(locale().toCurrencyString(query.value(coldb::PREZZO_VENDITA).toDouble()));
    ui->le_prezzo_venditaB->setText(locale().toCurrencyString(query.value(coldb::PREZZO_VENDITA_B).toDouble()));
    ui->le_fattura->setText(query.value(coldb::FATTURA).toString());
    ui->le_data->setDate(QDate::currentDate());

    ui->cb_sede->setModelColumn(CBM::ID);
    ui->cb_sede->setCurrentText(query.value(coldb::ID_SEDE_MAGAZZINO).toString());
    ui->cb_sede->setModelColumn(CBM::DESCR);

    ui->te_note->setText(query.value(coldb::NOTE).toString());
}

void ArticoloDialog::prepareMap()
{
    qDebug() << "ArticoloDialog::prepareMap";
    m_articoloMap[ph::DESCR] = ui->le_descrizione->text();
    m_articoloMap[ph::ID_MARC] = m_modelMarca->index(ui->cb_marca->currentIndex(), CBM::ID).data().toString();
    m_articoloMap[ph::MODELLO] = ui->le_modello->text();
    m_articoloMap[ph::COD_ART] = ui->le_cod_articolo->text();
    m_articoloMap[ph::COD_EAN] = ui->le_cod_barre->text();
    m_articoloMap[ph::ID_MERC] = m_modelCatMerce->index(ui->cb_catmerce->currentIndex(), CBM::ID).data().toString();
    m_articoloMap[ph::ID_UM] = m_modelUnita->index(ui->cb_unitamisura->currentIndex(), CBM::ID).data().toString();

    //Per i tipi numeri devo usare il locale C. Maledetto postgresql
    double scorta = stringToDouble(ui->le_scorta->text());
    m_articoloMap[ph::SCORTA] = QString().setNum(scorta);

    m_articoloMap[ph::ID_FORN] = m_modelFornitore->index(ui->cb_fornitore->currentIndex(), CBM::ID).data().toString();
    m_articoloMap[ph::COD_FRN] = ui->le_cod_fornitore->text();

    double quantita = stringToDouble(ui->le_quantita->text());
    m_articoloMap[ph::QUANTIT] = QString().setNum(quantita);

    double prezzo_fattura = stringToDouble(ui->le_prezzo_fattura->text());
    m_articoloMap[ph::PRZ_FAT] = QString().setNum(prezzo_fattura);

    QString sconto = ui->le_sconto->text();
    m_articoloMap[ph::SCONTO] = sconto.isEmpty() ? "0" : sconto;
    QString ricarico = ui->le_ricarico->text();
    m_articoloMap[ph::RICARIC] = ricarico.isEmpty() ? "0" : ricarico;

    double prezzo_acquisto = stringToDouble(ui->le_prezzo_acquisto->text());
    m_articoloMap[ph::PRZ_ACQ] = QString().setNum(prezzo_acquisto);
    m_articoloMap[ph::COD_IVA] = ui->cb_codiva->currentText();
    double iva = stringToDouble(ui->le_iva->text());
    m_articoloMap[ph::IVA] = QString().setNum(iva);
    double prezzo_vend = stringToDouble(ui->le_prezzo_vendita->text());
    m_articoloMap[ph::PRZ_VEN] = QString().setNum(prezzo_vend);
    double prezzo_vend_b = stringToDouble(ui->le_prezzo_venditaB->text());
    m_articoloMap[ph::PRZ_VEN_B] = QString().setNum(prezzo_vend_b);
    double prezzo_fin = stringToDouble(ui->le_prezzo_finito->text());
    m_articoloMap[ph::PRZ_FIN] = QString().setNum(prezzo_fin);

    m_articoloMap[ph::ID_SEDE] = m_modelSede->index(ui->cb_sede->currentIndex(), CBM::ID).data().toString();
    m_articoloMap[ph::DATA_ARRIVO] = ui->le_data->date().toString("dd/MM/yyyy");
    m_articoloMap[ph::FATTURA] = ui->le_fattura->text();
    m_articoloMap[ph::NOTE] = ui->te_note->toPlainText();
}

QSqlQuery ArticoloDialog::prepareQueryArticolo(void)
{
    qDebug() << "ArticoloDialog::prepareQueryArticolo()";
    QSqlQuery query_articolo;
    if (m_articoloMap.contains(ph::ID))
        query_articolo.prepare(sql::UPDATE_ARTICOLO);
    else
        query_articolo.prepare(sql::INSERT_ARTICOLO);

    for (QString &key : m_articoloMap.keys())
        query_articolo.bindValue(key, m_articoloMap[key]);

    return query_articolo;
}

QSqlQuery ArticoloDialog::prepareQueryStorico(void)
{
    qDebug() << "ArticoloDialog::prepareQueryStorico()";
    m_articoloMap[ph::ID_ART] = m_articoloMap[ph::ID];

    QSqlQuery query_check_storico;
    query_check_storico.prepare(sql::CHECK_STORICO);
    query_check_storico.bindValue(ph::ID_ART, m_articoloMap[ph::ID_ART]);
    query_check_storico.bindValue(ph::DATA_ARRIVO, m_articoloMap[ph::DATA_ARRIVO]);
    query_check_storico.exec();

    QSqlQuery query_storico;
    if (query_check_storico.first())
        query_storico.prepare(sql::UPDATE_STORICO);
    else
        query_storico.prepare(sql::INSERT_STORICO);

    for (QString &key : m_articoloMap.keys())
        query_storico.bindValue(key, m_articoloMap.value(key));

    return query_storico;
}

void ArticoloDialog::save(void)
{
    qDebug() << "ArticoloDialog::save()";
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();
    prepareMap();

    if (m_articoloMap[ph::DESCR].isEmpty()) {
        showDialogError(this, ERR050, MSG013); //NOTE codice errore 050
        ui->le_descrizione->setStyleSheet(css::WARNING_STYLE);
        return;
    }

    QSqlQuery query_articolo = prepareQueryArticolo();
    if (!query_articolo.exec()) {
        showDialogError(this, ERR039, MSG010, query_articolo.lastError().text()); //NOTE codice errore 039
        db.rollback();
        return;
    }

    if (!m_articoloMap.contains(ph::ID)) {
        query_articolo.first();
        m_articoloMap[ph::ID] = query_articolo.value(coldb::ID).toString();
    }

    QSqlQuery query_storico = prepareQueryStorico();

    if (!query_storico.exec()) {
        showDialogError(this, ERR041, MSG010, query_storico.lastError().text()); //NOTE codice errore 041
        db.rollback();
        return;
    }

    db.commit();
    this->accept();
}

void ArticoloDialog::updatePrezzoFattura(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoFattura()";
    //Slot usato da le_prezzo_fattura. Aggiunge il simbolo della moneta
    //al prezzo inserito, calcola il prezzo d'acquisto e mette in sola
    //scrittura le_prezzo_acquisto.
    QString prezzo_str = ui->le_prezzo_fattura->text();
    if (prezzo_str.isEmpty()) {
        freezeLineEdit(ui->le_prezzo_acquisto, false);
        return;
    }

    prezzo_str = locale().toCurrencyString(stringToDouble(prezzo_str));
    ui->le_prezzo_fattura->setText(prezzo_str);

    calculatePrezzoAcquisto();
    freezeLineEdit(ui->le_prezzo_acquisto, true);
}

void ArticoloDialog::freezeLineEdit(QLineEdit *le, bool status)
{
    qDebug() << "ArticoloDialog::freezeLineEdit()";
    le->setReadOnly(status);
    le->blockSignals(status);
    le->setStyleSheet(status ? css::WARNING_STYLE : "");
}

void ArticoloDialog::calculatePrezzoAcquisto(void)
{
    qDebug() << "ArticoloDialog::calculatePrezzoAcquisto()";
    //Slot usata da le_sconto e dallo slot updatePrezzoFattura per calcolare
    //il prezzo d'acquisto e scriverlo in le_prezzo_acquisto.
    QString prezzo_str = ui->le_prezzo_fattura->text();
    if (prezzo_str.isEmpty())
        return;

    QString sconto_str = ui->le_sconto->text().replace("%", "");
    double prezzo = stringToDouble(prezzo_str);
    double prezzo_acquisto = setSconto(prezzo, sconto_str);
    ui->le_prezzo_acquisto->setText(locale().toCurrencyString(prezzo_acquisto));
    updateIva();
}

void ArticoloDialog::updatePrezzoAcquisto(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoAcquisto()";
    //Slot usato da le_prezzo_acquisto se non e' in modalita solo lettura.
    ui->le_sconto->clear();
    QString prezzo = ui->le_prezzo_acquisto->text();
    if (!prezzo.contains(locale().currencySymbol()))
        ui->le_prezzo_acquisto->setText((locale().toCurrencyString(stringToDouble(prezzo))));
    updateIva();
}

void ArticoloDialog::updateIva(void)
{
    qDebug() << "ArticoloDialog::updateIva()";
    if (ui->le_prezzo_acquisto->text().isEmpty() || ui->le_ricarico->text().isEmpty())
        return;

    double prezzo = stringToDouble(ui->le_prezzo_acquisto->text());
    QString ricarico_str = ui->le_ricarico->text().replace("%","");
    double prezzo_acquisto = setRicarico(prezzo, ricarico_str);

    double codiva = stringToDouble(ui->cb_codiva->currentText())/100.0;
    double iva = prezzo_acquisto*codiva;
    ui->le_iva->setText(locale().toCurrencyString(iva));

    double prezzo_finito = prezzo_acquisto+iva;
    ui->le_prezzo_finito->setText(locale().toCurrencyString(prezzo_finito));
    double prezzo_vendita = stringToDouble(ui->le_prezzo_vendita->text());
    if (prezzo_vendita < prezzo_finito)
        ui->le_prezzo_vendita->setText(locale().toCurrencyString(prezzo_finito));
    if (ui->le_prezzo_venditaB->text().isEmpty())
        ui->le_prezzo_venditaB->setText(locale().toCurrencyString(prezzo_finito));
}

void ArticoloDialog::updatePrezzoFinito(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoFinito()";
    //Slot collegato a le_prezzo_finito.
    if (ui->le_prezzo_fattura->text().isEmpty())
        return;

    QString prezzo = ui->le_prezzo_finito->text();
    if (!prezzo.contains(locale().currencySymbol()))
        ui->le_prezzo_finito->setText(locale().toCurrencyString(stringToDouble(prezzo)));
}

void ArticoloDialog::updatePrezzoVendita(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoVendita()";
    //Slot collegato a le_prezzo_vendita.
    QString prezzo_ven = ui->le_prezzo_vendita->text();

    if (!prezzo_ven.contains(locale().currencySymbol())) {
        prezzo_ven = locale().toCurrencyString(stringToDouble(prezzo_ven));
        ui->le_prezzo_vendita->setText(prezzo_ven);
    }
}

void ArticoloDialog::updatePrezzoVenditaB(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoVenditaB()";
    //Slot collegato a le_prezzo_venditaB.
    QString prezzo_ven = ui->le_prezzo_venditaB->text();

    if (!prezzo_ven.contains(locale().currencySymbol())) {
        prezzo_ven = locale().toCurrencyString(stringToDouble(prezzo_ven));
        ui->le_prezzo_venditaB->setText(prezzo_ven);
    }
}

void ArticoloDialog::openAddMarca()
{
    qDebug() << "ArticoloDialog::openAddMarca()";
    QString newValue = allDlg(this, m_modelMarca, ADD_MARCA_QUERY, "Marca", ERR042); //NOTE codice errore 042
    if (!newValue.isEmpty())
        ui->cb_marca->setCurrentText(newValue);
}

void ArticoloDialog::openAddCategoria()
{
    qDebug() << "ArticoloDialog::openAddCategoria()";
    QString newValue = allDlg(this, m_modelCatMerce, ADD_CAT_MERCE_QUERY, "Categoria merce", ERR043); //NOTE codice errore 043
    if (!newValue.isEmpty())
        ui->cb_catmerce->setCurrentText(newValue);
}

void ArticoloDialog::openAddMisura()
{
    qDebug() << "ArticoloDialog::openAddMisura()";
    QString newValue = allDlg(this, m_modelUnita, ADD_UM_QUERY, "Unita di misura", ERR044); //NOTE codice errore 044
    if (!newValue.isEmpty())
        ui->cb_unitamisura->setCurrentText(newValue);
}

void ArticoloDialog::openAddFornitore()
{
    qDebug() << "ArticoloDialog::openAddFornitore()";
    AnagraficaAddDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok)
        return;

    //Trovo l'ultimo id inserito nel database
    QSqlQuery query;
    query.prepare("select * from lastval();");
    query.exec();
    query.first();
    QString id = query.value(0).toString();

    //Ricarico la query e seleziono il valore immesso
    m_modelFornitore->setQuery(sql::SELECT_CB_FORNITORE);
    ui->cb_fornitore->setModelColumn(CBM::ID);
    ui->cb_fornitore->setCurrentText(id);
    ui->cb_fornitore->setModelColumn(CBM::DESCR);
}

void ArticoloDialog::openAddIVA()
{
    qDebug() << "ArticoloDialog::openAddIVA()";
    QString newValue = allDlg(this, m_modelCodIva, ADD_IVA_QUERY, "Codice IVA", ERR045); //NOTE codice errore 045
    if (!newValue.isEmpty())
        ui->cb_codiva->setCurrentText(newValue);
}

void ArticoloDialog::openAddSede()
{
    qDebug() << "ArticoloDialog::openAddSede()";
    QString newValue = allDlg(this, m_modelSede, ADD_SEDE_QUERY, "Sede magazzino", ERR046); //NOTE codice errore 046
    if (!newValue.isEmpty())
        ui->cb_sede->setCurrentText(newValue);
}

void ArticoloDialog::copyCodArt()
{
    qDebug() << "ArticoloDialog::copyCodArt()";
    QString codArticolo = ui->le_cod_articolo->text();
    ui->le_cod_fornitore->setText(codArticolo);
}
