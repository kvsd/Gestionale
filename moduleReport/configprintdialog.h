#ifndef CONFIGPRINTDIALOG_H
#define CONFIGPRINTDIALOG_H

#include "moduleMagazzino/magazzino_const.h"
#include "report_const.h"
#include "libs/utils.h"

#include <QDialog>
#include <QSettings>
#include <QDebug>
#include <QSqlQueryModel>
#include <QComboBox>
#include <QStringListModel>
#include <QLineEdit>
#include <QTableWidget>

namespace Ui {
class ConfigPrintDialog;
}

class ConfigPrintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigPrintDialog(QWidget *parent = 0);
    ~ConfigPrintDialog();
    void setPage(int page, bool status);

private:
    Ui::ConfigPrintDialog *ui;
    QSettings settings;
    QSqlQueryModel *model;
    QMap <int, QString> headerMap;
    QStringListModel *colsModel;

    void initModel();
    void loadTableSettings(QTableWidget *table, QString settingsName);
    void loadSettings();
    void addRow(QTableWidget *table);
    void removeRow(QTableWidget *table);
    void setRow(QTableWidget *table, int row, QStringList values);
    void saveSettings(QTableWidget *table, QString settingsName);

private slots:
    void addColumn();
    void removeColumn();
    void save();
};

#endif // CONFIGPRINTDIALOG_H
