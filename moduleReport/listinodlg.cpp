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
    configLayout();
}

ListinoDlg::~ListinoDlg()
{
    qDebug() << "ListinoDlg::~ListinoDlg()";
    delete ui;
    delete m_printer;
}

void ListinoDlg::configLayout()
{
    qDebug() << "ListinoDlg::getColsLayout()";
    m_colsName.clear();
    m_stretchValues.clear();
    m_viewName.clear();
    m_settings.beginGroup(settings::listinoCols);
    for (auto s : m_settings.allKeys()) {
         QStringList value = m_settings.value(s).toStringList();
         m_colsName.append(value.at(CPD::DESCR));
         m_stretchValues.append(value.at(CPD::STRETCH).toInt());
         m_viewName.append(value.at(CPD::VIEW));
         QString a = value.at(CPD::ALIGN);
         if (a == align::left)
             m_align.append(Qt::AlignLeft);
         else if (a == align::right)
             m_align.append(Qt::AlignRight);
         else
             m_align.append(Qt::AlignHCenter);
    }
    m_settings.endGroup();
}

void ListinoDlg::initFornitoreCb()
{
    qDebug() << "ListinoDlg::initFornitoreCb()";
    m_modelFornitori = new QSqlQueryModel(this);
    m_modelFornitori->setQuery(sql::SELECT_FORNITORE);
    ui->fornitoreCb->setModel(m_modelFornitori);
    ui->fornitoreCb->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);
}

void ListinoDlg::nextPage()
{
    qDebug() << "ListinoDlg::nextPage()";
    m_printer->newPage();
    title->draw();
    header->draw();
    row->moveRow(header->getLeft(), header->getBottom());
}

void ListinoDlg::draw()
{
    qDebug() << "ListinoDlg::draw()";
    m_painter = new QPainter(m_printer);
    QString fornitore = ui->fornitoreCb->currentText();
    QString data = QDate::currentDate().toString("dd/MM/yyyy");

    //Configuro l'intestazione del listino
    title = new Cell(QPoint(0,0), m_printer->width(), 1, m_painter, this);
    title->setColorBg(Qt::lightGray);
    title->setColorLine(Qt::transparent);;
    title->setTextFont(QFont("fixed", 16), true);
    title->setText(QString("Listino di %1 del %2").arg(fornitore, data));

    //Configuro l'header della tabella
    header = new Row(m_stretchValues, QPoint(0,title->getBottom()), m_printer->width(), 1, m_painter, this);
    header->setText(m_viewName);
    header->setTextFont(m_painter->font(), true);
    header->setTextAlignment(QVector<Qt::Alignment>(4, Qt::AlignHCenter));

    //Configuro la riga che stampera i risultati
    row = new Row(m_stretchValues, QPoint(0,header->getBottom()), m_printer->width(), 1, m_painter, this);
    row->setTextAlignment(m_align);

    //Selezione e configurazione delle query
    QSqlQuery query;
    if (ui->printAllRb->isChecked())
        query.prepare(sql::SELECT_ARTICOLI_ALL + sql::FILTER_FORNITORE);
    else if (ui->printFromDateRb->isChecked())
        query.prepare(sql::SELECT_ARTICOLI_ALL + sql::FILTER_CURRENT_DATE);
    else if (ui->printFromFatturaRb->isChecked())
        query.prepare(sql::SELECT_ARTICOLI_ALL + sql::FILTER_FATTURA);

    query.bindValue(ph::RAG_SOCIALE, fornitore);
    query.bindValue(ph::DATA_ARRIVO, data);
    query.bindValue(ph::FATTURA, QString("%%1%").arg(ui->fatturaLE->text()));
    query.exec();

    //Inizio stampa
    title->draw();
    header->draw();
    while (query.next()) {
        QStringList list;
        for (auto i : m_colsName)
            list.append(query.record().value(i).toString());
        row->setText(list);
        row->draw();
        row->moveRow(row->getLeft(), row->getBottom());
        if (row->getBottom() > m_printer->height())
            nextPage();
    }

    delete m_painter;
}

void ListinoDlg::config()
{
    qDebug() << "ListinoDlg::config()";
    QPrintDialog dlg(m_printer, this);
    if (dlg.exec() == dlg.Accepted)
        draw();
}
