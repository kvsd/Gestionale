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
    m_model = new QSqlQueryModel(this);
    m_model->setQuery(sql::SELECT_ARTICOLI_ALL);
    m_headerMap = prepareMapsFromModel(m_model);
    m_colsModel = new QStringListModel(m_headerMap.values(), this);
}

void ConfigPrintDialog::loadTableSettings(QTableWidget *table, QString settingsName)
{
    qDebug() << "ConfigPrintDialog::loadTableSettings()";
    //Legge da QSettings le colonne salvate nel gruppo settingsName e le carica
    //nella QTableWidget table
    m_settings.beginGroup(settingsName);
    table->clearContents();
    for (QString key : m_settings.allKeys()) {
        QStringList values = m_settings.value(key).toStringList();
        if (values.size() != table->columnCount())
            break;
        addRow(table);
        setRow(table, key.toInt(), values);
    }
    m_settings.endGroup();
}

void ConfigPrintDialog::loadFont(QFontComboBox *box, QSpinBox *spin, QString setting_key)
{
    qDebug() << "ConfigPrintDialog::loadFont()";
    QString fontStr = m_settings.value(setting_key, "fixed").toString();
    QFont font;
    font.fromString(fontStr);
    box->setCurrentFont(font);
    spin->setValue(font.pointSize());
}

void ConfigPrintDialog::loadSettings()
{
    qDebug() << "ConfigPrintDialog::loadSettings()";
    loadTableSettings(ui->listinoTableWidget, settings::listinoCols);
    loadTableSettings(ui->ordineTableWidget, settings::ordineCols);
    loadFont(ui->listinoFontCB, ui->listinoFontSize, settings::listinoFont);
    loadFont(ui->ordineFontCB, ui->ordineFontSize, settings::ordineFont);
}

void ConfigPrintDialog::addRow(QTableWidget *table)
{
    qDebug() << "ConfigPrintDialog::addRow()";
    //Aggiunge una riga nella QTableWidget table, ogni riga e' composta da
    //un qcombobox per il nome della colonna, una qlineedit per lo stretch factor,
    //una qlineedit per rinominare il nome della colonna e un qcombobox per
    //allineamento del testo.
    int row = table->rowCount();
    table->insertRow(row);
    for (int col=0; col<table->columnCount(); col++) {
        if (col==CPD::DESCR || col==CPD::ALIGN) {
            table->setCellWidget(row, col, new QComboBox);
            auto cb = qobject_cast<QComboBox *>(table->cellWidget(row, col));
            if (col==CPD::DESCR)
                cb->setModel(m_colsModel);
            else if (col==CPD::ALIGN)
                cb->addItems({align::left, align::right, align::center});
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
    //Imposta i valori della QStringList values nella riga con indice row
    //della QTableWidget table.
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

void ConfigPrintDialog::saveTableSettings(QTableWidget *table, QString settingsName)
{
    qDebug() << "ConfigPrintDialog::saveSetting()";
    //Salva i dati delle colonne create nella QTableWidget table nel
    //QSettings con un sottogruppo settingsName.
    //formato values -> [ColsName, Stretch Factor, Display Name, Alignment]
    m_settings.beginGroup(settingsName);
    //Passando una stringa vuota rimuove tutti le voci del gruppo.
    m_settings.remove("");
    for (int row=0; row<table->rowCount(); row++) {
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
        m_settings.setValue(QString("%1").arg(row), values);
    }
    m_settings.endGroup();
}

void ConfigPrintDialog::saveFont(QFontComboBox *box, QSpinBox *spin, QString setting_key)
{
    qDebug() << "ConfigPrintDialog::saveFont()";
    QFont titleFont = box->currentFont();
    titleFont.setPointSize(spin->value());
    m_settings.setValue(setting_key, titleFont.toString());
}

void ConfigPrintDialog::addColumn()
{
    qDebug() << "ConfigPrintDialog::addColumn()";
    //Slot collegato con il pulsante addListinoButton e addOrdineButton,
    //aggiunge una nuova riga nella QTableWidget che risulta visibile.
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
    //Slot collegato al remListinoButton e remOrdineButton, rimuove una riga dalla
    //QTableWidget che risulta visibile.
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
    //Slot collegato al pulsante save.
    saveTableSettings(ui->listinoTableWidget, settings::listinoCols);
    saveTableSettings(ui->ordineTableWidget, settings::ordineCols);

    saveFont(ui->listinoFontCB, ui->listinoFontSize, settings::listinoFont);
    saveFont(ui->ordineFontCB, ui->ordineFontSize, settings::ordineFont);
}
