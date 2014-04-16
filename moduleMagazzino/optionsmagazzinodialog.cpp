#include "optionsmagazzinodialog.h"
#include "ui_optionsmagazzinodialog.h"

OptionsMagazzinoDialog::OptionsMagazzinoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsMagazzinoDialog)
{
    ui->setupUi(this);

    codIvaModel = new QSqlTableModel(this);
    codIvaModel->setTable(table::CODICE_IVA);
    codIvaModel->select();
    ui->codIvaComboBox->setModel(codIvaModel);
    ui->codIvaComboBox->setModelColumn(magazzino::COL_MG_DESCR);

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
    magazzinoNameCols = magazzino::prepareMapsNameColsArticolo();
    storicoNameCols = magazzino::prepareMapsNameColsStorico();
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

    settings.setValue(magazzino::DEFAULT_IVA, ui->codIvaComboBox->currentText());
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

    int index = ui->codIvaComboBox->findText(settings.value(magazzino::DEFAULT_IVA).toString(), 0);
    ui->codIvaComboBox->setCurrentIndex(index);
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

void OptionsMagazzinoDialog::setColumnColorMagazzino(QModelIndex index)
{
    QListWidgetItem *col;
    col = ui->magazzinoListView->item(index.row());

    QColorDialog dlg(this);
    bool ok = dlg.exec();
    if (ok) {
        QColor color = dlg.selectedColor();
        col->setBackgroundColor(color);
    }
}

void OptionsMagazzinoDialog::setColumnColorStorico(QModelIndex index)
{
    QListWidgetItem *col;
    col = ui->storicoListView->item(index.row());

    QColorDialog dlg(this);
    bool ok = dlg.exec();
    if (ok) {
        QColor color = dlg.selectedColor();
        col->setBackgroundColor(color);
    }
}

