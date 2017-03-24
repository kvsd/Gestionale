#include "custommodel.h"

CustomModel::CustomModel(QObject *parent)
    : QSqlQueryModel(parent),
      defaultAlign(Qt::AlignLeft),
      defaultBgColor(Qt::transparent),
      defaultFgColor(Qt::black)
{
}

CustomModel::CustomModel(Qt::AlignmentFlag textAlignment, QObject *parent)
    : QSqlQueryModel(parent),
      defaultAlign(textAlignment),
      defaultBgColor(Qt::transparent),
      defaultFgColor(Qt::black)
{
}

QVariant CustomModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    QString headerName = headerData(item.column(), Qt::Horizontal).toString();

    if (role == Qt::TextAlignmentRole)
        return alignMap.value(headerName, defaultAlign) + Qt::AlignVCenter;

    if (role == Qt::BackgroundRole && item.row()%2==1)
        return bgColorsMap.value(headerName, defaultBgColor);

    if (role == Qt::BackgroundRole && item.row()%2==0) {
        QBrush brush = bgColorsMap.value(headerName, defaultBgColor);
        return QBrush(brush.color().lighter(115));;
    }

    if (role == Qt::ForegroundRole)
        return fgColorsMap.value(headerName, defaultFgColor);

    return value;
}

void CustomModel::setBgMap(const QMap<QString, QBrush> &map) {
    bgColorsMap = map;
}

void CustomModel::setAlignMap(const QMap<QString, Qt::AlignmentFlag> &map)
{
    alignMap = map;
}

void CustomModel::setFgMap(const QMap<QString, QBrush> &map)
{
    fgColorsMap = map;
}

void CustomModel::setDefaultAlignment(Qt::AlignmentFlag flag)
{
    defaultAlign = flag;
}

void CustomModel::setDefaultFgColor(QBrush brush)
{
    defaultFgColor = brush;
}

void CustomModel::setDefaultBgColor(QBrush brush)
{
    defaultBgColor = brush;
}
