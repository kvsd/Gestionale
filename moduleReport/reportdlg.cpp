#include "reportdlg.h"
#include "ui_reportdlg.h"

ReportDlg::ReportDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportDlg)
{
    qDebug() << "ReportDlg::PrintReport()";
    ui->setupUi(this);

    printModel = new QSqlQueryModel(this);

    CURRENT_DATE = QDate::currentDate().toString("dd/MM/yyyy");
    CURRENT_YEARS = QDate::currentDate().toString("yyyy");

    showOptions(ui->reportComboBox->currentText());
    initComboBox();
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
    fornitoreModel = new QSqlQueryModel(this);
    fornitoreModel->setQuery(magazzino::SELECT_FORNITORE);
    ui->fornitoreComboBox->setModel(fornitoreModel);
    ui->fornitoreComboBox->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);
}

bool ReportDlg::setupPrinter()
{
    qDebug() << "Report::setupPrinter()";
    printer = new QPrinter(QPrinter::HighResolution);
    QPrintDialog dlg(printer, this);
    if (dlg.exec() == QPrintDialog::Accepted)
        return true;
    else
        return false;
}

bool ReportDlg::initPainter()
{
    //Configura QPainter
    qDebug() << "ReportDlg::initPainter()";
    painter = new QPainter;
    if (!painter->begin(printer))
        return false;
    QPen pen;
    pen.setWidth(10);
    painter->setPen(pen);
    return true;
}

void ReportDlg::print()
{
    setReport(report::LISTINO);
    if (!setupPrinter())
        return;
    if (!initPainter())
        return;

    pageHeight = printer->height();
    pageWidth = printer->width();
    colWidth = pageWidth/report::PRINT_COLS;

    titleRect = QRect(0, 0, pageWidth, report::PRINT_TITLE_HEIGHT);
    const int leftMargin = report::PRINT_MARGINS;
    const int rightMargin = report::PRINT_MARGINS*2;
    col1Rect = QRect(colWidth*0+leftMargin, 0, (colWidth*1)-rightMargin, report::PRINT_COLS_HEIGHT);
    col2Rect = QRect(colWidth*1+leftMargin, 0, (colWidth*3)-rightMargin, report::PRINT_COLS_HEIGHT);
    col3Rect = QRect(colWidth*4+leftMargin, 0, (colWidth*1)-rightMargin, report::PRINT_COLS_HEIGHT);
    col4Rect = QRect(colWidth*5+leftMargin, 0, (colWidth*1)-rightMargin, report::PRINT_COLS_HEIGHT);

    printHeader(titleStr.arg(1));
    printData(reportType);
    painter->end();

    QString info;
    if (printer->outputFileName() != "")
        info = "Il file pdf è stato creato.";
    else
        info = "Il processo di stampa è stato avviato.";

    QMessageBox::StandardButton ret;
    ret = QMessageBox::information(this, "Stampa", info+"Continuare?",
                                   QMessageBox::Yes, QMessageBox::No);
    delete printer;
    delete painter;
    if (ret == QMessageBox::Yes)
        return;
    else if (ret == QMessageBox::No)
        this->close();
}

void ReportDlg::setReport(report::Documenti reportType)
{
    //In base al tipo di report configura il model e le variabili colXName
    qDebug() << "ReportDlg::setReport()";

    if (reportType == report::LISTINO) {
        fornitore = ui->fornitoreComboBox->currentText();
        titleStr = QString("Listino %1 del %2 pag. %3").arg(fornitore).arg(CURRENT_DATE);
        QString query = "";
        if (ui->listinoPrintCurrentDate->isChecked())
            query = report::SELECT_ARTICLE_WITH_CURRENT_DATE.arg(fornitore);
        else if (ui->listinoPrintAll->isChecked())
            query = report::SELECT_ALL_ARTICLE_FROM_FORNITORE.arg(fornitore);

        printModel->setQuery(query);
        col1Name = settings.value(report::LISTINO_COL1, report::CMP_COD_ART).toString();
        col2Name = settings.value(report::LISTINO_COL2, report::CMP_DESCR).toString();
        col3Name = settings.value(report::LISTINO_COL3, report::CMP_PRZ_ACQ).toString();
        col4Name = settings.value(report::LISTINO_COL4, report::CMP_PRZ_VEN).toString();
    }
//    else if (reportType == report::INVENTARIO) {
//        titleStr = QString("Inventario %1 pag. %2").arg(CURRENT_YEARS);
//        printModel->setQuery(report::SELECT_INVENTARIO);
//        col1Name = report::CMP_QT;
//        col2Name = report::CMP_DESCR;
//        col3Name = report::CMP_PRZ_ACQ;
//        col4Name = report::CMP_SUBTOT;
//    }
//    else if  (reportType == report::ORDINE) {
//        titleStr = QString("Ordine %1 del %2 pag.%3").arg(fornitore).arg(CURRENT_DATE);
//        QString query = report::SELECT_ORDINE.arg(fornitore);
//        printModel->setQuery(query);
//        col1Name = settings.value(report::ORDINE_COL1, report::CMP_COD_ART).toString();
//        col2Name = settings.value(report::ORDINE_COL2, report::CMP_DESCR).toString();
//        col3Name = settings.value(report::ORDINE_COL3, report::CMP_QT).toString();
//        col4Name = settings.value(report::ORDINE_COL4, report::CMP_SCORTA).toString();
//    }
//    else {
//        return;
//    }
}

void ReportDlg::printHeader(QString titleStr)
{
    //Stampa l'intestazione titleStr e l'header del report con colXName
    qDebug() << "ReportDlg::printHeader()";
    //Stampo titolo
    painter->drawText(titleRect, Qt::AlignLeft|Qt::AlignVCenter, titleStr, &titleRect);

    //Stampo l'intestazione delle tabelle
    setRow(0);
    painter->drawText(col1Rect, Qt::AlignCenter, col1Name);
    painter->drawText(col2Rect, Qt::AlignCenter, col2Name);
    painter->drawText(col3Rect, Qt::AlignCenter, col3Name);
    painter->drawText(col4Rect, Qt::AlignCenter, col4Name);

    //Stampo la cornice dell'intestazione
    painter->drawLine(0, report::PRINT_TITLE_HEIGHT, pageWidth, report::PRINT_TITLE_HEIGHT);
    painter->drawLine(0, report::PRINT_TITLE_HEIGHT+report::PRINT_COLS_HEIGHT, pageWidth, report::PRINT_TITLE_HEIGHT+report::PRINT_COLS_HEIGHT);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, report::PRINT_TITLE_HEIGHT, colWidth*i, report::PRINT_TITLE_HEIGHT+report::PRINT_COLS_HEIGHT );
    }
}

void ReportDlg::printRow(int row, QSqlRecord record)
{
    //Stampa alla riga row il record passato come parametro.
    //I campi sono definiti tramite configPrintDialog
    qDebug() << "ReportDlg::printRow()";
    setRow(row);

    QString col1Value = record.value(col1Name).toString();
    QString col2Value = record.value(col2Name).toString();
    QString col3Value = record.value(col3Name).toString();
    QString col4Value = record.value(col4Name).toString();

    painter->drawText(col1Rect, Qt::AlignLeft|Qt::AlignVCenter, col1Value);
    painter->drawText(col2Rect, Qt::AlignLeft|Qt::AlignVCenter, col2Value);
    painter->drawText(col3Rect, Qt::AlignRight|Qt::AlignVCenter, col3Value);
    painter->drawText(col4Rect, Qt::AlignRight|Qt::AlignVCenter, col4Value);

    painter->drawLine(0, col1Rect.y()+report::PRINT_COLS_HEIGHT, pageWidth, col1Rect.y()+report::PRINT_COLS_HEIGHT);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, col1Rect.y(), colWidth*i, col1Rect.y()+report::PRINT_COLS_HEIGHT);
    }
}

void ReportDlg::printData(report::Documenti reportType)
{
    //Stampa tutte i record presenti nel model
    qDebug() << "ReportDlg::printData()";
    const int MAX_ROW = (pageHeight-report::PRINT_TITLE_HEIGHT)/report::PRINT_COLS_HEIGHT;
    const int ROWS = printModel->rowCount();
    int row = 0;
    int page = 2;
    for (int i=0; i<ROWS; i++, row++) {
        if (i%MAX_ROW == 0 && i!=0) {
            printer->newPage();
            row = 0;
            printHeader(titleStr.arg(page++));
        }
        printRow(row+1, printModel->record(i));
    }
    if (reportType == report::INVENTARIO) {
        printTotale(row+1);
    }
}

void ReportDlg::setRow(int row)
{
    //Imposta la riga per la stampa
    qDebug() << "ReportDlg::setRow()";
    const int y = (row*report::PRINT_COLS_HEIGHT)+report::PRINT_TITLE_HEIGHT;
    col1Rect.moveTop(y);
    col2Rect.moveTop(y);
    col3Rect.moveTop(y);
    col4Rect.moveTop(y);
}

void ReportDlg::printTotale(int row)
{
    qDebug() << "ReportDlg::printTotale()";
    setRow(row);

    QSqlQuery query(report::SQL_INVENTARIO_TOT);
    query.first();
    QString totale = query.record().value("Totale").toString();
    QString msg = "Totale: %1";

    const int leftMargin = report::PRINT_MARGINS;
    const int rightMargin = report::PRINT_MARGINS*2;
    QRect coltot(colWidth*4+leftMargin, col1Rect.y(), (colWidth*2)-rightMargin, report::PRINT_COLS_HEIGHT);

    painter->drawText(coltot, Qt::AlignRight|Qt::AlignVCenter, msg.arg(totale));
    painter->drawLine(col3Rect.x()-report::PRINT_MARGINS, col1Rect.y()+report::PRINT_COLS_HEIGHT,
                      pageWidth, col1Rect.y()+report::PRINT_COLS_HEIGHT);
    painter->drawLine(colWidth*4, col1Rect.y(), colWidth*4, col1Rect.y()+report::PRINT_COLS_HEIGHT);
    painter->drawLine(colWidth*6, col1Rect.y(), colWidth*6, col1Rect.y()+report::PRINT_COLS_HEIGHT);
}

void ReportDlg::launchConfigDlg()
{
    qDebug() << "ReportDlg::launchConfigDlg()";
    ConfigPrintDialog dlg(this);
    dlg.exec();
}

void ReportDlg::showOptions(QString text)
{
    qDebug() << "ReportDlg::showOptions()";
    if (text == "Listino") {
        ui->listinoGroupBox->setVisible(true);
        ui->ordineGroupBox->setVisible(false);
        ui->inventarioGroupBox->setVisible(false);
    }
    else if (text == "Ordine") {
        ui->listinoGroupBox->setVisible(false);
        ui->ordineGroupBox->setVisible(true);
        ui->inventarioGroupBox->setVisible(false);
    }
    else if (text == "Inventario") {
        ui->listinoGroupBox->setVisible(false);
        ui->ordineGroupBox->setVisible(false);
        ui->inventarioGroupBox->setVisible(true);
    }
    adjustSize();
}
