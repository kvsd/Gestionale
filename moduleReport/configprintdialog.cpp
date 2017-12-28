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

void ConfigPrintDialog::loadSettings()
{
    qDebug() << "ConfigPrintDialog::loadSettings()";
    loadTableSettings(ui->listinoTableWidget, settings::listinoCols);
    loadTableSettings(ui->ordineTableWidget, settings::ordineCols);

    QString listinofontStr = m_settings.value(settings::listinoFont, "fixed").toString();
    QFont listinoFont;
    listinoFont.fromString(listinofontStr);
    ui->listinoFontCB->setCurrentFont(listinoFont);

    QString ordinefontStr = m_settings.value(settings::ordineFont, "fixed").toString();
    QFont ordinefont;
    ordinefont.fromString(ordinefontStr);
    ui->ordineFontCB->setCurrentFont(ordinefont);
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

void ConfigPrintDialog::saveSettings(QTableWidget *table, QString settingsName)
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
    saveSettings(ui->listinoTableWidget, settings::listinoCols);
    saveSettings(ui->ordineTableWidget, settings::ordineCols);

    m_settings.setValue(settings::listinoFont, ui->listinoFontCB->currentFont().toString());
    m_settings.setValue(settings::ordineFont, ui->ordineFontCB->currentFont().toString());
}

void ConfigPrintDialog::openFontDlg()
{
    qDebug() << "ConfigPrintDialog::openFontDlg()";
    /* Slot che apre un QFontDialog e prende il font iniziale dal
     * QFontComboBox visibile per poi riscrive il font selezionato */
    QFontComboBox *cb = 0;
    QList<QFontComboBox *>list = this->findChildren<QFontComboBox *>();
    for (QFontComboBox *x : list)
        if (x->isVisible())
            cb = x;

    if (!cb)
        return;

    bool ok;
    QFont font = QFontDialog::getFont(&ok, cb->currentFont(), this);
    if (ok)
        cb->setCurrentFont(font);
}

