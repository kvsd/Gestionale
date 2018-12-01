#include "agentiadddialog.h"
#include "ui_agentiadddialog.h"

AgentiAddDialog::AgentiAddDialog(QWidget *parent) :
    CustomInsertDialog(parent),
    ui(new Ui::AgentiAddDialog)
{
    qDebug() << "AgentiAddDialog()";
    ui->setupUi(this);
    initForm();
}

AgentiAddDialog::~AgentiAddDialog()
{
    qDebug() << "~AgentiAddDialog()";
    delete ui;
}

void AgentiAddDialog::initForm()
{
    qDebug() << "AgentiAddDialog::initForm()";
    ui->nomeLineEdit->setProperty(m_property, coldb::NOME);
    ui->cognomeLineEdit->setProperty(m_property, coldb::COGNOME);
    ui->telLineEdit->setProperty(m_property, coldb::TEL);
    ui->celLineEdit->setProperty(m_property, coldb::CEL);
    ui->faxLineEdit->setProperty(m_property, coldb::FAX);
    ui->emailLineEdit->setProperty(m_property, coldb::EMAIL);
}

void AgentiAddDialog::initComboBox()
{
    qDebug() << "AgentiAddDialog::initComboBox()";
}

void AgentiAddDialog::setValue(QString id)
{
    qDebug() << "AgentiAddDialog::setValue()";
    QSqlQuery query;
    query.prepare(agenti::SELECT_FROM_ID);
    query.bindValue(ph::ID, id);
    query.exec();
    query.first();

    for (auto *le : findChildren<QLineEdit *>()) {
        QString colName = le->property(m_property).toString();
        QString value = query.value(colName).toString();
        le->setText(value);
    }

    mapAgente[ph::ID] = id;
}

void AgentiAddDialog::save(void)
{
    qDebug() << "AgentiAddDialog::save()";
    prepareMap(mapAgente);

    if (!checkLineEdit(ui->cognomeLineEdit, "cognome"))
        return;

    QSqlQuery query;
    if (mapAgente.contains(ph::ID)) {
        query.prepare(agenti::UPDATE_QUERY);
        query.bindValue(ph::ID, mapAgente[ph::ID]);
    }
    else
        query.prepare(agenti::INSERT_QUERY);

    for (auto key : mapAgente.keys())
        query.bindValue(key, mapAgente[key]);

    if (!query.exec()) {
        showDialogError(this, ERR009, MSG022, query.lastError().text()); //NOTE codice errore 009
        return;
    }

    while (query.next())
        setId(query.value("id").toString());

    this->accept();
}
