#include "magazzinowindow.h"

QMap<int,QString> magazzino::prepareMapsNameColsArticolo()
{
    QMap <int,QString> magazzinoNameCols;

    magazzinoNameCols[0] = "Id";
    magazzinoNameCols[1] = "Descrizione";
    magazzinoNameCols[2] = "Fornitore";
    magazzinoNameCols[3] = "Marca";
    magazzinoNameCols[4] = "Modello";
    magazzinoNameCols[5] = "Cod.Articolo";
    magazzinoNameCols[6] = "Cod.Fornitore";
    magazzinoNameCols[7] = "Cod.EAN";
    magazzinoNameCols[8] = "Cat.Merce";
    magazzinoNameCols[9] = "Cod.IVA";
    magazzinoNameCols[10] = "UM";
    magazzinoNameCols[11] = "Scorta Minima";
    magazzinoNameCols[12] = QString::fromUtf8("Quantità");
    magazzinoNameCols[13] = "Prezzo Acquisto";
    magazzinoNameCols[14] = "Sconto";
    magazzinoNameCols[15] = "Ricarico";
    magazzinoNameCols[16] = "Imponibile";
    magazzinoNameCols[17] = "Iva";
    magazzinoNameCols[18] = "Prezzo Finito";
    magazzinoNameCols[19] = QString::fromUtf8("Prezzo Vendità");
    magazzinoNameCols[20] = "Nr.Fattura";
    magazzinoNameCols[21] = "Data Arrivo";
    magazzinoNameCols[22] = "Sede Magazzino";
    magazzinoNameCols[23] = "Note";

    return magazzinoNameCols;
}

QMap<int,QString> magazzino::prepareMapsNameColsStorico()
{
    QMap <int,QString> storicoNameCols;

    storicoNameCols[0] = "Id Articolo";
    storicoNameCols[1] = "Data";
    storicoNameCols[2] = QString::fromUtf8("Quantità");
    storicoNameCols[3] = "Prezzo acquisto";
    storicoNameCols[4] = "Sconto";
    storicoNameCols[5] = "Ricarico";
    storicoNameCols[6] = "Imponibile";
    storicoNameCols[7] = "IVA";
    storicoNameCols[8] = "Prezzo finito";
    storicoNameCols[9] = QString::fromUtf8("Vendità");
    storicoNameCols[10] = "Nr. Fattura";

    return storicoNameCols;
}


QMap<QString, int> magazzino::prepareMapsSizeColsArticolo(void)
{
    QMap <QString, int> magazzinoSizeCols;

    magazzinoSizeCols["Id"] = 100;
    magazzinoSizeCols["Descrizione"] = 300;
    magazzinoSizeCols["Fornitore"] = 200;
    magazzinoSizeCols["Marca"] = 200;
    magazzinoSizeCols["Modello"] = 200 ;
    magazzinoSizeCols["Cod.Articolo"] = 200;
    magazzinoSizeCols["Cod.Fornitore"] = 200;
    magazzinoSizeCols["Cod.EAN"] = 200;
    magazzinoSizeCols["Cat.Merce"] = 200;
    magazzinoSizeCols["Cod.IVA"] = 200;
    magazzinoSizeCols["UM"] = 100;
    magazzinoSizeCols["Scorta Minima"] = 100;
    magazzinoSizeCols[QString::fromUtf8("Quantità")] = 100;
    magazzinoSizeCols["Prezzo Acquisto"] = 100;
    magazzinoSizeCols["Sconto"] = 100;
    magazzinoSizeCols["Ricarico"] = 100;
    magazzinoSizeCols["Imponibile"] = 100;
    magazzinoSizeCols["Iva"] = 100;
    magazzinoSizeCols["Prezzo Finito"] = 100;
    magazzinoSizeCols[QString::fromUtf8("Prezzo Vendità")] = 200;
    magazzinoSizeCols["Nr.Fattura"] = 200;
    magazzinoSizeCols["Data Arrivo"] = 200;
    magazzinoSizeCols["Sede Magazzino"] = 200;
    magazzinoSizeCols["Note"] = 200;

    return magazzinoSizeCols;
}
