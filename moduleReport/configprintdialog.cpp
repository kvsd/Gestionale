#include "configprintdialog.h"
#include "ui_configprintdialog.h"

ConfigPrintDialog::ConfigPrintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigPrintDialog)
{
    qDebug() << "ConfigPrintDialog()";
    ui->setupUi(this);
    initComboBoxs();
    loadSettings();
}

ConfigPrintDialog::~ConfigPrintDialog()
{
    qDebug() << "~ConfigPrintDialog()";
    delete ui;
}

void ConfigPrintDialog::initComboBoxs()
{
    qDebug() << "ConfigPrintDialog::initComboBoxs()";
    using namespace magazzino;
    QStringList cols;
    cols << CMP_ID << CMP_DESCR << CMP_FORNIT << CMP_MARCA << CMP_MODELLO << CMP_COD_ART << CMP_COD_FOR <<
            CMP_COD_EAN << CMP_MERCE << CMP_COD_IVA << CMP_UM << CMP_SCORTA << CMP_QT << CMP_PRZ_FAT <<
            CMP_SCONTO << CMP_RICAR << CMP_PRZ_ACQ << CMP_IVA << CMP_PRZ_FIN << CMP_PRZ_VEN << CMP_FATTURA <<
            CMP_DATA << CMP_SEDE << CMP_NOTE << CMP_ID_ART;

    ui->col1ComboBox->addItems(cols);
    ui->col2ComboBox->addItems(cols);
    ui->col3ComboBox->addItems(cols);
    ui->col4ComboBox->addItems(cols);

    ui->ordineCol1ComboBox->addItems(cols);
    ui->ordineCol2ComboBox->addItems(cols);
    ui->ordineCol3ComboBox->addItems(cols);
    ui->ordineCol4ComboBox->addItems(cols);
}

void ConfigPrintDialog::loadSettings()
{
    qDebug() << "ConfigPrintDialog::loadSettings()";
    //Configura listino
    QString col1 = settings.value(report::LISTINO_COL1, magazzino::CMP_COD_ART).toString();
    QString col2 = settings.value(report::LISTINO_COL2, magazzino::CMP_DESCR).toString();
    QString col3 = settings.value(report::LISTINO_COL3, magazzino::CMP_PRZ_ACQ).toString();
    QString col4 = settings.value(report::LISTINO_COL4, magazzino::CMP_PRZ_FIN).toString();

    int idCol1 = ui->col1ComboBox->findText(col1);
    int idCol2 = ui->col1ComboBox->findText(col2);
    int idCol3 = ui->col1ComboBox->findText(col3);
    int idCol4 = ui->col1ComboBox->findText(col4);

    ui->col1ComboBox->setCurrentIndex(idCol1);
    ui->col2ComboBox->setCurrentIndex(idCol2);
    ui->col3ComboBox->setCurrentIndex(idCol3);
    ui->col4ComboBox->setCurrentIndex(idCol4);

    //Configura ordine
    QString ordineCol1 = settings.value(report::ORDINE_COL1, magazzino::CMP_COD_ART).toString();
    QString ordineCol2 = settings.value(report::ORDINE_COL2, magazzino::CMP_DESCR).toString();
    QString ordineCol3 = settings.value(report::ORDINE_COL3, magazzino::CMP_QT).toString();
    QString ordineCol4 = settings.value(report::ORDINE_COL4, magazzino::CMP_SCORTA).toString();

    idCol1 = ui->ordineCol1ComboBox->findText(ordineCol1);
    idCol2 = ui->ordineCol2ComboBox->findText(ordineCol2);
    idCol3 = ui->ordineCol3ComboBox->findText(ordineCol3);
    idCol4 = ui->ordineCol4ComboBox->findText(ordineCol4);

    ui->ordineCol1ComboBox->setCurrentIndex(idCol1);
    ui->ordineCol2ComboBox->setCurrentIndex(idCol2);
    ui->ordineCol3ComboBox->setCurrentIndex(idCol3);
    ui->ordineCol4ComboBox->setCurrentIndex(idCol4);
}

void ConfigPrintDialog::save()
{
    qDebug() << "ConfigPrintDialog::save()";
    //Configura listino
    QString col1 = ui->col1ComboBox->currentText();
    QString col2 = ui->col2ComboBox->currentText();
    QString col3 = ui->col3ComboBox->currentText();
    QString col4 = ui->col4ComboBox->currentText();

    settings.setValue(report::LISTINO_COL1, col1);
    settings.setValue(report::LISTINO_COL2, col2);
    settings.setValue(report::LISTINO_COL3, col3);
    settings.setValue(report::LISTINO_COL4, col4);

    //Configura ordine
    QString ordineCol1 = ui->ordineCol1ComboBox->currentText();
    QString ordineCol2 = ui->ordineCol2ComboBox->currentText();
    QString ordineCol3 = ui->ordineCol3ComboBox->currentText();
    QString ordineCol4 = ui->ordineCol4ComboBox->currentText();

    settings.setValue(report::ORDINE_COL1, ordineCol1);
    settings.setValue(report::ORDINE_COL2, ordineCol2);
    settings.setValue(report::ORDINE_COL3, ordineCol3);
    settings.setValue(report::ORDINE_COL4, ordineCol4);
}
