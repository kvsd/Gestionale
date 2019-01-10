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
    resize(w+50, height());

    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)),
            this, SLOT(updateCell(int,int)));
    connect(ui->tableWidget, SIGNAL(cbTextChanged(int,int,QString)),
            this, SLOT(updateLabels()));
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

    QSqlQuery query_doc;
    query_doc.prepare("INSERT INTO documenti(id_cliente, id_tipo_documento, "
                      "                      id_moneta, data, years, nr_documento, "
                      "                      importo_tot, arrotondamento, casuale) "
                      "VALUES(:id_cliente, :id_tipo_documento, :id_moneta, :data, "
                      "       :years, 'FA'||nextval('fatt_seq'), :importo_tot, "
                      "       :arrotondamento, :casuale) "
                      "RETURNING id");

    for (QString key : string.keys())
        query_doc.bindValue(key, string[key]);

    if (!query_doc.exec())
        qDebug() << query_doc.lastError().text();

    //Id documento
    query_doc.first();
    QString id_doc = query_doc.value("id").toString();

    QString q = "INSERT INTO documenti_det (id_documento, linea, cod_articolo, "
                "                           descr, quantita, um, prezzo_unitario, "
                "                           prezzo_totale, aliquota_iva, rif) "
                "VALUES(:id_documento, :linea, :cod_articolo, "
                "       :descr, :quantita, :um, :prezzo_unitario, "
                "       :prezzo_totale, :aliquota_iva, :rif)";

    for (int r=0; r<ui->tableWidget->rowCount(); r++) {
        qDebug() << ui->tableWidget->getMap(r);
    }

    this->accept();
}

void DocumentiAddDialog::updateCell(int row, int col)
{
    qDebug() << "DocumentiAddDialog::updateCell()";
    if (col == int(CustomTableWidget::cols::qt) ||
            col == int(CustomTableWidget::cols::prezzo_u)) {
        auto item_qt = ui->tableWidget->item(row, int(CustomTableWidget::cols::qt));
        auto item_pu = ui->tableWidget->item(row, int(CustomTableWidget::cols::prezzo_u));
        double qt = stringToDouble(item_qt->text());
        double prezzo_u = stringToDouble(item_pu->text());

        item_qt->setText(QString::number(qt, 'f', 2));
        item_pu->setText(QString::number(prezzo_u, 'f', 2));

        auto item_pt = ui->tableWidget->item(row, int(CustomTableWidget::cols::prezzo_t));
        item_pt->setText(QString::number(qt*prezzo_u, 'f', 2));
    }
    updateLabels();
}

void DocumentiAddDialog::updateLabels()
{
    int colPrezzo = int(CustomTableWidget::cols::prezzo_t);
    int colIva = int(CustomTableWidget::cols::al_iva);
    QMap<QString, double>map;

    for (int r=0; r<ui->tableWidget->rowCount(); r++) {
        auto imponibileItem = ui->tableWidget->item(r, colPrezzo);
        auto *cb_iva = qobject_cast<QComboBox *> (ui->tableWidget->cellWidget(r, colIva));
        map[cb_iva->currentText()] += stringToDouble(imponibileItem->text());
    }

    for (QString i : map.keys()) {
        double imponibile = map[i];
        double imposta = map[i]*stringToDouble(i)/100;
        qDebug() << i << " " << QString::number(imponibile, 'f', 2)
                 << " " << QString::number(imposta, 'f', 2)
                 << " " << QString::number(imponibile+imposta, 'f', 2);
    }
}
