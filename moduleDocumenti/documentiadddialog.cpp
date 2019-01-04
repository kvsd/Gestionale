#include "documentiadddialog.h"
#include "ui_documentiadddialog.h"

DocumentiAddDialog::DocumentiAddDialog(QWidget *parent) :
    CustomInsertDialog(parent),
    ui(new Ui::DocumentiAddDialog)
{
    ui->setupUi(this);

    //La data corrente. Da definire l'ultima data disponibile.
    ui->dateLE->setDate(QDate::currentDate());

    initForm();
    initComboBox();

    ui->monetaCB->setCurrentText("Euro");
    ui->tipoDocumentoCB->setCurrentText("fattura");
    ui->tableWidget->initFattura();
    int w=0;
    for (int c=0; c<ui->tableWidget->columnCount(); c++) {
        w += ui->tableWidget->columnWidth(c);
    }
    setGeometry(x(), y(), w+50, height());

    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)),
            this, SLOT(test(int,int)));
}

DocumentiAddDialog::~DocumentiAddDialog()
{
    delete ui;
}

void DocumentiAddDialog::initForm()
{
    qDebug() << "DocumentiAddDialog::initForm()";
    ui->dateLE->setProperty(m_property, coldb::DATA);
    ui->clienteCB->setProperty(m_property, "id_cliente");
    ui->tipoDocumentoCB->setProperty(m_property, "id_tipo_documento");
    ui->monetaCB->setProperty(m_property, "id_moneta");
    ui->casualeLE->setProperty(m_property, "casuale");
}

void DocumentiAddDialog::initComboBox()
{
    qDebug() << "DocumentiAddDialog::initComboBox()";
    m_modelCliente = new QSqlQueryModel(this);
    m_modelCliente->setQuery(documenti::SELECT_CLIENTE);
    ui->clienteCB->setModel(m_modelCliente);
    ui->clienteCB->setModelColumn(1);

    m_modelDocumento = setupComboBox(table::TIPO_DOCUMENTO,
                                     ui->tipoDocumentoCB,
                                     int(modelCols::descr));
    m_modelMoneta = setupComboBox(table::MONETA, ui->monetaCB,
                                  int(modelCols::descr));
}

void DocumentiAddDialog::setValue(QString id)
{
    qDebug() << "DocumentiAddDialog::setValue(QString id)";
}

void DocumentiAddDialog::save()
{
    qDebug() << "DocumentiAddDialog::save()";
    QMap<QString, QString> string;
    prepareMap(string, int(modelCols::id));
    string[":years"] = ui->dateLE->date().toString("yyyy");

    QSqlQuery query;
    query.prepare("INSERT INTO documenti(id_cliente, id_tipo_documento, "
                  "                      id_moneta, data, years, nr_documento, casuale) "
                  "VALUES(:id_cliente, :id_tipo_documento, "
                  "       :id_moneta, :data, :years, 'FA'||nextval('fatt_seq'), :casuale)");

    for (QString key : string.keys())
        query.bindValue(key, string[key]);

    if (!query.exec())
        qDebug() << query.lastError().text();

    this->accept();
}

void DocumentiAddDialog::test(int row, int col)
{

}
