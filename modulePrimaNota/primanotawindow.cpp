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
    QMap <QString, Qt::AlignmentFlag> alignMap;
    alignMap[primanota::COL_VW_DATA] = Qt::AlignLeft;
    alignMap[primanota::COL_VW_DESCR] = Qt::AlignLeft;

    QMap <QString, QBrush> fgColorMap;
    fgColorMap[primanota::COL_VW_ENT_CASSA] = QBrush(Qt::blue);
    fgColorMap[primanota::COL_VW_ENT_BANCA] = QBrush(Qt::blue);
    fgColorMap[primanota::COL_VW_USC_CASSA] = QBrush(Qt::red);
    fgColorMap[primanota::COL_VW_USC_BANCA] = QBrush(Qt::red);

    //primaNotaModel = new CustomModel("", Qt::AlignRight, this);
    primaNotaModel = new CustomModel(Qt::AlignRight, this);
    primaNotaModel->setAlignMap(alignMap);
    primaNotaModel->setFgMap(fgColorMap);
    ui->noteTableView->setModel(primaNotaModel);
}

void PrimaNotaWindow::initComboBox()
{
    //Imposta le date nei combobox
    qDebug() << "PrimaNotaWindow::initComboBox()";
    QList <QWidget*> listWidget;
    listWidget << ui->allRadioButton << ui->monthDateEdit << ui->yearDateEdit << ui->fromDateEdit << ui->toDateEdit;
    QWidget *obj;
    foreach (obj, listWidget)
        obj->blockSignals(true);

    QDate date = QDate::currentDate();
    ui->monthDateEdit->setDate(date);
    ui->yearDateEdit->setDate(date);
    QDate startOfMonth(date.year(), date.month(), 1);
    ui->fromDateEdit->setDate(startOfMonth);
    ui->toDateEdit->setDate(date);

    foreach (obj, listWidget)
        obj->blockSignals(false);
}

void PrimaNotaWindow::getInfoLabel()
{
    //Imposta le label dei totali nel pannello a destra
    qDebug() << "PrimaNotaWindow::getInfoLabel()";    
    QSqlQuery query;
    query.prepare(primanota::SELECT_SUM + prepareFilterQuery());
    query.exec();
    query.next();

    QSqlRecord record = query.record();

    ui->ecLabel->setText(record.value(0).toString());
    ui->ebLabel->setText(record.value(1).toString());
    ui->ucLabel->setText(record.value(2).toString());
    ui->ubLabel->setText(record.value(3).toString());

    ui->ecLabel->setStyleSheet(primanota::positive_css);
    ui->ebLabel->setStyleSheet(primanota::positive_css);
    ui->ucLabel->setStyleSheet(primanota::negative_css);
    ui->ubLabel->setStyleSheet(primanota::negative_css);
}

void PrimaNotaWindow::updateViewNote()
{
    qDebug() << "PrimaNotaWindow::updateViewNote()";
    QString query = primanota::SELECT_ALL + prepareFilterQuery() + primanota::ORDER_BY;
    primaNotaModel->setQuery(query);
    ui->noteTableView->hideColumn(0);
    ui->noteTableView->resizeColumnsToContents();
    ui->noteTableView->horizontalHeader()->setStretchLastSection(true);
    getInfoLabel();
}

QString PrimaNotaWindow::prepareFilterQuery()
{
    qDebug() << "PrimaNotaWindow::prepareFilterQuery()";
    QStringList list;

    QString searchString = ui->searchLineEdit->text();
    if (!searchString.isEmpty())
        list.append(primanota::SEARCH_STR.arg(searchString));

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
    if (list.length() == 1)
        str = " WHERE " + list[0];
    else if (list.length() > 1)
        str = " WHERE " + list.join(" AND ");

    return str;
}

void PrimaNotaWindow::addNote()
{
    qDebug() << "PrimaNotaWindow::addNote()";
    PrimaNotaAddDlg dlg(this);
    bool ok = dlg.exec();
    if (!ok)
        return;

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

    QString id = primaNotaModel->record(index.row()).value(coldb::ID).toString();
    PrimaNotaAddDlg dlg(this);
    dlg.setValue(id);
    dlg.setWindowTitle("Modifica Nota");
    bool ok = dlg.exec();
    if (!ok)
        return;

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
    QString id = primaNotaModel->record(index.row()).value(coldb::ID).toString();
    QSqlQuery query;
    query.prepare(primanota::DELETE_NOTE);
    query.bindValue(ph::ID, id);
    if (!query.exec())
        showDialogError(this, ERR049, MSG003, query.lastError().text()); //NOTE codice errore 049

    updateViewNote();
}

