#ifndef LISTINODLG_H
#define LISTINODLG_H

#include <QDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPainter>
#include <QMargins>
#include <QSettings>
#include <QDebug>
#include <QDate>

#include "report_const.h"
#include "libs/gestionale_const.h"
#include "libs/error.h"
#include "queryreport.h"
#include "configprintdialog.h"

namespace Ui {
class ListinoDlg;
}

class ListinoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ListinoDlg(QWidget *parent = 0);
    ~ListinoDlg();
    enum CBCOLS {ID, DESCR};

protected:

private:
    Ui::ListinoDlg *ui;
    QPrinter *m_printer;
    QPainter *m_painter;
    QSqlQueryModel *m_modelFornitori;
    QStringList m_colsName;        // contiene i nomi delle colonne db.
    QVector<int> m_stretchValues;  // il fattore di larghezza delle colonne.
    QStringList m_viewName;        // nomi delle colonne da visualizzare nella stampa.
    QVector<Qt::Alignment> m_align;// contiene gli allineamenti delle colonne.
    QSettings m_settings;
    QFont listinoFont;

    void initFornitoreCb();
    void configLayout();
    void configPage(QString str);
    QString configQuery(QString fornitore);

private slots:
    void draw();
    void config();
};

#endif // LISTINODLG_H
