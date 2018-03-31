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

    ui->dataLE->setDate(QDate::currentDate());
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
    m_modelCatMerce->setSort(magazzino::DESCR, Qt::AscendingOrder);
    m_modelCatMerce->select();

    m_modelCodIva = new QSqlTableModel(this);
    m_modelCodIva->setTable(table::CODICE_IVA);
    m_modelCodIva->setSort(magazzino::DESCR, Qt::AscendingOrder);
    m_modelCodIva->select();

    m_modelFornitore = new QSqlQueryModel(this);
    m_modelFornitore->setQuery(magazzino::SELECT_CB_FORNITORE);

    m_modelMarca = new QSqlTableModel(this);
    m_modelMarca->setTable(table::MARCA);
    m_modelMarca->setSort(magazzino::DESCR, Qt::AscendingOrder);
    m_modelMarca->select();

    m_modelSede = new QSqlTableModel(this);
    m_modelSede->setTable(table::SEDE_MAGAZZINO);
    m_modelSede->setSort(magazzino::DESCR, Qt::AscendingOrder);
    m_modelSede->select();

    m_modelUnita = new QSqlTableModel(this);
    m_modelUnita->setTable(table::UNITA_MISURA);
    m_modelUnita->setSort(magazzino::DESCR, Qt::AscendingOrder);
    m_modelUnita->select();
}

void ArticoloDialog::initComboBox(void)
{
    qDebug() << "ArticoloDialog::initComboBox()";
    ui->catmerceCB->setModel(m_modelCatMerce);
    ui->catmerceCB->setModelColumn(magazzino::DESCR);

    //cb_codiva è collegato a updateiva tramite il segnale currentIndexChanged
    //devo bloccare il segnale prima di configurarlo, altrimenti a ogni impostazione
    //genera un segnale.
    ui->codivaCB->blockSignals(true);
    ui->codivaCB->setModel(m_modelCodIva);
    ui->codivaCB->setModelColumn(magazzino::DESCR);
    int index = ui->codivaCB->findText(m_settings.value(magazzino::DEFAULT_IVA).toString());
    ui->codivaCB->setCurrentIndex(index);
    ui->codivaCB->blockSignals(false);

    ui->fornitoreCB->setModel(m_modelFornitore);
    ui->fornitoreCB->setModelColumn(magazzino::DESCR);

    ui->marcaCB->setModel(m_modelMarca);
    ui->marcaCB->setModelColumn(magazzino::DESCR);

    ui->sedeCB->setModel(m_modelSede);
    ui->sedeCB->setModelColumn(magazzino::DESCR);

    ui->unitamisuraCB->setModel(m_modelUnita);
    ui->unitamisuraCB->setModelColumn(magazzino::DESCR);
}

void ArticoloDialog::setValue(QString id, bool update)
{
    qDebug() << "ArticoloDialog::setValue()";
    QSqlQuery query;
    query.prepare(magazzino::SELECT_ARTICOLO_FROM_ID);
    query.bindValue(ph::ID, id);
    if (!query.exec())
        showDialogError(this, ERR038, MSG010, query.lastError().text()); //NOTE codice errore 038

    query.first();
    if (update)
        m_articoloMap[ph::ID] = id;
    ui->descrizioneLE->setText(query.value(coldb::DESCRIZIONE).toString());

    ui->fornitoreCB->setModelColumn(magazzino::ID);
    ui->fornitoreCB->setCurrentText(query.value(coldb::ID_FORNITORE).toString());
    ui->fornitoreCB->setModelColumn(magazzino::DESCR);

    ui->marcaCB->setModelColumn(magazzino::ID);
    ui->marcaCB->setCurrentText(query.value(coldb::ID_MARCA).toString());
    ui->marcaCB->setModelColumn(magazzino::DESCR);

    ui->modelloLE->setText(query.value(coldb::MODELLO).toString());
    ui->codArticoloLE->setText(query.value(coldb::CODICE_ARTICOLO).toString());
    ui->codFornitoreLE->setText(query.value(coldb::CODICE_FORNITORE).toString());
    ui->codBarreLE->setText(query.value(coldb::CODICE_BARRE).toString());

    ui->catmerceCB->setModelColumn(magazzino::ID);
    ui->catmerceCB->setCurrentText(query.value(coldb::ID_MERCE).toString());
    ui->catmerceCB->setModelColumn(magazzino::DESCR);

    ui->codivaCB->setModelColumn(magazzino::DESCR);
    ui->codivaCB->setCurrentText(query.value(coldb::CODICE_IVA).toString());

    ui->unitamisuraCB->setModelColumn(magazzino::ID);
    ui->unitamisuraCB->setCurrentText(query.value(coldb::ID_UNITA).toString());
    ui->unitamisuraCB->setModelColumn(magazzino::DESCR);

    ui->scortaLE->setText(query.value(coldb::SCORTA_MINIMA).toString());
    ui->quantitaLE->setText(query.value(coldb::QUANTITA).toString());
    ui->prezzoFatturaLE->setText(locale().toCurrencyString(query.value(coldb::PREZZO_FATTURA).toDouble()));
    freezeLineEdit(ui->prezzoAcquistoLE, !ui->prezzoFatturaLE->text().isEmpty());
    ui->scontoLE->setText(query.value(coldb::SCONTO_FORNITORE).toString());
    ui->ricaricoLE->setText(query.value(coldb::RICARICO).toString());
    ui->prezzoAcquistoLE->setText(locale().toCurrencyString(query.value(coldb::PREZZO_ACQUISTO).toDouble()));
    ui->ivaLE->setText(locale().toCurrencyString(query.value(coldb::IVA).toDouble()));
    ui->prezzoFinitoLE->setText(locale().toCurrencyString(query.value(coldb::PREZZO_FINITO).toDouble()));
    ui->prezzoVendita1LE->setText(locale().toCurrencyString(query.value(coldb::PREZZO_VENDITA).toDouble()));
    ui->prezzoVendita2LE->setText(locale().toCurrencyString(query.value(coldb::PREZZO_VENDITA_B).toDouble()));
    ui->fatturaLE->setText(query.value(coldb::FATTURA).toString());
    ui->dataLE->setDate(QDate::currentDate());

    ui->sedeCB->setModelColumn(magazzino::ID);
    ui->sedeCB->setCurrentText(query.value(coldb::ID_SEDE_MAGAZZINO).toString());
    ui->sedeCB->setModelColumn(magazzino::DESCR);

    ui->noteTE->setText(query.value(coldb::NOTE).toString());
}

void ArticoloDialog::setFornitore(QString str)
{
    qDebug() << "ArticoloDialog::setFornitore()";
    ui->fornitoreCB->setCurrentText(str);
}

void ArticoloDialog::setCategoria(QString str)
{
    qDebug() << "ArticoloDialog::setCategoria()";
    ui->catmerceCB->setCurrentText(str);
}

void ArticoloDialog::setMarca(QString str)
{
    qDebug() << "ArticoloDialog::setMarca()";
    ui->marcaCB->setCurrentText(str);
}

void ArticoloDialog::setSede(QString str)
{
    qDebug() << "ArticoloDialog::setSede()";
    ui->sedeCB->setCurrentText(str);
}

void ArticoloDialog::setFattura(QString str)
{
    qDebug() << "ArticoloDialog::setFattura()";
    ui->fatturaLE->setText(str);
}

void ArticoloDialog::prepareMap()
{
    qDebug() << "ArticoloDialog::prepareMap";
    m_articoloMap[ph::DESCR] = ui->descrizioneLE->text();
    m_articoloMap[ph::ID_MARC] = m_modelMarca->index(ui->marcaCB->currentIndex(),
                                                     magazzino::ID).data().toString();
    m_articoloMap[ph::MODELLO] = ui->modelloLE->text();
    m_articoloMap[ph::COD_ART] = ui->codArticoloLE->text();
    m_articoloMap[ph::COD_EAN] = ui->codBarreLE->text();
    m_articoloMap[ph::ID_MERC] = m_modelCatMerce->index(ui->catmerceCB->currentIndex(),
                                                        magazzino::ID).data().toString();
    m_articoloMap[ph::ID_UM] = m_modelUnita->index(ui->unitamisuraCB->currentIndex(),
                                                   magazzino::ID).data().toString();

    //Per i tipi numeri devo usare il locale C. Maledetto postgresql
    double scorta = stringToDouble(ui->scortaLE->text());
    m_articoloMap[ph::SCORTA] = QString().setNum(scorta);

    m_articoloMap[ph::ID_FORN] = m_modelFornitore->index(ui->fornitoreCB->currentIndex(),
                                                         magazzino::ID).data().toString();
    m_articoloMap[ph::COD_FRN] = ui->codFornitoreLE->text();

    double quantita = stringToDouble(ui->quantitaLE->text());
    m_articoloMap[ph::QUANTIT] = QString().setNum(quantita);

    double prezzo_fattura = stringToDouble(ui->prezzoFatturaLE->text());
    m_articoloMap[ph::PRZ_FAT] = QString().setNum(prezzo_fattura);

    QString sconto = ui->scontoLE->text();
    m_articoloMap[ph::SCONTO] = sconto.isEmpty() ? "0" : sconto;
    QString ricarico = ui->ricaricoLE->text();
    m_articoloMap[ph::RICARIC] = ricarico.isEmpty() ? "0" : ricarico;

    double prezzo_acquisto = stringToDouble(ui->prezzoAcquistoLE->text());
    m_articoloMap[ph::PRZ_ACQ] = QString().setNum(prezzo_acquisto);
    m_articoloMap[ph::COD_IVA] = ui->codivaCB->currentText();
    double iva = stringToDouble(ui->ivaLE->text());
    m_articoloMap[ph::IVA] = QString().setNum(iva);
    double prezzo_vend = stringToDouble(ui->prezzoVendita1LE->text());
    m_articoloMap[ph::PRZ_VEN] = QString().setNum(prezzo_vend);
    double prezzo_vend_b = stringToDouble(ui->prezzoVendita2LE->text());
    m_articoloMap[ph::PRZ_VEN_B] = QString().setNum(prezzo_vend_b);
    double prezzo_fin = stringToDouble(ui->prezzoFinitoLE->text());
    m_articoloMap[ph::PRZ_FIN] = QString().setNum(prezzo_fin);

    m_articoloMap[ph::ID_SEDE] = m_modelSede->index(ui->sedeCB->currentIndex(),
                                                    magazzino::ID).data().toString();
    m_articoloMap[ph::DATA_ARRIVO] = ui->dataLE->date().toString("dd/MM/yyyy");
    m_articoloMap[ph::FATTURA] = ui->fatturaLE->text();
    m_articoloMap[ph::NOTE] = ui->noteTE->toPlainText();
}

QSqlQuery ArticoloDialog::prepareQueryArticolo(void)
{
    qDebug() << "ArticoloDialog::prepareQueryArticolo()";
    QSqlQuery query_articolo;
    if (m_articoloMap.contains(ph::ID))
        query_articolo.prepare(magazzino::UPDATE_ARTICOLO);
    else
        query_articolo.prepare(magazzino::INSERT_ARTICOLO);

    for (QString &key : m_articoloMap.keys())
        query_articolo.bindValue(key, m_articoloMap[key]);

    return query_articolo;
}

QSqlQuery ArticoloDialog::prepareQueryStorico(void)
{
    qDebug() << "ArticoloDialog::prepareQueryStorico()";
    m_articoloMap[ph::ID_ART] = m_articoloMap[ph::ID];

    QSqlQuery query_check_storico;
    query_check_storico.prepare(magazzino::CHECK_STORICO);
    query_check_storico.bindValue(ph::ID_ART, m_articoloMap[ph::ID_ART]);
    query_check_storico.bindValue(ph::DATA_ARRIVO, m_articoloMap[ph::DATA_ARRIVO]);
    query_check_storico.exec();

    QSqlQuery query_storico;
    if (query_check_storico.first())
        query_storico.prepare(magazzino::UPDATE_STORICO);
    else
        query_storico.prepare(magazzino::INSERT_STORICO);

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
        ui->descrizioneLE->setStyleSheet(css::warning);
        db.rollback();
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
    QString prezzo_str = ui->prezzoFatturaLE->text();
    if (prezzo_str.isEmpty()) {
        freezeLineEdit(ui->prezzoAcquistoLE, false);
        return;
    }

    prezzo_str = locale().toCurrencyString(stringToDouble(prezzo_str));
    ui->prezzoFatturaLE->setText(prezzo_str);

    calculatePrezzoAcquisto();
    freezeLineEdit(ui->prezzoAcquistoLE, true);
}

void ArticoloDialog::freezeLineEdit(QLineEdit *le, bool status)
{
    qDebug() << "ArticoloDialog::freezeLineEdit()";
    le->setReadOnly(status);
    le->blockSignals(status);
    le->setStyleSheet(status ? css::warning : "");
}

void ArticoloDialog::calculatePrezzoAcquisto(void)
{
    qDebug() << "ArticoloDialog::calculatePrezzoAcquisto()";
    //Slot usata da le_sconto e dallo slot updatePrezzoFattura per calcolare
    //il prezzo d'acquisto e scriverlo in le_prezzo_acquisto.
    QString prezzo_str = ui->prezzoFatturaLE->text();
    if (prezzo_str.isEmpty())
        return;

    QString sconto_str = ui->scontoLE->text().replace("%", "");
    double prezzo = stringToDouble(prezzo_str);
    double prezzo_acquisto = setSconto(prezzo, sconto_str);
    ui->prezzoAcquistoLE->setText(locale().toCurrencyString(prezzo_acquisto));
    updateIva();
}

void ArticoloDialog::updatePrezzoAcquisto(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoAcquisto()";
    //Slot usato da le_prezzo_acquisto se non e' in modalita solo lettura.
    ui->scontoLE->clear();
    QString prezzo = ui->prezzoAcquistoLE->text();
    if (!prezzo.contains(locale().currencySymbol()))
        ui->prezzoAcquistoLE->setText((locale().toCurrencyString(stringToDouble(prezzo))));
    updateIva();
}

void ArticoloDialog::updateIva(void)
{
    qDebug() << "ArticoloDialog::updateIva()";
    if (ui->prezzoAcquistoLE->text().isEmpty() || ui->ricaricoLE->text().isEmpty())
        return;

    double prezzo = stringToDouble(ui->prezzoAcquistoLE->text());
    QString ricarico_str = ui->ricaricoLE->text().replace("%","");
    double prezzo_acquisto = setRicarico(prezzo, ricarico_str);

    double codiva = stringToDouble(ui->codivaCB->currentText())/100.0;
    double iva = prezzo_acquisto*codiva;
    ui->ivaLE->setText(locale().toCurrencyString(iva));

    double prezzo_finito = prezzo_acquisto+iva;
    ui->prezzoFinitoLE->setText(locale().toCurrencyString(prezzo_finito));
    double prezzo_vendita = stringToDouble(ui->prezzoVendita1LE->text());
    if (prezzo_vendita < prezzo_finito)
        ui->prezzoVendita1LE->setText(locale().toCurrencyString(prezzo_finito));
    if (ui->prezzoVendita2LE->text().isEmpty())
        ui->prezzoVendita2LE->setText(locale().toCurrencyString(prezzo_finito));
}

void ArticoloDialog::updatePrezzoFinito(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoFinito()";
    //Slot collegato a le_prezzo_finito.
    if (ui->prezzoFatturaLE->text().isEmpty())
        return;

    QString prezzo = ui->prezzoFinitoLE->text();
    if (!prezzo.contains(locale().currencySymbol()))
        ui->prezzoFinitoLE->setText(locale().toCurrencyString(stringToDouble(prezzo)));
}

void ArticoloDialog::updatePrezzoVendita(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoVendita()";
    //Slot collegato a le_prezzo_vendita.
    QString prezzo_ven = ui->prezzoVendita1LE->text();

    if (!prezzo_ven.contains(locale().currencySymbol())) {
        prezzo_ven = locale().toCurrencyString(stringToDouble(prezzo_ven));
        ui->prezzoVendita1LE->setText(prezzo_ven);
    }
}

void ArticoloDialog::updatePrezzoVenditaB(void)
{
    qDebug() << "ArticoloDialog::updatePrezzoVenditaB()";
    //Slot collegato a le_prezzo_venditaB.
    QString prezzo_ven = ui->prezzoVendita2LE->text();

    if (!prezzo_ven.contains(locale().currencySymbol())) {
        prezzo_ven = locale().toCurrencyString(stringToDouble(prezzo_ven));
        ui->prezzoVendita2LE->setText(prezzo_ven);
    }
}

void ArticoloDialog::openAddMarca()
{
    qDebug() << "ArticoloDialog::openAddMarca()";
    QString newValue = allDlg(this, m_modelMarca, ADD_MARCA_QUERY, "Marca", ERR042); //NOTE codice errore 042
    if (!newValue.isEmpty())
        ui->marcaCB->setCurrentText(newValue);
}

void ArticoloDialog::openAddCategoria()
{
    qDebug() << "ArticoloDialog::openAddCategoria()";
    QString newValue = allDlg(this, m_modelCatMerce, ADD_CAT_MERCE_QUERY, "Categoria merce", ERR043); //NOTE codice errore 043
    if (!newValue.isEmpty())
        ui->catmerceCB->setCurrentText(newValue);
}

void ArticoloDialog::openAddMisura()
{
    qDebug() << "ArticoloDialog::openAddMisura()";
    QString newValue = allDlg(this, m_modelUnita, ADD_UM_QUERY, "Unita di misura", ERR044); //NOTE codice errore 044
    if (!newValue.isEmpty())
        ui->unitamisuraCB->setCurrentText(newValue);
}

void ArticoloDialog::openAddFornitore()
{
    qDebug() << "ArticoloDialog::openAddFornitore()";
    AnagraficaAddDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok)
        return;

    //TODO modificare la query insert di AnagraficaAddDialog
    //in modo che ritorni l'id
    //Trovo l'ultimo id inserito nel database
    QSqlQuery query;
    query.prepare("select * from lastval();");
    query.exec();
    query.first();
    QString id = query.value(0).toString();
    //Ricarico la query e seleziono il valore immesso
    m_modelFornitore->setQuery(magazzino::SELECT_CB_FORNITORE);
    ui->fornitoreCB->setModelColumn(magazzino::ID);
    ui->fornitoreCB->setCurrentText(id);
    ui->fornitoreCB->setModelColumn(magazzino::DESCR);
}

void ArticoloDialog::openAddIVA()
{
    qDebug() << "ArticoloDialog::openAddIVA()";
    QString newValue = allDlg(this, m_modelCodIva, ADD_IVA_QUERY, "Codice IVA", ERR045); //NOTE codice errore 045
    if (!newValue.isEmpty())
        ui->codivaCB->setCurrentText(newValue);
}

void ArticoloDialog::openAddSede()
{
    qDebug() << "ArticoloDialog::openAddSede()";
    QString newValue = allDlg(this, m_modelSede, ADD_SEDE_QUERY, "Sede magazzino", ERR046); //NOTE codice errore 046
    if (!newValue.isEmpty())
        ui->sedeCB->setCurrentText(newValue);
}

void ArticoloDialog::copyCodArt()
{
    qDebug() << "ArticoloDialog::copyCodArt()";
    QString codArticolo = ui->codArticoloLE->text();
    ui->codFornitoreLE->setText(codArticolo);
}
