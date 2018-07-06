#ifndef CUSTOMINSERTDIALOG_H
#define CUSTOMINSERTDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSqlTableModel>
#include <QDebug>

class CustomInsertDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomInsertDialog(QWidget *parent = 0);

protected:
    virtual void initComboBox() = 0;
    QSqlTableModel * setupComboBox(QString tablename, QComboBox *cb, int viewCol=0);
    void setValueCB(QComboBox *box, QString value, int searchCol);

public slots:
    void clearForm(void);
    virtual void save() = 0;
/*
class AziendaDialog : public CustomInsertDialog
{

public:
    explicit AziendaDialog(QWidget *parent = 0);
    ~AziendaDialog();
    enum cbcols {ID, DESCR, SIGLA};
    enum size {LOGO_WIDTH = 300, LOGO_HEIGHT=200};

private:
    QSqlTableModel * setupComboBox(QString tablename, QComboBox *cb);
    void setValue(QString id="0");
    void prepareMap(void);
    bool checkLineEdit(QLineEdit *le, QString nomeCampo);
    bool checkComboBox(QComboBox *cb, QString nomeCampo);
    bool checkValues(void);
*/
};

#endif // CUSTOMINSERTDIALOG_H
