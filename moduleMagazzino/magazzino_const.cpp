#include "magazzinowindow.h"

QMap<int,QString> magazzino::prepareMapsNameColsArticolo()
{
    qDebug() << "magazzino::prepareMapsNameColsArticolo()";
    QMap <int,QString> magazzinoNameCols;

    magazzinoNameCols[COL_MG_ID] = CMP_ID;              //Id
    magazzinoNameCols[COL_MG_DESCR] = CMP_DESCR;        //Descrizione;
    magazzinoNameCols[COL_MG_ID_FORN] = CMP_FORNIT;     //Fornitore;
    magazzinoNameCols[COL_MG_ID_MARCA] = CMP_MARCA;     //Marca;
    magazzinoNameCols[COL_MG_MODELLO] = CMP_MODELLO;    //Modello;
    magazzinoNameCols[COL_MG_COD_ART] = CMP_COD_ART;    //Cod.Articolo;
    magazzinoNameCols[COL_MG_COD_FOR] = CMP_COD_FOR;    //Cod.Fornitore;
    magazzinoNameCols[COL_MG_COD_EAN] = CMP_COD_EAN;    //Cod.EAN;
    magazzinoNameCols[COL_MG_ID_MERCE] = CMP_MERCE;     //Cat.Merce;
    magazzinoNameCols[COL_MG_COD_IVA] = CMP_COD_IVA; //Cod.IVA;
    magazzinoNameCols[COL_MG_ID_UM] = CMP_UM;           //UM;
    magazzinoNameCols[COL_MG_SCORTA] = CMP_SCORTA;      //Scorta Minima;
    magazzinoNameCols[COL_MG_QT] = CMP_QT;              //Quantita;
    magazzinoNameCols[COL_MG_PRZ_FAT] = CMP_PRZ_FAT;    //Prezzo Fattura;
    magazzinoNameCols[COL_MG_SCONTO] = CMP_SCONTO;      //Sconto;
    magazzinoNameCols[COL_MG_RICARICO] = CMP_RICAR;     //Ricarico;
    magazzinoNameCols[COL_MG_PRZ_ACQ] = CMP_PRZ_ACQ;    //Prezzo Acquisto;
    magazzinoNameCols[COL_MG_IVA] = CMP_IVA;            //Iva;
    magazzinoNameCols[COL_MG_PRZ_FIN] = CMP_PRZ_FIN;    //Prezzo Finito;
    magazzinoNameCols[COL_MG_PRZ_VEN] = CMP_PRZ_VEN;    //Prezzo Vendita;
    magazzinoNameCols[COL_MG_FATTURA] = CMP_FATTURA;    //Nr.Fattura;
    magazzinoNameCols[COL_MG_DATA] = CMP_DATA;          //Data Arrivo;
    magazzinoNameCols[COL_MG_ID_SEDE] = CMP_SEDE;       //Sede Magazzino";
    magazzinoNameCols[COL_MG_NOTE] = CMP_NOTE;          //Note

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
