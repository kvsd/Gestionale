#include "documentiadddialog.h"
#include "ui_documentiadddialog.h"

DocumentiAddDialog::DocumentiAddDialog(QWidget *parent) :
    CustomInsertDialog(parent),
    ui(new Ui::DocumentiAddDialog)
{
    ui->setupUi(this);

    ui->dateLE->setDate(QDate::currentDate());

    initForm();
    initComboBox();
}

DocumentiAddDialog::~DocumentiAddDialog()
{
    delete ui;
}

void DocumentiAddDialog::initForm()
{
    qDebug() << "DocumentiAddDialog::initForm()";
    ui->clienteCB->setProperty(m_property, "id_anagrafica");
    ui->dateLE->setProperty(m_property, coldb::DATA);
}

void DocumentiAddDialog::initComboBox()
{
    qDebug() << "DocumentiAddDialog::initComboBox()";
    m_modelCliente = new QSqlQueryModel(this);
    m_modelCliente->setQuery(documenti::SELECT_CLIENTE);
    ui->clienteCB->setModel(m_modelCliente);
    ui->clienteCB->setModelColumn(1);
}

void DocumentiAddDialog::setValue(QString id)
{
    qDebug() << "DocumentiAddDialog::setValue(QString id)";
}

void DocumentiAddDialog::save()
{
    qDebug() << "DocumentiAddDialog::save()";
    checkComboBox(ui->clienteCB, "boh");
}
