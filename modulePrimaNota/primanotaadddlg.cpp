#include "primanotaadddlg.h"
#include "ui_primanotaadddlg.h"

PrimaNotaAddDlg::PrimaNotaAddDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrimaNotaAddDlg)
{
    qDebug() << "PrimaNotaAddDlg()";
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
    descrModel = new QSqlQueryModel(this);
    descrModel->setQuery(primanota::SELECT_DESCR);
    ui->comboBox->setModel(descrModel);
    updateLineEdit();
}

PrimaNotaAddDlg::~PrimaNotaAddDlg()
{
    qDebug() << "~PrimaNotaAddDlg()";
    delete ui;
}

void PrimaNotaAddDlg::prepareMap()
{
    qDebug() << "PrimaNotaAddDlg::prepareMap()";

    mapQuery[primanota::PH_DATE] = ui->dateEdit->text();
    mapQuery[primanota::PH_DESCR] = ui->comboBox->currentText();

    double entCassa = stringToDouble(ui->entCassaLineEdit->text());
    mapQuery[primanota::PH_ENT_CASSA] = QString().setNum(entCassa);

    double entBanca = stringToDouble(ui->entBancaLineEdit->text());
    mapQuery[primanota::PH_ENT_BANCA] = QString().setNum(entBanca);

    double uscCassa = stringToDouble(ui->uscCassaLineEdit->text());
    mapQuery[primanota::PH_USC_CASSA] = QString().setNum(uscCassa);

    double uscBanca = stringToDouble(ui->uscBancaLineEdit->text());
    mapQuery[primanota::PH_USC_BANCA] = QString().setNum(uscBanca);
}

QSqlQuery PrimaNotaAddDlg::prepareQuery()
{
    qDebug() << "PrimaNotaAddDlg::prepareQuery()";
    prepareMap();

    QSqlQuery query;
    query.prepare(primanota::INSERT_NOTE);

    query.bindValue(primanota::PH_DATE, mapQuery[primanota::PH_DATE]);
    query.bindValue(primanota::PH_DESCR, mapQuery[primanota::PH_DESCR]);
    query.bindValue(primanota::PH_ENT_CASSA, mapQuery[primanota::PH_ENT_CASSA]);
    query.bindValue(primanota::PH_ENT_BANCA, mapQuery[primanota::PH_ENT_BANCA]);
    query.bindValue(primanota::PH_USC_CASSA, mapQuery[primanota::PH_USC_CASSA]);
    query.bindValue(primanota::PH_USC_BANCA, mapQuery[primanota::PH_USC_BANCA]);

    return query;
}

void PrimaNotaAddDlg::save()
{
    qDebug() << "PrimaNotaAddDlg::save()";
    QSqlQuery query = prepareQuery();

    if (mapQuery[primanota::PH_DESCR].isEmpty()) {
        showDialogError(this, ERR051, MSG013); //NOTE codice errore 051
        return;
    }

    bool ok = query.exec();
    if (!ok) {
        showDialogError(this, ERR052, MSG010, query.lastError().text()); //NOTE codice errore 052
        return;
    }
    this->accept();
}

void PrimaNotaAddDlg::updateLineEdit()
{
    qDebug() << "PrimaNotaAddDlg::updatePrezzo()";
    QString enCassa = ui->entCassaLineEdit->text();
    QString enBanca = ui->entBancaLineEdit->text();
    QString uscCassa = ui->uscCassaLineEdit->text();
    QString uscBanca = ui->uscBancaLineEdit->text();

    if (!enCassa.contains(locale().currencySymbol()))
        ui->entCassaLineEdit->setText(locale().toCurrencyString(stringToDouble(enCassa)));

    if (!enBanca.contains(locale().currencySymbol()))
        ui->entBancaLineEdit->setText(locale().toCurrencyString(stringToDouble(enBanca)));

    if (!uscCassa.contains(locale().currencySymbol()))
        ui->uscCassaLineEdit->setText(locale().toCurrencyString(stringToDouble(uscCassa)));

    if (!uscBanca.contains(locale().currencySymbol()))
        ui->uscBancaLineEdit->setText(locale().toCurrencyString(stringToDouble(uscBanca)));
}
