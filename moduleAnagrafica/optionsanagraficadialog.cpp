#include "optionsanagraficadialog.h"
#include "ui_optionsanagraficadialog.h"

OptionsAnagraficaDialog::OptionsAnagraficaDialog(CustomModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsAnagraficaDialog)
{
    qDebug() << "OptionsAnagraficaDialog()";
    ui->setupUi(this);

    anagraficaModel = model;
    prepareMap();
    populateAnagraficaList();
    loadConfig();
}

OptionsAnagraficaDialog::~OptionsAnagraficaDialog()
{
    qDebug() << "~OptionsAnagraficaDialog()";
    delete ui;
}

void OptionsAnagraficaDialog::prepareMap()
{
    qDebug() << "OptionsAnagraficaDialog::prepareMap()";
    anagraficaNameCols = prepareMapsFromModel(anagraficaModel);
}

void OptionsAnagraficaDialog::populateAnagraficaList(void)
{
    qDebug() << "OptionsAnagraficaDialog::populateAnagraficaList()";
    for (QMap<int,QString>::Iterator i = anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        ui->lw_column_anagrafica->insertItem(i.key(), i.value());
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        col->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        col->setCheckState(Qt::Checked);
    }
}

void OptionsAnagraficaDialog::saveConfig(void)
{
    qDebug() << "OptionsAnagraficaDialog::saveConfig()";
    settings.beginGroup(anagrafica::ANGRFC_STATUS);
    for (QMap<int,QString>::Iterator i=anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        int checkState = col->checkState()==Qt::Checked ? 1 : 0;
        settings.setValue(QVariant(i.key()).toString(), checkState);
    }
    settings.endGroup();

    settings.beginGroup(anagrafica::ANGRFC_COLORS);
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
    qDebug() << "OptionsAnagraficaDialog::loadConfig()";
    settings.beginGroup(anagrafica::ANGRFC_STATUS);
    for (QMap<int,QString>::Iterator i=anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        int status = settings.value(QVariant(i.key()).toString(), 1).toInt();
        col->setCheckState(status==1 ? Qt::Checked : Qt::Unchecked);
    }
    settings.endGroup();

    QColor color;
    settings.beginGroup(anagrafica::ANGRFC_COLORS);
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
    qDebug() << "OptionsAnagraficaDialog::restoreToDefault()";
    settings.beginGroup(anagrafica::ANGRFC_STATUS);
    for (QMap<int,QString>::Iterator i=anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        QListWidgetItem *col = ui->lw_column_anagrafica->item(i.key());
        col->setCheckState(Qt::Checked);
        settings.setValue(QVariant(i.key()).toString(), 1);
    }
    settings.endGroup();

    settings.beginGroup(anagrafica::ANGRFC_COLORS);
    for (QMap<int,QString>::Iterator i=anagraficaNameCols.begin(); i!=anagraficaNameCols.end(); i++) {
        settings.setValue(QVariant(i.key()).toString(), "-1");
    }
    settings.endGroup();
}

void OptionsAnagraficaDialog::setColumnColor(QModelIndex index)
{
    qDebug() << "OptionsAnagraficaDialog::setColumnColor()";
    QListWidgetItem *col = ui->lw_column_anagrafica->item(index.row());
    QColorDialog dlg(this);
    bool ok = dlg.exec();
    if (ok) {
        QColor color = dlg.selectedColor();
        col->setBackgroundColor(color);
    }
}
