#include "primanotamodel.h"

PrimaNotaModel::PrimaNotaModel(QObject *parent)
    :QSqlQueryModel(parent)
{
    color_positive = QColor("blue");
    color_negative = QColor("red");
}

QVariant PrimaNotaModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    int col = item.column();

    if (role == Qt::TextAlignmentRole) {
        if (col == primanota::COL_DESCR || col == primanota::COL_DATA)
            return Qt::AlignLeft+Qt::AlignVCenter;
        else
            return Qt::AlignRight+Qt::AlignVCenter;
    }

    if (role == Qt::ForegroundRole) {
        if (col == primanota::COL_ENT_BANCA || col == primanota::COL_ENT_CASSA)
            return color_positive;

        if (col == primanota::COL_USC_BANCA || col == primanota::COL_USC_CASSA)
            return color_negative;
    }

    return value;
}

