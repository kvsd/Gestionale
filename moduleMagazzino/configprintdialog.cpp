#include "configprintdialog.h"
#include "ui_configprintdialog.h"

ConfigPrintDialog::ConfigPrintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigPrintDialog)
{
    ui->setupUi(this);

    populateList();
    sizeCols = magazzino::prepareMapsSizeColsArticolo();
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

    for (int i=0; i<rowCount; i++) {
        QString name = ui->layoutListWidget->item(i)->text();
        qDebug() << nameCols.key(name) << name << sizeCols.value(name);
    }
}
