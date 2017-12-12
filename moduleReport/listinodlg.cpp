#include "listinodlg.h"
#include "ui_listinodlg.h"

ListinoDlg::ListinoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListinoDlg)
{
    qDebug() << "ListinoDlg::ListinoDlg()";
    ui->setupUi(this);
    m_printer = new QPrinter(QPrinter::HighResolution);
    QMargins margin(3.53, 3.53, 3.53, 3.53);
    m_printer->setPageMargins(margin, QPageLayout::Millimeter);
    m_printer->setOutputFileName("./listino.pdf");
    initFornitoreCb();
    setColsLayout();
}

ListinoDlg::~ListinoDlg()
{
    qDebug() << "ListinoDlg::~ListinoDlg()";
    delete ui;
    delete m_printer;
}

void ListinoDlg::setColsLayout()
{
    qDebug() << "ListinoDlg::getColsLayout()";
    m_colsName.clear();
    m_stretchValues.clear();
    m_viewName.clear();
    m_settings.beginGroup(report::listinoCols);
    for (auto s : m_settings.allKeys()) {
         QStringList value = m_settings.value(s).toStringList();
         m_colsName.append(value.at(0));
         m_stretchValues.append(value.at(1).toInt());
         m_viewName.append(value.at(2));
    }
    m_settings.endGroup();
}

void ListinoDlg::nextPage()
{
    qDebug() << "ListinoDlg::~nextPage()";
    m_printer->newPage();
}

void ListinoDlg::initFornitoreCb()
{
    qDebug() << "ListinoDlg::initFornitoreCb()";
    m_modelFornitori = new QSqlQueryModel(this);
    m_modelFornitori->setQuery(magazzino::SELECT_FORNITORE);
    ui->fornitoreCb->setModel(m_modelFornitori);
    ui->fornitoreCb->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);
}

void ListinoDlg::draw()
{
    qDebug() << "ListinoDlg::draw()";
    m_painter = new QPainter(m_printer);
    QString fornitore = ui->fornitoreCb->currentText();
    QString data = QDate::currentDate().toString("dd/MM/yyyy");

    //----------------Print Here
    Cell cell(QPoint(0,0), m_printer->width(), 1, m_painter, this);
    cell.setColorBg(Qt::lightGray);
    cell.setColorLine(Qt::transparent);
    cell.setTextFont(QFont("fixed", 16), true);
    cell.setText(QString("Listino di %1 del %2").arg(fornitore, data));

    Row header(m_stretchValues, QPoint(0,cell.getBottom()), m_printer->width(), 1, m_painter, this);
    header.setText(m_viewName);
    header.setTextFont(m_painter->font(), true);

    Row row(m_stretchValues, QPoint(0,header.getBottom()), m_printer->width(), 1, m_painter, this);

    QSqlQuery query;
    if (ui->printAllRb->isChecked())
        query.prepare(sql::SELECT_ARTICOLI_ALL + sql::FILTER_FORNITORE);
    else if (ui->printFromDateRb->isChecked())
        query.prepare(sql::SELECT_ARTICOLI_ALL + sql::FILTER_CURRENT_DATE);
    else if (ui->printFromFatturaRb->isChecked()) {
        query.prepare(sql::SELECT_ARTICOLI_ALL + sql::FILTER_FATTURA);
    }

    query.bindValue(ph::RAG_SOCIALE, ui->fornitoreCb->currentText());
    query.bindValue(ph::DATA_ARRIVO, data);
    query.bindValue(ph::FATTURA, QString("%%1%").arg(ui->fatturaLE->text()));
    query.exec();

    cell.draw();
    header.draw();
    while (query.next()) {
        QStringList x;
        for (auto i : m_colsName)
            x.append(query.record().value(i).toString());
        row.setText(x);
        row.draw();
        row.moveRow({row.getLeft(), row.getBottom()});
    }

    m_painter->end();
}

void ListinoDlg::config()
{
    qDebug() << "ListinoDlg::config()";
    QPrintDialog dlg(m_printer, this);
    if (dlg.exec() == dlg.Accepted)
        draw();
}
