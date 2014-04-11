#include "magazzinowindow.h"
#include "ui_magazzinowindow.h"

MagazzinoWindow::MagazzinoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MagazzinoWindow)
{
    qDebug() << "MagazzinoWindow";
    ui->setupUi(this);
    this->move(parent->pos());

    initModel();
    initComboBox();
    loadConfigSettings();

    ui->data1LineEdit->setDate(QDate::currentDate());
    ui->data2LineEdit->setDate(QDate::currentDate());

//    importMagazzinoCvs();
//    importStoricoCvs();
}

MagazzinoWindow::~MagazzinoWindow()
{
    qDebug() << "~MagazzinoWindow";
    delete ui;
}

void MagazzinoWindow::initModel()
{
    qDebug() << "MagazzinoWindow::initModel()";
    articoloModel = new CustomModel(magazzino::ARTICOLO_COLORS, this);
    storicoModel = new CustomModel(magazzino::STORICO_COLORS, this);
    fornitoreModel = new QSqlQueryModel(this);
    categoriaModel = new QSqlTableModel(this);
    marcaModel = new QSqlTableModel(this);
    sedeModel = new QSqlTableModel(this);

    ui->articoloView->setModel(articoloModel);
    ui->storicoView->setModel(storicoModel);
    fornitoreModel->setQuery(magazzino::SELECT_FILTER_FORNITORI);
    categoriaModel->setTable(table::CATEGORIA_MERCE);
    marcaModel->setTable(table::MARCA);
    sedeModel->setTable(table::SEDE_MAGAZZINO);

    updateModel();
}

void MagazzinoWindow::initComboBox()
{
    qDebug() << "MagazzinoWindow::initComboBox()";
    ui->fornitoreComboBox->setModel(fornitoreModel);
    ui->fornitoreComboBox->setModelColumn(magazzino::COL_DESCR);

    ui->categoriaComboBox->setModel(categoriaModel);
    ui->categoriaComboBox->setModelColumn(magazzino::COL_DESCR);

    ui->marcaComboBox->setModel(marcaModel);
    ui->marcaComboBox->setModelColumn(magazzino::COL_DESCR);

    ui->sedeComboBox->setModel(sedeModel);
    ui->sedeComboBox->setModelColumn(magazzino::COL_DESCR);

    ui->orderbyComboBox->addItems(magazzino::prepareMapsNameColsArticolo().values());
}

void MagazzinoWindow::updateModel()
{
    qDebug() << "MagazzinoWindow::updateModel()";
    categoriaModel->select();
    marcaModel->select();
    sedeModel->select();
}

void MagazzinoWindow::loadConfigSettings()
{
    qDebug() << "MagazzinoWindow::loadConfigSettings()";
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
    if (!articoloCols.isEmpty()) {
        for (QStringList::Iterator i=articoloCols.begin(); i!=articoloCols.end(); i++) {
            int col = QVariant((*i)).toInt();
            bool value = settings.value((*i)).toBool();
            ui->articoloView->setColumnHidden(col, !value);
        }
    }
    settings.endGroup();

    //Carico la visibilita delle colonne della vista storico
    settings.beginGroup(magazzino::STORICO_STATUS);
    QStringList storicoCols = settings.allKeys();
    if (!storicoCols.isEmpty()) {
        for (QStringList::Iterator i=storicoCols.begin(); i!=storicoCols.end(); i++) {
            int col = QVariant((*i)).toInt();
            bool value = settings.value((*i)).toBool();
            ui->storicoView->setColumnHidden(col, !value);
        }
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
    qDebug() << "MagazzinoWindow::saveConfigSettings()";
    settings.setValue(magazzino::WINDOW_SIZE, this->geometry());
    settings.setValue(magazzino::SPLITTER1_SIZE, ui->splitter_1->saveState());
    settings.setValue(magazzino::SPLITTER2_SIZE, ui->splitter_2->saveState());
    //Salvo la disposizione delle colonne delle viste BUGGATA si corrompe e non ne capisco il motivo
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
    qDebug() << "MagazzinoWindow::searchString()";
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
    qDebug() << "MagazzinoWindow::filterString()";
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

    if (ui->currentDateEnabler->isChecked()) {
        QString data = "\"Data Arrivo\" = '%1'";
        QString currentDate = QDate::currentDate().toString("dd/MM/yy");
        filter.append(data.arg(currentDate));
    }
    else if (ui->rangeDateEnabler->isChecked()) {
        QString data1 = ui->data1LineEdit->text();
        QString data2 = ui->data2LineEdit->text();
        QString data = "\"Data Arrivo\" > '%1' AND \"Data Arrivo\" < '%2'";
        filter.append(data.arg(data1, data2));
    }

    if (filter.isEmpty()) {
        return "";
    }
    else {
        return filter.join(" AND ");
    }
}

QString MagazzinoWindow::giacenzaString(void)
{
    qDebug() << "MagazzinoWindow::giacenzaString()";
    QString result = "";

    if (ui->radioGiacenzaPos->isChecked())
        result = QString::fromUtf8("\"Quantità\" >= \"Scorta Minima\"");
    else if (ui->radioGiacenzaNeg->isChecked())
        result = QString::fromUtf8("\"Quantità\" < \"Scorta Minima\"");
    else if (ui->radioGiacenza0->isChecked())
        result = QString::fromUtf8("\"Quantità\" = 0");

    return result;
}

QString MagazzinoWindow::orderString()
{
    qDebug() << "MagazzinoWindow::orderString()";
    QString str = " ORDER BY \"%1\"";
    if (ui->orderbyComboBox->isEnabled())
        return str.arg(ui->orderbyComboBox->currentText());
    else
        return "";
}

void MagazzinoWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "MagazzinoWindow::closeEvent()";
    this->parentWidget()->show();
    saveConfigSettings();
    event->accept();
}

void MagazzinoWindow::showEvent(QShowEvent *)
{
    qDebug() << "MagazzinoWindow::showEvent()";
    updateViewMagazzino();
}

void MagazzinoWindow::addRecord()
{
    qDebug() << "MagazzinoWindow::addRecord()";
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
    qDebug() << "MagazzinoWindow::updateRecord()";
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
    qDebug() << "MagazzinoWindow::removeRecord()";
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
}

void MagazzinoWindow::updateViewMagazzino(void)
{
    qDebug() << "MagazzinoWindow::updateViewMagazzino()";
    QString filter1 = filterString();
    QString filter2 = searchString();
    QString filter3 = giacenzaString();
    QString order = orderString();

    QString query = magazzino::SELECT_ARTICOLI_ALL;
    QStringList filterList;
    if (!filter1.isEmpty())
        filterList.append(filter1);

    if (!filter2.isEmpty())
        filterList.append(filter2);

    if (!filter3.isEmpty())
        filterList.append(filter3);

    if (filterList.length())
        query.append(" WHERE " + filterList.join(" AND "));

    if (!order.isEmpty()) {
        query.append(order);
    }


    articoloModel->setQuery(query);

    ui->articoloView->resizeColumnsToContents();//TODO Rallenta l'esecuzione
    ui->articoloView->horizontalHeader()->setStretchLastSection(true);

    /* Se viene chiusa immediatamente l'applicazione e il model e' vuoto, viene
       corrotto il file di configurazione. Questa impostazione permette di avere
       il model impostato senza valori ed evitare la corruzione dei dati di
       configurazione*/
    storicoModel->setQuery(magazzino::SELECT_STORICO.arg(-1));
}

void MagazzinoWindow::updateViewStorico(QModelIndex index)
{
    qDebug() << "MagazzinoWindow::updateViewStorico()";
    if (!index.isValid()) {
        storicoModel->setQuery(magazzino::SELECT_STORICO.arg(-1));
        return;
    }
    QString id = articoloModel->index(index.row(), magazzino::COL_ID).data().toString();
    storicoModel->setQuery(magazzino::SELECT_STORICO.arg(id));
    ui->storicoView->resizeColumnsToContents();
    ui->storicoView->horizontalHeader()->setStretchLastSection(true);
}

void MagazzinoWindow::openConfigDialog(void)
{
    qDebug() << "MagazzinoWindow::openConfigDialog()";
    saveConfigSettings();
    OptionsMagazzinoDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    loadConfigSettings();
}

void MagazzinoWindow::exportMagazzinoCsv(void)
{
    qDebug() << "MagazzinoWindow::exportMagazzinoCsv()";
    QString filename = QFileDialog::getSaveFileName();
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << magazzino::CVS_VERSION << "\n";

    QSqlQuery query(magazzino::SELECT_CSV_MAGAZZINO);
    while (query.next()) {
        QSqlRecord record = query.record();
        QStringList listValue;
        for (int c=0; c < record.count(); c++) {
            listValue.append(record.value(c).toString());
        }
        out << listValue.join(":")+"\n";
    }

    file.close();
}

void MagazzinoWindow::exportStoricoCsv(void)
{
    qDebug() << "MagazzinoWindow::exportStoricoCsv()";
    QString filename = QFileDialog::getSaveFileName();
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << magazzino::CVS_VERSION << "\n";

    QSqlQuery query(magazzino::SELECT_CSV_STORICO);
    while (query.next()) {
        QSqlRecord record = query.record();
        QStringList listValue;
        for (int c=0; c < record.count(); c++) {
            listValue.append(record.value(c).toString());
        }
        out << listValue.join(":")+"\n";
    }

    file.close();
}

void MagazzinoWindow::importMagazzinoCvs(void)
{
    qDebug() << "MagazzinoWindow::importMagazzinoCvs()";
    QString filename = QFileDialog::getOpenFileName();
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString version = in.readLine();
    if (version != magazzino::CVS_VERSION) {
        qDebug() << "ERRORE"; //TODO definire codice errore per CVS
        return;
    }

    QString line = in.readLine();
    while (!line.isNull()) {
        QStringList listvalue = line.split(":");
        QSqlQuery query;
        query.prepare(magazzino::INSERT_CSV_ARTICOLO);
        for (int i=0; i<listvalue.length(); i++) {
            query.bindValue(i, listvalue[i]);
        }
        qDebug() << query.lastError().text();
        query.exec();
        qDebug() << query.lastError().text();
        line = in.readLine();
    }

    file.close();
}

void MagazzinoWindow::importStoricoCvs(void)
{
    qDebug() << "MagazzinoWindow::importStoricoCvs()";
    QString filename = QFileDialog::getOpenFileName();
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString version = in.readLine();
    if (version != magazzino::CVS_VERSION) {
        qDebug() << "ERRORE"; //TODO definire codice errore per CVS
        return;
    }

    QString line = in.readLine();
    while (!line.isNull()) {
        QStringList listvalue = line.split(":");
        QSqlQuery query;
        query.prepare(magazzino::INSERT_STORICO);
        for (int i=0; i<listvalue.length(); i++) {
            query.bindValue(i, listvalue[i]);
        }
        query.exec();
        line = in.readLine();
    }

    file.close();
}

void MagazzinoWindow::changeCodIva(void)
{
    qDebug() << "MagazzinoWindow::changeCodIva()";
    codIvaUpdateDialog dlg(this);
    if (dlg.exec())
        updateViewMagazzino();
}

void MagazzinoWindow::launchConfigPrintDlg(void)
{
    qDebug() << "MagazzinoWindow::launchConfigPrintDlg()";
    ConfigPrintDialog dlg(this);
    dlg.exec();
}

void MagazzinoWindow::printListino(void)
{
    qDebug() << "MagazzinoWindow::printListino()";
    if (!ui->fornitoreComboBox->isEnabled()) {
        qDebug() << "ERRORE: devi selezionare il fornitore";
        return;
    }

    QString fornitore = ui->fornitoreComboBox->currentText();
    QString data = QDate::currentDate().toString("dd/MM/yy");
    QString titleStr = "%1 del %2";

    ListinoPrintLayout printDlg(articoloModel, titleStr.arg(fornitore).arg(data), this);
}

void MagazzinoWindow::printInventario(void)
{
    qDebug() << "MagazzinoWindow::printInventario()";
    InventarioPrintLayout inventarioDlg(this);
}

void MagazzinoWindow::printOrdine(void)
{
    qDebug() << "MagazzinoWindow::printOrdine()";
    if (!ui->fornitoreComboBox->isEnabled()) {
        qDebug() << "ERRORE: devi selezionare il fornitore";
        return;
    }

    QString fornitore = ui->fornitoreComboBox->currentText();
}

