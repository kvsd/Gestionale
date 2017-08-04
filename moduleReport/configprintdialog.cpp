#include "configprintdialog.h"
#include "ui_configprintdialog.h"

ConfigPrintDialog::ConfigPrintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigPrintDialog)
{
    qDebug() << "ConfigPrintDialog()";
    ui->setupUi(this);
    initModel();
    loadSettings();
}

ConfigPrintDialog::~ConfigPrintDialog()
{
    qDebug() << "~ConfigPrintDialog()";
    delete ui;
}

void ConfigPrintDialog::setPage(int page, bool status)
{
    ui->tabWidget->setTabEnabled(page, status);
}

void ConfigPrintDialog::initModel()
{
    qDebug() << "ConfigPrintDialog::initModel()";
    model = new QSqlQueryModel(this);
    model->setQuery(magazzino::SELECT_ARTICOLI_ALL);
    headerMap = prepareMapsFromModel(model);
    colsModel = new QStringListModel(headerMap.values(), this);
}

void ConfigPrintDialog::loadTableSettings(QTableWidget *table, QString settingsName)
{
    qDebug() << "ConfigPrintDialog::loadTableSettings()";
    settings.beginGroup(settingsName);
    for (QString key : settings.allKeys()) {
        QStringList values = settings.value(key).toStringList();
        addRow(table);
        setRow(table, key.toInt(), values);
    }
    settings.endGroup();
}

void ConfigPrintDialog::loadSettings()
{
    qDebug() << "ConfigPrintDialog::loadSettings()";
    loadTableSettings(ui->listinoTableWidget, report::listinoCols);
    loadTableSettings(ui->ordineTableWidget, report::ordineCols);
}

void ConfigPrintDialog::addRow(QTableWidget *table)
{
    qDebug() << "ConfigPrintDialog::addRow()";
    int row = table->rowCount();
    table->insertRow(row);
    for (int col=0; col<table->columnCount(); col++) {
        if (col==0) {
            table->setCellWidget(row, col, new QComboBox);
            auto cb = qobject_cast<QComboBox *>(table->cellWidget(row, col));
            cb->setModel(colsModel);
        }
        else {
            table->setCellWidget(row, col, new QLineEdit);
        }
    }
}

void ConfigPrintDialog::removeRow(QTableWidget *table)
{
    qDebug() << "ConfigPrintDialog::removeRow()";
    table->removeRow(table->rowCount()-1);
}

void ConfigPrintDialog::setRow(QTableWidget *table, int row, QStringList values)
{
    qDebug() << "ConfigPrintDialog::setRow()";
    for (int col=0; col<table->columnCount(); col++) {
        if (col == 0) {
            QComboBox *cb = qobject_cast<QComboBox *>(table->cellWidget(row, 0));
            cb->setCurrentText(values[col]);
        }
        else {
            QLineEdit *le = qobject_cast<QLineEdit *>(table->cellWidget(row, col));
            le->setText(values[col]);
        }
    }
}

void ConfigPrintDialog::saveSettings(QTableWidget *table, QString settingsName)
{
    qDebug() << "ConfigPrintDialog::saveSetting()";
    settings.beginGroup(settingsName);
    settings.remove(""); //passando una stringa vuota rimuove tutto
    for (int row=0; row<table->rowCount(); row++) {
        QStringList values; //[ColsName, Stretch Factor, Display Name]
        for (int col=0; col<table->columnCount(); col++) {
            if (col==0) {
                auto cb = qobject_cast<QComboBox *>(table->cellWidget(row, col));
                values << cb->currentText();
            }
            else {
                auto le = qobject_cast<QLineEdit *>(table->cellWidget(row, col));
                QString val = le->text();
                if (col==1 && val.isEmpty())
                    val = "1"; //Valore di default Stretch Factor
                else if (col==2 && val.isEmpty())
                    val = values[0]; //Valore di default Display Name
                values << val;
            }
        }
        settings.setValue(QString("%1").arg(row), values);
    }
    settings.endGroup();
}

void ConfigPrintDialog::addColumn()
{
    qDebug() << "ConfigPrintDialog::addColumn()";
    QTableWidget *table;
    if (ui->listinoTableWidget->isVisible())
        table = ui->listinoTableWidget;
    else if (ui->ordineTableWidget->isVisible())
        table = ui->ordineTableWidget;
    else
        return;

    addRow(table);
}

void ConfigPrintDialog::removeColumn()
{
    qDebug() << "ConfigPrintDialog::removeColumn()";
    QTableWidget *table;
    if (ui->listinoTableWidget->isVisible())
        table = ui->listinoTableWidget;
    else if (ui->ordineTableWidget->isVisible())
        table = ui->ordineTableWidget;
    else
        return;

    removeRow(table);
}

void ConfigPrintDialog::save()
{
    qDebug() << "ConfigPrintDialog::save()";
    //Configura listino
    saveSettings(ui->listinoTableWidget, report::listinoCols);
    saveSettings(ui->ordineTableWidget, report::ordineCols);
}

