#include "primanotawindow.h"
#include "ui_primanotawindow.h"

PrimaNotaWindow::PrimaNotaWindow(QWidget *parent) :
    CustomWindow(parent),
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
    saveSplittersState();
    saveWindowGeometry();
    saveTableViewSettings();
    event->accept();
}

void PrimaNotaWindow::showEvent(QShowEvent *event)
{
    qDebug() << "PrimaNotaWindow::showEvent()";
    loadSplittersState();
    loadWindowGeometry();
    loadTableViewSettings();
    updateViewNote();
    event->accept();
}

void PrimaNotaWindow::initModel()
{
    qDebug() << "PrimaNotaWindow::initModel()";
    QMap <QString, Qt::AlignmentFlag> alignMap;
    alignMap[colview::DATA] = Qt::AlignLeft;
    alignMap[colview::DESCRIZIONE] = Qt::AlignLeft;

    QMap <QString, QBrush> fgColorMap;
    fgColorMap[colview::ENT_CASSA] = QBrush(Qt::blue);
    fgColorMap[colview::ENT_BANCA] = QBrush(Qt::blue);
    fgColorMap[colview::USC_CASSA] = QBrush(Qt::red);
    fgColorMap[colview::USC_BANCA] = QBrush(Qt::red);

    m_primaNotaModel = new CustomModel(Qt::AlignRight, this);
    m_primaNotaModel->setAlignMap(alignMap);
    m_primaNotaModel->setFgMap(fgColorMap);
    ui->noteTableView->setModel(m_primaNotaModel);
}

void PrimaNotaWindow::initComboBox()
{
    //Imposta le date nei combobox
    qDebug() << "PrimaNotaWindow::initComboBox()";
    QList <QWidget*> listWidget;
    listWidget << ui->allResultRb << ui->monthDateEdit
               << ui->yearDateEdit << ui->fromDateEdit
               << ui->toDateEdit;

    for (auto &obj : listWidget)
        obj->blockSignals(true);

    QDate date = QDate::currentDate();
    ui->monthDateEdit->setDate(date);
    ui->yearDateEdit->setDate(date);
    QDate startOfMonth(date.year(), date.month(), 1);
    ui->fromDateEdit->setDate(startOfMonth);
    ui->toDateEdit->setDate(date);

    for (auto &obj : listWidget)
        obj->blockSignals(false);
}

void PrimaNotaWindow::getInfoLabel()
{
    //Imposta le label dei totali nel pannello a destra
    qDebug() << "PrimaNotaWindow::getInfoLabel()";    
    QSqlQuery query;
    query.prepare(primanota::SELECT_PN_TOTAL + prepareFilterQuery());
    query.exec();
    query.next();

    ui->ecLabel->setText(query.value(coldb::ENT_CASSA).toString());
    ui->ecLabel->setStyleSheet(css::positive);

    ui->ebLabel->setText(query.value(coldb::ENT_BANCA).toString());
    ui->ebLabel->setStyleSheet(css::positive);

    ui->ucLabel->setText(query.value(coldb::USC_CASSA).toString());
    ui->ucLabel->setStyleSheet(css::negative);

    ui->ubLabel->setText(query.value(coldb::USC_BANCA).toString());
    ui->ubLabel->setStyleSheet(css::negative);
}

void PrimaNotaWindow::updateViewNote()
{
    qDebug() << "PrimaNotaWindow::updateViewNote()";
    QString query = primanota::SELECT_PN + prepareFilterQuery() +
                    primanota::PN_ORDER;
    m_primaNotaModel->setQuery(query);
    ui->noteTableView->resizeColumnsToContents();
    ui->noteTableView->horizontalHeader()->setStretchLastSection(true);
    ui->noteTableView->hideColumn(0);
    getInfoLabel();
}

void PrimaNotaWindow::printNote()
{
    qDebug() << "printNote()";
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);

    QPrintDialog dlg(printer, this);
    if (!(dlg.exec() == dlg.Accepted))
        return;

    printer->setOrientation(QPrinter::Landscape);
    QPainter *painter = new QPainter(printer);
    QString query = m_primaNotaModel->query().executedQuery();

    QueryReport *report = new QueryReport(printer, painter, this);
    report->setTitle("PrimaNota");
    report->setStretchValues({1,3, 1, 1, 1, 1});
    report->setQuery(query);
    report->setQueryCols({colview::DATA, colview::DESCRIZIONE,
                         colview::ENT_CASSA, colview::USC_CASSA,
                         colview::ENT_BANCA, colview::USC_BANCA});
    report->setAlignCols({Qt::AlignLeft, Qt::AlignLeft, Qt::AlignRight,
                          Qt::AlignRight, Qt::AlignRight, Qt::AlignRight});
    report->draw();
    //Totale
    QPointF o(0, report->getBottom());
    Row *row = new Row({1,3,1,1,1,1}, o, report->getwitdh(), 1, painter);
    row->setTextAlignment({Qt::AlignLeft, Qt::AlignLeft, Qt::AlignRight,
                           Qt::AlignRight, Qt::AlignRight, Qt::AlignRight});
    row->setLineColor(Qt::transparent);
    row->setText({"", "", ui->ecLabel->text(), ui->ucLabel->text(),
                 ui->ebLabel->text(), ui->ubLabel->text()});
    row->setTextFont(font(), true);
    row->draw();

    delete painter;
}

QString PrimaNotaWindow::prepareFilterQuery()
{
    qDebug() << "PrimaNotaWindow::prepareFilterQuery()";
    QStringList list;

    QString searchString = ui->searchLineEdit->text();
    if (!searchString.isEmpty())
        list.append(primanota::PN_DESCR.arg(searchString));

    if (ui->monthRadioButton->isChecked()) {
        QDate data = ui->monthDateEdit->date();
        QString month = QString().setNum(data.month());
        QString years = QString().setNum(data.year());
        list.append(primanota::PN_MONTH.arg(month).arg(years));
    }
    else if (ui->yearRadioButton->isChecked()) {
        QString years = ui->yearDateEdit->text();
        list.append(primanota::PN_YEARS.arg(years));
    }
    else if (ui->rangeRadioButton->isChecked()) {
        QString fromDate = ui->fromDateEdit->text();
        QString toDate = ui->toDateEdit->text();
        list.append(primanota::PN_RANGE.arg(fromDate).arg(toDate));
    }

    if (list.length() >= 1)
        return " WHERE " + list.join(" AND ");
    else
        return "";
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

    QString id = m_primaNotaModel->record(index.row()).value(coldb::ID).toString();
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
    QString id = m_primaNotaModel->record(index.row()).value(coldb::ID).toString();
    QSqlQuery query;
    query.prepare(primanota::DELETE_PN);
    query.bindValue(ph::ID, id);
    if (!query.exec())
        showDialogError(this, ERR049, MSG003, query.lastError().text()); //NOTE codice errore 049

    updateViewNote();
}

