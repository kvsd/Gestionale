#ifndef CONFIGPRINTDIALOG_H
#define CONFIGPRINTDIALOG_H

#include "moduleMagazzino/magazzino_const.h"
#include "report_const.h"
#include "libs/utils.h"

#include <QDialog>
#include <QSettings>
#include <QDebug>
#include <QSqlQueryModel>
#include <QStringListModel>
#include <QLineEdit>
#include <QTableWidget>
#include <QFontComboBox>
#include <QSpinBox>

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

    enum CPDCOLS{DESCR, STRETCH, VIEW, ALIGN};

private:
    Ui::ConfigPrintDialog *ui;
    QSettings m_settings;
    QSqlQueryModel *m_model;
    QMap <int, QString> m_headerMap;
    QStringListModel *m_colsModel;

    void initModel();
    void loadTableSettings(QTableWidget *table, QString settingsName);
    void loadFont(QFontComboBox *box, QSpinBox *spin, QString setting_key);
    void loadSettings();
    void addRow(QTableWidget *table);
    void removeRow(QTableWidget *table);
    void setRow(QTableWidget *table, int row, QStringList values);
    void saveTableSettings(QTableWidget *table, QString settingsName);
    void saveFont(QFontComboBox *box, QSpinBox *spin, QString setting_key);

private slots:
    void addColumn();
    void removeColumn();
    void save();
};

#endif // CONFIGPRINTDIALOG_H
