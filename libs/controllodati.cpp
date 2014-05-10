#include "controllodati.h"

bool controlloPartitaIva(QString s)
{
    qDebug() << "controlloPartitaIva()";
    //La partita iva ha una lunghezza di 11 cifre
    if (s.length() != LENGHT_PAR_IVA) {
        return false;
    }

    //Tutti i caratteri della partita iva sono cifre
    for (int i=0; i<LENGHT_PAR_IVA; i++) {
        if (s[i].isLetter())
            return false;
    }

    //Somma delle Cifre dispari
    int x=0;
    for (int i=0; i<LENGHT_PAR_IVA-1; i+=2) {
        x += s[i].digitValue();
    }

    //Somma delle Cifre pari
    int y=0;
    for (int i=1; i<LENGHT_PAR_IVA-1; i+=2) {
        int a = s[i].digitValue()*2;
        if (a>9)
            a-=9;
        y+=a;
    }

    //Controllo se qualche simpaticone a messo tutti 0 -.-
    if (x==0 && y==0) {
        return false;
    }

    //Leggiti wikipedia e non rompere i coglioni -.-
    int controldigit = (10-((x+y)%10))%10;

    return controldigit == s[CHECKDIGIT_PIVA].digitValue();
}

bool controlloCodiceFiscale(QString s)
{
    qDebug() << "controlloCodiceFiscale()";
    //Il codice fiscale ha una lunghezza di 16 cifre
    if (s.length() != LENGHT_COD_FISCALE) {
        return false;
    }

    QHash <QChar, int> c_pari; //tabella conversione cifre pari
    c_pari['0'] = 0;  c_pari['1'] = 1;  c_pari['2'] = 2;  c_pari['3'] = 3;
    c_pari['4'] = 4;  c_pari['5'] = 5;  c_pari['6'] = 6;  c_pari['7'] = 7;
    c_pari['8'] = 8;  c_pari['9'] = 9;  c_pari['A'] = 0;  c_pari['B'] = 1;
    c_pari['C'] = 2;  c_pari['D'] = 3;  c_pari['E'] = 4;  c_pari['F'] = 5;
    c_pari['G'] = 6;  c_pari['H'] = 7;  c_pari['I'] = 8;  c_pari['J'] = 9;
    c_pari['K'] = 10; c_pari['L'] = 11; c_pari['M'] = 12; c_pari['N'] = 13;
    c_pari['O'] = 14; c_pari['P'] = 15; c_pari['Q'] = 16; c_pari['R'] = 17;
    c_pari['S'] = 18; c_pari['T'] = 19; c_pari['U'] = 20; c_pari['V'] = 21;
    c_pari['W'] = 22; c_pari['X'] = 23; c_pari['Y'] = 24; c_pari['Z'] = 25;

    QHash <QChar, int> c_disp; //tabella conversione cifre dispari
    c_disp['0'] = 1;  c_disp['1'] = 0;  c_disp['2'] = 5;  c_disp['3'] = 7;
    c_disp['4'] = 9;  c_disp['5'] = 13; c_disp['6'] = 15; c_disp['7'] = 17;
    c_disp['8'] = 19; c_disp['9'] = 21; c_disp['A'] = 1;  c_disp['B'] = 0;
    c_disp['C'] = 5;  c_disp['D'] = 7;  c_disp['E'] = 9;  c_disp['F'] = 13;
    c_disp['G'] = 15; c_disp['H'] = 17; c_disp['I'] = 19; c_disp['J'] = 21;
    c_disp['K'] = 2;  c_disp['L'] = 4;  c_disp['M'] = 18; c_disp['N'] = 20;
    c_disp['O'] = 11; c_disp['P'] = 3;  c_disp['Q'] = 6;  c_disp['R'] = 8;
    c_disp['S'] = 12; c_disp['T'] = 14; c_disp['U'] = 16; c_disp['V'] = 10;
    c_disp['W'] = 22; c_disp['X'] = 25; c_disp['Y'] = 24; c_disp['Z'] = 23;

    QHash <int, QChar> c_check; //tabella conversione cifra di controllo
    c_check[0] = 'A';  c_check[1] = 'B';  c_check[2] = 'C';  c_check[3] = 'D';
    c_check[4] = 'E';  c_check[5] = 'F';  c_check[6] = 'G';  c_check[7] = 'H';
    c_check[8] = 'I';  c_check[9] = 'J';  c_check[10] = 'K'; c_check[11] = 'L';
    c_check[12] = 'M'; c_check[13] = 'N'; c_check[14] = 'O'; c_check[15] = 'P';
    c_check[16] = 'Q'; c_check[17] = 'R'; c_check[18] = 'S'; c_check[19] = 'T';
    c_check[20] = 'U'; c_check[21] = 'V'; c_check[22] = 'W'; c_check[23] = 'X';
    c_check[24] = 'Y'; c_check[25] = 'Z';

    int x=0;
    for (int i=0; i<LENGHT_COD_FISCALE-1; i+=2) {
        x += c_disp[s[i].toUpper()];
    }

    int y=0;
    for (int i=1; i<LENGHT_COD_FISCALE-1; i+=2) {
        y += c_pari[s[i].toUpper()];
    }

    //Algoritmo
    //Somma le cifre pari convertendole con la tabella per le cifre pari
    //Somma le cifre dispari convertendole con la tabella per le cifre dispari
    //Somma il totale delle cifre pari a quelle dispari
    //Converti il resto della somme per 26 e controlla l'ultima cifra del codice fiscale
    return c_check[(x+y)%26] == s[CHECKDIGIT_CF].toUpper();
}
