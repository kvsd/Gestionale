#include "optionsmagazzinodialog.h"
#include "ui_optionsmagazzinodialog.h"

OptionsMagazzinoDialog::OptionsMagazzinoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsMagazzinoDialog)
{
    ui->setupUi(this);

    prepareMaps();
    populateList();
    loadConfig();
}

OptionsMagazzinoDialog::~OptionsMagazzinoDialog()
{
    delete ui;
}

void OptionsMagazzinoDialog::prepareMaps()
{
    magazzinoNameCols[0] = "Id";
    magazzinoNameCols[1] = "Descrizione";
    magazzinoNameCols[2] = "Fornitore";
    magazzinoNameCols[3] = "Modello";
    magazzinoNameCols[4] = "Cod.Articolo";
    magazzinoNameCols[5] = "Cod.Fornitore";
    magazzinoNameCols[6] = "Cod.EAN";
    magazzinoNameCols[7] = "Cat.Merce";
    magazzinoNameCols[8] = "Cod.IVA";
    magazzinoNameCols[9] = "UM";
    magazzinoNameCols[10] = "Scorta Minima";
    magazzinoNameCols[11] = "Quantità";
    magazzinoNameCols[12] = "Prezzo Acquisto";
    magazzinoNameCols[13] = "Sconto";
    magazzinoNameCols[14] = "Ricarico";
    magazzinoNameCols[15] = "Imponibile";
    magazzinoNameCols[16] = "Iva";
    magazzinoNameCols[17] = "Prezzo Finito";
    magazzinoNameCols[18] = "Prezzo Vendità";
    magazzinoNameCols[19] = "Nr.Fattura";
    magazzinoNameCols[20] = "Data Arrivo";
    magazzinoNameCols[21] = "Sede Magazzino";
    magazzinoNameCols[22] = "Note";

    storicoNameCols[0] = "Id Articolo";
    storicoNameCols[1] = "Data";
    storicoNameCols[2] = QString::fromUtf8("Quantità");
    storicoNameCols[3] = "Prezzo acquisto";
    storicoNameCols[4] = "Sconto";
    storicoNameCols[5] = "Ricarico";
    storicoNameCols[6] = "Imponibile";
    storicoNameCols[7] = "IVA";
    storicoNameCols[8] = "Prezzo finito";
    storicoNameCols[9] = QString::fromUtf8("Vendità");
    storicoNameCols[10] = "Nr. Fattura";
}

void OptionsMagazzinoDialog::populateList(void)
{
    for (QMap<int,QString>::Iterator i = magazzinoNameCols.begin(); i!=magazzinoNameCols.end(); i++) {
        ui->magazzinoListView->insertItem(i.key(), i.value());
        QListWidgetItem *col = ui->magazzinoListView->item(i.key());
        col->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        col->setCheckState(Qt::Checked);
    }

    for (QMap<int,QString>::Iterator i = storicoNameCols.begin(); i!=storicoNameCols.end(); i++) {
        ui->storicoListView->insertItem(i.key(), i.value());
        QListWidgetItem *col = ui->storicoListView->item(i.key());
        col->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        col->setCheckState(Qt::Checked);
    }
}

void OptionsMagazzinoDialog::saveConfig(void)
{
    settings.beginGroup(magazzino::ARTICOLO_STATUS);
    for (QMap<int,QString>::Iterator i=magazzinoNameCols.begin(); i!=magazzinoNameCols.end(); i++) {
        QListWidgetItem *col = ui->magazzinoListView->item(i.key());
        int checkState = col->checkState()==Qt::Checked ? 1 : 0;
        settings.setValue(QVariant(i.key()).toString(), checkState);
    }
    settings.endGroup();

    settings.beginGroup(magazzino::ARTICOLO_COLORS);
    for (QMap<int,QString>::Iterator i=magazzinoNameCols.begin(); i!=magazzinoNameCols.end(); i++) {
        QListWidgetItem *col = ui->magazzinoListView->item(i.key());
        QColor color = col->background().color();
        if (color == QColor(Qt::transparent))
            settings.setValue(QVariant(i.key()).toString(), "-1");
        else
            settings.setValue(QVariant(i.key()).toString(), color.name());
    }
    settings.endGroup();

    settings.beginGroup(magazzino::STORICO_STATUS);
    for (QMap<int,QString>::Iterator i=storicoNameCols.begin(); i!=storicoNameCols.end(); i++) {
        QListWidgetItem *col = ui->storicoListView->item(i.key());
        int checkState = col->checkState()==Qt::Checked ? 1 : 0;
        settings.setValue(QVariant(i.key()).toString(), checkState);
    }
    settings.endGroup();

    settings.beginGroup(magazzino::STORICO_COLORS);
    for (QMap<int,QString>::Iterator i=storicoNameCols.begin(); i!=storicoNameCols.end(); i++) {
        QListWidgetItem *col = ui->storicoListView->item(i.key());
        QColor color = col->background().color();
        if (color == QColor(Qt::transparent))
            settings.setValue(QVariant(i.key()).toString(), "-1");
        else
            settings.setValue(QVariant(i.key()).toString(), color.name());
    }
    settings.endGroup();
}

void OptionsMagazzinoDialog::loadConfig(void)
{
    settings.beginGroup(magazzino::ARTICOLO_STATUS);
    for (QMap<int,QString>::Iterator i=magazzinoNameCols.begin(); i!=magazzinoNameCols.end(); i++) {
        QListWidgetItem *col = ui->magazzinoListView->item(i.key());
        int status = settings.value(QVariant(i.key()).toString(), 1).toInt();
        col->setCheckState(status==1 ? Qt::Checked : Qt::Unchecked);
    }
    settings.endGroup();

    QColor color;
    settings.beginGroup(magazzino::ARTICOLO_COLORS);
    for (QMap<int,QString>::Iterator i=magazzinoNameCols.begin(); i!=magazzinoNameCols.end(); i++) {
        QListWidgetItem *col = ui->magazzinoListView->item(i.key());
        QString colorStr = settings.value(QVariant(i.key()).toString(), "-1").toString();
        if (colorStr == "-1")
            color = QColor(Qt::transparent);
        else
            color.setNamedColor(colorStr);

        col->setBackground(QBrush(color));
    }
    settings.endGroup();

    settings.beginGroup(magazzino::STORICO_STATUS);
    for (QMap<int,QString>::Iterator i=storicoNameCols.begin(); i!=storicoNameCols.end(); i++) {
        QListWidgetItem *col = ui->storicoListView->item(i.key());
        int status = settings.value(QVariant(i.key()).toString(), 1).toInt();
        col->setCheckState(status==1 ? Qt::Checked : Qt::Unchecked);
    }
    settings.endGroup();

    settings.beginGroup(magazzino::STORICO_COLORS);
    for (QMap<int,QString>::Iterator i=storicoNameCols.begin(); i!=storicoNameCols.end(); i++) {
        QListWidgetItem *col = ui->storicoListView->item(i.key());
        QString colorStr = settings.value(QVariant(i.key()).toString(), "-1").toString();
        if (colorStr == "-1")
            color = QColor(Qt::transparent);
        else
            color.setNamedColor(colorStr);

        col->setBackground(QBrush(color));
    }
    settings.endGroup();
}

void OptionsMagazzinoDialog::restoreToDefault(void)
{
    settings.beginGroup(magazzino::ARTICOLO_STATUS);
    for (QMap<int,QString>::Iterator i=magazzinoNameCols.begin(); i!=magazzinoNameCols.end(); i++) {
        QListWidgetItem *col = ui->magazzinoListView->item(i.key());
        col->setCheckState(Qt::Checked);
        settings.setValue(QVariant(i.key()).toString(), 1);
    }
    settings.endGroup();

    settings.beginGroup(magazzino::ARTICOLO_COLORS);
    for (QMap<int,QString>::Iterator i=magazzinoNameCols.begin(); i!=magazzinoNameCols.end(); i++) {
        settings.setValue(QVariant(i.key()).toString(), "-1");
    }
    settings.endGroup();

    settings.beginGroup(magazzino::STORICO_STATUS);
    for (QMap<int,QString>::Iterator i=storicoNameCols.begin(); i!=storicoNameCols.end(); i++) {
        QListWidgetItem *col = ui->storicoListView->item(i.key());
        col->setCheckState(Qt::Checked);
        settings.setValue(QVariant(i.key()).toString(), 1);
    }
    settings.endGroup();

    settings.beginGroup(magazzino::STORICO_COLORS);
    for (QMap<int,QString>::Iterator i=storicoNameCols.begin(); i!=storicoNameCols.end(); i++) {
        settings.setValue(QVariant(i.key()).toString(), "-1");
    }
    settings.endGroup();

    loadConfig();
}

void OptionsMagazzinoDialog::setColumnColor(QModelIndex index)
{
    QListWidgetItem *col;
    if (ui->tabWidget->currentIndex() == magazzino::TAB_MAGAZZINO)
        col = ui->magazzinoListView->item(index.row());
    else if (ui->tabWidget->currentIndex() == magazzino::TAB_STORICO)
        col = ui->storicoListView->item(index.row());
    QColorDialog dlg(this);
    bool ok = dlg.exec();
    if (ok) {
        QColor color = dlg.selectedColor();
        col->setBackgroundColor(color);
    }
}
