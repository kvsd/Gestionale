#include "custommodel.h"

CustomModel::CustomModel(QString colsGroup, QObject *parent) :
    QSqlQueryModel(parent)
{
    group = colsGroup;
    prepareMap();
    loadSettings();
}

QVariant CustomModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);

    if (role == Qt::BackgroundRole) {
        switch(item.column()) {
        case 0:
            return colors[0];
            break;
        case 1:
            return colors[1];
            break;
        case 2:
            return colors[2];
            break;
        case 3:
            return colors[3];
            break;
        case 4:
            return colors[4];
            break;
        case 5:
            return colors[5];
            break;
        case 6:
            return colors[6];
            break;
		case 7:
            return colors[7];
            break;
		case 8:
            return colors[8];
            break;
        case 9:
            return colors[9];
            break;
        case 10:
            return colors[10];
            break;
        case 11:
            return colors[11];
            break;
        case 12:
            return colors[12];
            break;
        case 13:
            return colors[13];
            break;
        case 14:
            return colors[14];
            break;
		case 15:
            return colors[15];
            break;
		case 16:
            return colors[16];
			break;
		case 17:
            return colors[17];
            break;
		case 18:
            return colors[18];
			break;
		case 19:
            return colors[19];
            break;
		case 20:
            return colors[20];
			break;
        case 21:
            return colors[21];
            break;
        case 22:
            return colors[22];
            break;
        case 23:
            return colors[23];
            break;
        case 24:
            return colors[24];
            break;
        case 25:
            return colors[25];
            break;
        case 26:
            return colors[26];
            break;
        case 27:
            return colors[27];
            break;
        case 28:
            return colors[28];
            break;
        case 29:
            return colors[29];
            break;
        case 30:
            return colors[30];
            break;
        default:
            return QBrush(Qt::transparent);
            break;

        }
    }

    return value;
}

void CustomModel::prepareMap(void)
{
    for (int i=0; i<=30; i++) {
        colors[i] = QBrush(Qt::transparent);
    }
}

void CustomModel::loadSettings(void)
{
    settings.beginGroup(group);
    int lenght = settings.allKeys().length();
    for (int i=0; i<lenght; i++) {
        QString value = settings.value(QVariant(i).toString(), "-1").toString();
        if (value == "-1")
            colors[i] = QBrush(Qt::transparent);
        else
            colors[i] = QBrush(QColor(value));
    }
    settings.endGroup();
}
