#include "custominsertdialog.h"

CustomInsertDialog::CustomInsertDialog(QWidget *parent)
    :QDialog(parent)
{
    qDebug() << "CustomInsertDialog()";

}

void CustomInsertDialog::clearForm()
{
    qDebug() << "CustomInsertDialog::clearForm()";
    auto lineEditList = findChildren<QLineEdit *>();
    for (auto *le : lineEditList) {
        le->clear();
        le->setStyleSheet("");
    }

    auto comboBoxList = findChildren<QComboBox *>();
    for (auto *cb : comboBoxList) {
        if (cb->objectName() == "regFiscaleCB")
            continue;
        cb->setCurrentIndex(0);
        cb->setStyleSheet(""); //BUG
    }

}

void CustomInsertDialog::save()
{
    qDebug() << "CustomInsertDialog::save()";
}
