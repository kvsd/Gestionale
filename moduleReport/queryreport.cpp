#include "queryreport.h"

QueryReport::QueryReport(QPrinter *printer, QPainter *painter, QObject *parent)
    : QObject(parent),
      m_printer(printer),
      m_painter(painter),
      m_current_page(1)
{
    qDebug() << "QueryReport::QueryReport()";
}

QueryReport::~QueryReport()
{
    qDebug() << "QueryReport::~QueryReport()";
    delete m_titleRow;
    delete m_displayPage;
    delete m_headerRow;
    delete m_dataRow;
}

void QueryReport::nextPage()
{
    qDebug() << "ListinoDlg::nextPage()";
    m_printer->newPage();
    m_current_page++;
    m_titleRow->draw();
    m_displayPage->setText(QString("Pag.%1").arg(m_current_page));
    m_displayPage->draw();
    m_headerRow->draw();
    m_dataRow->moveRow(m_headerRow->getLeft(), m_headerRow->getBottom());
}

void QueryReport::configPage()
{
    qDebug() << "Query::configTitle()";
    //Configuro il titolo del report
    m_titleRow = new Row({5,1}, m_origin, m_width, 1, m_painter, this);
    m_titleRow->setColorBg(m_titleColor);
    m_titleRow->setColorLine(m_titleColor);
    m_titleRow->setTextFont(m_titleFont, true);
    m_titleRow->setText({m_titleStr});

    //Configuro la numerazione pagina.
    QPointF t = {m_titleRow->at(1)->getLeft(), m_titleRow->getTop()};
    m_displayPage = new Cell(t, m_titleRow->at(1)->getWidth(), 1, m_painter, this);
    m_displayPage->setTextFont(QFont("fixed", 8));
    m_displayPage->setColorLine(Qt::transparent);
    m_displayPage->setTextAlignment(Qt::AlignRight);
    m_displayPage->setText(QString("(Pag.%1)").arg(m_current_page));

    //Configuro l'header della tabella
    m_headerRow = new Row(m_stretchValues, QPoint(m_origin.x(),m_titleRow->getBottom()), m_width, 1, m_painter, this);
    if (m_headerNames.isEmpty())
        m_headerNames = m_queryCols;
    m_headerRow->setText(m_headerNames);
    m_headerRow->setTextFont(m_painter->font(), true);
    m_headerRow->setTextAlignment(QVector<Qt::Alignment>(m_headerNames.count(), Qt::AlignHCenter));

    //Configuro la riga che stampera i risultati
    m_dataRow = new Row(m_stretchValues, QPoint(m_origin.x(),m_headerRow->getBottom()), m_width, 1, m_painter, this);
    m_dataRow->setTextAlignment(m_alignCols);
}

void QueryReport::draw()
{
    qDebug() << "QueryReport::draw()";
    configPage();
    QSqlQuery query;
    query.exec(m_query);
    m_titleRow->draw();
    m_displayPage->draw();
    m_headerRow->draw();
    while (query.next()) {
        QStringList values;
        for (QString &col : m_queryCols)
            values << query.value(col).toString();
        m_dataRow->setText(values);
        m_dataRow->draw();
        m_dataRow->moveRow(m_dataRow->getLeft(), m_dataRow->getBottom());
        if (m_dataRow->getBottom() > m_printer->height())
            nextPage();
    }
}
