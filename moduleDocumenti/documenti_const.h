#ifndef DOCUMENTI_CONST_H
#define DOCUMENTI_CONST_H

namespace documenti {

    const QString SELECT_DOC_ALL = "SELECT id AS \"Id\", "
                                   "       id_cliente AS \"Cliente\" "
                                   "FROM documenti";

    //Utilizzato nel combobox cliente di DocumentiAddDialog.
    const QString SELECT_CLIENTE = "SELECT id, concat(denominazione, cognome, nome) AS denominazione "
                                   "FROM anagrafica";

    //Utilizzato in DocumentiAddDialog.
    const QString INSERT_DOC = "INSERT INTO documenti(id_cliente, id_tipo_documento, "
                               "                      id_moneta, data, years, nr_documento, "
                               "                      importo_tot, arrotondamento, casuale) "
                               "VALUES(:id_cliente, :id_tipo_documento, :id_moneta, :data, "
                               "       :years, 'FA'||nextval('fatt_seq'), :importo_tot, "
                               "       :arrotondamento, :casuale) "
                               "RETURNING id";

     const QString INSERT_DET = "INSERT INTO documenti_det (id_documento, linea, cod_articolo, "
                                "                           descr, quantita, um, prezzo_unitario, "
                                "                           prezzo_totale, aliquota_iva, rif) "
                                "VALUES(:id_documento, :linea, :cod_articolo, "
                                "       :descr, :quantita, :um, :prezzo_unitario, "
                                "       :prezzo_totale, :aliquota_iva, :rif)";

     const QString INSERT_IVA = "INSERT INTO documenti_iva(id_documento, aliquota_iva, "
                                "                          imponibile, imposta)"
                                "VALUES (:id_documento, :aliquota_iva, "
                                "        :imponibile, :imposta)";

}
#endif // DOCUMENTI_CONST_H
