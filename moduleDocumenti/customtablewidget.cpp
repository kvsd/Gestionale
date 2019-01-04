#include "customtablewidget.h"

CustomTableWidget::CustomTableWidget(QWidget *parent)
    :QTableWidget(parent)
{
    qDebug() << "CustomTableWidget()";
    setAlternatingRowColors(true);
}

void CustomTableWidget::initFattura()
{
    qDebug() << "CustomTableWidget::initFattura()";
    win = tableType::fattura;
    QStringList cols = {colview::CODICE_ARTICOLO,
                        colview::DESCRIZIONE,
                        colview::QUANTITA,
                        "unita misura",
                        "Prezzo unitario",
                        "Prezzo totale",
                        "Aliquota IVA",
                        "Riferimento Amm."};

    setColumnCount(cols.length());
    setHorizontalHeaderLabels(cols);
    insertRow();
}

void CustomTableWidget::insertRow()
{
    QTableWidget::insertRow(rowCount());
    if (win == tableType::fattura) {
        for (int c=0; c<columnCount(); c++) {
            int r = rowCount()-1;
            QTableWidgetItem *item = new QTableWidgetItem;
            if (c==int(fattCols::qt) ||
                c==int(fattCols::prezzo_u) ||
                c==int(fattCols::prezzo_t)) {
                item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                setItem(r, c, item);
            }
            else if (c==int(fattCols::um) || c==int(fattCols::al_iva)) {
                QComboBox *cb = new QComboBox;
                cb->setProperty("col", c);
                cb->setProperty("row", r);
                QString t = c==int(fattCols::um) ? table::UNITA_MISURA : table::CODICE_IVA;
                setupComboBox(t, cb, 1);
                setCellWidget(r, c, cb);
            }
            else
                setItem(r, c, item);
        }
    }
    resizeColumnsToContents();        
    horizontalHeader()->setStretchLastSection(true);
}

void CustomTableWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab &&
            (currentColumn() == columnCount()-1) &&
            (currentRow() == rowCount()-1))
        insertRow();
    QTableWidget::keyPressEvent(event);
}
