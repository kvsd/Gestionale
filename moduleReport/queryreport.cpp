#include "queryreport.h"

QueryReport::QueryReport(QPrinter *printer, QPainter *painter, QObject *parent)
    : QObject(parent),
      m_printer(printer),
      m_painter(painter),
      m_querySize(-1),
      m_current_page(1),
      m_titleBgColor(Qt::transparent),
      m_titleFgColor(Qt::black),
      m_headerBgColor(Qt::transparent),
      m_headerFgColor(Qt::black),
      m_rowBgColor(Qt::transparent),
      m_rowFgColor(Qt::black),
      m_origin(QPointF(0,0)),
      m_width(m_printer->width()),
      m_isNewPage(false),
      m_titleRow(0),
      m_headerRow(0),
      m_dataRow(0)
{
    qDebug() << "QueryReport::QueryReport()";
}

QueryReport::~QueryReport()
{
    qDebug() << "QueryReport::~QueryReport()";
}

void QueryReport::nextPage()
{
    qDebug() << "ListinoDlg::nextPage()";
    m_printer->newPage();
    m_current_page++;
    m_titleRow->at(1)->setText(QString("Pag.%1").arg(m_current_page));
    m_dataRow->moveRow(0,0);
    m_bottom = m_dataRow->getTop();
    m_isNewPage = true;
}

void QueryReport::configPage()
{
    qDebug() << "Query::configTitle()";
    //Configuro il titolo del report
    m_titleRow = new Row({5,1}, m_origin, m_width, 1, m_painter, this);
    m_titleRow->setBgColor(m_titleBgColor);
    m_titleRow->setFgColor(m_titleFgColor);
    m_titleRow->setLineColor(m_titleBgColor);
    m_titleRow->setTextFont(m_titleFont, true);
    m_titleRow->setText({m_titleStr, QString("(Pag.%1)").arg(m_current_page)});
    m_titleRow->setTextAlignment({Qt::AlignLeft, Qt::AlignRight});

    //Configuro l'header della tabella
    m_headerRow = new Row(m_stretchValues, QPoint(m_origin.x(),m_titleRow->getBottom()), m_width, 1, m_painter, this);
    if (m_headerNames.isEmpty())
        m_headerNames = m_queryCols;
    m_headerRow->setText(m_headerNames);
    m_headerRow->setBgColor(m_headerBgColor);
    m_headerRow->setFgColor(m_headerFgColor);
    m_headerRow->setTextFont(m_headerFont, true);
    m_headerRow->setTextAlignment(QVector<Qt::Alignment>(m_headerNames.count(), Qt::AlignHCenter));

    //Configuro la riga che stampera i risultati
    m_dataRow = new Row(m_stretchValues, QPoint(m_origin.x(),m_headerRow->getBottom()), m_width, 1, m_painter, this);
    m_dataRow->setTextAlignment(m_alignCols);
    m_dataRow->setBgColor(m_rowBgColor);
    m_dataRow->setFgColor(m_rowFgColor);
    m_dataRow->setTextFont(m_rowFont, false);
}

void QueryReport::draw()
{
    qDebug() << "QueryReport::draw()";
    configPage();
    QSqlQuery query;
    if (!query.exec(m_query))
        qDebug() << query.lastError().text();
    m_querySize = query.size();
    m_titleRow->draw();
    m_headerRow->draw();
    while (query.next()) {
        if(m_isNewPage) {
            m_isNewPage = false;
            m_titleRow->draw();
            m_headerRow->draw();
            m_dataRow->moveRow(m_headerRow->getLeft(), m_headerRow->getBottom());
        }
        QStringList values;
        for (QString &col : m_queryCols)
            values << query.value(col).toString();
        m_dataRow->setText(values);
        m_dataRow->draw();
        m_bottom = m_dataRow->getBottom();
        m_dataRow->moveRow(m_dataRow->getLeft(), m_dataRow->getBottom());
        if (m_dataRow->getBottom() > m_printer->height())
            nextPage();
    }
}
