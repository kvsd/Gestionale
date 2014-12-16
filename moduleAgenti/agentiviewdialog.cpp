#include "agentiviewdialog.h"
#include "ui_agentiviewdialog.h"

AgentiViewDialog::AgentiViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgentiViewDialog)
{
    qDebug() << "AgentiViewDialog()";
    ui->setupUi(this);
    modelAgenti = new QSqlQueryModel(this);
    modelAgenti->setQuery(agenti::SQL_SELECT_AGENTI);
    modelAgenti->setHeaderData(agenti::COL_NOME, Qt::Horizontal, "Nome");
    modelAgenti->setHeaderData(agenti::COL_COGNOME, Qt::Horizontal, "Cognome");
    modelAgenti->setHeaderData(agenti::COL_TEL, Qt::Horizontal, "Telefono");
    modelAgenti->setHeaderData(agenti::COL_FAX, Qt::Horizontal, "Fax");
    modelAgenti->setHeaderData(agenti::COL_CEL, Qt::Horizontal, "Cellulare");
    modelAgenti->setHeaderData(agenti::COL_EMAIL, Qt::Horizontal, "E-mail");

    ui->agentiView->setModel(modelAgenti);
    ui->agentiView->hideColumn(agenti::COL_ID);
    ui->agentiView->resizeColumnsToContents();

    this->setGeometry(settings.value(agenti::WINDOW_SIZE, QRect(0, 0, 700, 500)).toRect());
}

AgentiViewDialog::~AgentiViewDialog()
{
    qDebug() << "~AgentiViewDialog()";
    delete ui;
}

void AgentiViewDialog::closeEvent(QCloseEvent *event)
{
    qDebug() << "AgentiViewDialog::closeEvent()";
    settings.setValue(agenti::WINDOW_SIZE, this->geometry());
    event->accept();
}

void AgentiViewDialog::updateViewAgenti(void)
{
    qDebug() << "AgentiViewDialog::updateViewAgenti()";
    ui->searchLineEdit->clear();
    modelAgenti->setQuery(agenti::SQL_SELECT_AGENTI);
    ui->agentiView->resizeColumnsToContents();
    ui->agentiView->horizontalHeader()->setStretchLastSection(true);
}

void AgentiViewDialog::addRecord(void)
{
    qDebug() << "AgentiViewDialog::addRecord()";
    AgentiAddDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }

    updateViewAgenti();
}

void AgentiViewDialog::updateRecord(void)
{
    qDebug() << "AgentiViewDialog::updateRecord()";
    QModelIndex index = ui->agentiView->currentIndex();
    QString id = modelAgenti->index(index.row(), agenti::COL_ID).data().toString();

    if (id=="") {
        showDialogError(this, ERR010, MSG007); //NOTE codice errore 010
        return;
    }

    AgentiAddDialog dlg(this);
    dlg.setValue(id);
    dlg.setWindowTitle("Modifica Agente");
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }

    updateViewAgenti();
}

void AgentiViewDialog::removeRecord(void)
{
    qDebug() << "AgentiViewDialog::removeRecord()";
    QModelIndex index = ui->agentiView->currentIndex();
    QString id = modelAgenti->index(index.row(), agenti::COL_ID).data().toString();

    if (id=="") {
        showDialogError(this, ERR013, MSG004); //NOTE codice errore 013
        return;
    }

    QSqlQuery query;
    query.prepare(agenti::SQL_DELETE_AGENTE);
    query.bindValue(agenti::PH_ID, id);
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

    QString query(agenti::SQL_SEARCH_AGENTI);
    modelAgenti->setQuery(query.arg(s));
    ui->agentiView->resizeColumnsToContents();
    ui->agentiView->horizontalHeader()->setStretchLastSection(true);
}
