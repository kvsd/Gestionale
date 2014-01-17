#include "custommodel.h"

CustomModel::CustomModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    colors[0] = QColor(Qt::transparent);
    colors[1] = QColor(Qt::transparent);
    colors[2] = QColor(Qt::transparent);
    colors[3] = QColor(Qt::transparent);
    colors[4] = QColor(Qt::transparent);
    colors[5] = QColor(Qt::transparent);
    colors[6] = QColor(Qt::transparent);
    colors[7] = QColor(Qt::transparent);
    colors[8] = QColor(Qt::transparent);
    colors[9] = QColor(Qt::transparent);
    colors[10] = QColor(Qt::transparent);
    colors[11] = QColor(Qt::transparent);
    colors[12] = QColor(Qt::transparent);
    colors[13] = QColor(Qt::transparent);
    colors[14] = QColor(Qt::transparent);
    colors[15] = QColor(Qt::transparent);
    colors[16] = QColor(Qt::transparent);
    colors[17] = QColor(Qt::transparent);
    colors[18] = QColor(Qt::transparent);
    colors[19] = QColor(Qt::transparent);
    colors[20] = QColor(Qt::transparent);
}

QVariant CustomModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);

    if (role == Qt::BackgroundRole) {
        switch(item.column()) {
        case 0:
            return QBrush(colors[0]);
            break;
        case 1:
            return QBrush(colors[1]);
            break;
        case 2:
            return QBrush(colors[2]);
            break;
        case 3:
            return QBrush(colors[3]);
            break;
        case 4:
            return QBrush(colors[4]);
            break;
        case 5:
            return QBrush(colors[5]);
            break;
        case 6:
            return QBrush(colors[6]);
            break;
		case 7:
            return QBrush(colors[7]);
            break;
		case 8:
            return QBrush(colors[8]);
            break;
        case 9:
            return QBrush(colors[9]);
            break;
        case 10:
            return QBrush(colors[10]);
            break;
        case 11:
            return QBrush(colors[11]);
            break;
        case 12:
            return QBrush(colors[12]);
            break;
        case 13:
            return QBrush(colors[13]);
            break;
        case 14:
            return QBrush(colors[14]);
            break;
		case 15:
            return QBrush(colors[15]);
            break;
		case 16:
			return QBrush(colors[16]);
			break;
		case 17:
            return QBrush(colors[17]);
            break;
		case 18:
			return QBrush(colors[18]);
			break;
		case 19:
            return QBrush(colors[19]);
            break;
		case 20:
			return QBrush(colors[20]);
			break;
        default:
            return QBrush(colors[5]);
            break;

        }
    }

    return value;
}
