#include "primanotawindow.h"
#include "ui_primanotawindow.h"

PrimaNotaWindow::PrimaNotaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PrimaNotaWindow)
{
    ui->setupUi(this);
    initModel();
    initComboBox();
}

PrimaNotaWindow::~PrimaNotaWindow()
{
    delete ui;
}

void PrimaNotaWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "PrimaNotaWindow::closeEvent()";
    this->parentWidget()->show();
    //TODO SALVARE LE IMPOSTAZIONI
    settings.setValue(primanota::SPLITTER_SIZE, ui->splitter->saveState());
    event->accept();
}

void PrimaNotaWindow::showEvent(QShowEvent *event)
{
    qDebug() << "PrimaNotaWindow::showEvent()";
    Q_UNUSED(event)
    //TODO CARICARE LE IMPOSTAZIONI
    ui->splitter->restoreState(settings.value(primanota::SPLITTER_SIZE).toByteArray());
    updateViewNote();
}

void PrimaNotaWindow::initModel()
{
    qDebug() << "PrimaNotaWindow::initModel()";
    primaNotaModel = new PrimaNotaModel(this);
    ui->noteTableView->setModel(primaNotaModel);
}

void PrimaNotaWindow::initComboBox()
{
    //Imposta le date nei combobox
    qDebug() << "PrimaNotaWindow::initComboBox()";
    QDate date = QDate::currentDate();
    ui->monthDateEdit->setDate(date);
    ui->yearDateEdit->setDate(date);
    ui->fromDateEdit->setDate(date);
    ui->toDateEdit->setDate(date);
}

void PrimaNotaWindow::getInfoLabel()
{
    //Imposta le label dei totali nel pannello a destra
    qDebug() << "PrimaNotaWindow::getInfoLabel()";
    QSqlQuery query;
    query.prepare(primanota::SELECT_SUM);
    query.exec();
    query.next();

    QString entrate_cassa = query.value(0).toString();
    QString entrate_banca = query.value(1).toString();
    QString uscite_cassa = query.value(2).toString();
    QString uscite_banca = query.value(3).toString();

    ui->ecLabel->setText(QString("%1").arg(entrate_cassa));
    ui->ecLabel->setStyleSheet(primanota::positive_css);
    ui->ebLabel->setText(QString("%1").arg(entrate_banca));
    ui->ebLabel->setStyleSheet(primanota::positive_css);
    ui->ucLabel->setText(QString("%1").arg(uscite_cassa));
    ui->ucLabel->setStyleSheet(primanota::negative_css);
    ui->ubLabel->setText(QString("%1").arg(uscite_banca));
    ui->ubLabel->setStyleSheet(primanota::negative_css);
}

void PrimaNotaWindow::updateViewNote()
{
    qDebug() << "PrimaNotaWindow::updateViewNote()";
    primaNotaModel->setQuery(primanota::SELECT_ALL);
    ui->noteTableView->hideColumn(primanota::COL_ID);
    ui->noteTableView->resizeColumnsToContents();
    ui->noteTableView->horizontalHeader()->setStretchLastSection(true);
    getInfoLabel();
}

void PrimaNotaWindow::addNote()
{
    qDebug() << "PrimaNotaWindow::addNote()";
    PrimaNotaAddDlg dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    updateViewNote();
}

void PrimaNotaWindow::updateNote()
{
    qDebug() << "PrimaNotaWindow::updateNote()";
}

void PrimaNotaWindow::removeNote()
{
    qDebug() << "PrimaNotaWindow::removeNote()";
    QModelIndex index = ui->noteTableView->currentIndex();
    if (!index.isValid()) {
        showDialogError(this, ERR048, MSG012); //NOTE codice errore 048
        return;
    }
    QString id = primaNotaModel->index(index.row(), primanota::COL_ID).data().toString();
    QSqlQuery query;
    query.prepare(primanota::DELETE_NOTE);
    query.bindValue(primanota::PH_ID, id);
    if (!query.exec()) {
        showDialogError(this, ERR049, MSG003, query.lastError().text()); //NOTE codice errore 049
    }
    updateViewNote();
}

