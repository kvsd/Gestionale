#include "optionsmagazzinodialog.h"
#include "ui_optionsmagazzinodialog.h"

OptionsMagazzinoDialog::OptionsMagazzinoDialog(QWidget *parent) :
    OptionsDialog(parent),
    ui(new Ui::OptionsMagazzinoDialog),
    codIvaModel(new QSqlTableModel(this)),
    articoloModel(new QSqlQueryModel(this)),
    storicoModel(new QSqlQueryModel(this))
{
    qDebug() << "OptionsMagazzinoDialog()";
    ui->setupUi(this);

    codIvaModel->setTable(table::CODICE_IVA);
    codIvaModel->select();

    articoloModel->setQuery(sql::SELECT_ARTICOLI_ALL);
    storicoModel->setQuery(sql::SELECT_STORICO.arg(-1));

    ui->codIvaComboBox->setModel(codIvaModel);
    ui->codIvaComboBox->setModelColumn(CBM::DESCR);

    populateList(ui->magazzinoListView, articoloModel);
    populateList(ui->storicoListView, storicoModel);
    loadConfig();
}

OptionsMagazzinoDialog::~OptionsMagazzinoDialog()
{
    qDebug() << "~OptionsMagazzinoDialog()";
    delete ui;
}

void OptionsMagazzinoDialog::saveConfig(void)
{
    qDebug() << "OptionsMagazzinoDialog::saveConfig()";
    //Salvo la visibilita' delle colonne della vista Articolo
    saveVisibility(ui->magazzinoListView, settings::ARTICOLO_STATUS);

    //Salvo i colori della vista Articolo
    saveBgColor(ui->magazzinoListView, settings::ARTICOLO_COLORS);

    //Salvo la visibilita' delle colonne della vista Storico
    saveVisibility(ui->storicoListView, settings::STORICO_STATUS);

    //Salvo i colori della vista Storico
    saveBgColor(ui->storicoListView, settings::STORICO_COLORS);

    settings.setValue(settings::DEFAULT_IVA, ui->codIvaComboBox->currentText());
}

void OptionsMagazzinoDialog::loadConfig(void)
{
    qDebug() << "OptionsMagazzinoDialog::loadConfig()";

    //Carico la visibilita' delle colonne della vista Articolo
    loadVisibility(ui->magazzinoListView, settings::ARTICOLO_STATUS);

    //Carico i colori della vista Articolo
    loadBgColor(ui->magazzinoListView, settings::ARTICOLO_COLORS);

    //Carico la visibilita' delle colonne della vista Storico
    loadVisibility(ui->storicoListView, settings::STORICO_STATUS);

    //Carico i colori della vista Storico
    loadBgColor(ui->storicoListView, settings::STORICO_COLORS);

    int index = ui->codIvaComboBox->findText(m_settings.value(settings::DEFAULT_IVA).toString(), 0);
    ui->codIvaComboBox->setCurrentIndex(index);
}

void OptionsMagazzinoDialog::restoreToDefault(void)
{
    qDebug() << "OptionsMagazzinoDialog::restoreToDefault()";

    restoreListWidget(ui->magazzinoListView);
    restoreListWidget(ui->storicoListView);

    saveConfig();
    loadConfig();
}
