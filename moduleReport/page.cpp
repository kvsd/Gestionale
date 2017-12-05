#include "page.h"

Page::Page(QObject *parent) : QObject(parent),
  m_currentPage(1)
{
    m_printer = new QPrinter(QPrinter::HighResolution);
    QPrintDialog dlg(m_printer, qobject_cast<QWidget *>(parent));
    dlg.exec();
    m_painter = new QPainter(m_printer);
}

Page::~Page()
{
    m_painter->end();
    delete m_printer;
    delete m_painter;
}

void Page::draw()
{
    qDebug() << "Page::draw() -> row testing";
    QVector<int> v{1,3,1,1};
    Row *row = new Row(v, {0,0}, width(), 1, m_painter, this);
    row->setText({"prova", "prova", "prova", "prova", "prova"});
    row->draw();
}

//void Page::draw()
//{
//    qDebug() << "Page::draw() -> Cell testing";
//    Cell *cell = new Cell(QPoint(0,0), width(), 1, m_painter, this);
//    cell->setText("ciao mondo");
//    cell->draw();
//    cell->moveCell(0, cell->getBottom());
//    cell->setRowHeight(3);
//    cell->setWidth(width()/2);
//    cell->draw();
//    //---------------------------------------------
//    QPoint p(cell->getRight(), cell->getBottom());
//    cell->moveCell(p);
//    cell->setRowHeight(2);
//    cell->setColorHeader(Qt::magenta);
//    cell->setColorBg(Qt::blue);
//    cell->setColorLine(Qt::red);
//    cell->setColorText(Qt::yellow);
//    cell->setHeader("header:");
//    cell->setHeaderFont(QFont("comics", 16), true);
//    cell->setText("nuovo testo\nlinea2");
//    cell->setTextAlignment(Qt::AlignRight);
//    cell->draw();
//    //---------------------------------------------
//    cell->moveCell(0, cell->getBottom());
//    cell->setRowHeight(3);
//    cell->setColorBg(Qt::darkGray);
//    cell->setColorHeader(Qt::white);
//    cell->setHeaderFont(QFont("comics", 10), true);
//    cell->setTextFont(QFont("helvetica", 14));
//    cell->setTextAlignment(Qt::AlignHCenter);
//    cell->draw();
//    //-----------------------------------------------

//    cell->setRowHeight(5);
//    cell->setWidth(cell->getHeight());
//    cell->moveCell(width()/2-cell->getWidth()/2, height()/2);
//    float left = cell->getLeft();
//    float right = cell->getRight();
//    float top = cell->getTop();
//    float bottom = cell->getBottom();
//    cell->draw();

//    cell->moveCell(left, top-cell->getHeight());
//    cell->setColorBg(Qt::darkBlue);
//    cell->draw();

//    cell->moveCell(left, bottom);
//    cell->setColorBg(Qt::darkCyan);
//    cell->draw();

//    cell->moveCell(left-cell->getWidth(), top);
//    cell->setColorBg(Qt::darkGreen);
//    cell->draw();

//    cell->moveCell(right, top);
//    cell->setColorBg(Qt::darkRed);
//    cell->draw();
//}
