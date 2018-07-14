#include "custominsertdialog.h"

CustomInsertDialog::CustomInsertDialog(QWidget *parent)
    :QDialog(parent)
{
    qDebug() << "CustomInsertDialog()";

}

void CustomInsertDialog::prepareMap(QMap<QString, QString> &map, int colId)
{
    qDebug() << objectName() + "::prepareMap() *";
    for (auto *le : findChildren<QLineEdit *>()) {
        QString colName = le->property(m_property).toString();
        if (colName.isEmpty())
            continue;
        QString value = le->text();
        map[':'+colName] = value;
    }

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
}

QSqlTableModel * CustomInsertDialog::setupComboBox(QString tablename, QComboBox *cb, int viewCol)
{
    //Inizializza un QSqlTableModel con la tabella tablename e
    //l'assegna al QComboBox cb e ritorna il model.
    qDebug() << objectName() + "::setupComboBox() *";
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(tablename);
    model->setSort(viewCol, Qt::AscendingOrder);
    model->select();
    cb->setModel(model);
    cb->setModelColumn(viewCol);
    return model;
}

void CustomInsertDialog::setValueCB(QComboBox *box, QString value, int searchCol)
{
    //Cerca nel campo ID del QComboBox il valore value e lo
    //imposta come selezione corrente.
    qDebug() << objectName() + "::setValueCB() *";
    int oldCol = box->modelColumn();
    box->setModelColumn(searchCol);
    box->setCurrentText(value);
    box->setModelColumn(oldCol);
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
    auto lineEditList = findChildren<QLineEdit *>();
    for (auto *le : lineEditList) {
        le->clear();
        le->setStyleSheet("");
    }

    auto comboBoxList = findChildren<QComboBox *>();
    for (auto *cb : comboBoxList) {
        cb->setCurrentIndex(0);
        //cb->setStyleSheet(""); BUG IRRISOLTO
    }
}
