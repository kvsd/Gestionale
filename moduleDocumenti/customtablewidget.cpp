#include "customtablewidget.h"

CustomTableWidget::CustomTableWidget(QWidget *parent)
    :QTableWidget(parent)
{
    qDebug() << "CustomTableWidget()";
    setAlternatingRowColors(true);
    setToolTip("<b>Ctrl +</b> Aggiungi riga\n<b>Ctrl -</b> Rimuovi riga");
}

void CustomTableWidget::initFattura()
{
    qDebug() << "CustomTableWidget::initFattura()";
    m_win = tableType::fattura;
    QStringList cols = {colview::CODICE_ARTICOLO,
                        colview::DESCRIZIONE,
                        colview::QUANTITA,
                        colview::UN_MISURA,
                        colview::PREZZO_UNITARIO,
                        colview::PREZZO_TOTALE,
                        colview::CODICE_IVA,
                        colview::RIF_AMMIN};
    m_ph = QStringList({":cod_articolo", ":descr", ":quantita", ":um", ":prezzo_unitario",
            ":prezzo_totale", ":aliquota_iva", ":rif"});
    setColumnCount(cols.length());
    setHorizontalHeaderLabels(cols);
    insertRow();
}

void CustomTableWidget::insertRow()
{
    QTableWidget::insertRow(rowCount());
    blockSignals(true);
    if (m_win == tableType::fattura) {
        insertRowFattura();
    }
    emit insertedRow();
    blockSignals(false);
    resizeColumnsToContents();        
    horizontalHeader()->setStretchLastSection(true);
}

void CustomTableWidget::insertRowFattura()
{
    qDebug() << "CustomTableWidget::insertRowFattura()";
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
            connect(cb, SIGNAL(activated(QString)),
                    this, SLOT(cbIdentify(QString)));
        }
        else
            setItem(row, col, item);
    }
}

void CustomTableWidget::removeRow()
{
    qDebug() << "CustomTableWidget::removeRow()";
    QTableWidget::removeRow(rowCount()-1);
    emit removedRow();
}

QMap<QString, QString> CustomTableWidget::getRowMap(int row)
{
    QMap<QString, QString> map;
    if (row > rowCount())
        return map;

    for (int col=0; col<columnCount(); col++) {
        if (col==int(cols::um) || col==int(cols::al_iva)) {
            QComboBox *cb = qobject_cast<QComboBox *>(cellWidget(row, col));
            map[m_ph[col]] = cb->currentText();
            continue;
        }
        map[m_ph[col]] = item(row, col)->text();
    }

    return map;
}

void CustomTableWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab &&
            (currentColumn() == columnCount()-1) &&
            (currentRow() == rowCount()-1))
        insertRow();
    if (event->key() == Qt::Key_Plus &&
            event->modifiers() == Qt::ControlModifier)
        insertRow();
    if (event->key() == Qt::Key_Minus &&
        event->modifiers() == Qt::ControlModifier) {
        removeRow();
    }

    QTableWidget::keyPressEvent(event);
}

void CustomTableWidget::cbIdentify(QString s)
{
    QComboBox *cb = qobject_cast<QComboBox *>(sender());
    int row = cb->property("row").toInt();
    int col = cb->property("col").toInt();
    emit cbTextChanged(row, col, s);
}
