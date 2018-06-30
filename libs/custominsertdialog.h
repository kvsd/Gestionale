#ifndef CUSTOMINSERTDIALOG_H
#define CUSTOMINSERTDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDebug>

class CustomInsertDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomInsertDialog(QWidget *parent = 0);

public slots:
    void clearForm(void);
    void save(void);
/*
class AziendaDialog : public CustomInsertDialog
{

public:
    explicit AziendaDialog(QWidget *parent = 0);
    ~AziendaDialog();
    enum cbcols {ID, DESCR, SIGLA};
    enum size {LOGO_WIDTH = 300, LOGO_HEIGHT=200};

private:
    void initComboBox();
    QSqlTableModel * setupComboBox(QString tablename, QComboBox *cb);
    void setValueCB(QComboBox *box, QString value);
    void setValue(QString id="0");
    void prepareMap(void);
    bool checkLineEdit(QLineEdit *le, QString nomeCampo);
    bool checkComboBox(QComboBox *cb, QString nomeCampo);
    bool checkValues(void);
*/
};

#endif // CUSTOMINSERTDIALOG_H
