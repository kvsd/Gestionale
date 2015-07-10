#include "reportdlg.h"
#include "ui_reportdlg.h"

ReportDlg::ReportDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportDlg)
{
    qDebug() << "ReportDlg::PrintReport()";
    ui->setupUi(this);

    m_printModel = new QSqlQueryModel(this);
    m_ordineModel = new QStandardItemModel(this);
    ui->orderView->setModel(m_ordineModel);

    CURRENT_DATE = QDate::currentDate().toString("dd/MM/yyyy");
    CURRENT_YEARS = QDate::currentDate().toString("yyyy");

    initComboBox();
    showOptions(ui->reportComboBox->currentText());
}

ReportDlg::~ReportDlg()
{
    qDebug() << "ReportDlg::~PrintReport()";
    delete ui;
}

void ReportDlg::initComboBox()
{
    qDebug() << "Report::initComboBox()";
    //Configura il model e il combobox fornitore
    m_fornitoreModel = new QSqlQueryModel(this);
    m_fornitoreModel->setQuery(magazzino::SELECT_FORNITORE);
    ui->fornitoreComboBox->blockSignals(true);
    ui->fornitoreComboBox->setModel(m_fornitoreModel);
    ui->fornitoreComboBox->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);
    ui->fornitoreComboBox->blockSignals(false);

    //Configura il combobox reportType
    QStringList items;
    items << report::LISTINO << report::ORDINE << report::INVENTARIO;
    ui->reportComboBox->blockSignals(true);
    ui->reportComboBox->addItems(items);
    ui->reportComboBox->blockSignals(false);
}

bool ReportDlg::setupPrinter()
{
    //Imposta QPrinter tramite PrintDialog
    qDebug() << "Report::setupPrinter()";
    m_printer = new QPrinter(QPrinter::HighResolution);
    QPrintDialog dlg(m_printer, this);
    if (dlg.exec() == QPrintDialog::Accepted)
        return true;
    else
        return false;
}

bool ReportDlg::initPainter()
{
    //Configura QPainter
    qDebug() << "ReportDlg::initPainter()";
    m_painter = new QPainter;
    if (!m_painter->begin(m_printer))
        return false;
    QPen pen;
    pen.setWidth(10);
    m_painter->setPen(pen);
    return true;
}

void ReportDlg::print()
{
    if (!setupPrinter())
        return;
    if (!initPainter())
        return;

    m_pageHeight = m_printer->height();
    m_pageWidth = m_printer->width();
    m_colWidth = m_pageWidth/report::PRINT_COLS;

    m_titleRect = QRect(0, 0, m_pageWidth, report::PRINT_TITLE_HEIGHT);
    const int leftMargin = report::PRINT_MARGINS;
    const int rightMargin = report::PRINT_MARGINS*2;
    m_col1Rect = QRect(m_colWidth*0+leftMargin, 0, (m_colWidth*1)-rightMargin, report::PRINT_COLS_HEIGHT);
    m_col2Rect = QRect(m_colWidth*1+leftMargin, 0, (m_colWidth*3)-rightMargin, report::PRINT_COLS_HEIGHT);
    m_col3Rect = QRect(m_colWidth*4+leftMargin, 0, (m_colWidth*1)-rightMargin, report::PRINT_COLS_HEIGHT);
    m_col4Rect = QRect(m_colWidth*5+leftMargin, 0, (m_colWidth*1)-rightMargin, report::PRINT_COLS_HEIGHT);

    printHeader(m_titleStr.arg(1));
    printData();
    m_painter->end();

    QString info;
    if (m_printer->outputFileName() != "")
        info = tr("Il file pdf è stato creato.");
    else
        info = tr("Il processo di stampa è stato avviato.");

    QMessageBox::StandardButton ret;
    ret = QMessageBox::information(this, "Stampa", info+"Uscire?",
                                   QMessageBox::Yes, QMessageBox::No);
    delete m_printer;
    delete m_painter;
    if (ret == QMessageBox::Yes)
        this->close();
    else if (ret == QMessageBox::No)
        return;
}

void ReportDlg::setReport()
{
    //In base al tipo di report configura il model e le variabili colXName
    qDebug() << "ReportDlg::setReport()";
    const QString reportType = ui->reportComboBox->currentText();
    if (reportType == report::LISTINO) {
        m_titleStr = QString("Listino %1 del %2 pag. %3").arg(m_fornitore).arg(CURRENT_DATE);
        QString query = "";
        if (ui->listinoPrintCurrentDate->isChecked())
            query = report::SELECT_ARTICLE_WITH_CURRENT_DATE.arg(m_fornitore);
        else if (ui->listinoPrintAll->isChecked())
            query = report::SELECT_ALL_ARTICLE_FROM_FORNITORE.arg(m_fornitore);

        m_printModel->setQuery(query);
        m_col1Name = m_settings.value(report::LISTINO_COL1, report::CMP_COD_ART).toString();
        m_col2Name = m_settings.value(report::LISTINO_COL2, report::CMP_DESCR).toString();
        m_col3Name = m_settings.value(report::LISTINO_COL3, report::CMP_PRZ_ACQ).toString();
        m_col4Name = m_settings.value(report::LISTINO_COL4, report::CMP_PRZ_VEN).toString();
    }
    else if (reportType == report::INVENTARIO) {
        m_titleStr = QString("Inventario %1 pag. %2").arg(CURRENT_YEARS);
        m_printModel->setQuery(report::SELECT_INVENTARIO);
        m_col1Name = report::CMP_QT;
        m_col2Name = report::CMP_DESCR;
        m_col3Name = report::CMP_PRZ_ACQ;
        m_col4Name = report::CMP_SUBTOT;
    }
    else if (reportType == report::ORDINE) {
        m_titleStr = QString("Ordine %1 del %2 pag.%3").arg(m_fornitore).arg(CURRENT_DATE);
        QString query = report::SELECT_ORDINE.arg(m_fornitore);
        m_printModel->setQuery(query);
        m_col1Name = m_settings.value(report::ORDINE_COL1, report::CMP_COD_ART).toString();
        m_col2Name = m_settings.value(report::ORDINE_COL2, report::CMP_DESCR).toString();
        m_col3Name = m_settings.value(report::ORDINE_COL3, report::CMP_QT).toString();
        m_col4Name = m_settings.value(report::ORDINE_COL4, report::CMP_SCORTA).toString();
        initOrderView(m_printModel);
    }
}

void ReportDlg::initOrderView(QSqlQueryModel *model)
{
    qDebug() << "ReportDlg::initListView()";
    const int ROWS = model->rowCount();
    const int COLS = 5; //le quattro colonne classiche piu' la colonna per il checkbox

    m_ordineModel->setColumnCount(COLS);
    m_ordineModel->setRowCount(ROWS);

    //Imposto i nomi delle intestazioni della tabella ordini
    QStringList headersName;
    headersName << "Id" << m_col1Name << m_col2Name << m_col3Name << m_col4Name;
    for (int col=0; col<COLS; col++) {
        m_ordineModel->setHeaderData(col, Qt::Horizontal, headersName[col]);
    }

    //Leggo i dati da model e li carico in m_ordineModel
    for (int row=0; row<ROWS; row++) {
        for (int col=0; col<COLS; col++) {
            QStandardItem *Item = new QStandardItem();
            if (col == 0) {
                Item->setCheckable(true);
                Item->setEditable(false);
            }
            QString name = model->record(row).value(headersName[col]).toString();
            Item->setText(name);
            m_ordineModel->setItem(row, col, Item);
        }
    }

    ui->orderView->horizontalHeader()->setStretchLastSection(true);
    ui->orderView->resizeColumnsToContents();
}

void ReportDlg::printHeader(QString titleStr)
{
    //Stampa l'intestazione titleStr e l'header del report con colXName
    qDebug() << "ReportDlg::printHeader()";
    //Stampo titolo
    m_painter->drawText(m_titleRect, Qt::AlignLeft|Qt::AlignVCenter, titleStr, &m_titleRect);

    //Stampo l'intestazione delle tabelle
    setRow(0);
    m_painter->drawText(m_col1Rect, Qt::AlignCenter, m_col1Name);
    m_painter->drawText(m_col2Rect, Qt::AlignCenter, m_col2Name);
    m_painter->drawText(m_col3Rect, Qt::AlignCenter, m_col3Name);
    m_painter->drawText(m_col4Rect, Qt::AlignCenter, m_col4Name);

    //Stampo la cornice dell'intestazione
    m_painter->drawLine(0, report::PRINT_TITLE_HEIGHT, m_pageWidth, report::PRINT_TITLE_HEIGHT);
    m_painter->drawLine(0, report::PRINT_TITLE_HEIGHT+report::PRINT_COLS_HEIGHT, m_pageWidth, report::PRINT_TITLE_HEIGHT+report::PRINT_COLS_HEIGHT);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        m_painter->drawLine(m_colWidth*i, report::PRINT_TITLE_HEIGHT, m_colWidth*i, report::PRINT_TITLE_HEIGHT+report::PRINT_COLS_HEIGHT );
    }
}

void ReportDlg::printRow(int row, QStringList rowValues)
{
    setRow(row);
    if (rowValues.isEmpty()) {
        return;
    }
    QList <QRect> rectCols;
    rectCols << m_col1Rect << m_col2Rect << m_col3Rect << m_col4Rect;

    for (int col=0; col<4; col++) {
        int alignment = 0;
        if (col <= 1)
            alignment = Qt::AlignLeft|Qt::AlignVCenter;
        else
            alignment = Qt::AlignRight|Qt::AlignVCenter;

        m_painter->drawText(rectCols[col],alignment, rowValues[col]);
    }

    m_painter->drawLine(0, m_col1Rect.y()+report::PRINT_COLS_HEIGHT, m_pageWidth, m_col1Rect.y()+report::PRINT_COLS_HEIGHT);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        m_painter->drawLine(m_colWidth*i, m_col1Rect.y(), m_colWidth*i, m_col1Rect.y()+report::PRINT_COLS_HEIGHT);
    }
}

QStringList ReportDlg::getFields(QSqlRecord record)
{
    //Metodo che ritorna una QStringList i valori di record. Il nome dei campi
    //viene preso dagli attributi di classe m_colXName.
    QStringList list;
    QStringList fieldName;
    fieldName << m_col1Name << m_col2Name << m_col3Name << m_col4Name;
    for (int col=0; col<4; col++) {
        list << record.value(fieldName[col]).toString();
    }
    return list;
}

QStringList ReportDlg::getFields(QList<QStandardItem*> items)
{
    //Metodo che ritorna i valori di items, utilizzata nella
    //gestione degli ordini
    QStringList list;
    for (int col=1; col<5; col++) {
        list << items[col]->text();
    }
    return list;
}

void ReportDlg::printData()
{
    //Stampa tutte i record presenti nel model
    qDebug() << "ReportDlg::printData()";
    const int MAX_ROW = (m_pageHeight-report::PRINT_TITLE_HEIGHT)/report::PRINT_COLS_HEIGHT;
    const int ROWS = m_printModel->rowCount();
    int row = 1;
    int page = 2;

    const QString reportType = ui->reportComboBox->currentText();

    for (int i=0; i<ROWS; i++, row++) {
        if (i%MAX_ROW == 0 && i!=0) {
            m_printer->newPage();
            row = 1;
            printHeader(m_titleStr.arg(page++));
        }
        QStringList fields;
        if (reportType == report::LISTINO || reportType == report::INVENTARIO) {
            QSqlRecord record = m_printModel->record(i);
            fields = getFields(record);
        }
        else if (reportType == report::ORDINE) {
            QList <QStandardItem *> items = m_ordineModel->takeRow(0);
            if (items[0]->checkState())
                fields = getFields(items);
            else
                row--;
        }
        printRow(row, fields);
    }
    if (reportType == report::INVENTARIO)
        printTotale(row);
}

void ReportDlg::setRow(int row)
{
    //Imposta la riga per la stampa
    qDebug() << "ReportDlg::setRow()";
    const int y = (row*report::PRINT_COLS_HEIGHT)+report::PRINT_TITLE_HEIGHT;
    m_col1Rect.moveTop(y);
    m_col2Rect.moveTop(y);
    m_col3Rect.moveTop(y);
    m_col4Rect.moveTop(y);
}

void ReportDlg::printTotale(int row)
{
    //Interroga il database e stampa il totale dell'inventario
    qDebug() << "ReportDlg::printTotale()";
    setRow(row);

    QSqlQuery query(report::SQL_INVENTARIO_TOT);
    query.first();
    QString totale = query.record().value("Totale").toString();
    QString msg = "Totale: %1";

    const int leftMargin = report::PRINT_MARGINS;
    const int rightMargin = report::PRINT_MARGINS*2;
    QRect coltot(m_colWidth*4+leftMargin, m_col1Rect.y(), (m_colWidth*2)-rightMargin, report::PRINT_COLS_HEIGHT);

    m_painter->drawText(coltot, Qt::AlignRight|Qt::AlignVCenter, msg.arg(totale));
    m_painter->drawLine(m_col3Rect.x()-report::PRINT_MARGINS, m_col1Rect.y()+report::PRINT_COLS_HEIGHT,
                      m_pageWidth, m_col1Rect.y()+report::PRINT_COLS_HEIGHT);
    m_painter->drawLine(m_colWidth*4, m_col1Rect.y(), m_colWidth*4, m_col1Rect.y()+report::PRINT_COLS_HEIGHT);
    m_painter->drawLine(m_colWidth*6, m_col1Rect.y(), m_colWidth*6, m_col1Rect.y()+report::PRINT_COLS_HEIGHT);
}

void ReportDlg::launchConfigDlg()
{
    qDebug() << "ReportDlg::launchConfigDlg()";
    ConfigPrintDialog dlg(this);
    dlg.exec();
}

void ReportDlg::showOptions(QString text)
{
    //Slot collegato al segnale currentTextChanged del widget reportComboBox
    //Modifica la gui in base alla selezione.
    qDebug() << "ReportDlg::showOptions()";
    if (text == report::LISTINO) {
        ui->fornitoreLabel->setVisible(true);
        ui->fornitoreComboBox->setVisible(true);
        ui->listinoGroupBox->setVisible(true);
        ui->ordineGroupBox->setVisible(false);
        ui->inventarioGroupBox->setVisible(false);
    }
    else if (text == report::ORDINE) {
        ui->fornitoreLabel->setVisible(true);
        ui->fornitoreComboBox->setVisible(true);
        ui->listinoGroupBox->setVisible(false);
        ui->ordineGroupBox->setVisible(true);
        ui->inventarioGroupBox->setVisible(false);
    }
    else if (text == report::INVENTARIO) {
        ui->fornitoreLabel->setVisible(false);
        ui->fornitoreComboBox->setVisible(false);
        ui->listinoGroupBox->setVisible(false);
        ui->ordineGroupBox->setVisible(false);
        ui->inventarioGroupBox->setVisible(true);
    }
    adjustSize();
    setReport();
}

void ReportDlg::updateFornitore(QString fornitore)
{
    //Slot collegato a fornitoreComboBox
    qDebug() << "ReportDlg::updateFornitore()";
    m_fornitore = fornitore;
    setReport();
}
