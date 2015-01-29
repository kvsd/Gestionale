#include "simpledialogs.h"

QString allDlg(QWidget *parent, QSqlTableModel *model, QString strquery, const char *title, QString error_nr)
{
    qDebug() << "allDlg()";
    bool ok;
    QString value = QInputDialog::getText(parent, QString::fromUtf8(title), QString("<b>Aggiungi un nuovo valore:</b>"), QLineEdit::Normal,"",&ok);
    if (ok && !value.isEmpty()) {
        QSqlQuery query;
        query.prepare(strquery);
        query.bindValue(":value", value);
        if (!query.exec()) {
            showDialogError(parent, error_nr, MSG015, query.lastError().text());
        }
        model->select();
        return value;
    }
    return "";
}
