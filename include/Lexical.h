#ifndef LEXICAL_H
#define LEXICAL_H

#include <bits/stdc++.h>
#include "Structures.h"
#include <iostream>
#include <fstream>

using namespace std;


class Lexical
{
private:
  string tableHachageMC[250];
  vector<string> tableHachageID[100000];
  char carEnAvance;
  int nbLignes;
  ofstream lexicalStream;
  fstream programme;

public:
  Lexical();                                                 //Constructeur de la classe
  TUniteLexicale uniteSuivante();                            //Utilisée par le lexical pour savoir l'unité lexicale suivante à lire
  char lireCar();                                            //Permet de lire un caractère
  void enMiniscule(string &s);                               //Transforme la chaine fournie en miniscule, car en C-- les identificateurs ne sont pas sensibles à la casse.
  void ajouterCar(string &lexeme);                           //Ajouter un caractère au léxème
  bool estBlanc(char c);                                     //Traite le cas où un caractère est blanc
  bool estLettre(char c);                                    //Traite le cas où le caractère est une lettre
  bool estChiffre(char c);                                   //Traite le cas où le caractère est un chiffre
  int convertirChaineValeurEntier(string lexeme);            //Convertit le lexème à sa valeur en entier
  int rechercheDansMotCle(string lexeme);                    //Convertit le lexème à sa valeur en entier
  int rechercheAjoutDansListeIdentificateurs(string lexeme); //Recherche le lexème donnée dans la liste des ident et l'ajoute s'il n'y existe pas
  int hashMotCle(string s);                                  //Hashe le mot clé fourni
  int hashIdent(string s);                                   // Hashe l'ident fourni
  void afficheTableHachageID();                              //Affiche la table de hachage des identificateurs avec un formattage agréable
  string getIdentificateur(int pos, int posConflit);
  string afficherUL(TUniteLexicale u);
  int getNbLignes(){return nbLignes;}
  ~Lexical();
};

#endif // LEXICAL_H
