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
    anagraficaNameCols[0] = "Id";
    anagraficaNameCols[1] = "Ragione sociale";
    anagraficaNameCols[2] = "Tipo di ditta";
    anagraficaNameCols[3] = "Nome";
    anagraficaNameCols[4] = "Cognome";
    anagraficaNameCols[5] = "Indirizzo";
    anagraficaNameCols[6] = "Citta";
    anagraficaNameCols[7] = "Provincia";
    anagraficaNameCols[8] = "CAP";
    anagraficaNameCols[9] = "Stato";
    anagraficaNameCols[10] = "Codice fiscale";
    anagraficaNameCols[11] = "Partita iva";
    anagraficaNameCols[12] = "Agente";
    anagraficaNameCols[13] = "Telefono";
    anagraficaNameCols[14] = "Fax";
    anagraficaNameCols[15] = "Cellulare";
    anagraficaNameCols[16] = "Email";
    anagraficaNameCols[17] = "Sito web";
    anagraficaNameCols[18] = "Banca";
    anagraficaNameCols[19] = "Agenzia";
    anagraficaNameCols[20] = "Conto";
    anagraficaNameCols[21] = "Swift";
    anagraficaNameCols[22] = "Iban";
    anagraficaNameCols[23] = "Destinazione merce";
    anagraficaNameCols[24] = "Note";
}

void OptionsAnagraficaDialog::populateAnagraficaList(void)
{
    for (QMap<int,QString>::Iterator i = anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        ui->lw_column_anagrafica->insertItem(i.key(), i.value());
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        col->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        col->setCheckState(Qt::Checked);
    }
}

void OptionsAnagraficaDialog::saveConfig(void)
{
    settings.beginGroup("AnagraficaColsStatus");
    for (QMap<int,QString>::Iterator i=anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        int checkState = col->checkState()==Qt::Checked ? 1 : 0;
        settings.setValue(QVariant(i.key()).toString(), checkState);
    }
    settings.endGroup();

    settings.beginGroup("AnagraficaColsColors");
    for (QMap<int,QString>::Iterator i=anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        QColor color = col->background().color();
        if (color == QColor(Qt::transparent))
            settings.setValue(QVariant(i.key()).toString(), "-1");
        else
            settings.setValue(QVariant(i.key()).toString(), color.name());
    }
    settings.endGroup();
}

void OptionsAnagraficaDialog::loadConfig(void)
{
    settings.beginGroup("AnagraficaColsStatus");
    for (QMap<int,QString>::Iterator i=anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        int status = settings.value(QVariant(i.key()).toString(), 1).toInt();
        col->setCheckState(status==1 ? Qt::Checked : Qt::Unchecked);
    }
    settings.endGroup();

    QColor color;
    settings.beginGroup("AnagraficaColsColors");
    for (QMap<int,QString>::Iterator i=anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        QString colorStr = settings.value(QVariant(i.key()).toString(), "-1").toString();
        if (colorStr == "-1")
            color = QColor(Qt::transparent);
        else
            color.setNamedColor(colorStr);

        col->setBackground(QBrush(color));
    }
    settings.endGroup();
}

void OptionsAnagraficaDialog::restoreToDefault(void)
{
    settings.beginGroup("AnagraficaColsStatus");
    for (QMap<int,QString>::Iterator i=anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        col->setCheckState(Qt::Checked);
        settings.setValue(QVariant(i.key()).toString(), 1);
    }
    settings.endGroup();

    settings.beginGroup("AnagraficaColsColors");
    for (QMap<int,QString>::Iterator i=anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        settings.setValue(QVariant(i.key()).toString(), "-1");
    }
    settings.endGroup();
}

void OptionsAnagraficaDialog::setColumnColor(QModelIndex index)
{
    QListWidgetItem *col = ui->lw_column_anagrafica->item(index.row());
    QColorDialog dlg(this);
    bool ok = dlg.exec();
    if (ok) {
        QColor color = dlg.selectedColor();
        col->setBackgroundColor(color);
    }
}
