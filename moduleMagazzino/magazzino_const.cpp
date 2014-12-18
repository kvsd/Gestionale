#include "magazzinowindow.h"

QMap<int,QString> magazzino::prepareMapsNameColsArticolo()
{
    qDebug() << "magazzino::prepareMapsNameColsArticolo()";
    QMap <int,QString> magazzinoNameCols;

    magazzinoNameCols[0] = CMP_ID;         //Id
    magazzinoNameCols[1] = CMP_DESCR;      //Descrizione;
    magazzinoNameCols[2] = CMP_MODELLO;    //Modello;
    magazzinoNameCols[3] = CMP_COD_ART;    //Cod.Articolo;
    magazzinoNameCols[4] = CMP_COD_FOR;    //Cod.Fornitore;
    magazzinoNameCols[5] = CMP_COD_EAN;    //Cod.EAN;
    magazzinoNameCols[6] = CMP_COD_IVA;    //Cod.IVA;
    magazzinoNameCols[7] = CMP_SCORTA;     //Scorta Minima;
    magazzinoNameCols[8] = CMP_QT;         //Quantita;
    magazzinoNameCols[9] = CMP_PRZ_FAT;    //Prezzo Fattura;
    magazzinoNameCols[10] = CMP_SCONTO;    //Sconto;
    magazzinoNameCols[11] = CMP_RICAR;     //Ricarico;
    magazzinoNameCols[12] = CMP_PRZ_ACQ;   //Prezzo Acquisto;
    magazzinoNameCols[13] = CMP_IVA;       //Iva;
    magazzinoNameCols[14] = CMP_PRZ_FIN;   //Prezzo Finito;
    magazzinoNameCols[15] = CMP_PRZ_VEN;   //Prezzo Vendita;
    magazzinoNameCols[16] = CMP_FATTURA;   //Nr.Fattura;
    magazzinoNameCols[17] = CMP_DATA;      //Data Arrivo;
    magazzinoNameCols[18] = CMP_NOTE;      //Note

    return magazzinoNameCols;
}

QMap<int,QString> magazzino::prepareMapsNameColsStorico()
{
    qDebug() << "magazzino::prepareMapsNameColsStorico()";
    QMap <int,QString> storicoNameCols;

    storicoNameCols[COL_ST_ID_ARTICOLO] = CMP_ID_ART;   //Id Articolo
    storicoNameCols[COL_ST_DATA] = CMP_DATA;            //Data
    storicoNameCols[COL_ST_QT] = CMP_QT;                //Quantita
    storicoNameCols[COL_ST_PRZ_FAT] = CMP_PRZ_FAT;      //Prezzo Fattura
    storicoNameCols[COL_ST_SCONTO] = CMP_SCONTO;        //Sconto
    storicoNameCols[COL_ST_RICARICO] = CMP_RICAR;       //Ricarico
    storicoNameCols[COL_ST_PRZ_ACQ] = CMP_PRZ_ACQ;      //Prezzo Acquisto
    storicoNameCols[COL_ST_IVA] = CMP_IVA;              //IVA
    storicoNameCols[COL_ST_PRZ_FIN] = CMP_PRZ_FIN;      //Prezzo Finito
    storicoNameCols[COL_ST_PRZ_VEN] = CMP_PRZ_VEN;      //Prezzo Vendità
    storicoNameCols[COL_ST_FATTURA] = CMP_FATTURA;      //Nr. Fattura

    return storicoNameCols;
}
