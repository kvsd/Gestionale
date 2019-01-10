#ifndef CUSTOMTABLEWIDGET_H
#define CUSTOMTABLEWIDGET_H

#include "libs/gestionale_const.h"
#include "libs/utils.h"

#include <QObject>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QComboBox>
#include <QKeyEvent>
#include <QMap>
#include <QDebug>

class CustomTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    enum class tableType {fattura, ddt};
    enum class cols {cod_articolo, descr, qt, um, prezzo_u, prezzo_t, al_iva, rif};

    CustomTableWidget(QWidget *parent);
    void initFattura();
    void insertRow();
    QMap<int,QString> getMap(int row);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    tableType win;

private slots:
    void cbIdentify(QString s);

signals:
    void cbTextChanged(int row, int col, QString str);
};

#endif // CUSTOMTABLEWIDGET_H
