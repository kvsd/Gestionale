#include "magazzinowindow.h"
#include "ui_magazzinowindow.h"

const QString SELECT_ARTICOLI_ALL = "SELECT * FROM vw_magazzino";
const QString SELECT_ARTICOLI_FORNITORE = "SELECT * FROM vw_magazzino WHERE \"Fornitore\" = '%1'";
const QString SELECT_ARTICOLI_MARCA = "SELECT * FROM vw_magazzino WHERE \"Marca\"= '%1'";
const QString SELECT_ARTICOLI_CATEGORIA = "SELECT * FROM vw_magazzino WHERE \"Cat.Merce\" = '%1'";
const QString SELECT_ARTICOLI_SEDE = "SELECT * FROM vw_magazzino WHERE \"Sede Magazzino\" = '%1'";
const QString SELECT_FILTER = "SELECT id, descr FROM %1";
const QString SELECT_FILTER_FORNITORI = "SELECT \"Id\" as id, \"Ragione sociale\" as descr FROM vw_anagrafica_fornitori";
const QString SELECT_STORICO = "SELECT * FROM vw_listino_storico WHERE \"Id Articolo\"='%1' ORDER BY \"Data\" DESC, \"Imponibile\" DESC";
const QString DELETE_ARTICOLO = "DELETE FROM magazzino WHERE id = :id";

enum columns {COL_ID=0,
              COL_DESCR=1};


const QString ARTICOLO_COLORS = "MagazzinoWindow.cols.colors.articolo";
const QString ARTICOLO_STATUS = "MagazzinoWindow.cols.status.articolo";
const QString STORICO_COLORS = "MagazzinoWindow.cols.colors.storico";
const QString STORICO_STATUS = "MagazzinoWindow.cols.status.storico";
const QString WINDOW_SIZE = "MagazzinoWindow.size";


MagazzinoWindow::MagazzinoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MagazzinoWindow)
{
    ui->setupUi(this);
    this->move(parent->pos());
    QList <int> list;
    list.append(400); //Larghezza articoloView
    list.append(150); //Larghezza storicoView
    ui->splitter->setSizes(list);

    articoloModel = new CustomModel(ARTICOLO_COLORS, this);
    ui->articoloView->setModel(articoloModel);

    selectionModel = new QSqlQueryModel(this);
    ui->filterValueComboBox->setModel(selectionModel);

    storicoModel = new CustomModel(STORICO_COLORS, this);
    /* Se viene chiusa immediatamente l'applicazione e il model e' vuoto, viene
       corrotto il file di configurazione. Questa impostazione permette di avere
       il model impostato senza valori ed evitare la corruzione dei dati di
       configurazione*/
    storicoModel->setQuery(SELECT_STORICO.arg(-1));
    ui->storicoView->setModel(storicoModel);

    filterMap["-----"] = "";
    filterMap["Fornitore"] = "";
    filterMap["Marca"] = "marca";
    filterMap["Categoria"] = "cat_merce";
    filterMap["Sede Magazzino"] = "sede_magazzino";
    ui->filterTypeComboBox->insertItems(0, filterMap.keys());

    loadConfigSettings();
}

MagazzinoWindow::~MagazzinoWindow()
{
    delete ui;
}

void MagazzinoWindow::loadConfigSettings()
{
    this->setGeometry(settings.value(WINDOW_SIZE, QRect(0,0,700,500)).toRect());

    ui->articoloView->horizontalHeader()->setMovable(true);
    if (settings.contains("MagazzinoWindow.header.articolo")) {
        QByteArray array = settings.value("MagazzinoWindow.header.articolo").toByteArray();
        ui->articoloView->horizontalHeader()->restoreState(array);
    }

    ui->storicoView->horizontalHeader()->setMovable(true);
    if (settings.contains("MagazzinoWindow.header.storico")) {
        QByteArray array = settings.value("MagazzinoWindow.header.storico").toByteArray();
        ui->storicoView->horizontalHeader()->restoreState(array);
    }

    settings.beginGroup(ARTICOLO_STATUS);
    QStringList articoloCols = settings.allKeys();
    if (articoloCols.isEmpty()) {
        return;
    }
    for (QStringList::Iterator i=articoloCols.begin(); i!=articoloCols.end(); i++) {
        int col = QVariant((*i)).toInt();
        bool value = settings.value((*i)).toBool();
        ui->articoloView->setColumnHidden(col, !value);

    }
    settings.endGroup();

    settings.beginGroup(STORICO_STATUS);
    QStringList storicoCols = settings.allKeys();
    if (storicoCols.isEmpty()) {
        return;
    }
    for (QStringList::Iterator i=storicoCols.begin(); i!=storicoCols.end(); i++) {
        int col = QVariant((*i)).toInt();
        bool value = settings.value((*i)).toBool();
        ui->storicoView->setColumnHidden(col, !value);

    }
    settings.endGroup();

    articoloModel->loadSettings();
    storicoModel->loadSettings();
}

void MagazzinoWindow::saveConfigSettings()
{
    settings.setValue(WINDOW_SIZE, this->geometry());
    settings.setValue("MagazzinoWindow.header.articolo", ui->articoloView->horizontalHeader()->saveState());
    settings.setValue("MagazzinoWindow.header.storico", ui->storicoView->horizontalHeader()->saveState());
    //TODO salvare stato menu Ricerca
}

void MagazzinoWindow::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->show();
    saveConfigSettings();
    event->accept();
}

void MagazzinoWindow::showEvent(QShowEvent *)
{
    updateViewMagazzino();
}

void MagazzinoWindow::addRecord()
{
    ArticoloDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    updateViewMagazzino();
}

void MagazzinoWindow::updateRecord(void)
{
    QModelIndex index = ui->articoloView->currentIndex();
    if (!index.isValid()) {
        qDebug() << "Errore: " << "selezionare prima di aggiornare"; //TODO definire codice errore
        return;
    }

    QString id = articoloModel->index(index.row(), COL_ID).data().toString();
    ArticoloDialog dlg(this);
    dlg.setValue(id);
    dlg.setWindowTitle("Modifica Articolo");
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    updateViewMagazzino();
    updateViewStorico(index);
}

void MagazzinoWindow::removeRecord(void)
{
    QModelIndex index = ui->articoloView->currentIndex();
    if (!index.isValid()) {
        qDebug() << "Errore: " << "selezionare prima di cancellare"; //TODO definire codice errore
        return;
    }
    QString id = articoloModel->index(index.row(), COL_ID).data().toString();
    QSqlQuery query;
    query.prepare(DELETE_ARTICOLO);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Errore query: " << query.lastError().text(); //TODO definire codice errore
    }
    updateViewMagazzino();
    storicoModel->setQuery("");
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
    ui->filterValueComboBox->setModelColumn(COL_DESCR);
}

void MagazzinoWindow::updateViewMagazzino(void)
{
    QString filter = ui->filterTypeComboBox->currentText();
    if (filter == "-----") {
        articoloModel->setQuery(SELECT_ARTICOLI_ALL);
    }
    else if (filter == "Marca") {
        articoloModel->setQuery(SELECT_ARTICOLI_MARCA.arg(ui->filterValueComboBox->currentText()));
    }
    else if (filter == "Fornitore") {
        articoloModel->setQuery(SELECT_ARTICOLI_FORNITORE.arg(ui->filterValueComboBox->currentText()));
    }
    else if (filter == "Categoria") {
        articoloModel->setQuery(SELECT_ARTICOLI_CATEGORIA.arg(ui->filterValueComboBox->currentText()));
    }
    else if (filter == "Sede Magazzino") {
        articoloModel->setQuery(SELECT_ARTICOLI_SEDE.arg(ui->filterValueComboBox->currentText()));
    }
    else {
        articoloModel->clear();
    }
    ui->articoloView->resizeColumnsToContents();
    ui->articoloView->horizontalHeader()->setStretchLastSection(true);
    ui->articoloView->hideColumn(COL_ID);
}

void MagazzinoWindow::updateViewStorico(QModelIndex index)
{
    if (!index.isValid()) {
        storicoModel->setQuery(SELECT_STORICO.arg(-1));
    }
    QString id = articoloModel->index(index.row(), COL_ID).data().toString();
    storicoModel->setQuery(SELECT_STORICO.arg(id));
    ui->storicoView->hideColumn(COL_ID);
    ui->storicoView->resizeColumnsToContents();
    ui->storicoView->horizontalHeader()->setStretchLastSection(true);
}

void MagazzinoWindow::searchRecord(void)
{
    //TODO riscrivere funzione
    QString pattern = ui->searchLineEdit->text();
    if (pattern == "") {
        articoloModel->setQuery(SELECT_ARTICOLI_ALL);
        return;
    }

    QStringList filtri;
    if (ui->actionDescrizione->isChecked())
        filtri.append("\"Descrizione\" ILIKE '%%1%'");
    if (ui->actionCod_Fornitore->isChecked())
        filtri.append("\"Cod.Fornitore\" ILIKE '%%1%'");
    if (ui->actionCod_Articolo->isChecked())
        filtri.append("\"Cod.Articolo\" ILIKE '%%1%'");
    if (ui->actionEAN->isChecked())
        filtri.append("\"Cod.EAN\" ILIKE '%%1%'");

    if (filtri.length() == 0)
        articoloModel->setQuery(SELECT_ARTICOLI_ALL);
    else
        articoloModel->setQuery(SELECT_ARTICOLI_ALL + " WHERE " + filtri.join(" OR ").arg(pattern));
}

void MagazzinoWindow::openConfigDialog(void)
{
    OptionsMagazzinoDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    loadConfigSettings();
}
