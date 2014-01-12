#ifndef ARTICOLODIALOG_H
#define ARTICOLODIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMap>
#include <QDebug>
#include <QLocale>

namespace Ui {
class ArticoloDialog;
}

class ArticoloDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArticoloDialog(QWidget *parent = 0);
    ~ArticoloDialog();

private:
    Ui::ArticoloDialog *ui;
    QSqlTableModel *modelCatMerce;
    QSqlTableModel *modelCodIva;
    QSqlQueryModel *modelFornitore;
    QSqlTableModel *modelMarca;
    QSqlTableModel *modelSede;
    QSqlTableModel *modelUnita;
    QMap <QString,QString> articolo;
    QMap <QString, double> articolo_d;

    void initModel(void);
    void prepareMap(void);
    QSqlQuery prepareQueryArticolo(void);
    QSqlQuery prepareQueryStorico(void);

public slots:
    void updatePrezzoAcquisto(void);
    void updateImponibile(void);
    void updateIva(void);
    void updatePrezzoFinito(void);
    void save(void);
};

#endif // ARTICOLODIALOG_H
