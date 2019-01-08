#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <bits/stdc++.h>

using namespace std;

typedef enum
{
    IDENT,
    CONST_INT,
    MOT_CLE,
    VIRG,
    NON,
    PLUS,
    MOINS,
    MULT,
    DIV,
    DEC_DROITE,
    DEC_GAUCHE,
    BIN_ET,
    BIN_OU,
    ET,
    OU,
    INF,
    SUP,
    INFEGAL,
    SUPEGAL,
    EGAL,
    DIFF,
    AFFEC,
    SEP,
    PAR_OUV,
    PAR_FER,
    CRO_OUV,
    CRO_FER,
    ACC_OUV,
    ACC_FER,
    DEB_COM,
    FIN_COM,
    POINT,
    ERREUR,
    ENDOF
} TUnite;

typedef struct TUniteLexicale
{
    TUnite UL;
    int attribut;
    int positionConflit;
} TUniteLexicale;

/// S�mantique - Tables des Symboles globales ///

typedef struct celluleTS
{
    string type;
    string nomIdent;
    int tailleMaxTab;
} celluleTS;

typedef struct celluleTableStructures
{
    string type;
    bool estLocale;
    vector<celluleTS> listeAttributs;
} celluleTableStructures;

typedef struct celluleTableFonctions
{
    string type;
    string identFonction;
    vector<celluleTS> listeParametres;
} celluleTableFonctions;

#endif // STRUCTURES_H_INCLUDED
