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
    settings.setValue(primanota::SPLITTER_SIZE, ui->splitter->saveState());
    settings.setValue(primanota::WINDOW_SIZE, this->saveGeometry());
    event->accept();
}

void PrimaNotaWindow::showEvent(QShowEvent *event)
{
    qDebug() << "PrimaNotaWindow::showEvent()";
    Q_UNUSED(event)
    ui->splitter->restoreState(settings.value(primanota::SPLITTER_SIZE).toByteArray());
    restoreGeometry(settings.value(primanota::WINDOW_SIZE).toByteArray());
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
    ui->allRadioButton->blockSignals(true);
    ui->monthDateEdit->blockSignals(true);
    ui->yearDateEdit->blockSignals(true);
    ui->fromDateEdit->blockSignals(true);
    ui->toDateEdit->blockSignals(true);

    QDate date = QDate::currentDate();
    ui->monthDateEdit->setDate(date);
    ui->yearDateEdit->setDate(date);
    QDate startOfMonth(date.year(), date.month(), 1);
    ui->fromDateEdit->setDate(startOfMonth);
    ui->toDateEdit->setDate(date);

    ui->allRadioButton->blockSignals(false);
    ui->monthDateEdit->blockSignals(false);
    ui->yearDateEdit->blockSignals(false);
    ui->fromDateEdit->blockSignals(false);
    ui->toDateEdit->blockSignals(false);
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
    QString query = primanota::SELECT_ALL + prepareFilterQuery();
    primaNotaModel->setQuery(query);
    ui->noteTableView->hideColumn(primanota::COL_ID);
    ui->noteTableView->resizeColumnsToContents();
    ui->noteTableView->horizontalHeader()->setStretchLastSection(true);
    getInfoLabel();
}

QString PrimaNotaWindow::prepareFilterQuery()
{
    qDebug() << "PrimaNotaWindow::prepareFilterQuery()";
    QStringList list;

    QString searchString = ui->searchLineEdit->text();
    if (!searchString.isEmpty()) {
        list.append(primanota::SEARCH_STR.arg(searchString));
    }

    if (ui->monthRadioButton->isChecked()) {
        QDate data = ui->monthDateEdit->date();
        QString month = QString().setNum(data.month());
        QString years = QString().setNum(data.year());
        list.append(primanota::MONTH_STR.arg(month).arg(years));
    }
    else if (ui->yearRadioButton->isChecked()) {
        QString years = ui->yearDateEdit->text();
        list.append(primanota::YEARS_STR.arg(years));

    }
    else if (ui->rangeRadioButton->isChecked()) {
        QString fromDate = ui->fromDateEdit->text();
        QString toDate = ui->toDateEdit->text();
        list.append(primanota::RANGE_STR.arg(fromDate).arg(toDate));
    }

    QString str("");
    if (list.length() == 1) {
        str = " WHERE " + list[0];
    }
    else if (list.length() > 1) {
        str = " WHERE " + list.join(" AND ");
    }

    return str+primanota::ORDER_BY;
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

    QModelIndex index = ui->noteTableView->currentIndex();
    if (!index.isValid()) {
        showDialogError(this, ERR054, MSG025); //Note Codice errore 054
        return;
    }

    QString id = primaNotaModel->index(index.row(), primanota::COL_ID).data().toString();
    PrimaNotaAddDlg dlg(this);
    dlg.setValue(id);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    updateViewNote();
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

