#include "optionsanagraficadialog.h"
#include "ui_optionsanagraficadialog.h"

OptionsAnagraficaDialog::OptionsAnagraficaDialog(QWidget *parent) :
    OptionsDialog(parent),
    ui(new Ui::OptionsAnagraficaDialog),
    m_anagraficaModel(new CustomModel(this))
{
    qDebug() << "OptionsAnagraficaDialog()";
    ui->setupUi(this);

    m_anagraficaModel->setQuery(anagrafica::SELECT_ALL);
    populateList(ui->lw_column_anagrafica, m_anagraficaModel);
    loadConfig();
}

OptionsAnagraficaDialog::~OptionsAnagraficaDialog()
{
    qDebug() << "~OptionsAnagraficaDialog()";
    delete ui;
}

void OptionsAnagraficaDialog::saveConfig(void)
{
    qDebug() << "OptionsAnagraficaDialog::saveConfig()";
    //Salva la visibilità delle colonne
    saveVisibility(ui->lw_column_anagrafica, anagrafica::ANGRFC_STATUS);

    //Salva il colore di sfondo delle colonne
    saveBgColor(ui->lw_column_anagrafica, anagrafica::ANGRFC_COLORS);
}

void OptionsAnagraficaDialog::loadConfig(void)
{
    qDebug() << "OptionsAnagraficaDialog::loadConfig()";
    //Carica la visibilita delle colonne
    loadVisibility(ui->lw_column_anagrafica, anagrafica::ANGRFC_STATUS);

    //Carica il colore di sfondo delle colonne
    loadBgColor(ui->lw_column_anagrafica, anagrafica::ANGRFC_COLORS);
}

void OptionsAnagraficaDialog::restoreToDefault(void)
{
    qDebug() << "OptionsAnagraficaDialog::restoreToDefault()";

    restoreListWidget(ui->lw_column_anagrafica);
    saveConfig();
    loadConfig();
}

