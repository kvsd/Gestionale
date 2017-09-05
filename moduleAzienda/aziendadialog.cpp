#include "aziendadialog.h"
#include "ui_aziendadialog.h"

AziendaDialog::AziendaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AziendaDialog)
{
    qDebug() << "AziendaDialog()";
    ui->setupUi(this);

    initComboBox();
    setValue();
}

AziendaDialog::~AziendaDialog()
{
    qDebug() << "~AziendaDialog()";
    delete ui;
}

void AziendaDialog::initComboBox()
{
    qDebug() << "AziendaDialog::initComboBox()";
    modelCitta = new QSqlTableModel(this);
    modelCitta->setTable(table::CITTA);
    modelCitta->select();
    ui->cb_citta->setModel(modelCitta);
    ui->cb_citta->setModelColumn(azienda::COL_DESCR);

    modelProvincia = new QSqlTableModel(this);
    modelProvincia->setTable(table::PROVINCIA);
    modelProvincia->select();
    ui->cb_provincia->setModel(modelProvincia);
    ui->cb_provincia->setModelColumn(azienda::COL_DESCR);

    modelCap = new QSqlTableModel(this);
    modelCap->setTable(table::CAP);
    modelCap->select();
    ui->cb_cap->setModel(modelCap);
    ui->cb_cap->setModelColumn(azienda::COL_DESCR);

    modelStato = new QSqlTableModel(this);
    modelStato->setTable(table::STATO);
    modelStato->select();
    ui->cb_stato->setModel(modelStato);
    ui->cb_stato->setModelColumn(azienda::COL_DESCR);
}

void AziendaDialog::openAddCitta(void)
{
    qDebug() << "AziendaDialog::open_add_citta()";
    allDlg(this, modelCitta, ADD_CITTA_QUERY, "Città", ERR016); //NOTE codice errore 016.1
}

void AziendaDialog::openAddProvincia(void)
{
    qDebug() << "AziendaDialog::open_add_provincia()";
    allDlg(this, modelProvincia, ADD_PROVINCIA_QUERY, "Provincia", ERR017); //NOTE codice errore 017.1
}

void AziendaDialog::openAddCap(void)
{
    qDebug() << "AziendaDialog::open_add_cap()";
    allDlg(this, modelCap, ADD_CAP_QUERY, "CAP", ERR018); //NOTE codice errore 018.1
}

void AziendaDialog::openAddStato(void)
{
    qDebug() << "AziendaDialog::open_add_stato()";
    allDlg(this, modelStato, ADD_STATO_QUERY, "Stato", ERR019); //NOTE codice errore 019.1
}

void AziendaDialog::openAddLogo(void)
{
    qDebug() << "AziendaDialog::open_add_logo()";
    QString filename = QFileDialog::getOpenFileName(this, "Seleziona un immagine", ".",  "Images (*.png *.xpm *.jpg *.jpeg)");
    if (filename.isEmpty()) {
        return;
    }

    logo.load(filename);
    logo = logo.scaled(azienda::WIDTH, azienda::HEIGHT, Qt::KeepAspectRatio);
    ui->im_logo->setPixmap(logo);
}

void AziendaDialog::setValue(QString id)
{
    qDebug() << "AziendaDialog::setValue()";
    QSqlQuery query;
    query.prepare(azienda::SELECT_QUERY);
    query.bindValue(ph::ID, id);
    query.exec();
    query.first();

    ui->le_rag_sociale->setText(query.value(azienda::COL_RAG_SOC).toString());
    ui->le_nome->setText(query.value(azienda::COL_NOME).toString());
    ui->le_cognome->setText(query.value(azienda::COL_COGNOME).toString());
    ui->le_prtiva->setText(query.value(azienda::COL_PRT_IVA).toString());
    ui->le_codfisc->setText(query.value(azienda::COL_COD_FISC).toString());
    ui->le_indirizzo->setText(query.value(azienda::COL_INDIRIZZO).toString());

    ui->cb_citta->setModelColumn(azienda::COL_ID);
    int index = ui->cb_citta->findText(query.value(azienda::COL_CITTA).toString());
    ui->cb_citta->setModelColumn(azienda::COL_DESCR);
    ui->cb_citta->setCurrentIndex(index);

    ui->cb_provincia->setModelColumn(azienda::COL_ID);
    index = ui->cb_provincia->findText(query.value(azienda::COL_PROVINCIA).toString());
    ui->cb_provincia->setModelColumn(azienda::COL_DESCR);
    ui->cb_provincia->setCurrentIndex(index);

    ui->cb_cap->setModelColumn(azienda::COL_ID);
    index = ui->cb_cap->findText(query.value(azienda::COL_CAP).toString());
    ui->cb_cap->setModelColumn(azienda::COL_DESCR);
    ui->cb_cap->setCurrentIndex(index);

    ui->cb_stato->setModelColumn(azienda::COL_ID);
    index = ui->cb_stato->findText(query.value(azienda::COL_STATO).toString());
    ui->cb_stato->setModelColumn(azienda::COL_DESCR);
    ui->cb_stato->setCurrentIndex(index);

    ui->le_tel->setText(query.value(azienda::COL_TEL).toString());
    ui->le_fax->setText(query.value(azienda::COL_FAX).toString());
    ui->le_email->setText(query.value(azienda::COL_EMAIL).toString());

    ui->le_cciaa->setText(query.value(azienda::COL_CCIAA).toString());
    ui->le_iscr_trib->setText(query.value(azienda::COL_TRIB).toString());
    ui->le_reg_imprese->setText(query.value(azienda::COL_REG_IMPRESE).toString());

    logo.loadFromData(query.value(azienda::COL_LOGO).toByteArray());
    if (logo.isNull()) {
        return;
    }
    ui->im_logo->setPixmap(logo);
}

void AziendaDialog::prepareMap(void)
{
    qDebug() << "AziendaDialog::prepareMap()";
    mapAzienda[ph::RAG_SOCIALE] = ui->le_rag_sociale->text();
    mapAzienda[ph::NOME] = ui->le_nome->text();
    mapAzienda[ph::COGNOME] = ui->le_cognome->text();
    mapAzienda[ph::INDIRIZZO] = ui->le_indirizzo->text();
    mapAzienda[ph::CITTA] = modelCitta->index(ui->cb_citta->currentIndex(), azienda::COL_ID).data().toString();
    mapAzienda[ph::PROVINCIA] = modelProvincia->index(ui->cb_provincia->currentIndex(), azienda::COL_ID).data().toString();
    mapAzienda[ph::CAP] = modelCap->index(ui->cb_cap->currentIndex(), azienda::COL_ID).data().toString();
    mapAzienda[ph::STATO] = modelStato->index(ui->cb_stato->currentIndex(), azienda::COL_ID).data().toString();
    mapAzienda[ph::TEL] = ui->le_tel->text();
    mapAzienda[ph::FAX] = ui->le_fax->text();
    mapAzienda[ph::EMAIL] = ui->le_email->text();
    mapAzienda[ph::PRT_IVA] = ui->le_prtiva->text();
    mapAzienda[ph::COD_FISCALE] = ui->le_codfisc->text();
    mapAzienda[ph::ISCR_TRIB] = ui->le_iscr_trib->text();
    mapAzienda[ph::CCIAA] = ui->le_cciaa->text();
    mapAzienda[ph::REG_IMPRESE] = ui->le_reg_imprese->text();
}

void AziendaDialog::save(void)
{
    qDebug() << "AziendaDialog::save()";
    prepareMap();    

    if (mapAzienda[ph::RAG_SOCIALE].isEmpty()) {
        showDialogError(this, ERR029, MSG016); //NOTE codice errore 029
        ui->le_rag_sociale->setStyleSheet(azienda::CSS_WARNING_STYLE);
        return;
    }
    else if (mapAzienda[ph::INDIRIZZO].isEmpty()) {
        showDialogError(this, ERR030, MSG014); //NOTE codice errore 030
        ui->le_indirizzo->setStyleSheet(azienda::CSS_WARNING_STYLE);
        return;
    }
    else if (mapAzienda[ph::PRT_IVA].isEmpty() ||
             mapAzienda[ph::COD_FISCALE].isEmpty()) {
        showDialogError(this, ERR031, MSG018); //NOTE codice errore 031
        ui->le_prtiva->setStyleSheet(azienda::CSS_WARNING_STYLE);
        ui->le_codfisc->setStyleSheet(azienda::CSS_WARNING_STYLE);
        return;
    }

    if (!controlloPartitaIva(mapAzienda[ph::PRT_IVA])) {
        if (!showDialogWarning(this, ERR032, MSG019)) //NOTE codice errore 032
            return;
    }

    if (mapAzienda[ph::COD_FISCALE] != mapAzienda[ph::PRT_IVA]) {
        if (!controlloCodiceFiscale(mapAzienda[ph::COD_FISCALE])) {
            if (!showDialogWarning(this, ERR033, MSG020)) //NOTE codice errore 033
                return;
        }
    }

    QSqlQuery query;
    query.prepare(azienda::UPDATE_QUERY);
    QMapIterator <QString, QString>it(mapAzienda);
    while (it.hasNext()) {
        it.next();
        query.bindValue(it.key(), it.value());
    }

    //Per Salvare logo all'interno del database
    QByteArray array;
    QBuffer buffer(&array);
    buffer.open(QIODevice::WriteOnly);
    logo.save(&buffer, "PNG");
    query.bindValue(ph::LOGO, array);

    if (!query.exec()) {
        showDialogError(this, ERR012, MSG005, query.lastError().text()); //NOTE codice errore 012
        return;
    }
    this->accept();
}

void AziendaDialog::clearForm(void)
{
    qDebug() << "AziendaDialog::clearCombobox()";
    ui->cb_citta->setCurrentIndex(0);
    ui->cb_provincia->setCurrentIndex(0);
    ui->cb_cap->setCurrentIndex(0);
    ui->cb_stato->setCurrentIndex(0);
    ui->im_logo->clear();
    logo = QPixmap();
}

void AziendaDialog::copyPrtIva(void)
{
    qDebug() << "AziendaDialog::copy_prt_iva()";
    QString prtiva = ui->le_prtiva->text();
    ui->le_codfisc->setText(prtiva);
}
