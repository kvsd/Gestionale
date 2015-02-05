#include "custommodel.h"

CustomModel::CustomModel(QString colsGroup, QObject *parent) :
    QSqlQueryModel(parent)
{
    group = colsGroup;
    prepareMap();
    loadSettings();
    leftAlign = Qt::AlignLeft+Qt::AlignVCenter;
    rightAlign = Qt::AlignRight+Qt::AlignVCenter;
}

QVariant CustomModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);

    if (role == Qt::TextAlignmentRole) {
        QString headerName = headerData(item.column(), Qt::Horizontal).toString();
        return alignMaps.value(headerName, rightAlign);
    }

    if (role == Qt::BackgroundRole) {
        return colorsMaps.value(item.column(), Qt::transparent);
    }

    return value;
}

void CustomModel::prepareMap(void)
{
    const int MAX_COLUMNS = 30;
    for (int i=0; i<=MAX_COLUMNS; i++) {
        colorsMaps[i] = QBrush(Qt::transparent);
    }
    //Campi che hanno l'allineamento del testo a sinistra
    alignMaps["Descrizione"] = leftAlign;
    alignMaps["Note"] = leftAlign;
    alignMaps["Ragione sociale"] = leftAlign;
}

void CustomModel::loadSettings(void)
{
    settings.beginGroup(group);
    int lenght = settings.allKeys().length();
    for (int i=0; i<lenght; i++) {
        QString value = settings.value(QVariant(i).toString(), "-1").toString();
        if (value == "-1")
            colorsMaps[i] = QBrush(Qt::transparent);
        else
            colorsMaps[i] = QBrush(QColor(value));
    }
    settings.endGroup();
}
