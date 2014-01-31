#include "magazzinowindow.h"
#include "ui_magazzinowindow.h"

MagazzinoWindow::MagazzinoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MagazzinoWindow)
{
    ui->setupUi(this);
    this->move(parent->pos());
    QList <int> list;
    list.append(400); //Altezza articoloView
    list.append(150); //Altezza storicoView
    ui->splitter->setSizes(list);

    articoloModel = new CustomModel(magazzino::ARTICOLO_COLORS, this);
    ui->articoloView->setModel(articoloModel);

    selectionModel = new QSqlQueryModel(this);
    ui->filterValueComboBox->setModel(selectionModel);

    storicoModel = new CustomModel(magazzino::STORICO_COLORS, this);
    /* Se viene chiusa immediatamente l'applicazione e il model e' vuoto, viene
       corrotto il file di configurazione. Questa impostazione permette di avere
       il model impostato senza valori ed evitare la corruzione dei dati di
       configurazione*/
    storicoModel->setQuery(magazzino::SELECT_STORICO.arg(-1));
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
    this->setGeometry(settings.value(magazzino::WINDOW_SIZE, magazzino::DEFAULT_WINDOW_SIZE).toRect());

    //Carico la disposizione delle colonne della vista articolo
    ui->articoloView->horizontalHeader()->setMovable(true);
    if (settings.contains(magazzino::ARTICOLO_HEADER)) {
        QByteArray array = settings.value(magazzino::ARTICOLO_HEADER).toByteArray();
        ui->articoloView->horizontalHeader()->restoreState(array);
    }

    //Carico la disposizione delle colonne della vista storico
    ui->storicoView->horizontalHeader()->setMovable(true);
    if (settings.contains(magazzino::STORICO_HEADER)) {
        QByteArray array = settings.value(magazzino::STORICO_HEADER).toByteArray();
        ui->storicoView->horizontalHeader()->restoreState(array);
    }

    //Carico la visibilita delle colonne della vista articolo
    settings.beginGroup(magazzino::ARTICOLO_STATUS);
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

    //Carico la visibilita delle colonne della vista storico
    settings.beginGroup(magazzino::STORICO_STATUS);
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

    //Carico il colore dello sfondo delle colonne. (Si e' gestito dai model)
    articoloModel->loadSettings();
    storicoModel->loadSettings();

    //Carico le impostazioni del menu ricerca
    ui->actionDescrizione->setChecked(settings.value(magazzino::SEARCH_DESCR, true).toBool());
    ui->actionCod_Articolo->setChecked(settings.value(magazzino::SEARCH_COD_ART, false).toBool());
    ui->actionCod_Fornitore->setChecked(settings.value(magazzino::SEARCH_COD_FRN, false).toBool());
    ui->actionEAN->setChecked(settings.value(magazzino::SEARCH_COD_EAN, false).toBool());
}

void MagazzinoWindow::saveConfigSettings()
{
    settings.setValue(magazzino::WINDOW_SIZE, this->geometry());
    //Salvo la disposizione delle colonne delle viste
    settings.setValue(magazzino::ARTICOLO_HEADER, ui->articoloView->horizontalHeader()->saveState());
    settings.setValue(magazzino::STORICO_HEADER, ui->storicoView->horizontalHeader()->saveState());
    //Salvo le impostazioni del menu Ricerca
    settings.setValue(magazzino::SEARCH_DESCR, ui->actionDescrizione->isChecked());
    settings.setValue(magazzino::SEARCH_COD_ART, ui->actionCod_Articolo->isChecked());
    settings.setValue(magazzino::SEARCH_COD_FRN, ui->actionCod_Fornitore->isChecked());
    settings.setValue(magazzino::SEARCH_COD_EAN, ui->actionEAN->isChecked());
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

    QString id = articoloModel->index(index.row(), magazzino::COL_ID).data().toString();
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
    QString id = articoloModel->index(index.row(), magazzino::COL_ID).data().toString();
    QSqlQuery query;
    query.prepare(magazzino::DELETE_ARTICOLO);
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
        selectionModel->setQuery(magazzino::SELECT_FILTER_FORNITORI);
    }
    else {
        selectionModel->setQuery(magazzino::SELECT_FILTER.arg(filterMap[s]));
    }
    ui->filterValueComboBox->setModelColumn(magazzino::COL_DESCR);
}

void MagazzinoWindow::updateViewMagazzino(void)
{
    QString filter = ui->filterTypeComboBox->currentText();
    if (filter == "-----") {
        articoloModel->setQuery(magazzino::SELECT_ARTICOLI_ALL);
    }
    else if (filter == "Marca") {
        articoloModel->setQuery(magazzino::SELECT_ARTICOLI_MARCA.arg(ui->filterValueComboBox->currentText()));
    }
    else if (filter == "Fornitore") {
        articoloModel->setQuery(magazzino::SELECT_ARTICOLI_FORNITORE.arg(ui->filterValueComboBox->currentText()));
    }
    else if (filter == "Categoria") {
        articoloModel->setQuery(magazzino::SELECT_ARTICOLI_CATEGORIA.arg(ui->filterValueComboBox->currentText()));
    }
    else if (filter == "Sede Magazzino") {
        articoloModel->setQuery(magazzino::SELECT_ARTICOLI_SEDE.arg(ui->filterValueComboBox->currentText()));
    }
    else {
        articoloModel->clear();
    }
    ui->articoloView->resizeColumnsToContents();
    ui->articoloView->horizontalHeader()->setStretchLastSection(true);
    ui->articoloView->hideColumn(magazzino::COL_ID);
}

void MagazzinoWindow::updateViewStorico(QModelIndex index)
{
    if (!index.isValid()) {
        storicoModel->setQuery(magazzino::SELECT_STORICO.arg(-1));
    }
    QString id = articoloModel->index(index.row(), magazzino::COL_ID).data().toString();
    storicoModel->setQuery(magazzino::SELECT_STORICO.arg(id));
    ui->storicoView->hideColumn(magazzino::COL_ID);
    ui->storicoView->resizeColumnsToContents();
    ui->storicoView->horizontalHeader()->setStretchLastSection(true);
}

void MagazzinoWindow::searchRecord(void)
{
    QString pattern = ui->searchLineEdit->text();
    if (pattern == "") {
        ui->filterTypeComboBox->setCurrentIndex(0);
        articoloModel->setQuery(magazzino::SELECT_ARTICOLI_ALL);
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
        articoloModel->setQuery(magazzino::SELECT_ARTICOLI_ALL);
    else {
        QString current_query = articoloModel->query().lastQuery();
        QString filter = filtri.join(" OR ").arg(pattern);
        if (current_query.contains("WHERE")) {
            articoloModel->setQuery(current_query + " AND " + filter);
        }
        else {
            articoloModel->setQuery(current_query + " WHERE" + filter);
        }
    }
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
