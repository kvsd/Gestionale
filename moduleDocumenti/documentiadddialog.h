#ifndef DOCUMENTIADDDIALOG_H
#define DOCUMENTIADDDIALOG_H

#include "libs/custominsertdialog.h"
#include "libs/utils.h"
#include "libs/simpledialogs.h"
#include "documenti_const.h"
#include "customtablewidget.h"

#include <QSqlQueryModel>
#include <QSqlError>

namespace Ui {
class DocumentiAddDialog;
}

class DocumentiAddDialog : public CustomInsertDialog
{
    Q_OBJECT

public:
    explicit DocumentiAddDialog(QWidget *parent = 0);
    ~DocumentiAddDialog();
    void initFattura();
    void initDdt();

private:
    Ui::DocumentiAddDialog *ui;
    QSqlQueryModel *m_modelCliente;
    QSqlTableModel *m_modelDocumento;
    QSqlTableModel *m_modelMoneta;
    QMap<QString, QString> m_docMap;
    QMap<QString, double> m_ivaMap;


    void initForm();
    void initComboBox();
    void setValue(QString id="0");

protected:
    void closeEvent(QCloseEvent *);
    void reject();

private slots:
    void save();
    void updateCell(int row, int col);
    void updateIvaMap();
};

#endif // DOCUMENTIADDDIALOG_H
