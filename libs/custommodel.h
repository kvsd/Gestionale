#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <QSqlQueryModel>
#include <QMap>
#include <QColor>
#include <QBrush>

class CustomModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit CustomModel(QObject *parent = 0);
    explicit CustomModel(Qt::AlignmentFlag textAlignment, QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;

    void setAlignMap(const QMap <QString, Qt::AlignmentFlag> &map){alignMap = map;}
    void setBgMap(const QMap <QString, QBrush> &map){bgColorsMap = map;}
    void setFgMap(const QMap<QString, QBrush> &map){fgColorsMap = map;}

    void setDefaultAlignment(Qt::AlignmentFlag flag){defaultAlign = flag;}
    void setDefaultFgColor(QBrush brush){defaultFgColor = brush;}
    void setDefaultBgColor(QBrush brush){defaultBgColor = brush;}

    Qt::AlignmentFlag getDefaultAlignment(void) const {return defaultAlign;}
    QBrush getDefaultBgColor(void) const {return defaultBgColor;}
    QBrush getDefaultFgColor(void) const {return defaultFgColor;}

    QMap<QString, QBrush> getBgColorsMap() const {return bgColorsMap;}
    QMap<QString, QBrush> getFgColorsMap() const {return fgColorsMap;}
    QMap<QString, Qt::AlignmentFlag> getAlignMap() const {return alignMap;}

private:
    QMap<QString, QBrush>bgColorsMap;
    QMap<QString, QBrush>fgColorsMap;
    QMap<QString, Qt::AlignmentFlag>alignMap;

    Qt::AlignmentFlag defaultAlign;
    QBrush defaultBgColor;
    QBrush defaultFgColor;

signals:

public slots:

};

#endif // CUSTOMMODEL_H
