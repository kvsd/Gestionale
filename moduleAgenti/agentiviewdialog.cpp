#include "agentiviewdialog.h"
#include "ui_agentiviewdialog.h"

AgentiViewDialog::AgentiViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgentiViewDialog)
{
    qDebug() << "AgentiViewDialog()";
    ui->setupUi(this);

    m_modelAgenti = new QSqlQueryModel(this);
    ui->agentiView->setModel(m_modelAgenti);
    updateViewAgenti();

    this->setGeometry(m_settings.value(agenti::WINDOW_SIZE, QRect(0, 0, 700, 500)).toRect());
}

AgentiViewDialog::~AgentiViewDialog()
{
    qDebug() << "~AgentiViewDialog()";
    delete ui;
}

void AgentiViewDialog::closeEvent(QCloseEvent *event)
{
    qDebug() << "AgentiViewDialog::closeEvent()";
    m_settings.setValue(agenti::WINDOW_SIZE, this->geometry());
    event->accept();
}

void AgentiViewDialog::updateViewAgenti(void)
{
    qDebug() << "AgentiViewDialog::updateViewAgenti()";
    ui->searchLineEdit->clear();
    m_modelAgenti->setQuery(agenti::SELECT_AGENTI + agenti::ORDER_CLAUSE);
    ui->agentiView->resizeColumnsToContents();
    ui->agentiView->horizontalHeader()->setStretchLastSection(true);
    ui->agentiView->hideColumn(0);
}

void AgentiViewDialog::addRecord(void)
{
    qDebug() << "AgentiViewDialog::addRecord()";
    AgentiAddDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok)
        return;

    updateViewAgenti();
}

void AgentiViewDialog::updateRecord(void)
{
    qDebug() << "AgentiViewDialog::updateRecord()";
    QModelIndex index = ui->agentiView->currentIndex();

    if (!index.isValid()) {
        showDialogError(this, ERR010, MSG007); //NOTE codice errore 010
        return;
    }

    QString id = m_modelAgenti->record(index.row()).value(coldb::ID).toString();
    AgentiAddDialog dlg(this);
    dlg.setValue(id);
    dlg.setWindowTitle("Modifica Agente");
    bool ok = dlg.exec();
    if (!ok)
        return;

    updateViewAgenti();
}

void AgentiViewDialog::removeRecord(void)
{
    qDebug() << "AgentiViewDialog::removeRecord()";
    QModelIndex index = ui->agentiView->currentIndex();

    if (!index.isValid()) {
        showDialogError(this, ERR013, MSG004); //NOTE codice errore 013
        return;
    }

    QString id = m_modelAgenti->record(index.row()).value(coldb::ID).toString();
    QSqlQuery query;
    query.prepare(agenti::DELETE_QUERY);
    query.bindValue(ph::ID, id);
    if (!query.exec()) {
        showDialogError(this, ERR014, MSG003, query.lastError().text()); //NOTE codice errore 014
        return;
    }

    updateViewAgenti();
}

void AgentiViewDialog::searchRecord()
{
    qDebug() << "AgentiViewDialog::searchRecord()";
    QString s = ui->searchLineEdit->text();

    if (s.isEmpty()) {
        updateViewAgenti();
        return;
    }

    //QString query(agenti::SQL_SEARCH_AGENTI);
    QString query(agenti::SELECT_AGENTI + agenti::SEARCH_CLAUSE + agenti::ORDER_CLAUSE);
    m_modelAgenti->setQuery(query.arg(s));
    ui->agentiView->resizeColumnsToContents();
    ui->agentiView->horizontalHeader()->setStretchLastSection(true);
}
