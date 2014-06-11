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
}

void ConfigPrintDialog::loadSettings()
{
    qDebug() << "ConfigPrintDialog::loadSettings()";
    QString col1 = settings.value(magazzino::LISTINO_COL1, magazzino::CMP_COD_ART).toString();
    QString col2 = settings.value(magazzino::LISTINO_COL2, magazzino::CMP_DESCR).toString();
    QString col3 = settings.value(magazzino::LISTINO_COL3, magazzino::CMP_PRZ_ACQ).toString();
    QString col4 = settings.value(magazzino::LISTINO_COL4, magazzino::CMP_PRZ_FIN).toString();

    int idCol1 = ui->col1ComboBox->findText(col1);
    int idCol2 = ui->col1ComboBox->findText(col2);
    int idCol3 = ui->col1ComboBox->findText(col3);
    int idCol4 = ui->col1ComboBox->findText(col4);

    ui->col1ComboBox->setCurrentIndex(idCol1);
    ui->col2ComboBox->setCurrentIndex(idCol2);
    ui->col3ComboBox->setCurrentIndex(idCol3);
    ui->col4ComboBox->setCurrentIndex(idCol4);
}

void ConfigPrintDialog::save()
{
    qDebug() << "ConfigPrintDialog::save()";
    QString col1 = ui->col1ComboBox->currentText();
    QString col2 = ui->col2ComboBox->currentText();
    QString col3 = ui->col3ComboBox->currentText();
    QString col4 = ui->col4ComboBox->currentText();

    settings.setValue(magazzino::LISTINO_COL1, col1);
    settings.setValue(magazzino::LISTINO_COL2, col2);
    settings.setValue(magazzino::LISTINO_COL3, col3);
    settings.setValue(magazzino::LISTINO_COL4, col4);
}
