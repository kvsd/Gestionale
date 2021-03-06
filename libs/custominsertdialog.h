#ifndef CUSTOMINSERTDIALOG_H
#define CUSTOMINSERTDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSqlTableModel>
#include <QMap>
#include <QDebug>
#include <QTextEdit>
#include <QDateEdit>
#include <QRadioButton>
#include <QSqlQuery>

#include "libs/error.h"
#include "gestionale_const.h"
#include "libs/simpledialogs.h"
#include "libs/utils.h"

class CustomInsertDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomInsertDialog(QWidget *parent = nullptr);
    QString getId(void){return m_id;}

protected:
    const char *m_property = "coldb";

    virtual void initForm(void) = 0;
    virtual void initComboBox(void) = 0;
    virtual void setValue(QString id="0") = 0;
    void setValueLineEdit(const QSqlQuery &query, bool blockSignals=true);
    void setValueComboBox(const QSqlQuery &query, bool blockSignals=true);
    void setValueRadioBtn(const QSqlQuery &query, bool blockSignals=true);
    void setValueTextEdit(const QSqlQuery &query, bool blockSignals=true);
    void setId(QString id){m_id=id;}
    void prepareMap(QMap<QString, QString> &map, int colId=0);
    //QSqlTableModel * setupComboBox(QString tablename, QComboBox *cb, int viewCol=0);
    //void setValueCB(QComboBox *box, QString value, int searchCol);
    bool checkLineEdit(QLineEdit *le, QString nomeCampo="");
    bool checkComboBox(QComboBox *cb, QString nomeCampo="");

private:
    QString m_id;

protected slots:
    void clearForm(void);
    virtual void save() = 0;
};

#endif // CUSTOMINSERTDIALOG_H
