#include "error.h"

void showDialogError(QWidget *parent, QString title, QString informative, QString details)
{
    qDebug() << "showDialogError()";
    QMessageBox dlg(parent);
    dlg.setIcon(QMessageBox::Critical);
    dlg.setWindowTitle("Errore");
    dlg.setText(title);

    if (informative != "")
        dlg.setInformativeText(informative);
    if (details != "")
        dlg.setDetailedText(details);

    dlg.exec();
}

bool showDialogWarning(QWidget *parent, QString title, QString informative, QString details)
{
    qDebug() << "showDialogWarning()";
    QMessageBox dlg(parent);
    dlg.setIcon(QMessageBox::Warning);
    dlg.setWindowTitle("Avviso");
    dlg.setText(title);
    QAbstractButton *yesbtn = dlg.addButton("Si", QMessageBox::YesRole);
    QAbstractButton *nobtn = dlg.addButton("No", QMessageBox::NoRole);

    if (informative != "")
        dlg.setInformativeText(informative);
    if (details != "")
        dlg.setDetailedText(details);

    dlg.exec();
    if (dlg.clickedButton() == yesbtn) {
        return true;
    }
    else if (dlg.clickedButton() == nobtn) {
        return false;
    }

    return false;
}

void showDialogInfo(QWidget *parent, QString title, QString informative)
{
    qDebug() << "showDialogInfo()";
    QMessageBox dlg(parent);
    dlg.setIcon(QMessageBox::Information);
    dlg.setWindowTitle(title);
    dlg.setText(informative);
    dlg.exec();
}
