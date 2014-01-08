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
    anagrafica_cols[0] = "Id";
    anagrafica_cols[1] = "Ragione sociale";
    anagrafica_cols[2] = "Tipo di ditta";
    anagrafica_cols[3] = "Nome";
    anagrafica_cols[4] = "Cognome";
    anagrafica_cols[5] = "Indirizzo";
    anagrafica_cols[6] = "Citta";
    anagrafica_cols[7] = "Provincia";
    anagrafica_cols[8] = "CAP";
    anagrafica_cols[9] = "Stato";
    anagrafica_cols[10] = "Codice fiscale";
    anagrafica_cols[11] = "Partita iva";
    anagrafica_cols[12] = "Agente";
    anagrafica_cols[13] = "Telefono";
    anagrafica_cols[14] = "Fax";
    anagrafica_cols[15] = "Cellulare";
    anagrafica_cols[16] = "Email";
    anagrafica_cols[17] = "Sito web";
    anagrafica_cols[18] = "Banca";
    anagrafica_cols[19] = "Agenzia";
    anagrafica_cols[20] = "Conto";
    anagrafica_cols[21] = "Swift";
    anagrafica_cols[22] = "Iban";
    anagrafica_cols[23] = "Destinazione merce";
    anagrafica_cols[24] = "Note";
}

void OptionsAnagraficaDialog::populateAnagraficaList(void)
{
    for (QMap<int,QString>::Iterator i = anagrafica_cols.begin(); i!=anagrafica_cols.end(); i++) {
        ui->lw_column_anagrafica->insertItem(i.key(), i.value());
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        col->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        col->setCheckState(Qt::Checked);
    }
}

void OptionsAnagraficaDialog::saveConfig(void)
{
    settings.beginGroup("AnagraficaCols");
    for (QMap<int,QString>::Iterator i=anagrafica_cols.begin(); i!=anagrafica_cols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        int checkState = col->checkState()==Qt::Checked ? 1 : 0;
        settings.setValue(QVariant(i.key()).toString(), checkState);
    }
    settings.endGroup();
}

void OptionsAnagraficaDialog::loadConfig(void)
{
    settings.beginGroup("AnagraficaCols");
    for (QMap<int,QString>::Iterator i=anagrafica_cols.begin(); i!=anagrafica_cols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        int status = settings.value(QVariant(i.key()).toString(), 1).toInt();
        col->setCheckState(status==1 ? Qt::Checked : Qt::Unchecked);
    }
    settings.endGroup();
}

void OptionsAnagraficaDialog::restoreToDefault(void)
{
    settings.beginGroup("AnagraficaCols");
    for (QMap<int,QString>::Iterator i=anagrafica_cols.begin(); i!=anagrafica_cols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        col->setCheckState(Qt::Checked);
        settings.setValue(QVariant(i.key()).toString(), 1);
    }
    settings.endGroup();
}
