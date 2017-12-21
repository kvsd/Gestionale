#include "configprintdialog.h"
#include "ui_configprintdialog.h"

ConfigPrintDialog::ConfigPrintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigPrintDialog)
{
    qDebug() << "ConfigPrintDialog()";
    ui->setupUi(this);
    //rimuovo il tab di configurazione dell'ordine, devo decidere.
    ui->tabWidget->removeTab(1);
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
    model->setQuery(sql::SELECT_ARTICOLI_ALL);
    headerMap = prepareMapsFromModel(model);
    colsModel = new QStringListModel(headerMap.values(), this);
}

void ConfigPrintDialog::loadTableSettings(QTableWidget *table, QString settingsName)
{
    qDebug() << "ConfigPrintDialog::loadTableSettings()";
    settings.beginGroup(settingsName);
    for (QString key : settings.allKeys()) {
        QStringList values = settings.value(key).toStringList();
        if (values.size() != table->columnCount())
            break;
        addRow(table);
        setRow(table, key.toInt(), values);
    }
    settings.endGroup();
}

void ConfigPrintDialog::loadSettings()
{
    qDebug() << "ConfigPrintDialog::loadSettings()";
    loadTableSettings(ui->listinoTableWidget, settings::listinoCols);
    loadTableSettings(ui->ordineTableWidget, settings::ordineCols);
}

void ConfigPrintDialog::addRow(QTableWidget *table)
{
    qDebug() << "ConfigPrintDialog::addRow()";
    int row = table->rowCount();
    table->insertRow(row);
    for (int col=0; col<table->columnCount(); col++) {
        if (col==CPD::DESCR || col==CPD::ALIGN) {
            table->setCellWidget(row, col, new QComboBox);
            auto cb = qobject_cast<QComboBox *>(table->cellWidget(row, col));
            if (col==CPD::DESCR)
                cb->setModel(colsModel);
            else if (col==CPD::ALIGN)
                cb->addItems({"Sinistra", "Destra", "Centrale"});
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
        if (col == CPD::DESCR || col == CPD::ALIGN) {
            QComboBox *cb = qobject_cast<QComboBox *>(table->cellWidget(row, col));
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
    //Passando una stringa vuota rimuove tutti le voci del gruppo. L'iterazione è
    //eseguita sulle colonne della tablewidget, valori precedentemente salvati non
    //verrebbero sovrascritti.
    settings.remove("");
    for (int row=0; row<table->rowCount(); row++) {
        //formato values -> [ColsName, Stretch Factor, Display Name, Alignment]
        QStringList values;
        for (int col=0; col<table->columnCount(); col++) {
            if (col==CPD::DESCR || col==CPD::ALIGN) {
                auto cb = qobject_cast<QComboBox *>(table->cellWidget(row, col));
                values << cb->currentText();
            }
            else {
                auto le = qobject_cast<QLineEdit *>(table->cellWidget(row, col));
                QString val = le->text();
                if (col==CPD::STRETCH && val.isEmpty())
                    val = "1"; //Valore di default Stretch Factor
                else if (col==CPD::VIEW && val.isEmpty())
                    val = values[CPD::DESCR]; //Valore di default Display Name
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
    saveSettings(ui->listinoTableWidget, settings::listinoCols);
    saveSettings(ui->ordineTableWidget, settings::ordineCols);
}

