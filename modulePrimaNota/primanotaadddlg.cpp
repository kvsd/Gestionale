#include "primanotaadddlg.h"
#include "ui_primanotaadddlg.h"

PrimaNotaAddDlg::PrimaNotaAddDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrimaNotaAddDlg)
{
    qDebug() << "PrimaNotaAddDlg()";
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());

    m_descrModel = new QSqlQueryModel(this);
    m_descrModel->setQuery(sql::SELECT_NOTE_DISTINCT);
    ui->comboBox->setModel(m_descrModel);
    updateLineEdit();
}

PrimaNotaAddDlg::~PrimaNotaAddDlg()
{
    qDebug() << "~PrimaNotaAddDlg()";
    delete ui;
}

void PrimaNotaAddDlg::setValue(QString id)
{
    qDebug() << "PrimaNotaAddDlg::setValue()";
    QSqlQuery query;
    query.prepare(sql::SELECT_PN_FROM_ID);
    query.bindValue(ph::ID, id);
    if (!query.exec())
        // NOTE codice errore 053
        showDialogError(this, ERR053, MSG010, query.lastError().text());

    query.first();
    m_mapQuery[ph::ID] = id;

    QDate data = query.value(coldb::DATA).toDate();
    QString descr = query.value(coldb::DESCRIZIONE).toString();
    QString entCassa = query.value(coldb::ENT_CASSA).toString();
    QString entBanca = query.value(coldb::ENT_BANCA).toString();
    QString uscCassa = query.value(coldb::USC_CASSA).toString();
    QString uscBanca = query.value(coldb::USC_BANCA).toString();

    ui->dateEdit->setDate(data);
    ui->comboBox->setCurrentText(descr);
    ui->entCassaLineEdit->setText(entCassa);
    ui->entBancaLineEdit->setText(entBanca);
    ui->uscCassaLineEdit->setText(uscCassa);
    ui->uscBancaLineEdit->setText(uscBanca);

    updateLineEdit();
}

void PrimaNotaAddDlg::prepareMap()
{
    qDebug() << "PrimaNotaAddDlg::prepareMap()";

    m_mapQuery[ph::DATE] = ui->dateEdit->text();
    m_mapQuery[ph::DESCR] = ui->comboBox->currentText();

    double entCassa = stringToDouble(ui->entCassaLineEdit->text());
    m_mapQuery[ph::ENT_CASSA] = QString().setNum(entCassa);

    double entBanca = stringToDouble(ui->entBancaLineEdit->text());
    m_mapQuery[ph::ENT_BANCA] = QString().setNum(entBanca);

    double uscCassa = stringToDouble(ui->uscCassaLineEdit->text());
    m_mapQuery[ph::USC_CASSA] = QString().setNum(uscCassa);

    double uscBanca = stringToDouble(ui->uscBancaLineEdit->text());
    m_mapQuery[ph::USC_BANCA] = QString().setNum(uscBanca);
}

QSqlQuery PrimaNotaAddDlg::prepareQuery()
{
    qDebug() << "PrimaNotaAddDlg::prepareQuery()";
    prepareMap();

    QSqlQuery query;
    if (m_mapQuery.contains(ph::ID)) {
        query.prepare(sql::UPDATE_PN);
        query.bindValue(ph::ID, m_mapQuery[ph::ID]);
    }
    else
        query.prepare(sql::INSERT_PN);

    for (QString &key : m_mapQuery.keys())
        query.bindValue(key, m_mapQuery[key]);

    return query;
}

void PrimaNotaAddDlg::save()
{
    qDebug() << "PrimaNotaAddDlg::save()";
    QSqlQuery query = prepareQuery();

    if (m_mapQuery[ph::DESCR].isEmpty()) {
        showDialogError(this, ERR051, MSG013); //NOTE codice errore 051
        return;
    }

    bool ok = query.exec();
    if (!ok) {
        //NOTE codice errore 052
        showDialogError(this, ERR052, MSG010, query.lastError().text());
        return;
    }
    this->accept();
}


void PrimaNotaAddDlg::updateLineEdit()
{
    qDebug() << "PrimaNotaAddDlg::updateLineEdit()";
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
