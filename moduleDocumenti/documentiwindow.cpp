#include "documentiwindow.h"
#include "ui_documentiwindow.h"

DocumentiWindow::DocumentiWindow(QWidget *parent) :
    CustomWindow(parent),
    ui(new Ui::DocumentiWindow)
{
    ui->setupUi(this);
    initModel();
    loadConfigSettings();
}

DocumentiWindow::~DocumentiWindow()
{
    delete ui;
}

void DocumentiWindow::loadConfigSettings()
{
    qDebug() << "DocumentiWindow::loadConfigSettings()";
    loadWindowGeometry();
    loadSplittersState();
    //loadTableViewSettings();
}

void DocumentiWindow::saveConfigSettings()
{
    qDebug() << "DocumentiWindow::saveConfigSettings()";
    saveWindowGeometry();
    saveSplittersState();
    //saveTableViewSettings();
}

void DocumentiWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "DocumentiWindow::closeEvent()";
    this->parentWidget()->show();
    saveConfigSettings();
    event->accept();
}

void DocumentiWindow::showEvent(QShowEvent *event)
{
    qDebug() << "DocumentiWindow::showEvent()";
    event->accept();
}

void DocumentiWindow::initModel()
{
    qDebug() << "DocumentiWindow::initModel()";
    docModel = new CustomModel(this);
    docModel->setQuery("select doc.id AS \"Id\","
                       "       doc.nr_documento AS \"Numero\", "
                       "       an.rag_sociale AS \"Rag.Sociale\","
                       "       an.nome AS \"Nome\", "
                       "       an.cognome AS \"Cognome\" ,"
                       "       doc.data AS \"Data\" "
                       "FROM documenti AS doc, anagrafica AS an "
                       "WHERE doc.id_cliente=an.id");
    ui->documentiView->setModel(docModel);
    ui->documentiView->resizeColumnsToContents();
}
