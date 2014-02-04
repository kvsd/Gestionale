#ifndef MAGAZZINO_CONST_H
#define MAGAZZINO_CONST_H

#include <QString>
#include <QRect>

namespace magazzino {

    const int TAB_MAGAZZINO = 0;
    const int TAB_STORICO = 1;

    const QString ARTICOLO_COLORS = "MagazzinoWindow.cols.colors.articolo";
    const QString ARTICOLO_STATUS = "MagazzinoWindow.cols.status.articolo";
    const QString ARTICOLO_HEADER = "MagazzinoWindow.header.articolo";

    const QString STORICO_COLORS = "MagazzinoWindow.cols.colors.storico";
    const QString STORICO_STATUS = "MagazzinoWindow.cols.status.storico";
    const QString STORICO_HEADER = "MagazzinoWindow.header.storico";

    const QString WINDOW_SIZE = "MagazzinoWindow.size";
    const QRect DEFAULT_WINDOW_SIZE = QRect(0, 0, 700, 500);

    const QString SEARCH_DESCR = "MagazzinoWindow.search.descrizione";
    const QString SEARCH_COD_ART = "MagazzinoWindow.search.codarticolo";
    const QString SEARCH_COD_FRN = "MagazzinoWindow.search.codfornitore";
    const QString SEARCH_COD_EAN = "MagazzinoWindow.search.codean";

    const QString SELECT_ARTICOLI_ALL = "SELECT * FROM vw_magazzino";
    const QString SELECT_ARTICOLI_FORNITORE = "SELECT * FROM vw_magazzino WHERE \"Fornitore\" = '%1'";
    const QString SELECT_ARTICOLI_MARCA = "SELECT * FROM vw_magazzino WHERE \"Marca\"= '%1'";
    const QString SELECT_ARTICOLI_CATEGORIA = "SELECT * FROM vw_magazzino WHERE \"Cat.Merce\" = '%1'";
    const QString SELECT_ARTICOLI_SEDE = "SELECT * FROM vw_magazzino WHERE \"Sede Magazzino\" = '%1'";

    const QString SELECT_FILTER = "SELECT id, descr FROM %1";
    const QString SELECT_FILTER_FORNITORI = "SELECT \"Id\" as id, \"Ragione sociale\" as descr FROM vw_anagrafica_fornitori";

    const QString SELECT_STORICO = "SELECT * FROM vw_listino_storico WHERE \"Id Articolo\"='%1' ORDER BY \"Data\" DESC, \"Imponibile\" DESC";

    const QString INSERT_ARTICOLO = "INSERT INTO magazzino (descr, id_fornitore, id_marca, modello, cod_articolo, cod_fornitore, cod_barre ,id_merce ,id_cod_iva, id_unita_misura, scorta_minima, quantita, prezzo_acquisto, sconto_fornitore, ricarico, imponibile, iva, prezzo_finito, prezzo_vendita, fattura, data_arrivo, id_sede_magazzino, note) VALUES (:descr, :id_fornitore, :id_marca, :modello, :cod_articolo, :cod_fornitore, :cod_barre, :id_merce, :id_cod_iva, :id_unita_merce, :scorta_minima, :quantita, :prezzo_acquisto, :sconto_fornitore, :ricarico, :imponibile, :iva, :prezzo_finito, :prezzo_vendita, :fattura, :data_arrivo, :id_sede_magazzino, :note)";
    const QString INSERT_STORICO = "INSERT INTO listino_storico (id_articolo, data_arrivo, quantita, prezzo_acquisto, sconto_fornitore, ricarico, imponibile, iva, prezzo_finito, prezzo_vendita, fattura) VALUES (:id_articolo, :data_arrivo, :quantita, :prezzo_acquisto, :sconto_fornitore, :ricarico, :imponibile, :iva, :prezzo_finito, :prezzo_vendita, :fattura)";
    const QString DELETE_ARTICOLO = "DELETE FROM magazzino WHERE id = :id";
    const QString UPDATE_ARTICOLO = "UPDATE magazzino SET descr=:descr, id_fornitore=:id_fornitore, id_marca=:id_marca, modello=:modello, cod_articolo=:cod_articolo, cod_fornitore=:cod_fornitore, cod_barre=:cod_barre, id_merce=:id_merce, id_cod_iva=:id_cod_iva, id_unita_misura=:id_unita_merce, scorta_minima=:scorta_minima, quantita=:quantita, prezzo_acquisto=:prezzo_acquisto, sconto_fornitore=:sconto_fornitore, ricarico=:ricarico, imponibile=:imponibile, iva=:iva, prezzo_finito=:prezzo_finito, prezzo_vendita=:prezzo_vendita, fattura=:fattura, data_arrivo=:data_arrivo, id_sede_magazzino=:id_sede_magazzino, note=:note WHERE id=:id";

    const QString SELECT_FORNITORE = "SELECT \"Id\", \"Ragione sociale\" from vw_anagrafica_fornitori ORDER BY \"Ragione sociale\"";
    const QString SELECT_FROM_ID = "SELECT * FROM magazzino WHERE id = :id";

    enum columns {COL_ID,
                  COL_DESCR = 1,
                  COL_ID_FORN,
                  COL_ID_MARCA,
                  COL_MODELLO,
                  COL_COD_ART,
                  COL_COD_FOR,
                  COL_COD_EAN,
                  COL_ID_MERCE,
                  COL_ID_COD_IVA,
                  COL_ID_UM,
                  COL_SCORTA,
                  COL_QUANTITA,
                  COL_PREZZO_ACQ,
                  COL_SCONTO,
                  COL_RICARICO,
                  COL_IMPONIBILE,
                  COL_IVA,
                  COL_PREZZO_FIN,
                  COL_PREZZO_VEN,
                  COL_FATTURA,
                  COL_DATA,
                  COL_ID_SEDE,
                  COL_NOTE};
}
#endif // MAGAZZINO_CONST_H