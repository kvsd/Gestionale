#include "aziendadialog.h"
#include "ui_aziendadialog.h"

AziendaDialog::AziendaDialog(QWidget *parent) :
    CustomInsertDialog(parent),
    ui(new Ui::AziendaDialog)
{
    qDebug() << "AziendaDialog()";
    ui->setupUi(this);

    initForm();
    initComboBox();
    setValue("0"); //richiamo l'unico record della tabella azienda
}

AziendaDialog::~AziendaDialog()
{
    qDebug() << "~AziendaDialog()";
    delete ui;
}

void AziendaDialog::initForm()
{
    qDebug() << "AziendaDialog::initForm()";
    ui->ragSocialeLE->setProperty(m_ph, coldb::RAGIONE_SOCIALE);
    ui->nomeLE->setProperty(m_ph, coldb::NOME);
    ui->cognomeLE->setProperty(m_ph, coldb::COGNOME);
    ui->prtivaLE->setProperty(m_ph, coldb::PARTITA_IVA);
    ui->codfiscLE->setProperty(m_ph, coldb::CODICE_FISCALE);
    ui->numeroReaLE->setProperty(m_ph, coldb::NUMERO_REA);
    ui->indirizzoLE->setProperty(m_ph, coldb::INDIRIZZO);
    ui->telLE->setProperty(m_ph, coldb::TEL);
    ui->faxLE->setProperty(m_ph, coldb::FAX);
    ui->emailLE->setProperty(m_ph, coldb::EMAIL);

    ui->regFiscaleCB->setProperty(m_ph, coldb::ID_REG_FISCALE);
    ui->provinciaReaCB->setProperty(m_ph, coldb::ID_PROVINCIA_REA);
    ui->statoLiquidCB->setProperty(m_ph, coldb::ID_STATO_LIQUID);
    ui->cittaCB->setProperty(m_ph, coldb::ID_CITTA);
    ui->provinciaCB->setProperty(m_ph, coldb::ID_PROVINCIA);
    ui->capCB->setProperty(m_ph, coldb::ID_CAP);
    ui->statoCB->setProperty(m_ph, coldb::ID_STATO);
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

    for (auto *le : findChildren<QLineEdit *>()) {
        QString colName = le->property(m_ph).toString();
        QString value = query.value(colName).toString();
        le->setText(value);
    }

    for (auto *cb : findChildren<QComboBox *>()) {
        QString colName = cb->property(m_ph).toString();
        QString value = query.value(colName).toString();
        setValueCB(cb, value, ID);
    }

    m_logo.loadFromData(query.value(coldb::LOGO).toByteArray());
    if (m_logo.isNull())
        return;
    ui->logoImage->setPixmap(m_logo);
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
    prepareMap(ID);

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
