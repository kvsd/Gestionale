#include "codivaupdatedialog.h"
#include "ui_codivaupdatedialog.h"

codIvaUpdateDialog::codIvaUpdateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::codIvaUpdateDialog)
{
    qDebug() << "codIvaUpdateDialog()";
    ui->setupUi(this);

    initModel();
    initComboBox();
}

codIvaUpdateDialog::~codIvaUpdateDialog()
{
    qDebug() << "~codIvaUpdateDialog()";
    delete ui;
}

void codIvaUpdateDialog::initModel(void)
{
    qDebug() << "codIvaUpdateDialog::initModel()";
    oldIvaModel = new QSqlTableModel(this);
    oldIvaModel->setTable(table::CODICE_IVA);
    oldIvaModel->select();

    newIvaModel = new QSqlTableModel(this);
    newIvaModel->setTable(table::CODICE_IVA);
    newIvaModel->select();
}

void codIvaUpdateDialog::initComboBox(void)
{
    qDebug() << "codIvaUpdateDialog::initComboBox()";
    ui->oldCodIvaComboBox->setModel(oldIvaModel);
    ui->oldCodIvaComboBox->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->newCodIvaComboBox->setModel(newIvaModel);
    ui->newCodIvaComboBox->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);
}

void codIvaUpdateDialog::updateIva(void)
{
    qDebug() << "codIvaUpdateDialog::updateIva()";
    int oldIvaIndex = ui->oldCodIvaComboBox->currentIndex();
    int newIvaIndex = ui->newCodIvaComboBox->currentIndex();

    int oldIvastr = oldIvaModel->record(oldIvaIndex).value(magazzino::COL_TABLE_DESCRIZIONE).toInt();
    int newIvastr = newIvaModel->record(newIvaIndex).value(magazzino::COL_TABLE_DESCRIZIONE).toInt();

    if (oldIvastr == newIvastr) {
        showDialogError(this, ERR057, MSG030);
        return;
    }

    if (!showDialogWarning(this, "Attenzione", MSG023.arg(oldIvastr).arg(newIvastr))) {
        return;
    }
    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << "Transaction start:" << db.transaction();

    QSqlQuery query;
    query.prepare(magazzino::SELECT_ARTICOLI_FROM_IVA);
    query.bindValue(ph::COD_IVA, oldIvastr);
    query.exec();
    while (query.next()) {
        QString id = query.value(coldb::ID).toString();
        QString data = QDate::currentDate().toString("dd/MM/yyyy");
        QString quantita = query.value(coldb::QUANTITA).toString();
        QString prezzo_fattura = query.value(coldb::PREZZO_FATTURA).toString();
        QString sconto = query.value(coldb::SCONTO_FORNITORE).toString();
        QString ricarico = query.value(coldb::RICARICO).toString();
        QString fattura = query.value(coldb::FATTURA).toString();
        double prezzo_acquisto = query.value(coldb::PREZZO_ACQUISTO).toDouble();
        double prezzo_ricarico = setRicarico(prezzo_acquisto, ricarico);
        double iva = prezzo_ricarico*newIvastr/100.0;
        double prezzo_finito = prezzo_ricarico+iva;
        double prezzo_vendita = query.value(coldb::PREZZO_VENDITA).toDouble();
        if (prezzo_finito > prezzo_vendita)
            prezzo_vendita = prezzo_finito;

        QSqlQuery queryUpdateIva;
        queryUpdateIva.prepare(magazzino::UPDATE_ARTICOLI_FROM_IVA);
        queryUpdateIva.bindValue(ph::ID, id);
        queryUpdateIva.bindValue(ph::COD_IVA, newIvastr);
        queryUpdateIva.bindValue(ph::IVA, iva);
        queryUpdateIva.bindValue(ph::PRZ_FIN, prezzo_finito);
        queryUpdateIva.bindValue(ph::PRZ_VEN, prezzo_vendita);
        if (!queryUpdateIva.exec()) {
            showDialogError(this, "Errore",
                            "Errore nell'aggiornamento della tabella articolo");
            db.rollback();
            return;
        }

        QSqlQuery query_check_storico;
        query_check_storico.prepare(magazzino::CHECK_STORICO);
        query_check_storico.bindValue(ph::ID_ART, id);
        query_check_storico.bindValue(ph::DATA_ARRIVO, data);
        query_check_storico.exec();

        QSqlQuery queryInsertStorico;
        if (query_check_storico.first())
            queryInsertStorico.prepare(magazzino::UPDATE_STORICO);
        else
            queryInsertStorico.prepare(magazzino::INSERT_STORICO);

        queryInsertStorico.bindValue(ph::ID_ART, id);
        queryInsertStorico.bindValue(ph::DATA_ARRIVO, data);
        queryInsertStorico.bindValue(ph::QUANTIT, quantita);
        queryInsertStorico.bindValue(ph::PRZ_FAT, prezzo_fattura);
        queryInsertStorico.bindValue(ph::SCONTO, sconto);
        queryInsertStorico.bindValue(ph::RICARIC, ricarico);
        queryInsertStorico.bindValue(ph::PRZ_ACQ, prezzo_acquisto);
        queryInsertStorico.bindValue(ph::IVA, iva);
        queryInsertStorico.bindValue(ph::PRZ_FIN, prezzo_finito);
        queryInsertStorico.bindValue(ph::PRZ_VEN, prezzo_vendita);
        queryInsertStorico.bindValue(ph::FATTURA, fattura);
        if (!queryInsertStorico.exec()) {
            showDialogError(this, "Errore",
                            "Errore nell'aggiornamento della tabella storico");
            db.rollback();
            return;
        }

    }
    qDebug() << "Transaction commited:" << db.commit();
}
