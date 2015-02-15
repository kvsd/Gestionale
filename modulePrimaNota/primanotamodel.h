#ifndef PRIMANOTAMODEL_H
#define PRIMANOTAMODEL_H

#include <QSqlQueryModel>
#include <QColor>

#include "primanota_const.h"

class PrimaNotaModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit PrimaNotaModel(QObject *parent=0);
    QVariant data(const QModelIndex &item, int role) const;

private:
    QColor color_positive;
    QColor color_negative;
};

#endif // PRIMANOTAMODEL_H
