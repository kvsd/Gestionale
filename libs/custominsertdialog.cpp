#include "custominsertdialog.h"

CustomInsertDialog::CustomInsertDialog(QWidget *parent)
    :QDialog(parent),
      m_id("")
{
    qDebug() << "CustomInsertDialog()";

}

void CustomInsertDialog::setValueLineEdit(const QSqlQuery &query, bool blockSignals)
{
    /* Compila tutte le QLineEdit che hanno la proprieta' m_property che
    ** corrisponde a una colonna della query passata come argomento.
    ** E' possibile bloccare i segnali delle QLineEdit specificando
    ** l'argomento blockSignals(default true) */
    qDebug() << objectName() + "::setValueLineEdit() *";

    for (auto *le : findChildren<QLineEdit *>()) {
        if (blockSignals)
            le->blockSignals(true);
        QString colName = le->property(m_property).toString();
        if (colName.isEmpty())
            continue;
        QString value = query.value(colName).toString();
        le->setText(value);
        if (blockSignals)
            le->blockSignals(false);
    }
}

void CustomInsertDialog::setValueComboBox(const QSqlQuery &query, bool blockSignals)
{
    /* Imposta tutti i QComboBox che hanno la proprieta' m_property che
    ** corrisponde a una colonna della query passata come argomento.
    ** E' possibile bloccare i segnali dei QComboBox
    ** specificando l'argomento blockSignals(default true) */
    qDebug() << objectName() + "::setValueComboBox() *";

    for (auto *cb : findChildren<QComboBox *>()) {
        if (blockSignals)
            cb->blockSignals(true);
        QString colName = cb->property(m_property).toString();
        if (colName.isEmpty())
            continue;
        QString value = query.value(colName).toString();
        setValueCB(cb, value, int(modelCols::id));
        if (blockSignals)
            cb->blockSignals(false);
    }
}

void CustomInsertDialog::setValueRadioBtn(const QSqlQuery &query, bool blockSignals)
{
    /* Imposta tutti i QRadioButton che hanno la proprieta' m_property che
    ** corrisponde a una colonna della query passata come argomento.
    ** E' possibile bloccare i segnali dei QRadioButton
    ** specificando l'argomento blockSignals(default true) */
    qDebug() << objectName() + "::setValueRadioBtn() *";

    for (auto *rb : findChildren<QRadioButton *>()) {
        if (blockSignals)
            rb->blockSignals(true);
        QString colName = rb->property(m_property).toString();
        bool value = query.value(colName).toBool();
        if (value)
            rb->click();
        if (blockSignals)
            rb->blockSignals(false);
    }
}

void CustomInsertDialog::setValueTextEdit(const QSqlQuery &query, bool blockSignals)
{
    /* Compila tutte le QTextEdit che hanno la proprieta' m_property che
    ** corrisponde a una colonna della query passata come argomento.
    ** E' possibile bloccare i segnali delle QTextEdit specificando
    ** l'argomento blockSignals(default true) */
    qDebug() << objectName() + "::setValueTextEdit() *";

    for (auto *te : findChildren<QTextEdit *>()) {
        if (blockSignals)
            te->blockSignals(true);
        QString colName = te->property(m_property).toString();
        if (colName.isEmpty())
            continue;
        QString value = query.value(colName).toString();
        te->setText(value);
        if (blockSignals)
            te->blockSignals(false);
    }
}

void CustomInsertDialog::prepareMap(QMap<QString, QString> &map, int colId)
{
    qDebug() << objectName() + "::prepareMap() *";
    //QLineEdit
    for (auto *le : findChildren<QLineEdit *>()) {
        QString colName = le->property(m_property).toString();
        if (colName.isEmpty())
            continue;
        QString value = le->text();
        map[':'+colName] = value;
    }

    //QComboBox
    for (auto *cb : findChildren<QComboBox *>()) {
        QString colName = cb->property(m_property).toString();
        if (colName.isEmpty())
            continue;
        int oldCol = cb->modelColumn();
        cb->setModelColumn(colId);
        QString value = cb->currentText();
        map[':'+colName] = value;
        cb->setModelColumn(oldCol);
    }

    //QTextEdit
    for (auto *te : findChildren<QTextEdit *>()) {
        QString colName = te->property(m_property).toString();
        if (colName.isEmpty())
            continue;
        QString value = te->toPlainText();
        map[':'+colName] = value;
    }

    //QDateEdit
    for (auto *dtle : findChildren<QDateEdit *>()) {
        QString colName = dtle->property(m_property).toString();
        if (colName.isEmpty())
            continue;
        QString value = dtle->date().toString(DATA_FORMAT);
        map[':'+colName] = value;
    }

    //QRadioButton
    for (auto *rb : findChildren<QRadioButton *>()) {
        QString colName = rb->property(m_property).toString();
        map[':'+colName] = rb->isChecked() ? "y" : "n";
    }
}

bool CustomInsertDialog::checkLineEdit(QLineEdit *le, QString nomeCampo)
{
    qDebug() << objectName() + "::checkLineEdit() *";
    if (le->text().isEmpty()) {
        showDialogError(this, ERR034, MSG031.arg(nomeCampo)); //NOTE codice errore 034
        le->setStyleSheet(css::warning);
        return false;
    }
    return true;
}

bool CustomInsertDialog::checkComboBox(QComboBox *cb, QString nomeCampo)
{
    qDebug() << objectName() + "::checkComboBox()";
    if (cb->currentIndex() == 0) {
        showDialogError(this, ERR035, MSG032.arg(nomeCampo)); //NOTE codice errore 035
        //cb->setStyleSheet(css::warning_cb); BUG IRRISOLTO
        return false;
    }
    return true;
}

void CustomInsertDialog::clearForm()
{
    qDebug() << objectName() + "::clearForm()*";
    //QLineEdit
    for (auto *le : findChildren<QLineEdit *>()) {
        le->clear();
        le->setStyleSheet("");
    }

    //QComboBox
    for (auto *cb : findChildren<QComboBox *>()) {
        cb->setCurrentIndex(0);
        //cb->setStyleSheet(""); BUG IRRISOLTO
    }

    //QTextEdit
    for (auto *te : findChildren<QTextEdit *>()) {
        te->clear();
    }
}
