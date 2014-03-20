#include "configprintdialog.h"
#include "ui_configprintdialog.h"

ConfigPrintDialog::ConfigPrintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigPrintDialog)
{
    ui->setupUi(this);

    populateList();
    sizeCols = magazzino::prepareMapsSizeColsArticolo();
    loadSettings();
}

ConfigPrintDialog::~ConfigPrintDialog()
{
    delete ui;
}

void ConfigPrintDialog::populateList()
{
    nameCols = magazzino::prepareMapsNameColsArticolo();
    for (QMap<int,QString>::Iterator i = nameCols.begin(); i!=nameCols.end(); i++) {
        ui->columnListWidget->insertItem(i.key(), i.value());
        QListWidgetItem *col = ui->columnListWidget->item(i.key());
        col->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
}

void ConfigPrintDialog::loadSettings()
{
    QStringList default_list;
    default_list.append(nameCols.value(5));
    default_list.append(nameCols.value(1));
    default_list.append(nameCols.value(16));
    default_list.append(nameCols.value(18));
    default_list.append(nameCols.value(19));

    QStringList cols_list = settings.value(magazzino::LISTINO_COLS_ORDER, default_list).toStringList();

    for (int i=0; i<cols_list.length(); i++) {
        ui->layoutListWidget->addItem(cols_list[i]);
    }
}

void ConfigPrintDialog::addColumn(void)
{
    QListWidgetItem *col = ui->columnListWidget->currentItem();
    if (!col) {
        //TODO dialog error
        return;
    }
    ui->layoutListWidget->addItem(col->text());
}

void ConfigPrintDialog::removeColumn(void)
{
    int row = ui->layoutListWidget->currentRow();
    if (row == -1) {
        //TODO dialog error
        return;
    }
    QListWidgetItem *col = ui->layoutListWidget->takeItem(row);
    delete col;
}

void ConfigPrintDialog::save(void)
{
    int rowCount = ui->layoutListWidget->count();

    if (!rowCount) {
        //TODO dialog error
        return;
    }

    QStringList cols_listino;
    for (int i=0; i<rowCount; i++) {
        QString name = ui->layoutListWidget->item(i)->text();
        cols_listino.append(name);
    }

    settings.setValue(magazzino::LISTINO_COLS_ORDER, cols_listino);
}
