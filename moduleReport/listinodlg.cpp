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
    getColsLayout();
}

ListinoDlg::~ListinoDlg()
{
    qDebug() << "ListinoDlg::~ListinoDlg()";
    delete ui;
    delete m_printer;
}

void ListinoDlg::getColsLayout()
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

    //----------------Print Here
    QSqlQuery query;
    query.prepare(magazzino::SELECT_ARTICOLI_ALL + "AND rag_sociale=:rag_sociale");
    query.bindValue(":rag_sociale", ui->fornitoreCb->currentText());
    query.exec();
    while (query.next()) {
        QStringList x;
        for (auto i : m_colsName)
            x.append(query.record().value(i).toString());
        qDebug() << x.join(" | ");
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