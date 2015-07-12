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
    QString headerName = headerData(item.column(), Qt::Horizontal).toString();

    if (role == Qt::TextAlignmentRole)
        return alignMaps.value(headerName, defaulTextAlign) + Qt::AlignVCenter;

    if (role == Qt::BackgroundRole)
        return bgColorsMaps.value(item.column(), Qt::transparent);

    if (role == Qt::ForegroundRole)
        return fgColorsMaps.value(headerName, Qt::black);

    return value;
}

void CustomModel::prepareMap(void)
{
    const int MAX_COLUMNS = 30;
    for (int i=0; i<=MAX_COLUMNS; i++) {
        bgColorsMaps[i] = QBrush(Qt::transparent);
    }
}

void CustomModel::loadSettings(void)
{
    settings.beginGroup(group);
    int lenght = settings.allKeys().length();
    for (int i=0; i<lenght; i++) {
        QString value = settings.value(QVariant(i).toString(), "-1").toString();
        if (value == "-1")
            bgColorsMaps[i] = QBrush(Qt::transparent);
        else
            bgColorsMaps[i] = QBrush(QColor(value));
    }
    settings.endGroup();
}

void CustomModel::setAlignMap(const QMap<QString, Qt::AlignmentFlag> &map)
{
    alignMaps = map;
}

void CustomModel::setForegroundMap(const QMap<QString, QBrush> &map)
{
    fgColorsMaps = map;
}
