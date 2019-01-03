#ifndef DOCUMENTIADDDIALOG_H
#define DOCUMENTIADDDIALOG_H

#include "libs/custominsertdialog.h"
#include "libs/utils.h"
#include "libs/simpledialogs.h"
#include "documenti_const.h"

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

private:
    Ui::DocumentiAddDialog *ui;
    QSqlQueryModel *m_modelCliente;
    QSqlTableModel *m_modelDocumento;
    QSqlTableModel *m_modelMoneta;

    void initForm();
    void initComboBox();
    void setValue(QString id="0");

private slots:
    void save();
};

#endif // DOCUMENTIADDDIALOG_H
