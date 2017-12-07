#include "listinodlg.h"
#include "ui_listinodlg.h"

ListinoDlg::ListinoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListinoDlg)
{
    qDebug() << "ListinoDlg::ListinoDlg()";
    ui->setupUi(this);
    m_printer = new QPrinter(QPrinter::HighResolution);
    //QMargins margin(3.5, 3.5, 3.5, 3.5);
    //m_printer->setPageMargins(margin);
    m_printer->setOutputFileName("./listino.pdf");
    initFornitoreCb();
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

    m_painter->end();
}

void ListinoDlg::config()
{
    qDebug() << "ListinoDlg::config()";
    QPrintDialog dlg(m_printer, this);
    if (dlg.exec() == dlg.Accepted)
        draw();
}
