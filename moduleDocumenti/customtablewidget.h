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
#include <QDebug>

class CustomTableWidget : public QTableWidget
{
public:
    enum class tableType {fattura, ddt};
    enum class fattCols {cod_articolo, descr, qt, um, prezzo_u, prezzo_t, al_iva, rif};

    CustomTableWidget(QWidget *parent);
    void initFattura();
    void insertRow();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    tableType win;
};

#endif // CUSTOMTABLEWIDGET_H
