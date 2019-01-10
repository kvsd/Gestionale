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
                        colview::UN_MISURA,
                        colview::PREZZO_UNITARIO,
                        colview::PREZZO_TOTALE,
                        colview::CODICE_IVA,
                        colview::RIF_AMMIN};

    setColumnCount(cols.length());
    setHorizontalHeaderLabels(cols);
    insertRow();
}

void CustomTableWidget::insertRow()
{
    QTableWidget::insertRow(rowCount());
    blockSignals(true);
    if (win == tableType::fattura) {
        for (int col=0; col<columnCount(); col++) {
            int row = rowCount()-1;
            QTableWidgetItem *item = new QTableWidgetItem;
            if (col==int(cols::qt) ||
                col==int(cols::prezzo_u) ||
                col==int(cols::prezzo_t)) {
                item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                if (col==int(cols::prezzo_t))
                    item->setFlags(Qt::ItemIsEnabled);
                setItem(row, col, item);
            }
            else if (col==int(cols::um) || col==int(cols::al_iva)) {
                QComboBox *cb = new QComboBox;
                cb->setProperty("col", col);
                cb->setProperty("row", row);
                QString t = col==int(cols::um) ? table::UNITA_MISURA : table::CODICE_IVA;
                setupComboBox(t, cb, 1);
                setCellWidget(row, col, cb);
                connect(cb, SIGNAL(currentTextChanged(QString)),
                        this, SLOT(cbIdentify(QString)));
            }
            else
                setItem(row, col, item);
        }
    }
    blockSignals(false);
    resizeColumnsToContents();        
    horizontalHeader()->setStretchLastSection(true);
}

QMap<int, QString> CustomTableWidget::getMap(int row)
{
    QMap<int, QString> map;
    if (row > rowCount())
        return map;

    for (int c=0; c<columnCount(); c++) {
        if (c==int(cols::um) || c==int(cols::al_iva)) {
            QComboBox *cb = qobject_cast<QComboBox *>(cellWidget(row, c));
            map[c] = cb->currentText();
            continue;
        }
        map[c] = item(row, c)->text();
    }

    return map;
}

void CustomTableWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab &&
            (currentColumn() == columnCount()-1) &&
            (currentRow() == rowCount()-1))
        insertRow();
    QTableWidget::keyPressEvent(event);
}

void CustomTableWidget::cbIdentify(QString s)
{
    QComboBox *cb = qobject_cast<QComboBox *>(sender());
    int row = cb->property("row").toInt();
    int col = cb->property("col").toInt();
    emit cbTextChanged(row, col, s);
}
