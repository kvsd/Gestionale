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
    QMap<QString, QString> getRowMap(int row);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    tableType m_win;
    QStringList m_ph; //placeholder

private slots:
    void cbIdentify(QString s);

public slots:
    void insertRow();
    void removeRow();

signals:
    void cbTextChanged(int row, int col, QString str);
    void insertedRow();
    void removedRow();
};

#endif // CUSTOMTABLEWIDGET_H
