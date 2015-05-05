#include "custommodel.h"

CustomModel::CustomModel(QString colsGroup, Qt::AlignmentFlag textAlignment, QObject *parent) :
    QSqlQueryModel(parent)
{
    group = colsGroup;
    defaulTextAlign = textAlignment;
    prepareMap();
    loadSettings();
}

QVariant CustomModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);

    if (role == Qt::TextAlignmentRole) {
        QString headerName = headerData(item.column(), Qt::Horizontal).toString();
        return alignMaps.value(headerName, defaulTextAlign) + Qt::AlignVCenter;
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

void CustomModel::setAlignMap(QMap<QString, Qt::AlignmentFlag> map)
{
    alignMaps = map;
}
