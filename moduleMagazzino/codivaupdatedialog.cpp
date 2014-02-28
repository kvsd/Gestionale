#include "codivaupdatedialog.h"
#include "ui_codivaupdatedialog.h"

codIvaUpdateDialog::codIvaUpdateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::codIvaUpdateDialog)
{
    ui->setupUi(this);

    initModel();
    initComboBox();
}

codIvaUpdateDialog::~codIvaUpdateDialog()
{
    delete ui;
}

void codIvaUpdateDialog::initModel(void)
{
    oldIvaModel = new QSqlTableModel(this);
    oldIvaModel->setTable(table::CODICE_IVA);
    oldIvaModel->select();

    newIvaModel = new QSqlTableModel(this);
    newIvaModel->setTable(table::CODICE_IVA);
    newIvaModel->select();
}

void codIvaUpdateDialog::initComboBox(void)
{
    ui->oldCodIvaComboBox->setModel(oldIvaModel);
    ui->oldCodIvaComboBox->setModelColumn(magazzino::COL_DESCR);

    ui->newCodIvaComboBox->setModel(newIvaModel);
    ui->newCodIvaComboBox->setModelColumn(magazzino::COL_DESCR);
}

void codIvaUpdateDialog::updateIva(void)
{
    QString oldIvaId = oldIvaModel->index(ui->oldCodIvaComboBox->currentIndex(), magazzino::COL_ID).data().toString();
    QString newIvaId = oldIvaModel->index(ui->newCodIvaComboBox->currentIndex(), magazzino::COL_ID).data().toString();

    int oldIvastr = oldIvaModel->index(ui->oldCodIvaComboBox->currentIndex(), magazzino::COL_DESCR).data().toInt();
    int newIvastr = newIvaModel->index(ui->newCodIvaComboBox->currentIndex(), magazzino::COL_DESCR).data().toInt();

    if (!showDialogWarning(this, "Attenzione", MSG023.arg(oldIvastr).arg(newIvastr))) {
        return;
    }

    QSqlQuery query;
    query.prepare(magazzino::SELECT_ARTICOLI_FROM_IVA);
    query.bindValue(":cod_iva", oldIvaId);
    query.exec();
    while (query.next()) {
        QString id = query.value(magazzino::COL_ID).toString();
        QString data = QDate::currentDate().toString("dd/MM/yyyy");
        QString quantita = query.value(magazzino::COL_QUANTITA).toString();
        QString prezzo_acquisto = query.value(magazzino::COL_PREZZO_ACQ).toString();
        QString sconto = query.value(magazzino::COL_SCONTO).toString();
        QString ricarico = query.value(magazzino::COL_RICARICO).toString();
        QString fattura = query.value(magazzino::COL_FATTURA).toString();
        double imponibile = query.value(magazzino::COL_IMPONIBILE).toDouble();
        double iva = imponibile*newIvastr/100.0;
        double prezzo_finito = imponibile+iva;
        double prezzo_vendita = prezzo_finito;

        QSqlQuery queryUpdateIva;
        queryUpdateIva.prepare(magazzino::UPDATE_ARTICOLI_FROM_IVA);
        queryUpdateIva.bindValue(":id", id);
        queryUpdateIva.bindValue(":cod_iva", newIvaId);
        queryUpdateIva.bindValue(":iva", iva);
        queryUpdateIva.bindValue(":prezzo_finito", prezzo_finito);
        queryUpdateIva.bindValue(":prezzo_vendita", prezzo_vendita);
        queryUpdateIva.exec();

        QSqlQuery queryInsertStorico;
        queryInsertStorico.prepare(magazzino::INSERT_STORICO);
        queryInsertStorico.bindValue(":id_articolo", id);
        queryInsertStorico.bindValue(":data_arrivo", data);
        queryInsertStorico.bindValue(":quantita", quantita);
        queryInsertStorico.bindValue(":prezzo_acquisto", prezzo_acquisto);
        queryInsertStorico.bindValue(":sconto_fornitore", sconto);
        queryInsertStorico.bindValue(":ricarico", ricarico);
        queryInsertStorico.bindValue(":imponibile", imponibile);
        queryInsertStorico.bindValue(":iva", iva);
        queryInsertStorico.bindValue(":prezzo_finito", prezzo_finito);
        queryInsertStorico.bindValue(":prezzo_vendita", prezzo_vendita);
        queryInsertStorico.bindValue(":fattura", fattura);
        queryInsertStorico.exec();
    }
}
