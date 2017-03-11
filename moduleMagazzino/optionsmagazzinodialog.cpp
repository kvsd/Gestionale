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

    articoloModel->setQuery(magazzino::SELECT_ARTICOLI_ALL);
    storicoModel->setQuery(magazzino::SELECT_STORICO.arg(-1));

    ui->codIvaComboBox->setModel(codIvaModel);
    ui->codIvaComboBox->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

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
    saveVisibility(ui->magazzinoListView, magazzino::ARTICOLO_STATUS);

    //Salvo i colori della vista Articolo
    saveBgColor(ui->magazzinoListView, magazzino::ARTICOLO_COLORS);

    //Salvo la visibilita' delle colonne della vista Storico
    saveVisibility(ui->storicoListView, magazzino::STORICO_STATUS);

    //Salvo i colori della vista Storico
    saveBgColor(ui->storicoListView, magazzino::STORICO_COLORS);

    settings.setValue(magazzino::DEFAULT_IVA, ui->codIvaComboBox->currentText());
}

void OptionsMagazzinoDialog::loadConfig(void)
{
    qDebug() << "OptionsMagazzinoDialog::loadConfig()";

    //Carico la visibilita' delle colonne della vista Articolo
    loadVisibility(ui->magazzinoListView, magazzino::ARTICOLO_STATUS);

    //Carico i colori della vista Articolo
    loadBgColor(ui->magazzinoListView, magazzino::ARTICOLO_COLORS);

    //Carico la visibilita' delle colonne della vista Storico
    loadVisibility(ui->storicoListView, magazzino::STORICO_STATUS);

    //Carico i colori della vista Storico
    loadBgColor(ui->storicoListView, magazzino::STORICO_COLORS);

    int index = ui->codIvaComboBox->findText(settings.value(magazzino::DEFAULT_IVA).toString(), 0);
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
