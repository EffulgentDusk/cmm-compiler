#ifndef SEMANTIQUE_H
#define SEMANTIQUE_H

#include "Structures.h"
#include "Lexical.h"

class Semantique
{
public:
  Semantique();
  void afficherContenu();
  string getTypeCourant();
  void setTypeCourant(string typeCourant);
  bool getdansBlocFonction();
  void setdansBlocFonction(bool);

  /* Variable Courante */
  string getTypeVariableCourante();
  string getIdentVarCourante();

  /* Structures */
  void stockerAttributsStruct(Lexical &, TUniteLexicale &);
  void stockerIdentStruct(Lexical &, TUniteLexicale &, bool);
  bool identStructDuplique();
  bool attributStructDuplique(Lexical &, TUniteLexicale &);
  bool attributStructExiste(Lexical &, TUniteLexicale &);
  string getTypeAttributStruct();
  void changeTypeTailleAttributStruct(TUniteLexicale &);
  bool structDeclaree();
  void stockerIdentStructTS(Lexical &, TUniteLexicale &);
  void eliminerStruct();

  /* Variables de type int */
  void stockerIdentTS(Lexical &lex, TUniteLexicale &motCourant);
  void stockerIdentTS(TUniteLexicale &motCourant, Lexical &lex);
  bool identDuplique(Lexical &lex, TUniteLexicale &motCourant);
  void changeTypeTailleVariable(TUniteLexicale &);
  void eliminerVariable();

  /* Fonctions */
  void stockerIdentFonction(Lexical &, TUniteLexicale &, string);
  void stockerParamsFonction(Lexical &, TUniteLexicale &);
  bool identFonctionDuplique(Lexical &, TUniteLexicale &);
  bool paramFonctionDuplique(Lexical &, TUniteLexicale &);
  void eliminerFonction();

  /* Variables locales dans fonctions */
  void stockerVariableLocale(Lexical &, TUniteLexicale &);
  bool identExiste(Lexical &, TUniteLexicale &);
  void stockerStructLocale(Lexical &, TUniteLexicale &);
  void changeTypeTailleVariableLocale(TUniteLexicale &);
  void destructeurLocalFonction();

private:
  bool dansBlocFonction;
  string typeCourant;
  celluleTS variableCourante;
  vector<celluleTableStructures> TableStructures;
  vector<celluleTS> TS;
  vector<celluleTableFonctions> TableFonctions;
};

#endif // SEMANTIQUE_H
