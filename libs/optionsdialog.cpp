#include "optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
{

}

void OptionsDialog::populateList(QListWidget *list, QSqlQueryModel *model)
{
    qDebug() << objectName() + "::populateList() *";
    auto modelNameCols = prepareMapsFromModel(model);
    for (auto i = modelNameCols.begin(); i!=modelNameCols.end(); i++) {
        list->insertItem(i.key(), i.value());
        QListWidgetItem *col = list->item(i.key());
        col->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        col->setCheckState(Qt::Checked);
    }
}

void OptionsDialog::saveVisibility(QListWidget *list, QString groupSettings)
{
    qDebug() << objectName() + "::saveVisibility() *";
    settings.beginGroup(groupSettings);
    for (int i=0; i<list->count(); i++) {
        QListWidgetItem *col = list->item(i);
        int checkState = (col->checkState()==Qt::Checked) ? 1 : 0;
        settings.setValue(QString().setNum(i), checkState);
    }
    settings.endGroup();
}

void OptionsDialog::saveBgColor(QListWidget *list, QString groupSettings)
{
    qDebug() << objectName() + "::saveBgColor() *";
    settings.beginGroup(groupSettings);
    for (int i=0; i<list->count(); i++) {
        QListWidgetItem *col = list->item(i);
        QColor color = col->background().color();
        if (color == QColor(Qt::transparent))
            settings.setValue(col->text(), "-1");
        else
            settings.setValue(col->text(), color.name());
    }
    settings.endGroup();
}

void OptionsDialog::loadVisibility(QListWidget *list, QString groupSettings)
{
    qDebug() << objectName() + "::loadVisibility() *";
    settings.beginGroup(groupSettings);
    for (int i=0; i<list->count(); i++) {
        QListWidgetItem *col = list->item(i);
        int status = settings.value(QString().setNum(i), 1).toInt();
        col->setCheckState(status==1 ? Qt::Checked : Qt::Unchecked);
    }
    settings.endGroup();
}

void OptionsDialog::loadBgColor(QListWidget *list, QString groupSettings)
{
    qDebug() << objectName() + "::loadBgColor() *";
    QColor color;
    settings.beginGroup(groupSettings);
    for (int i=0; i<list->count(); i++) {
        QListWidgetItem *col = list->item(i);
        QString colorStr = settings.value(col->text(), "-1").toString();
        if (colorStr == "-1")
            color = QColor(Qt::transparent);
        else
            color.setNamedColor(colorStr);

        col->setBackground(QBrush(color));
    }
    settings.endGroup();
}

void OptionsDialog::restoreListWidget(QListWidget *list)
{
    qDebug() << objectName() + "::restoreListWidget() *";
    for (int i=0; i<list->count(); i++) {
        QListWidgetItem *col = list->item(i);
        col->setCheckState(Qt::Checked);
        col->setBackground(Qt::transparent);
    }
}

void OptionsDialog::setColumnColor(QModelIndex index)
{
    qDebug() << objectName() + "::setColumnColor() *";
    /* Funzione membro richiamata dal segnale itemDoubleClicked di
     * una ListWidget, riconosce quale pulsante del mouse è stato
     * usato per generare il segnale. Con il pulsante sinistro apre
     * un QColorDialog per la selezione del colore, mentre con il
     * destro ripristina il colore trasparente. */

    auto buttons = qApp->mouseButtons();
    QListWidgetItem *col;
    QListWidget *list = qobject_cast<QListWidget *>(sender());
    if (list!=NULL) {
        col = list->item(index.row());
        if (buttons == Qt::RightButton)
            col->setBackgroundColor(Qt::transparent);
        else {
            QColorDialog dlg(this);
            bool ok = dlg.exec();
            if (ok) {
                QColor color = dlg.selectedColor();
                col->setBackgroundColor(color);
            }
        }
        list->clearSelection();
    }
}
