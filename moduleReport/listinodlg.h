#ifndef LISTINODLG_H
#define LISTINODLG_H

#include <QDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QPainter>
#include <QMargins>
#include <QSettings>
#include <QDebug>

#include "report_const.h"
#include "moduleMagazzino/magazzino_const.h"
#include "libs/gestionale_const.h"
#include "row.h"

namespace Ui {
class ListinoDlg;
}

class ListinoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ListinoDlg(QWidget *parent = 0);
    ~ListinoDlg();

protected:
    QPrinter *m_printer;
    QPainter *m_painter;
    QSqlQueryModel *m_modelFornitori;

private:
    Ui::ListinoDlg *ui;
    QStringList m_colsName;        // contiene i nomi delle colonne db
    QVector<int> m_stretchValues;  // il fattore di larghezza delle colonne
    QStringList m_viewName;        // nomi delle colonne da visualizzare nella stampa
    QSettings m_settings;

    void getColsLayout();
    void initFornitoreCb();
    void nextPage();

private slots:
    void draw();
    void config();
};

#endif // LISTINODLG_H
