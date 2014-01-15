#include "agentiviewdialog.h"
#include "ui_agentiviewdialog.h"

const QString ADD_QUERY = "INSERT INTO agenti(nome, cognome, tel, cel, email) VALUES(:nome, :cognome, :tel, :cel, :email)";
const QString UPDATE_QUERY = "UPDATE agenti SET nome=:nome, cognome=:cognome, tel=:tel, cel=:cel, email=:email WHERE id=:id";
const QString DELETEQUERY = "DELETE FROM agenti WHERE id=:id";
const QString SELECT_QUERY = "SELECT * FROM agenti WHERE id>0 ORDER BY cognome";
const QString STR_SEARCH = "SELECT * FROM agenti WHERE \"cognome\" ILIKE '\%%1\%' AND id>0 ORDER BY cognome";

AgentiViewDialog::AgentiViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgentiViewDialog)
{
    ui->setupUi(this);
    model = new QSqlQueryModel(this);
    model->setQuery(SELECT_QUERY);
    model->setHeaderData(agenti::COL_NOME, Qt::Horizontal, "Nome");
    model->setHeaderData(agenti::COL_COGNOME, Qt::Horizontal, "Cognome");
    model->setHeaderData(agenti::COL_TEL, Qt::Horizontal, "Telefono");
    model->setHeaderData(agenti::COL_CEL, Qt::Horizontal, "Cellulare");
    model->setHeaderData(agenti::COL_EMAIL, Qt::Horizontal, "E-mail");

    ui->agentiView->setModel(model);
    ui->agentiView->hideColumn(agenti::COL_ID);
    ui->agentiView->resizeColumnsToContents();

    this->setGeometry(settings.value("AgentiViewDlg.size", QRect(0, 0, 700, 500)).toRect());
}

AgentiViewDialog::~AgentiViewDialog()
{
    delete ui;
}

void AgentiViewDialog::closeEvent(QCloseEvent *event)
{
    settings.setValue("AgentiViewDlg.size", this->geometry());
    event->accept();
}

void AgentiViewDialog::updateTable(void)
{
    model->setQuery(SELECT_QUERY);
    ui->agentiView->resizeColumnsToContents();
    ui->agentiView->horizontalHeader()->setStretchLastSection(true);
}

void AgentiViewDialog::addRecord(void)
{
    AgentiAddDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }

    updateTable();
}

void AgentiViewDialog::updateRecord(void)
{
    QModelIndex index = ui->agentiView->currentIndex();
    QString id = model->index(index.row(), agenti::COL_ID).data().toString();

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

    updateTable();
}

void AgentiViewDialog::removeRecord(void)
{
    QModelIndex index = ui->agentiView->currentIndex();
    QString id = model->index(index.row(), agenti::COL_ID).data().toString();

    if (id=="") {
        showDialogError(this, ERR013, MSG004); //NOTE codice errore 013
        return;
    }

    QSqlQuery query;
    query.prepare(DELETEQUERY);
    query.bindValue(":id", id);
    if (!query.exec()) {
        showDialogError(this, ERR014, MSG003, query.lastError().text()); //NOTE codice errore 014
        return;
    }

    updateTable();
}

void AgentiViewDialog::searchRecord(QString s)
{
    if (s.isEmpty()) {
        updateTable();
        return;
    }

    QString query(STR_SEARCH);
    model->setQuery(query.arg(s));
    ui->agentiView->resizeColumnsToContents();
    ui->agentiView->horizontalHeader()->setStretchLastSection(true);
}
