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

    if (!showDialogWarning(this, "Attenzione", MSG023.arg(oldIvastr).arg(newIvastr))) {
        return;
    }

    QSqlQuery query;
    query.prepare(magazzino::SELECT_ARTICOLI_FROM_IVA);
    query.bindValue(magazzino::PH_COD_IVA, oldIvastr);
    query.exec();
    while (query.next()) {
        QString id = query.value(magazzino::COL_ID).toString();
        QString data = QDate::currentDate().toString("dd/MM/yyyy");
        QString quantita = query.value(magazzino::COL_QUANTITA).toString();
        QString prezzo_fattura = query.value(magazzino::COL_PREZZO_FATTURA).toString();
        QString sconto = query.value(magazzino::COL_SCONTO_FORNITORE).toString();
        QString ricarico = query.value(magazzino::COL_RICARICO).toString();
        QString fattura = query.value(magazzino::COL_FATTURA).toString();
        double prezzo_acquisto = query.value(magazzino::COL_PREZZO_ACQUISTO).toDouble();
        double prezzo_ricarico = 0;
        if (ricarico.contains("+")) {
            QStringList ricarichi = ricarico.split("+");
            QString s;
            prezzo_ricarico = prezzo_acquisto;
            foreach(s, ricarichi) {
                prezzo_ricarico += prezzo_ricarico * stringToDouble(s) / 100.0;
            }
        }
        else
            prezzo_ricarico = prezzo_acquisto + (prezzo_acquisto*ricarico.toDouble()/100.0);

        double iva = prezzo_ricarico*newIvastr/100.0;
        double prezzo_finito = prezzo_ricarico+iva;
        double prezzo_vendita = query.value(magazzino::COL_PREZZO_VENDITA).toDouble();
        if (prezzo_finito > prezzo_vendita) {
            prezzo_vendita = prezzo_finito;
        }

        QSqlQuery queryUpdateIva;
        queryUpdateIva.prepare(magazzino::UPDATE_ARTICOLI_FROM_IVA);
        queryUpdateIva.bindValue(magazzino::PH_ID, id);
        queryUpdateIva.bindValue(magazzino::PH_COD_IVA, newIvastr);
        queryUpdateIva.bindValue(magazzino::PH_IVA, iva);
        queryUpdateIva.bindValue(magazzino::PH_PRZ_FIN, prezzo_finito);
        queryUpdateIva.bindValue(magazzino::PH_PRZ_VEN, prezzo_vendita);
        queryUpdateIva.exec();

        QSqlQuery query_check_storico;
        query_check_storico.prepare(magazzino::CHECK_STORICO);
        query_check_storico.bindValue(magazzino::PH_ID_ART, id);
        query_check_storico.bindValue(magazzino::PH_DATA, data);
        query_check_storico.exec();

        QSqlQuery queryInsertStorico;
        if (query_check_storico.first()) {
            queryInsertStorico.prepare(magazzino::UPDATE_STORICO);
        }
        else {
            queryInsertStorico.prepare(magazzino::INSERT_STORICO);
        }

        queryInsertStorico.bindValue(magazzino::PH_ID_ART, id);
        queryInsertStorico.bindValue(magazzino::PH_DATA, data);
        queryInsertStorico.bindValue(magazzino::PH_QUANTIT, quantita);
        queryInsertStorico.bindValue(magazzino::PH_PRZ_FAT, prezzo_fattura);
        queryInsertStorico.bindValue(magazzino::PH_SCONTO, sconto);
        queryInsertStorico.bindValue(magazzino::PH_RICARIC, ricarico);
        queryInsertStorico.bindValue(magazzino::PH_PRZ_ACQ, prezzo_acquisto);
        queryInsertStorico.bindValue(magazzino::PH_IVA, iva);
        queryInsertStorico.bindValue(magazzino::PH_PRZ_FIN, prezzo_finito);
        queryInsertStorico.bindValue(magazzino::PH_PRZ_VEN, prezzo_vendita);
        queryInsertStorico.bindValue(magazzino::PH_FATTURA, fattura);
        queryInsertStorico.exec();
    }
}
