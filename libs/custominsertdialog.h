#ifndef CUSTOMINSERTDIALOG_H
#define CUSTOMINSERTDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSqlTableModel>
#include <QDebug>

#include "libs/error.h"
#include "gestionale_const.h"

class CustomInsertDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomInsertDialog(QWidget *parent = 0);

protected:
    virtual void initComboBox() = 0;
    QSqlTableModel * setupComboBox(QString tablename, QComboBox *cb, int viewCol=0);
    void setValueCB(QComboBox *box, QString value, int searchCol);
    bool checkLineEdit(QLineEdit *le, QString nomeCampo="");
    bool checkComboBox(QComboBox *cb, QString nomeCampo="");

protected slots:
    void clearForm(void);
    virtual void save() = 0;
};

/*
    void setValue(QString id="0");
    void prepareMap(void);
    bool checkValues(void);

public slots:
    void copyPrtIva(void);
    void openAddCitta(void);
    void openAddCap(void);
    void openAddLogo(void);
*/

#endif // CUSTOMINSERTDIALOG_H
