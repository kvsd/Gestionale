#include "primanotawindow.h"
#include "ui_primanotawindow.h"

PrimaNotaWindow::PrimaNotaWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PrimaNotaWindow)
{
    ui->setupUi(this);
    primaNotaModel = new QSqlQueryModel(this);
    primaNotaModel->setQuery(primanota::SELECT_ALL);
    ui->noteTableView->setModel(primaNotaModel);
}

PrimaNotaWindow::~PrimaNotaWindow()
{
    delete ui;
}

void PrimaNotaWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "PrimaNotaWindow::closeEvent()";
    this->parentWidget()->show();
    event->accept();
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

