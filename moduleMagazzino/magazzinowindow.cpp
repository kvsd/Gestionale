#include "magazzinowindow.h"
#include "ui_magazzinowindow.h"

MagazzinoWindow::MagazzinoWindow(QWidget *parent) :
    CustomWindow(parent),
    ui(new Ui::MagazzinoWindow)
{
    qDebug() << "MagazzinoWindow()";
    ui->setupUi(this);
    this->move(parent->pos());

    initModel();
    initComboBox();
    loadConfigSettings();

    ui->data1LineEdit->setDate(QDate::currentDate());
    ui->data2LineEdit->setDate(QDate::currentDate());
}

MagazzinoWindow::~MagazzinoWindow()
{
    qDebug() << "~MagazzinoWindow()";
    delete ui;
}

void MagazzinoWindow::initModel()
{
    qDebug() << "MagazzinoWindow::initModel()";

    QMap <QString, Qt::AlignmentFlag> map;
    QStringList cols;
    cols << "Descrizione" << "Fornitore" << "Note" << "Modello"
         << "Cod.Articolo" << "Cod.Fornitore";
    for (auto col : cols)
        map[col] = Qt::AlignLeft;

    articoloModel = new CustomModel(Qt::AlignRight, this);
    articoloModel->setAlignMap(map);

    storicoModel = new CustomModel(Qt::AlignRight, this);
    fornitoreModel = new QSqlQueryModel(this);
    categoriaModel = new QSqlTableModel(this);
    marcaModel = new QSqlTableModel(this);
    sedeModel = new QSqlTableModel(this);

    ui->articoloView->setModel(articoloModel);
    ui->storicoView->setModel(storicoModel);

    fornitoreModel->setQuery(sql::SELECT_FORNITORE);

    categoriaModel->setTable(table::CATEGORIA_MERCE);
    categoriaModel->setSort(magazzino::COL_TABLE_DESCRIZIONE, Qt::AscendingOrder);

    marcaModel->setTable(table::MARCA);
    marcaModel->setSort(magazzino::COL_TABLE_DESCRIZIONE, Qt::AscendingOrder);

    sedeModel->setTable(table::SEDE_MAGAZZINO);
    sedeModel->setSort(magazzino::COL_TABLE_DESCRIZIONE, Qt::AscendingOrder);

    updateModel();
}

void MagazzinoWindow::initComboBox()
{
    qDebug() << "MagazzinoWindow::initComboBox()";
    ui->fornitoreComboBox->setModel(fornitoreModel);
    ui->fornitoreComboBox->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->categoriaComboBox->setModel(categoriaModel);
    ui->categoriaComboBox->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->marcaComboBox->setModel(marcaModel);
    ui->marcaComboBox->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);

    ui->sedeComboBox->setModel(sedeModel);
    ui->sedeComboBox->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);
}

void MagazzinoWindow::updateModel()
{
    qDebug() << "MagazzinoWindow::updateModel()";
    QString fornitoreText = ui->fornitoreComboBox->currentText();
    QString categoriaText = ui->categoriaComboBox->currentText();
    QString marcaText = ui->marcaComboBox->currentText();
    QString sedeText = ui->sedeComboBox->currentText();

    fornitoreModel->setQuery(sql::SELECT_FORNITORE);
    categoriaModel->select();
    marcaModel->select();
    sedeModel->select();

    if (fornitoreText.isEmpty() || categoriaText.isEmpty() ||
            marcaText.isEmpty() || sedeText.isEmpty())
        return;

    ui->fornitoreComboBox->setCurrentText(fornitoreText);
    ui->categoriaComboBox->setCurrentText(categoriaText);
    ui->marcaComboBox->setCurrentText(marcaText);
    ui->sedeComboBox->setCurrentText(sedeText);
}

void MagazzinoWindow::loadConfigSettings()
{
    qDebug() << "MagazzinoWindow::loadConfigSettings()";

    loadWindowGeometry();
    loadSplittersState();
    loadTableViewSettings();

    //Carico la visibilita delle colonne della vista articolo e storico
    loadColumnVisibility(ui->articoloView, magazzino::ARTICOLO_STATUS);
    loadColumnVisibility(ui->storicoView, magazzino::STORICO_STATUS);

    //Carico il colore dello sfondo delle colonne. (Si e' gestito dai model)
    //articoloModel->setDefaultBgColor(QColor(255,255,180));
    articoloModel->setBgMap(getBgSettings(magazzino::ARTICOLO_COLORS));
    //storicoModel->setDefaultBgColor(QColor(220,220,180));
    storicoModel->setBgMap(getBgSettings(magazzino::STORICO_COLORS));

    //Carico le impostazioni del menu ricerca
    ui->actionDescrizione->setChecked(settings.value(magazzino::SEARCH_DESCR, true).toBool());
    ui->actionCod_Articolo->setChecked(settings.value(magazzino::SEARCH_COD_ART, false).toBool());
    ui->actionCod_Fornitore->setChecked(settings.value(magazzino::SEARCH_COD_FRN, false).toBool());
    ui->actionEAN->setChecked(settings.value(magazzino::SEARCH_COD_EAN, false).toBool());
}

void MagazzinoWindow::saveConfigSettings()
{
    qDebug() << "MagazzinoWindow::saveConfigSettings()";

    saveWindowGeometry();
    saveSplittersState();
    saveTableViewSettings();

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
    QString value = ui->searchLineEdit->text();
    if (value.isEmpty())
        return "";

    QStringList filter;
    QString pattern = "%1 ILIKE '%%2%'";
    if (ui->actionDescrizione->isChecked())
        filter.append(pattern.arg(col::DESCRIZIONE));

    if (ui->actionCod_Fornitore->isChecked())
        filter.append(pattern.arg(col::CODICE_FORNITORE));

    if (ui->actionCod_Articolo->isChecked())
        filter.append(pattern.arg(col::CODICE_ARTICOLO));

    if (ui->actionEAN->isChecked())
        filter.append(pattern.arg(col::CODICE_BARRE));

    if (filter.isEmpty())
        return "";

    return ( "(" + filter.join(" OR ").arg(value) + ")" );
}

QString MagazzinoWindow::filterString(void) {
    //Prepara i filtri della query in base ai vari parametri che vengono
    //selezionati nel pannello filtro
    qDebug() << "MagazzinoWindow::filterString()";
    QStringList filter;
    QString pattern = "%1 = '%2'";
    if (ui->fornitoreComboBox->isEnabled()) {
        int index = ui->fornitoreComboBox->currentIndex();
        QString id = fornitoreModel->record(index).value(magazzino::COL_TABLE_ID).toString();
        filter.append(pattern.arg(col::ID_FORNITORE).arg(id));
    }

    if (ui->categoriaComboBox->isEnabled()) {
        int index = ui->categoriaComboBox->currentIndex();
        QString id = categoriaModel->record(index).value(magazzino::COL_TABLE_ID).toString();
        filter.append(pattern.arg(col::ID_MERCE).arg(id));
    }

    if (ui->marcaComboBox->isEnabled()) {
        int index = ui->marcaComboBox->currentIndex();
        QString id = marcaModel->record(index).value(magazzino::COL_TABLE_ID).toString();
        filter.append(pattern.arg(col::ID_MARCA).arg(id));
    }

    if (ui->sedeComboBox->isEnabled()) {
        int index = ui->sedeComboBox->currentIndex();
        QString id = sedeModel->record(index).value(magazzino::COL_TABLE_ID).toString();
        filter.append(pattern.arg(col::ID_SEDE_MAGAZZINO).arg(id));
    }

    if (ui->fatturaLineEdit->isEnabled()) {
        QString numero_fattura = ui->fatturaLineEdit->text();
        QString pattern("fattura ILIKE '%%1%'");
        filter.append(pattern.arg(numero_fattura));
    }

    if (ui->currentDateEnabler->isChecked()) {
        QString currentDate = QDate::currentDate().toString("dd/MM/yy");
        filter.append(pattern.arg(col::DATA_ARRIVO).arg(currentDate));
    }
    else if (ui->rangeDateEnabler->isChecked()) {
        QString data1 = ui->data1LineEdit->text();
        QString data2 = ui->data2LineEdit->text();
        QString data = "data_arrivo >= '%1' AND data_arrivo <= '%2'";
        filter.append(data.arg(data1, data2));
    }

    if (filter.isEmpty())
        return "";
    else
        return filter.join(" AND ");
}

QString MagazzinoWindow::giacenzaString(void)
{
    //Prepara il filtro giacenza in base alla selezione dei checkbox giacenza
    qDebug() << "MagazzinoWindow::giacenzaString()";
    QString result = "";

    if (ui->radioGiacenzaPos->isChecked())
        result = QString("%1 >= %2").arg(col::QUANTITA).arg(col::SCORTA_MINIMA);
    else if (ui->radioGiacenzaNeg->isChecked())
        result = QString("%1 < %2").arg(col::QUANTITA).arg(col::SCORTA_MINIMA);
    else if (ui->radioGiacenza0->isChecked())
        result = QString("%1 = 0").arg(col::QUANTITA);

    return result;
}

QString MagazzinoWindow::orderString()
{
    //Prepara il filtro per ordinare la query in base alla selezione di
    //orderbyComboBox
    qDebug() << "MagazzinoWindow::orderString()";
    QString str = " ORDER BY \"%1\"";
    if (ui->orderbyComboBox->isEnabled())
        return str.arg(ui->orderbyComboBox->currentText());
    else
        return str.arg(col::DESCRIZIONE);
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
    if (!ok)
        return;

    updateViewMagazzino();
    updateModel();
}

void MagazzinoWindow::updateRecord(void)
{
    qDebug() << "MagazzinoWindow::updateRecord()";
    QModelIndex index = ui->articoloView->currentIndex();
    if (!index.isValid()) {
        showDialogError(this, ERR047, MSG011); //NOTE codice errore 047
        return;
    }

    QString id = articoloModel->record(index.row()).value(col::ID).toString();
    ArticoloDialog dlg(this);
    dlg.setValue(id);
    dlg.setWindowTitle("Modifica Articolo");
    bool ok = dlg.exec();
    if (!ok)
        return;

    updateViewMagazzino();
    updateViewStorico(index);
    updateModel();
}

void MagazzinoWindow::cloneRecord(void)
{
    qDebug() << "MagazzinoWindow::cloneRecord()";
    QModelIndex index = ui->articoloView->currentIndex();
    if (!index.isValid()) {
        showDialogError(this, ERR056, MSG028); //NOTE codice errore 056
        return;
    }

    QString id = articoloModel->record(index.row()).value(col::ID).toString();
    ArticoloDialog dlg(this);
    dlg.setValue(id, false);
    bool ok = dlg.exec();
    if (!ok)
        return;

    updateViewMagazzino();
    updateModel();
}

void MagazzinoWindow::removeRecord(void)
{
    qDebug() << "MagazzinoWindow::removeRecord()";
    QModelIndex index = ui->articoloView->currentIndex();
    if (!index.isValid()) {
        showDialogError(this, ERR036, MSG009); //NOTE codice errore 036
        return;
    }
    QString id = articoloModel->record(index.row()).value(col::ID).toString();
    QSqlQuery query;
    query.prepare(magazzino::DELETE_ARTICOLO);
    query.bindValue(ph::ID, id);
    if (!query.exec())
        showDialogError(this, ERR037, MSG003, query.lastError().text()); //NOTE codice errore 037

    updateViewMagazzino();
}

void MagazzinoWindow::updateViewMagazzino(void)
{
    //Aggiorna il model articoloModel applicando i vari filtri selezionati
    qDebug() << "MagazzinoWindow::updateViewMagazzino()";
    QString filter1 = filterString();
    QString filter2 = searchString();
    QString filter3 = giacenzaString();
    QString order = orderString();

    QString query = sql::SELECT_ARTICOLI_ALL;
    QStringList filterList;
    if (!filter1.isEmpty())
        filterList.append(filter1);

    if (!filter2.isEmpty())
        filterList.append(filter2);

    if (!filter3.isEmpty())
        filterList.append(filter3);

    if (filterList.length())
        query.append(" AND " + filterList.join(" AND "));

    if (!order.isEmpty())
        query.append(order);

    articoloModel->setQuery(query);

    ui->articoloView->resizeColumnsToContents();
    ui->articoloView->horizontalHeader()->setStretchLastSection(true);

    /* Per creare l'elenco dinamico delle colonne devo prima impostare il model
    ** per questo viene settato in updateViewMagazzino e non in initComboBox */
    if (!ui->orderbyComboBox->count())
        ui->orderbyComboBox->addItems(prepareMapsFromModel(articoloModel).values());

    /* Se viene chiusa immediatamente l'applicazione e il model e' vuoto, viene
       corrotto il file di configurazione. Questa impostazione permette di avere
       il model impostato senza valori ed evitare la corruzione dei dati di
       configurazione*/
    storicoModel->setQuery(magazzino::SELECT_STORICO.arg(-1));
}

void MagazzinoWindow::updateViewStorico(QModelIndex index)
{
    //Aggiorna il view Storico listino quando viene selezionato un
    //articolo nella view Articolo.
    qDebug() << "MagazzinoWindow::updateViewStorico()";
    if (!index.isValid()) {
        storicoModel->setQuery(magazzino::SELECT_STORICO.arg(-1));
        return;
    }
    QString id = articoloModel->record(index.row()).value(col::ID).toString();
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
    if (!ok)
        return;

    ui->articoloView->clearSelection();
    loadConfigSettings();
}

void MagazzinoWindow::changeCodIva(void)
{
    qDebug() << "MagazzinoWindow::changeCodIva()";
    codIvaUpdateDialog dlg(this);
    if (dlg.exec())
        updateViewMagazzino();
}

void MagazzinoWindow::launchReportConfig(void)
{
    qDebug() << "MagazzinoWindow::launchReportConfig()";
    ConfigPrintDialog dlg(this);
    dlg.exec();
}

void MagazzinoWindow::launchReportListino()
{
    qDebug() << "MagazzinoWindow::launchReportListino()";
    ListinoDlg dlg(this);
    dlg.exec();
}

void MagazzinoWindow::launchReportInventario()
{
    qDebug() << "MagazzinoWindow::launchReportInventario()";
//    ReportInventario dlg(this);
//    dlg.exec();
}

void MagazzinoWindow::findCodBarre()
{
    //Slot che ricerca tutti gli articoli senza codice a barre.
    qDebug() << "MagazzinoWindow::findCodBarre()";
    QSqlQuery SELECT_COD_BARRE = QSqlQuery(sql::SELECT_ARTICOLI_ALL +
                                           " AND cod_barre='' " +
                                           orderString());
    articoloModel->setQuery(SELECT_COD_BARRE);
}
