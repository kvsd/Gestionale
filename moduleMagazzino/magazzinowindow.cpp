#include "magazzinowindow.h"
#include "ui_magazzinowindow.h"
#include <QStyledItemDelegate>
#include <QItemEditorFactory>

const QString SELECT_ARTICOLI_ALL = "SELECT * FROM vw_magazzino";
const QString SELECT_ARTICOLI_FORNITORE = "SELECT * FROM vw_magazzino WHERE \"Fornitore\" = '%1'";
const QString SELECT_ARTICOLI_MARCA = "SELECT * FROM vw_magazzino WHERE \"Marca\"= '%1'";
const QString SELECT_ARTICOLI_CATEGORIA = "SELECT * FROM vw_magazzino WHERE \"Cat.Merce\" = '%1'";
const QString SELECT_FILTER = "SELECT id, descr FROM %1";
const QString SELECT_FILTER_FORNITORI = "SELECT \"Id\" as id, \"Ragione sociale\" as descr FROM vw_anagrafica_fornitori";
const QString SELECT_STORICO = "SELECT * FROM vw_listino_storico WHERE \"Id Articolo\"='%1' ORDER BY \"Data\"";

enum columns {COL_ID=0,
              COL_ID_FORN, COL_RAG_SOC=1, COL_DESCR=1};

MagazzinoWindow::MagazzinoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MagazzinoWindow)
{
    ui->setupUi(this);
    this->move(parent->pos());

    ui->groupBoxInfo->setHidden(true);

    magazzinoModel = new QSqlQueryModel(this);
    ui->articoloView->setModel(magazzinoModel);

    selectionModel = new QSqlQueryModel(this);
    ui->cb_filter_value->setModel(selectionModel);

    storicoModel = new QSqlQueryModel(this);
    ui->storicoView->setModel(storicoModel);

    filterMap["-----"] = "";
    filterMap["Fornitore"] = "";
    filterMap["Marca"] = "marca";
    filterMap["Categoria"] = "cat_merce" ;
    ui->cb_filter_selection->insertItems(0, filterMap.keys());

}

MagazzinoWindow::~MagazzinoWindow()
{
    delete ui;
}

void MagazzinoWindow::closeEvent(QCloseEvent *)
{
    this->parentWidget()->show();
}

void MagazzinoWindow::showEvent(QShowEvent *)
{
    updateTableMagazzino();
}

void MagazzinoWindow::updateTableMagazzino(void)
{
    QString filter = ui->cb_filter_selection->currentText();
    if (filter == "-----") {
        magazzinoModel->setQuery(SELECT_ARTICOLI_ALL);
    }
    else if (filter == "Marca") {
        magazzinoModel->setQuery(SELECT_ARTICOLI_MARCA.arg(ui->cb_filter_value->currentText()));
    }
    else if (filter == "Fornitore") {
        magazzinoModel->setQuery(SELECT_ARTICOLI_FORNITORE.arg(ui->cb_filter_value->currentText()));
    }
    else if (filter == "Categoria") {
        magazzinoModel->setQuery(SELECT_ARTICOLI_CATEGORIA.arg(ui->cb_filter_value->currentText()));
    }
    else {
        magazzinoModel->clear();
    }
    ui->articoloView->resizeColumnsToContents();
    ui->articoloView->horizontalHeader()->setStretchLastSection(true);
    ui->articoloView->hideColumn(COL_ID);
}


void MagazzinoWindow::addRecord()
{
    ArticoloDialog dlg(this);
    dlg.exec();
}

void MagazzinoWindow::updateFilterValue(QString s)
{
    if (s == "-----") {
        selectionModel->clear();
    }
    else if (s == "Fornitore") {
        selectionModel->setQuery(SELECT_FILTER_FORNITORI);
    }
    else {
        selectionModel->setQuery(SELECT_FILTER.arg(filterMap[s]));
    }
    ui->cb_filter_value->setModelColumn(COL_DESCR);
}

void MagazzinoWindow::updateStoricoView(QModelIndex index)
{
    QString id = magazzinoModel->index(index.row(), COL_ID).data().toString();
    storicoModel->setQuery(SELECT_STORICO.arg(id));
    ui->storicoView->hideColumn(COL_ID);
    ui->storicoView->resizeColumnsToContents();
    ui->storicoView->horizontalHeader()->setStretchLastSection(true);
}
