#include "aziendadialog.h"
#include "ui_aziendadialog.h"

AziendaDialog::AziendaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AziendaDialog)
{
    qDebug() << "AziendaDialog()";
    ui->setupUi(this);

    initComboBox();
    setValue("0"); //richiamo l'unico record della tabella azienda
}

AziendaDialog::~AziendaDialog()
{
    qDebug() << "~AziendaDialog()";
    delete ui;
}

QSqlTableModel * AziendaDialog::setupComboBox(QString tablename, QComboBox *cb)
{
    qDebug() << "AziendaDialog::setupComboBox()";
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(tablename);
    model->setSort(DESCR, Qt::AscendingOrder);
    model->select();
    cb->setModel(model);
    cb->setModelColumn(DESCR);
    return model;
}

void AziendaDialog::initComboBox()
{
    qDebug() << "AziendaDialog::initComboBox()";
    m_modelCitta = setupComboBox(table::CITTA, ui->cittaCB);
    m_modelProvincia = setupComboBox(table::PROVINCIA, ui->provinciaCB);
    m_modelProvinciaREA = setupComboBox(table::PROVINCIA, ui->provinciaReaCB);
    m_modelCap = setupComboBox(table::CAP, ui->capCB);
    m_modelStato = setupComboBox(table::STATO, ui->statoCB);
    m_modelRegFiscale = setupComboBox(table::REG_FISCALE, ui->regFiscaleCB);
}

void AziendaDialog::setValueCB(QComboBox *box, QString value)
{
    qDebug() << "AziendaDialog::setValueCB()";
    box->setModelColumn(ID);
    int index = box->findText(value);
    box->setModelColumn(DESCR);
    box->setCurrentIndex(index);
}

void AziendaDialog::setValue(QString id)
{
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

    setValueCB(ui->regFiscaleCB, query.value(coldb::ID_REG_FISCALE).toString());
    setValueCB(ui->provinciaReaCB, query.value(coldb::ID_PROVINCIA_REA).toString());
    setValueCB(ui->cittaCB, query.value(coldb::ID_CITTA).toString());
    setValueCB(ui->provinciaCB, query.value(coldb::ID_PROVINCIA).toString());
    setValueCB(ui->capCB, query.value(coldb::ID_CAP).toString());
    setValueCB(ui->statoCB, query.value(coldb::ID_STATO).toString());

    m_logo.loadFromData(query.value(coldb::LOGO).toByteArray());
    if (m_logo.isNull())
        return;
    ui->logoImage->setPixmap(m_logo);
}

void AziendaDialog::prepareMap(void)
{
    qDebug() << "AziendaDialog::prepareMap()";
    m_mapAzienda[ph::RAG_SOCIALE] = ui->ragSocialeLE->text();
    m_mapAzienda[ph::NOME] = ui->nomeLE->text();
    m_mapAzienda[ph::COGNOME] = ui->cognomeLE->text();
    m_mapAzienda[ph::PRT_IVA] = ui->prtivaLE->text();
    m_mapAzienda[ph::COD_FISCALE] = ui->codfiscLE->text();
    m_mapAzienda[ph::ID_REG_FISCALE] = m_modelRegFiscale->index(
                ui->regFiscaleCB->currentIndex(), ID).data().toString();
    m_mapAzienda[ph::ID_PROVINCIA_REA] = m_modelProvinciaREA->index(
                ui->provinciaReaCB->currentIndex(), ID).data().toString();
    m_mapAzienda[ph::NUMERO_REA] = ui->numeroReaLE->text();
    m_mapAzienda[ph::INDIRIZZO] = ui->indirizzoLE->text();
    m_mapAzienda[ph::CITTA] = m_modelCitta->index(
                ui->cittaCB->currentIndex(), ID).data().toString();
    m_mapAzienda[ph::PROVINCIA] = m_modelProvincia->index(
                ui->provinciaCB->currentIndex(), ID).data().toString();
    m_mapAzienda[ph::CAP] = m_modelCap->index(
                ui->capCB->currentIndex(), ID).data().toString();
    m_mapAzienda[ph::STATO] = m_modelStato->index(
                ui->statoCB->currentIndex(), ID).data().toString();
    m_mapAzienda[ph::TEL] = ui->telLE->text();
    m_mapAzienda[ph::FAX] = ui->faxLE->text();
    m_mapAzienda[ph::EMAIL] = ui->emailLE->text();
}

void AziendaDialog::clearForm(void)
{
    qDebug() << "AziendaDialog::clearCombobox()";
    auto lineEditList = findChildren<QLineEdit *>();
    for (auto *le : lineEditList) {
        le->clear();
        le->setStyleSheet("");
    }

    auto comboBoxList = findChildren<QComboBox *>();
    for (auto *cb : comboBoxList)
        cb->setCurrentIndex(0);

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
    QString value = allDlg(this, m_modelCitta, ADD_CITTA_QUERY, "Città", "ERRORE DA DEFINIRE"); //NOTE codice errore
    ui->cittaCB->setCurrentText(value);
}

void AziendaDialog::openAddCap(void)
{
    qDebug() << "AziendaDialog::open_add_cap()";
    QString value = allDlg(this, m_modelCap, ADD_CAP_QUERY, "CAP", "ERRORE DA DEFINIRE"); //NOTE codice errore
    ui->capCB->setCurrentText(value);
}

void AziendaDialog::openAddLogo(void)
{
    qDebug() << "AziendaDialog::open_add_logo()";
    QString filename = QFileDialog::getOpenFileName(this, "Seleziona un immagine", ".",  "Images (*.png *.xpm *.jpg *.jpeg)");
    if (filename.isEmpty())
        return;

    m_logo.load(filename);
    m_logo = m_logo.scaled(LOGO_WIDTH, LOGO_HEIGHT, Qt::KeepAspectRatio);
    ui->logoImage->setPixmap(m_logo);
}

void AziendaDialog::save(void)
{
    qDebug() << "AziendaDialog::save()";
    prepareMap();

    if (m_mapAzienda[ph::RAG_SOCIALE].isEmpty() &&
            (m_mapAzienda[ph::NOME].isEmpty() ||
            m_mapAzienda[ph::COGNOME].isEmpty())) {
        showDialogError(this, "err1", "");
        ui->ragSocialeLE->setStyleSheet(css::warning);
        ui->nomeLE->setStyleSheet(css::warning);
        ui->cognomeLE->setStyleSheet(css::warning);
        return;
    }

    if (m_mapAzienda[ph::COD_FISCALE].isEmpty() ||
            m_mapAzienda[ph::PRT_IVA].isEmpty()) {
        showDialogError(this, "err2", "La partita IVA e il codice fiscale sono campi obbligatori");
        ui->prtivaLE->setStyleSheet(css::warning);
        ui->codfiscLE->setStyleSheet(css::warning);
        return;
    }

    if (m_mapAzienda[ph::NUMERO_REA].isEmpty()) {
        showDialogError(this, "err", "Il numero REA e' un campo obbligatorio");
        ui->numeroReaLE->setStyleSheet(css::warning);
        return;
    }

    if (!controlloPartitaIva(m_mapAzienda[ph::PRT_IVA]))
        if (!showDialogWarning(this, "err2", "Partita iva errata, vuoi continuare?"))
            return;

    if (!controlloCodiceFiscale(m_mapAzienda[ph::COD_FISCALE]))
        if (!showDialogWarning(this, "err3", "codice fiscale errato, vuoi continuare?"))
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

void AziendaDialog::checkRagSociale(QString str)
{
    qDebug() << "AziendaDialog::checkRagSociale()";
    bool status = str.isEmpty();
    if (!status) {
        ui->ragSocialeLE->setStyleSheet("");
        ui->nomeLE->clear();
        ui->nomeLE->setStyleSheet("");
        ui->cognomeLE->clear();
        ui->cognomeLE->setStyleSheet("");
    }
    ui->nomeLE->setEnabled(status);
    ui->cognomeLE->setEnabled(status);
}
