#include "magazzinowindow.h"
#include "ui_magazzinowindow.h"

MagazzinoWindow::MagazzinoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MagazzinoWindow)
{
    ui->setupUi(this);
    this->move(parent->pos());

    initModel();
    loadConfigSettings();

    ui->data1LineEdit->setDate(QDate::currentDate());
    ui->data2LineEdit->setDate(QDate::currentDate());
}

MagazzinoWindow::~MagazzinoWindow()
{
    delete ui;
}

void MagazzinoWindow::initModel()
{
    articoloModel = new CustomModel(magazzino::ARTICOLO_COLORS, this);
    ui->articoloView->setModel(articoloModel);

    storicoModel = new CustomModel(magazzino::STORICO_COLORS, this);
    ui->storicoView->setModel(storicoModel);

    fornitoreModel = new QSqlQueryModel(this);
    fornitoreModel->setQuery(magazzino::SELECT_FILTER_FORNITORI);
    ui->fornitoreComboBox->setModel(fornitoreModel);
    ui->fornitoreComboBox->setModelColumn(magazzino::COL_DESCR);

    categoriaModel = new QSqlTableModel(this);
    categoriaModel->setTable("cat_merce");
    ui->categoriaComboBox->setModel(categoriaModel);
    ui->categoriaComboBox->setModelColumn(magazzino::COL_DESCR);

    marcaModel = new QSqlTableModel(this);
    marcaModel->setTable("marca");
    ui->marcaComboBox->setModel(marcaModel);
    ui->marcaComboBox->setModelColumn(magazzino::COL_DESCR);

    sedeModel = new QSqlTableModel(this);
    sedeModel->setTable("sede_magazzino");
    ui->sedeComboBox->setModel(sedeModel);
    ui->sedeComboBox->setModelColumn(magazzino::COL_DESCR);

    updateModel();
}

void MagazzinoWindow::updateModel()
{
    categoriaModel->select();
    marcaModel->select();
    sedeModel->select();
}

void MagazzinoWindow::loadConfigSettings()
{
    this->setGeometry(settings.value(magazzino::WINDOW_SIZE, magazzino::DEFAULT_WINDOW_SIZE).toRect());
    ui->splitter_1->restoreState(settings.value(magazzino::SPLITTER1_SIZE).toByteArray());
    ui->splitter_2->restoreState(settings.value(magazzino::SPLITTER2_SIZE).toByteArray());

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
    settings.setValue(magazzino::SPLITTER1_SIZE, ui->splitter_1->saveState());
    settings.setValue(magazzino::SPLITTER2_SIZE, ui->splitter_2->saveState());
    //Salvo la disposizione delle colonne delle viste
    settings.setValue(magazzino::ARTICOLO_HEADER, ui->articoloView->horizontalHeader()->saveState());
    settings.setValue(magazzino::STORICO_HEADER, ui->storicoView->horizontalHeader()->saveState());
    //Salvo le impostazioni del menu Ricerca
    settings.setValue(magazzino::SEARCH_DESCR, ui->actionDescrizione->isChecked());
    settings.setValue(magazzino::SEARCH_COD_ART, ui->actionCod_Articolo->isChecked());
    settings.setValue(magazzino::SEARCH_COD_FRN, ui->actionCod_Fornitore->isChecked());
    settings.setValue(magazzino::SEARCH_COD_EAN, ui->actionEAN->isChecked());
}

QString MagazzinoWindow::searchString(void) {
    //Prepara i filtri della query in base alla stringa che viene
    //immessa nel box della ricerca veloce e ai parametri del menu
    //ricerca veloce
    QString pattern = ui->searchLineEdit->text();
    if (pattern.isEmpty()) {
        return "";
    }

    QStringList filter;
    if (ui->actionDescrizione->isChecked()) {
        filter.append("\"Descrizione\" ILIKE '%%1%'");
    }

    if (ui->actionCod_Fornitore->isChecked()) {
        filter.append("\"Cod.Fornitore\" ILIKE '%%1%'");
    }

    if (ui->actionCod_Articolo->isChecked()) {
        filter.append("\"Cod.Articolo\" ILIKE '%%1%'");
    }

    if (ui->actionEAN->isChecked()) {
        filter.append("\"Cod.EAN\" ILIKE '%%1%'");
    }

    if (filter.isEmpty()) {
        return "";
    }

    return ( "(" + filter.join(" OR ").arg(pattern) + ")" );
}

QString MagazzinoWindow::filterString(void) {
    //Prepara i filtri della query in base ai vari parametri che vengono
    //selezionati nel pannello filtro
    QStringList filter;
    if (ui->fornitoreComboBox->isEnabled()) {
        QString fornitore = "\"Fornitore\" = '%1'";
        filter.append(fornitore.arg(ui->fornitoreComboBox->currentText()));
    }

    if (ui->categoriaComboBox->isEnabled()) {
        QString catmerce = "\"Cat.Merce\" = '%1'";
        filter.append(catmerce.arg(ui->categoriaComboBox->currentText()));
    }

    if (ui->marcaComboBox->isEnabled()) {
        QString marca = "\"Marca\" = '%1'";
        filter.append(marca.arg(ui->marcaComboBox->currentText()));
    }

    if (ui->sedeComboBox->isEnabled()) {
        QString sede = "\"Sede Magazzino\" = '%1'";
        filter.append(sede.arg(ui->sedeComboBox->currentText()));
    }

    if (ui->data1LineEdit->isEnabled() && ui->data2LineEdit->isEnabled()) {
        QString data1 = ui->data1LineEdit->text();
        QString data2 = ui->data2LineEdit->text();
        QString data = "\"Data Arrivo\" > '%1' AND \"Data Arrivo\" < '%2'";
        filter.append(data.arg(data1, data2));
    }
    else if(ui->data1LineEdit->isEnabled() && !ui->data2LineEdit->isEnabled()) {
        QString data = "\"Data Arrivo\" = '%1'";
        filter.append(data.arg(ui->data1LineEdit->text()));
        ui->data2LineEdit->setDate(ui->data1LineEdit->date());
    }

    if (filter.isEmpty()) {
        return "";
    }
    else {
        return filter.join(" AND ");
    }
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
    updateModel();
}

void MagazzinoWindow::updateRecord(void)
{
    QModelIndex index = ui->articoloView->currentIndex();
    if (!index.isValid()) {
        showDialogError(this, "Errore 1", "Errore 2", "Errore 3"); //TODO definire codice errore
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
    updateModel();
}

void MagazzinoWindow::removeRecord(void)
{
    QModelIndex index = ui->articoloView->currentIndex();
    if (!index.isValid()) {
        showDialogError(this, "Errore 1", "Errore 2", "Errore 3"); //TODO definire codice errore
        return;
    }
    QString id = articoloModel->index(index.row(), magazzino::COL_ID).data().toString();
    QSqlQuery query;
    query.prepare(magazzino::DELETE_ARTICOLO);
    query.bindValue(":id", id);
    if (!query.exec()) {
        showDialogError(this, "Errore 1", "Errore 2", query.lastError().text()); //TODO definire codice errore
    }
    updateViewMagazzino();
    storicoModel->setQuery("");
}

void MagazzinoWindow::updateViewMagazzino(void)
{
    QString filter1 = filterString();
    QString filter2 = searchString();

    QString query;

    if (filter1.isEmpty() && filter2.isEmpty()) {
        query = magazzino::SELECT_ARTICOLI_ALL;
    }
    else if (!filter1.isEmpty() && filter2.isEmpty()) {
        query = magazzino::SELECT_ARTICOLI_ALL + " WHERE " + filter1;
    }
    else if (filter1.isEmpty() && !filter2.isEmpty()) {
        query = magazzino::SELECT_ARTICOLI_ALL + " WHERE " + filter2;
    }
    else {
        query = magazzino::SELECT_ARTICOLI_ALL + " WHERE " + filter2 + " AND " + filter1;
    }

    articoloModel->setQuery(query);

    ui->articoloView->resizeColumnsToContents();
    ui->articoloView->horizontalHeader()->setStretchLastSection(true);
    ui->articoloView->hideColumn(magazzino::COL_ID);

    /* Se viene chiusa immediatamente l'applicazione e il model e' vuoto, viene
       corrotto il file di configurazione. Questa impostazione permette di avere
       il model impostato senza valori ed evitare la corruzione dei dati di
       configurazione*/
    storicoModel->setQuery(magazzino::SELECT_STORICO.arg(-1));
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

void MagazzinoWindow::openConfigDialog(void)
{
    OptionsMagazzinoDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    loadConfigSettings();
}

void MagazzinoWindow::exportMagazzinoCsv(void)
{
    QString filename = QFileDialog::getSaveFileName();
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    QSqlQuery query("SELECT * FROM magazzino");
    while (query.next()) {
        QSqlRecord record = query.record();
        for (int c=0; c < record.count(); c++) {
            out << record.value(c).toString() << ":";
        }
        out << "\n";
    }

    file.close();
}

void MagazzinoWindow::exportStoricoCsv(void)
{
    QString filename = QFileDialog::getSaveFileName();
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    QSqlQuery query("SELECT * FROM listino_storico");
    while (query.next()) {
        QSqlRecord record = query.record();
        for (int c=0; c < record.count(); c++) {
            out << record.value(c).toString() << ":";
        }
        out << "\n";
    }

    file.close();
}
