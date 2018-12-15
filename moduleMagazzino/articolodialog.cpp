#include "articolodialog.h"
#include "ui_articolodialog.h"

ArticoloDialog::ArticoloDialog(QWidget *parent) :
    CustomInsertDialog(parent),
    ui(new Ui::ArticoloDialog)
{
    qDebug() << "ArticoloDialog()";
    ui->setupUi(this);

    initForm();
    initComboBox();

    ui->dataLE->setDate(QDate::currentDate());
}

ArticoloDialog::~ArticoloDialog()
{
    qDebug() << "~ArticoloDialog()";
    delete ui;
}

void ArticoloDialog::initForm()
{
    qDebug() << "ArticoloDialog::initForm()";
    ui->descrizioneLE->setProperty(m_property, coldb::DESCRIZIONE);
    ui->fornitoreCB->setProperty(m_property, coldb::ID_FORNITORE);
    ui->marcaCB->setProperty(m_property, coldb::ID_MARCA);
    ui->modelloLE->setProperty(m_property, coldb::MODELLO);
    ui->codArticoloLE->setProperty(m_property, coldb::CODICE_ARTICOLO);
    ui->codFornitoreLE->setProperty(m_property, coldb::CODICE_FORNITORE);
    ui->codBarreLE->setProperty(m_property, coldb::CODICE_BARRE);
    ui->catmerceCB->setProperty(m_property, coldb::ID_MERCE);
    ui->codivaCB->setProperty(m_property, coldb::CODICE_IVA);
    ui->unitamisuraCB->setProperty(m_property, coldb::ID_UNITA);
    ui->scortaLE->setProperty(m_property, coldb::SCORTA_MINIMA);
    ui->quantitaLE->setProperty(m_property, coldb::QUANTITA);
    ui->prezzoFatturaLE->setProperty(m_property, coldb::PREZZO_FATTURA);
    ui->scontoLE->setProperty(m_property, coldb::SCONTO_FORNITORE);
    ui->ricaricoLE->setProperty(m_property, coldb::RICARICO);
    ui->prezzoAcquistoLE->setProperty(m_property, coldb::PREZZO_ACQUISTO);
    ui->ivaLE->setProperty(m_property, coldb::IVA);
    ui->prezzoFinitoLE->setProperty(m_property, coldb::PREZZO_FINITO);
    ui->prezzoVendita1LE->setProperty(m_property, coldb::PREZZO_VENDITA);
    ui->prezzoVendita2LE->setProperty(m_property, coldb::PREZZO_VENDITA_B);
    ui->fatturaLE->setProperty(m_property, coldb::FATTURA);
    ui->dataLE->setProperty(m_property, coldb::DATA_ARRIVO);
    ui->sedeCB->setProperty(m_property, coldb::ID_SEDE_MAGAZZINO);
    ui->noteTE->setProperty(m_property, coldb::NOTE);
}

void ArticoloDialog::initComboBox(void)
{
    qDebug() << "ArticoloDialog::initComboBox(void)";
    m_modelCatMerce = setupComboBox(table::CATEGORIA_MERCE, ui->catmerceCB, int(modelCols::descr));
    m_modelMarca = setupComboBox(table::MARCA, ui->marcaCB, int(modelCols::descr));
    m_modelSede = setupComboBox(table::SEDE_MAGAZZINO, ui->sedeCB, int(modelCols::descr));
    m_modelUnita = setupComboBox(table::UNITA_MISURA, ui->unitamisuraCB, int(modelCols::descr));

    m_modelFornitore = new QSqlQueryModel(this);
    m_modelFornitore->setQuery(magazzino::SELECT_CB_FORNITORE);
    ui->fornitoreCB->setModel(m_modelFornitore);
    ui->fornitoreCB->setModelColumn(int(modelCols::descr));

    //cb_codiva è collegato a updateiva tramite il segnale currentIndexChanged
    //devo bloccare il segnale prima di configurarlo, altrimenti a ogni impostazione
    //genera un segnale.
    ui->codivaCB->blockSignals(true);
    m_modelCodIva = setupComboBox(table::CODICE_IVA, ui->codivaCB, int(modelCols::descr));
    int index = ui->codivaCB->findText(m_settings.value(magazzino::DEFAULT_IVA).toString());
    ui->codivaCB->setCurrentIndex(index);
    ui->codivaCB->blockSignals(false);
}

void ArticoloDialog::setValue(QString id)
{
    qDebug() << "ArticoloDialog::setValue()";
    QSqlQuery query;
    query.prepare(magazzino::SELECT_ARTICOLO_FROM_ID);
    query.bindValue(ph::ID, id);
    if (!query.exec())
        showDialogError(this, ERR038, MSG010, query.lastError().text()); //NOTE codice errore 038

    query.first();

    for (auto *le : findChildren<QLineEdit *>()) {
        QString colName = le->property(m_property).toString();
        if (colName.isEmpty())
            continue;
        QString value = query.value(colName).toString();
        le->setText(value);
    }

    for (auto *cb : findChildren<QComboBox *>()) {
        QString colName = cb->property(m_property).toString();
        if (colName.isEmpty())
            continue;
        QString value = query.value(colName).toString();
        setValueCB(cb, value, int(modelCols::id));
    }

    ui->noteTE->setText(query.value(coldb::NOTE).toString());

    m_articoloMap[ph::ID] = id;

    setMoney(ui->prezzoAcquistoLE);
    setMoney(ui->prezzoVendita1LE);
    setMoney(ui->prezzoVendita2LE);

    if (ui->prezzoFatturaLE->text() == "0") {
        ui->prezzoFatturaLE->clear();
        ui->scontoLE->clear();
    }
    else
        setMoney(ui->prezzoFatturaLE);
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
    CustomInsertDialog::prepareMap(m_articoloMap, int(magazzino::cols::id));

    //Pulisco i campi contenuti nella QStringList placeholder
    QStringList placeholder = {ph::SCORTA, ph::QUANTIT, ph::PRZ_FAT,
                               ph::PRZ_ACQ, ph::IVA, ph::PRZ_VEN,
                               ph::PRZ_VEN_B, ph::PRZ_FIN};

    for (auto str : placeholder) {
        double value = stringToDouble(m_articoloMap[str]);
        m_articoloMap[str] = QString().setNum(value);
    }

    //Questo campo e' un combobox che viene gestito dalla funzione
    //prepareMap di CustomInsertDialog, ma la query al posto dell'id
    //vuole il valore dell'iva (si sono un coglione).
    m_articoloMap[ph::CODICE_IVA] = ui->codivaCB->currentText();

    if (m_articoloMap[ph::SCONTO].isEmpty())
        m_articoloMap[ph::SCONTO] = "0";

    if (m_articoloMap[ph::RICARIC].isEmpty())
        m_articoloMap[ph::RICARIC] = "0";
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

    if (m_articoloMap[ph::DESCRIZIONE].isEmpty()) {
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

void ArticoloDialog::setMoney(QLineEdit *le)
{
    qDebug() << "ArticoloDialog::setMoney()";
    QString prezzo = le->text();

    if (!prezzo.contains(locale().currencySymbol())) {
        prezzo = locale().toCurrencyString(stringToDouble(prezzo));
        le->setText(prezzo);
    }
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
    setMoney(ui->prezzoAcquistoLE);
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

void ArticoloDialog::updatePrezzi(void)
{
    qDebug() << "ArticoloDialog::updatePrezzi()";
    QLineEdit *le = qobject_cast<QLineEdit *>(sender());
    if (le->text().isEmpty())
        return;
    setMoney(le);
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

    //Trovo l'ultimo id inserito nel database (guarda query)
    QString id = dlg.getId();
    //Ricarico la query e seleziono il valore immesso
    m_modelFornitore->setQuery(magazzino::SELECT_CB_FORNITORE);
    ui->fornitoreCB->setModelColumn(int(magazzino::cols::id));
    ui->fornitoreCB->setCurrentText(id);
    ui->fornitoreCB->setModelColumn(int(magazzino::cols::descr));
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
//489
