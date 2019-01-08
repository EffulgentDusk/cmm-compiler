#include "Semantique.h"

#include <bits/stdc++.h>

using namespace std;

Semantique::Semantique()
{
    dansBlocFonction = false;
}

//Fonction qui affiche le contenu des différentes tables utilisées
void Semantique::afficherContenu()
{
    cout << "========================== Remarque ============================" << endl;
    cout << "Remarque : Les variables declarees localement dans les fonctions sont supprimes" << endl;
    cout << "de la table des structures et de la table des fonctions." << endl;
    cout << "Les variables locales ne seront pas affiches, mais elles sont stockes." << endl;
    cout << "Pour afficher les variables locales d'une fonction, inserer une erreur" << endl;
    cout << "avant la fin d'une fonction (pour arreter la compilation). Les variables locales seront affiches." << endl;

    cout << "========================== Table des Structures ============================" << endl;
    for (int i = 0; i < TableStructures.size(); i++)
    {
        cout << TableStructures[i].type << " ";
        TableStructures[i].estLocale ? cout << "-> La structure est locale " << endl : cout << " " << endl;
        cout << "Nombre d'attributs: " << TableStructures[i].listeAttributs.size() << endl;
        for (int j = 0; j < TableStructures[i].listeAttributs.size(); j++)
        {
            cout << TableStructures[i].listeAttributs[j].type << " ";
            cout << TableStructures[i].listeAttributs[j].nomIdent << " ";
            TableStructures[i].listeAttributs[j].tailleMaxTab != 0 ? cout << "-> TailleTab: " << TableStructures[i].listeAttributs[j].tailleMaxTab << endl : cout << " " << endl;
        }
        cout << endl;
    }

    cout << "========================== Table des Symboles ============================" << endl;
    for (int i = 0; i < TS.size(); i++)
    {
        cout << TS[i].type << " " << TS[i].nomIdent << " ";
        if (TS[i].tailleMaxTab != 0)
        {
            cout << "-> TailleTab: " << TS[i].tailleMaxTab;
        }
        else
        {
            cout << " ";
        }
        cout << " " << endl;
    }

    cout << "============================= Table des Fonctions ===========================" << endl;

    for (int i = 0; i < TableFonctions.size(); i++)
    {
        cout << "Fonction: " << TableFonctions[i].type << " ";
        cout << TableFonctions[i].identFonction << " ";
        cout << "Parametres (et variables locales s'ils existent): "
             << " ";

        for (int j = 0; j < TableFonctions[i].listeParametres.size(); j++)
        {
            cout << TableFonctions[i].listeParametres[j].type << " ";
            cout << TableFonctions[i].listeParametres[j].nomIdent << ", ";
            TableFonctions[i].listeParametres[j].tailleMaxTab != 0 ? cout << " TailleTab: " << TableFonctions[i].listeParametres[j].tailleMaxTab << " " : cout << " ";
        }
        cout << endl;
    }
}

/* Getteurs et setteurs */

string Semantique::getTypeCourant()
{
    return typeCourant;
}

void Semantique::setTypeCourant(string typeCourant)
{
    this->typeCourant = typeCourant;
}

bool Semantique::getdansBlocFonction()
{
    return dansBlocFonction;
}

void Semantique::setdansBlocFonction(bool dansBlocFonction)
{
    this->dansBlocFonction = dansBlocFonction;
}

string Semantique::getIdentVarCourante()
{
    return variableCourante.nomIdent;
}

string Semantique::getTypeVariableCourante()
{
    return variableCourante.type;
}

/// Structures ///

/* Stocke l'ident de la struct dans la table des structures */
void Semantique::stockerIdentStruct(Lexical &lex, TUniteLexicale &motCourant, bool estLocale)
{
    celluleTableStructures temp;
    temp.type = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    temp.estLocale = estLocale;
    TableStructures.push_back(temp);
}

bool Semantique::identStructDuplique()
{
    bool identDuplique = false;
    string ident = TableStructures[TableStructures.size() - 1].type;

    if (TableStructures.size() > 0)
    {
        /* On vérifie ici pas avant pour etre sur qu'on est dans une déclaration de struct pas une instanciation) */
        //Parcourt la TS des structures et verifie si l'identificateur courant existe deja (si la structure dupliquee)
        //Le der
        for (int i = 0; i < TableStructures.size() - 1; i++)
        {
            if (TableStructures[i].type == ident)
                identDuplique = true;
        }
    }
    if (identDuplique)
    {
        TableStructures.pop_back();
    }
    return identDuplique;
}

/* Stocke les attributs (de type int) de la struct courante */
void Semantique::stockerAttributsStruct(Lexical &lex, TUniteLexicale &motCourant)
{
    //Semantique
    celluleTS temp;
    temp.type = "int";
    temp.nomIdent = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    temp.tailleMaxTab = 0;
    /* Ajoute les attributs de la structure courante
     dans la Table des symboles des Struct */
    TableStructures[TableStructures.size() - 1].listeAttributs.push_back(temp);
}

/* Vérifie si les attributs de la struct courante sont dupliqués */
bool Semantique::attributStructDuplique(Lexical &lex, TUniteLexicale &motCourant)
{
    bool attributDuplique = false;

    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    int taille = TableStructures[TableStructures.size() - 1].listeAttributs.size();
    for (int i = 0; i < taille; i++)
    {
        if (TableStructures[TableStructures.size() - 1].listeAttributs[i].nomIdent == ident)
            attributDuplique = true;
    }
    return attributDuplique;
}

bool Semantique::attributStructExiste(Lexical &lex, TUniteLexicale &motCourant)
{
    bool attributExiste = false;
    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    for (int i = 0; i < TableStructures.size(); i++)
    {
        if (TableStructures[i].type == getTypeVariableCourante())
        {
            for (int j = 0; j < TableStructures[i].listeAttributs.size(); j++)
            {
                if (TableStructures[i].listeAttributs[j].nomIdent == ident)
                {
                    attributExiste = true;
                    variableCourante = TableStructures[i].listeAttributs[j];
                }
            }
        }
    }
    return attributExiste;
}

string Semantique::getTypeAttributStruct()
{
    return variableCourante.type;
}

/* Change le type et la taille de l'attribut de la struct courante */
void Semantique::changeTypeTailleAttributStruct(TUniteLexicale &motCourant)
{
    int taille = TableStructures[TableStructures.size() - 1].listeAttributs.size() - 1;
    TableStructures[TableStructures.size() - 1].listeAttributs[taille].type = "int_tableau";
    TableStructures[TableStructures.size() - 1].listeAttributs[taille].tailleMaxTab = motCourant.attribut;
}

/* Vérifier qu'une structure instanciée a été déclarée */
bool Semantique::structDeclaree()
{
    string ident = TableStructures[TableStructures.size() - 1].type;
    bool estDeclare = false; //Flag qui detecte la declaration

    if (TableStructures.size() > 0)
    {
        //Parcourt la TS des structures et verifie si l'identificateur courant existe dans cette table, donc si la structure a ete declaree
        for (int i = 0; i < TableStructures.size() - 1; i++)
        {
            if (TableStructures[i].type == ident)
                estDeclare = true;
        }
    }
    return estDeclare;
}

void Semantique::stockerIdentStructTS(Lexical &lex, TUniteLexicale &motCourant)
{
    string ident = TableStructures[TableStructures.size() - 1].type;
    celluleTS temp;
    temp.type = ident;
    temp.nomIdent = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    temp.tailleMaxTab = 0;
    TS.push_back(temp);
}

void Semantique::eliminerStruct()
{
    TableStructures.pop_back(); //On elimine le dernier identificateur stocke parce qu'il est deje stocke (voir blocStruct)
}

/// Variables ///

void Semantique::stockerIdentTS(Lexical &lex, TUniteLexicale &motCourant)
{
    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    celluleTS temp;

    temp.type = "int";
    temp.nomIdent = ident;
    temp.tailleMaxTab = 0;
    TS.push_back(temp);
}

void Semantique::stockerIdentTS(TUniteLexicale &motCourant, Lexical &lex)
{
    string type = TS[TS.size() - 1].type;

    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    celluleTS temp;
    temp.type = type;
    temp.nomIdent = ident;
    temp.tailleMaxTab = 0;
    TS.push_back(temp);
}

bool Semantique::identDuplique(Lexical &lex, TUniteLexicale &motCourant)
{
    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);

    bool identDuplique = false;
    // On verifie que l'identificateur n'est pas duplique
    for (int i = 0; i < TS.size(); i++)
    {
        if (TS[i].nomIdent == ident)
            identDuplique = true;
    }
    return identDuplique;
}

void Semantique::changeTypeTailleVariable(TUniteLexicale &motCourant)
{
    TS[TS.size() - 1].type = "int_tableau";
    TS[TS.size() - 1].tailleMaxTab = motCourant.attribut;
}

void Semantique::eliminerVariable()
{
    TS.pop_back(); //On elimine le dernier identificateur stocke de la TS parce qu'il est deje stocke
}

/// Fonctions ///

/* Ajoute l'identificateur de la fonction dans la TS*/
void Semantique::stockerIdentFonction(Lexical &lex, TUniteLexicale &motCourant, string typeFonction)
{
    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    celluleTableFonctions tempFonction;
    tempFonction.type = typeFonction;
    tempFonction.identFonction = ident;
    TableFonctions.push_back(tempFonction);
}

/* Ajoute les parametres de la fonctions dans la Table des fonctions */
void Semantique::stockerParamsFonction(Lexical &lex, TUniteLexicale &motCourant)
{
    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    celluleTS temp;
    temp.nomIdent = ident;
    temp.type = "int";
    temp.tailleMaxTab = 0;

    TableFonctions[TableFonctions.size() - 1].listeParametres.push_back(temp);
}

/* Verifie que les identificateurs ne sont pas dupliques */
bool Semantique::identFonctionDuplique(Lexical &lex, TUniteLexicale &motCourant)
{
    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    bool fonctionDuplique = false;

    for (int i = 0; i < TS.size(); i++)
    {
        if (TS[i].nomIdent == ident)
            fonctionDuplique = true;
    }
    for (int i = 0; i < TableFonctions.size(); i++)
    {
        if (TableFonctions[i].identFonction == ident)
            fonctionDuplique = true;
    }
    return fonctionDuplique;
}

void Semantique::eliminerFonction()
{
    TableFonctions.pop_back(); //On elimine le dernier identificateur stocke de la Table des fonctions parce qu'il est deje stocke
}

/* Vérifie si un parametre d'une fonction est duplique */
bool Semantique::paramFonctionDuplique(Lexical &lex, TUniteLexicale &motCourant)
{
    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    bool parametreDuplique = false;
    for (int i = 0; i < TableFonctions[TableFonctions.size() - 1].listeParametres.size(); i++)
    {
        if (TableFonctions[TableFonctions.size() - 1].listeParametres[i].nomIdent == ident)
            parametreDuplique = true;
    }
    return parametreDuplique;
}

void Semantique::destructeurLocalFonction()
{

    int i = TableStructures.size() - 1;
    while (i >= 0)
    {
        if (TableStructures[i].estLocale)
        {
            TableStructures.pop_back();
        }

        i--;
    }

    //On elimine tous apres avoir quitte la fonction (sauf les parametres)

    i = TableFonctions[TableFonctions.size() - 1].listeParametres.size() - 1;
    while (i >= 0)
    {
        if (TableFonctions[TableFonctions.size() - 1].listeParametres[i].type != "int")
            TableFonctions[TableFonctions.size() - 1].listeParametres.pop_back();
        i--;
    }
}

/// Variables locales dans les fonctions ///

void Semantique::stockerVariableLocale(Lexical &lex, TUniteLexicale &motCourant)
{
    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    celluleTS temp;

    temp.type = "int_fonction";
    temp.nomIdent = ident;
    temp.tailleMaxTab = 0;
    //On stocke la variable locale dans la listedesParametres
    TableFonctions[TableFonctions.size() - 1].listeParametres.push_back(temp);
}

void Semantique::stockerStructLocale(Lexical &lex, TUniteLexicale &motCourant)
{
    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);
    celluleTS temp;

    temp.type = TableStructures[TableStructures.size() - 1].type;
    ;
    temp.nomIdent = ident;
    temp.tailleMaxTab = 0;
    //On stocke la struct locale dans la listedesParametres
    TableFonctions[TableFonctions.size() - 1].listeParametres.push_back(temp);
}

void Semantique::changeTypeTailleVariableLocale(TUniteLexicale &motCourant)
{
    int taille = TableFonctions[TableFonctions.size() - 1].listeParametres.size() - 1;

    TableFonctions[TableFonctions.size() - 1].listeParametres[taille].type = "int_tableau_fonction";
    TableFonctions[TableFonctions.size() - 1].listeParametres[taille].tailleMaxTab = motCourant.attribut;
}

/* Verifie que les variables manipulées sont déclarées (globalement ou localement) */
bool Semantique::identExiste(Lexical &lex, TUniteLexicale &motCourant)
{
    string ident = lex.getIdentificateur(motCourant.attribut, motCourant.positionConflit);

    bool identExiste = false;

    //Verification dans la table des symboles
    for (int i = 0; i < TS.size(); i++)
    {
        if (TS[i].nomIdent == ident)
        {
            identExiste = true;
            variableCourante = TS[i];
        }
    }

    //On donne la priorité aux déclarations locales
    for (int i = 0; i < TableFonctions[TableFonctions.size() - 1].listeParametres.size(); i++)
    {
        if (TableFonctions[TableFonctions.size() - 1].listeParametres[i].nomIdent == ident)
        {
            identExiste = true;
            variableCourante = TableFonctions[TableFonctions.size() - 1].listeParametres[i];
        }
    }

    //Verification dans la table des fonctions
    for (int i = 0; i < TableFonctions.size(); i++)
    {
        if (TableFonctions[i].identFonction == ident)
            identExiste = true;
    }

    return identExiste;
}
