#ifndef SYNTAXIQUE_H_INCLUDED
#define SYNTAXIQUE_H_INCLUDED

#include "Semantique.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

class Syntaxique
{
  public:
    Syntaxique();
    bool affectation();
    bool programme();
    bool blocStruct();
    bool blocStructPrime();
    bool programmePrime();
    bool programmeSeconde();
    bool programmeTierce();
    bool listeParams();
    bool listeParamsPrime();
    bool declaration();
    bool declarationPrime();
    bool declarateurPrime();
    bool listeDeclarations();
    bool listeDeclarateurs();
    bool listeDeclarateursPrime();
    bool listeDeclarateursStruct();
    bool listeDeclarationsPrime();
    bool listeInstructions();
    bool instruction();
    bool listeInstructionsPrime();
    bool listeFonctions();
    bool listeFonctionsPrime();
    bool declarateur();
    bool fonction();
    bool parametre();
    bool instructionPrime();
    bool type();
    bool iteration();
    bool selection();
    bool selectionPrime();
    bool saut();
    bool listeExpressionsPrime();
    bool sautPrime();
    bool bloc();
    bool variable();
    bool variablePrime();
    bool expression();
    bool expressionPrime();
    bool expressionSeconde();
    bool expressionTierce();
    bool listeExpressions();
    bool condition();
    bool conditionPrime();
    bool structure();
    bool listeAttributs();
    bool listeAttributsPrime();
    bool binaryOp();
    bool binaryRel();
    bool binaryComp();
    Semantique seman;

  private:
    TUniteLexicale motCourant;
    Lexical lex;
};

#endif // SYNTAXIQUE_H_INCLUDED
