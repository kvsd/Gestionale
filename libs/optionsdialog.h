#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QSettings>
#include <QDebug>
#include <QColorDialog>
#include <QSqlQueryModel>
#include <libs/utils.h>

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent);

    void populateList(QListWidget *list, QSqlQueryModel *model);
    void saveVisibility(QListWidget *list, QString groupSettings);
    void saveBgColor(QListWidget *list, QString groupSettings);
    void loadVisibility(QListWidget *list, QString groupSettings);
    void loadBgColor(QListWidget *list, QString groupSettings);
    void restoreListWidget(QListWidget *list);

protected:
    QSettings settings;

private:

protected slots:
    virtual void saveConfig(){}
    void setColumnColor(QModelIndex index);
};

#endif // OPTIONSDIALOG_H
