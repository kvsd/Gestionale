#include "aziendadialog.h"
#include "ui_aziendadialog.h"

AziendaDialog::AziendaDialog(QWidget *parent) :
    CustomInsertDialog(parent),
    ui(new Ui::AziendaDialog)
{
    qDebug() << "AziendaDialog()";
    ui->setupUi(this);

    initComboBox();
    setValue("0"); //richiamo l'unico record della tabella azienda
    const char * m_ph = "placeholder";
    ui->ragSocialeLE->setProperty(m_ph, ph::RAG_SOCIALE);
    ui->nomeLE->setProperty(m_ph, ph::NOME);
    ui->cognomeLE->setProperty(m_ph, ph::COGNOME);
    ui->prtivaLE->setProperty(m_ph, ph::PRT_IVA);
    ui->codfiscLE->setProperty(m_ph, ph::COD_FISCALE);
    ui->numeroReaLE->setProperty(m_ph, ph::NUMERO_REA);
    ui->indirizzoLE->setProperty(m_ph, ph::INDIRIZZO);
    ui->telLE->setProperty(m_ph, ph::TEL);
    ui->faxLE->setProperty(m_ph, ph::FAX);
    ui->emailLE->setProperty(m_ph, ph::EMAIL);

    ui->regFiscaleCB->setProperty(m_ph, ph::ID_REG_FISCALE);
    ui->provinciaReaCB->setProperty(m_ph, ph::ID_PROVINCIA_REA);
    ui->statoLiquidCB->setProperty(m_ph, ph::ID_STATO_LIQUID);
    ui->cittaCB->setProperty(m_ph, ph::CITTA);
    ui->provinciaCB->setProperty(m_ph, ph::PROVINCIA);
    ui->capCB->setProperty(m_ph, ph::CAP);
    ui->statoCB->setProperty(m_ph, ph::STATO);
}

AziendaDialog::~AziendaDialog()
{
    qDebug() << "~AziendaDialog()";
    delete ui;
}

void AziendaDialog::initComboBox()
{
    //Inizializza i combobox
    qDebug() << "AziendaDialog::initComboBox()";
    m_modelCitta = setupComboBox(table::CITTA, ui->cittaCB, DESCR);
    m_modelProvincia = setupComboBox(table::PROVINCIA, ui->provinciaCB, DESCR);
    m_modelProvinciaREA = setupComboBox(table::PROVINCIA, ui->provinciaReaCB, DESCR);
    m_modelCap = setupComboBox(table::CAP, ui->capCB, DESCR);
    m_modelStato = setupComboBox(table::STATO, ui->statoCB, DESCR);
    m_modelRegFiscale = setupComboBox(table::REG_FISCALE, ui->regFiscaleCB, DESCR);
    m_modelLiquidazione = setupComboBox(table::STATO_LIQUID, ui->statoLiquidCB, DESCR);
}

void AziendaDialog::setValue(QString id)
{
    //Imposta i dati salvati del db nel Dialog per poterli modificare.
    qDebug() << "AziendaDialog::setValue()";
    QSqlQuery query;
    query.prepare(azienda::SELECT_QUERY);
    query.bindValue(ph::ID, id);
    query.exec();
    query.first();

    ui->ragSocialeLE->setText(query.value(coldb::RAGIONE_SOCIALE).toString());
    ui->nomeLE->setText(query.value(coldb::NOME).toString());
    ui->cognomeLE->setText(query.value(coldb::COGNOME).toString());
    ui->prtivaLE->setText(query.value(coldb::PARTITA_IVA).toString());
    ui->codfiscLE->setText(query.value(coldb::CODICE_FISCALE).toString());
    ui->numeroReaLE->setText(query.value(coldb::NUMERO_REA).toString());
    ui->indirizzoLE->setText(query.value(coldb::INDIRIZZO).toString());
    ui->telLE->setText(query.value(coldb::TEL).toString());
    ui->faxLE->setText(query.value(coldb::FAX).toString());
    ui->emailLE->setText(query.value(coldb::EMAIL).toString());

    setValueCB(ui->regFiscaleCB, query.value(coldb::ID_REG_FISCALE).toString(), ID);
    setValueCB(ui->provinciaReaCB, query.value(coldb::ID_PROVINCIA_REA).toString(), ID);
    setValueCB(ui->statoLiquidCB, query.value(coldb::ID_STATO_LIQUID).toString(), ID);
    setValueCB(ui->cittaCB, query.value(coldb::ID_CITTA).toString(), ID);
    setValueCB(ui->provinciaCB, query.value(coldb::ID_PROVINCIA).toString(), ID);
    setValueCB(ui->capCB, query.value(coldb::ID_CAP).toString(), ID);
    setValueCB(ui->statoCB, query.value(coldb::ID_STATO).toString(), ID);

    m_logo.loadFromData(query.value(coldb::LOGO).toByteArray());
    if (m_logo.isNull())
        return;
    ui->logoImage->setPixmap(m_logo);
}

void AziendaDialog::prepareMap(void)
{
    qDebug() << "AziendaDialog::prepareMap()";
    for (auto *le : findChildren<QLineEdit *>()) {
        QString ph = le->property("placeholder").toString();
        if (ph.isEmpty())
            continue;
        QString value = le->text();
        m_mapAzienda[ph] = value;
    }

    //Legge i combobox
    for (auto *cb : findChildren<QComboBox *>()) {
        QString ph = cb->property("placeholder").toString();
        if (ph.isEmpty())
            continue;
        int oldCol = cb->modelColumn();
        cb->setModelColumn(ID);
        QString value = cb->currentText();
        m_mapAzienda[ph] = value;
        cb->setModelColumn(oldCol);
    }
}

void AziendaDialog::clearForm(void)
{
    //Slot cancella i dati immessi dall'utente.
    CustomInsertDialog::clearForm();

    ui->logoImage->clear();
    m_logo = QPixmap();
}

void AziendaDialog::copyPrtIva(void)
{
    qDebug() << "AziendaDialog::copy_prt_iva()";
    //Funzione slot che copia la partita iva nel codice fiscale
    QString prtiva = ui->prtivaLE->text();
    ui->codfiscLE->setText(prtiva);
}

void AziendaDialog::openAddCitta(void)
{
    qDebug() << "AziendaDialog::open_add_citta()";
    QString value = allDlg(this, m_modelCitta, ADD_CITTA_QUERY, "Città", ERR029); //NOTE codice errore 029
    ui->cittaCB->setCurrentText(value);
}

void AziendaDialog::openAddCap(void)
{
    qDebug() << "AziendaDialog::open_add_cap()";
    QString value = allDlg(this, m_modelCap, ADD_CAP_QUERY, "CAP", ERR030); //NOTE codice errore 030
    ui->capCB->setCurrentText(value);
}

void AziendaDialog::openAddLogo(void)
{
    qDebug() << "AziendaDialog::open_add_logo()";
    QString filename = QFileDialog::getOpenFileName(this, "Seleziona un immagine",
                                                    ".",  "Images (*.png *.xpm *.jpg *.jpeg)");
    if (filename.isEmpty())
        return;

    m_logo.load(filename);
    m_logo = m_logo.scaled(LOGO_WIDTH, LOGO_HEIGHT, Qt::KeepAspectRatio);
    ui->logoImage->setPixmap(m_logo);
}

bool AziendaDialog::checkLineEdit(QLineEdit *le, QString nomeCampo="")
{
    qDebug() << "AziendaDialog::checkLineEdit()";
    if (le->text().isEmpty()) {
        showDialogError(this, ERR034, MSG031.arg(nomeCampo)); //NOTE codice errore 034
        le->setStyleSheet(css::warning);
        return false;
    }
    return true;
}

bool AziendaDialog::checkComboBox(QComboBox *cb, QString nomeCampo="")
{
    qDebug() << "AziendaDialog::checkComboBox()";
    if (cb->currentIndex() == 0) {
        showDialogError(this, ERR035, MSG032.arg(nomeCampo)); //NOTE codice errore 035
        cb->setStyleSheet(css::warning_cb);
        return false;
    }
    return true;
}

bool AziendaDialog::checkValues()
{
    //Funzione che controlla i dati inseriti dall'utente.
    qDebug() << "AziendaDialog::checkValue()";
    QString rag = ui->ragSocialeLE->text();
    QString nome = ui->nomeLE->text();
    QString cognome = ui->cognomeLE->text();

    //Il campo ragione sociale escude i campi nome e cognome
    if ((!rag.isEmpty() && (!nome.isEmpty() || !cognome.isEmpty())) ||
        (rag.isEmpty() && nome.isEmpty() && cognome.isEmpty()) ||
        (rag.isEmpty() && (nome.isEmpty() || cognome.isEmpty())) ) {
        ui->ragSocialeLE->setStyleSheet(css::warning);
        ui->nomeLE->setStyleSheet(css::warning);
        ui->cognomeLE->setStyleSheet(css::warning);
        //NOTE codice errore 033
        showDialogError(this, ERR033, MSG016);
        return false;
    }

    //Controllo se i campi obbligatori sono stati inseriti.
    if (!checkLineEdit(ui->prtivaLE, "partita IVA") ||
            !checkLineEdit(ui->codfiscLE, "codice fiscale") ||
            !checkComboBox(ui->regFiscaleCB, "regime fiscale") ||
            !checkComboBox(ui->provinciaReaCB, "ufficio rea") ||
            !checkLineEdit(ui->numeroReaLE, "numero rea") ||
            !checkComboBox(ui->statoLiquidCB, "stato liquidazione") ||
            !checkLineEdit(ui->indirizzoLE, "indirizzo") ||
            !checkComboBox(ui->cittaCB, "citta") ||
            !checkComboBox(ui->provinciaCB, "provincia") ||
            !checkComboBox(ui->capCB, "CAP") ||
            !checkComboBox(ui->statoCB, "stato"))
        return false;

    //Controllo se partita iva e codice fiscale sono corretti;
    if (!controlloPartitaIva(m_mapAzienda[ph::PRT_IVA]))
        if (!showDialogWarning(this, ERR031, MSG019)) //NOTE codice errore 031
            return false;
    if (!controlloCodiceFiscale(m_mapAzienda[ph::COD_FISCALE]))
        if (!showDialogWarning(this, ERR032, MSG020)) //NOTE codice errore 032
            return false;

    return true;
}

void AziendaDialog::save(void)
{
    qDebug() << "AziendaDialog::save()";
    prepareMap();

    if (!checkValues())
        return;

    QSqlQuery query;
    query.prepare(azienda::UPDATE_QUERY);
    for (QString key : m_mapAzienda.keys())
        query.bindValue(key, m_mapAzienda[key]);

    //Per Salvare logo all'interno del database
    QByteArray array;
    QBuffer buffer(&array);
    buffer.open(QIODevice::WriteOnly);
    m_logo.save(&buffer, "PNG");
    query.bindValue(ph::LOGO, array);

    if (!query.exec()) {
        showDialogError(this, ERR012, MSG005, query.lastError().text()); //NOTE codice errore 012
        return;
    }
    this->accept();
}
