#include "primanotawindow.h"
#include "ui_primanotawindow.h"

PrimaNotaWindow::PrimaNotaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PrimaNotaWindow)
{
    ui->setupUi(this);
    initModel();
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
}

void PrimaNotaWindow::initModel()
{
    qDebug() << "PrimaNotaWindow::initModel()";
    primaNotaModel = new PrimaNotaModel(this);
    primaNotaModel->setQuery(primanota::SELECT_ALL);
    ui->noteTableView->setModel(primaNotaModel);
    ui->noteTableView->hideColumn(primanota::COL_ID);
    ui->noteTableView->resizeColumnsToContents();
}

void PrimaNotaWindow::addNote()
{
    qDebug() << "PrimaNotaWindow::addNote()";
}

void PrimaNotaWindow::updateNote()
{
    qDebug() << "PrimaNotaWindow::updateNote()";
}

void PrimaNotaWindow::removeNote()
{
    qDebug() << "PrimaNotaWindow::removeNote()";
}

