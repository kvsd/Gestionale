#include "optionsanagraficadialog.h"
#include "ui_optionsanagraficadialog.h"

OptionsAnagraficaDialog::OptionsAnagraficaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsAnagraficaDialog)
{
    ui->setupUi(this);

    prepareMap();
    populateAnagraficaList();
    loadConfig();
}

OptionsAnagraficaDialog::~OptionsAnagraficaDialog()
{
    delete ui;
}

void OptionsAnagraficaDialog::prepareMap()
{
    mapAnagraficaCols[0] = "Id";
    mapAnagraficaCols[1] = "Ragione sociale";
    mapAnagraficaCols[2] = "Tipo di ditta";
    mapAnagraficaCols[3] = "Nome";
    mapAnagraficaCols[4] = "Cognome";
    mapAnagraficaCols[5] = "Indirizzo";
    mapAnagraficaCols[6] = "Citta";
    mapAnagraficaCols[7] = "Provincia";
    mapAnagraficaCols[8] = "CAP";
    mapAnagraficaCols[9] = "Stato";
    mapAnagraficaCols[10] = "Codice fiscale";
    mapAnagraficaCols[11] = "Partita iva";
    mapAnagraficaCols[12] = "Agente";
    mapAnagraficaCols[13] = "Telefono";
    mapAnagraficaCols[14] = "Fax";
    mapAnagraficaCols[15] = "Cellulare";
    mapAnagraficaCols[16] = "Email";
    mapAnagraficaCols[17] = "Sito web";
    mapAnagraficaCols[18] = "Banca";
    mapAnagraficaCols[19] = "Agenzia";
    mapAnagraficaCols[20] = "Conto";
    mapAnagraficaCols[21] = "Swift";
    mapAnagraficaCols[22] = "Iban";
    mapAnagraficaCols[23] = "Destinazione merce";
    mapAnagraficaCols[24] = "Note";
}

void OptionsAnagraficaDialog::populateAnagraficaList(void)
{
    for (QMap<int,QString>::Iterator i = mapAnagraficaCols.begin(); i!=mapAnagraficaCols.end(); i++) {
        ui->lw_column_anagrafica->insertItem(i.key(), i.value());
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        col->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        col->setCheckState(Qt::Checked);
    }
}

void OptionsAnagraficaDialog::saveConfig(void)
{
    settings.beginGroup("AnagraficaCols");
    for (QMap<int,QString>::Iterator i=mapAnagraficaCols.begin(); i!=mapAnagraficaCols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        int checkState = col->checkState()==Qt::Checked ? 1 : 0;
        settings.setValue(QVariant(i.key()).toString(), checkState);
    }
    settings.endGroup();
}

void OptionsAnagraficaDialog::loadConfig(void)
{
    settings.beginGroup("AnagraficaCols");
    for (QMap<int,QString>::Iterator i=mapAnagraficaCols.begin(); i!=mapAnagraficaCols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        int status = settings.value(QVariant(i.key()).toString(), 1).toInt();
        col->setCheckState(status==1 ? Qt::Checked : Qt::Unchecked);
    }
    settings.endGroup();
}

void OptionsAnagraficaDialog::restoreToDefault(void)
{
    settings.beginGroup("AnagraficaCols");
    for (QMap<int,QString>::Iterator i=mapAnagraficaCols.begin(); i!=mapAnagraficaCols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        col->setCheckState(Qt::Checked);
        settings.setValue(QVariant(i.key()).toString(), 1);
    }
    settings.endGroup();
}
