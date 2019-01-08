#include "Lexical.h"
#include "Constantes.h"

using namespace std;

// Le constructeur hashe les mots clés
Lexical::Lexical()
{
    lexicalStream.open("./LexicalOutPut.txt");
    programme.open("./main.txt");
    for (int i = 0; i < 10; i++)
    {
        int pos = hashMotCle(listeMotsCle[i]);
        tableHachageMC[pos] = listeMotsCle[i];
    }
    nbLignes = 1;
    carEnAvance = lireCar();
}

char Lexical::lireCar()
{
    return programme.get();
    //return getc(stdin);
}

void Lexical::ajouterCar(string &lexeme)
{
    lexeme += carEnAvance;
}

bool Lexical::estBlanc(char c)
{
    if (c == '\n' || c == EOF)
    {
        nbLignes++;
        //cout<<nbLignes<<endl;
    }
    return (c == ' ') || (c == '\t') || (c == '\n') || (c == '\v');
}

bool Lexical::estLettre(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool Lexical::estChiffre(char c)
{
    return isdigit(c);
}

// Retourne l'unité lexicale suivante
TUniteLexicale Lexical::uniteSuivante()
{
    while (estBlanc(carEnAvance))
    {
        carEnAvance = lireCar();
    }

    /* Dès que notre caractère est différent de blanc, on étudie les cas possibles.
    On retourne le léxème correspondant et l'attribut dans chaque cas en suivant l'automate construit.
    */

    switch (carEnAvance)
    {
    case ',':
    {
        TUniteLexicale lexeme;
        lexeme.UL = VIRG;
        carEnAvance = lireCar();
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }
    case '+':
    {
        TUniteLexicale lexeme;
        lexeme.UL = PLUS;
        carEnAvance = lireCar();
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }
    case '-':
    {
        TUniteLexicale lexeme;
        lexeme.UL = MOINS;
        carEnAvance = lireCar();
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }
    case ';':
    {
        TUniteLexicale lexeme;
        lexeme.UL = SEP;
        carEnAvance = lireCar();
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }
    case '(':
    {
        TUniteLexicale lexeme;
        lexeme.UL = PAR_OUV;
        carEnAvance = lireCar();
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }
    case ')':
    {
        TUniteLexicale lexeme;
        lexeme.UL = PAR_FER;
        carEnAvance = lireCar();
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }
    case '[':
    {
        TUniteLexicale lexeme;
        lexeme.UL = CRO_OUV;
        carEnAvance = lireCar();
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }
    case ']':
    {
        TUniteLexicale lexeme;
        lexeme.UL = CRO_FER;
        carEnAvance = lireCar();
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }
    case '{':
    {
        TUniteLexicale lexeme;
        lexeme.UL = ACC_OUV;
        carEnAvance = lireCar();
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }
    case '}':
    {
        TUniteLexicale lexeme;
        lexeme.UL = ACC_FER;
        carEnAvance = lireCar();
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }
    case '!':
    {
        carEnAvance = lireCar();
        if (carEnAvance == '=')
        {
            TUniteLexicale lexeme;
            lexeme.UL = DIFF;
            carEnAvance = lireCar();
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
        else
        {
            TUniteLexicale lexeme;
            lexeme.UL = NON;

            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
    }
    case '/':
    {
        carEnAvance = lireCar();
        if (carEnAvance == '*')
        {
            TUniteLexicale lexeme;
            lexeme.UL = DEB_COM;
            carEnAvance = lireCar();
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
        else
        {
            TUniteLexicale lexeme;
            lexeme.UL = DIV;

            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
    }
    case '*':
    {
        carEnAvance = lireCar();
        if (carEnAvance == '/')
        {
            TUniteLexicale lexeme;
            lexeme.UL = FIN_COM;
            carEnAvance = lireCar();
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
        else
        {
            TUniteLexicale lexeme;
            lexeme.UL = MULT;

            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
    }
    case '&':
    {
        carEnAvance = lireCar();
        if (carEnAvance == '&')
        {
            TUniteLexicale lexeme;
            lexeme.UL = ET;
            carEnAvance = lireCar();
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
        else
        {
            TUniteLexicale lexeme;
            lexeme.UL = BIN_ET;

            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
    }
    case '|':
    {
        carEnAvance = lireCar();
        if (carEnAvance == '|')
        {
            TUniteLexicale lexeme;
            lexeme.UL = OU;
            carEnAvance = lireCar();
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
        else
        {
            TUniteLexicale lexeme;
            lexeme.UL = BIN_OU;

            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
    }
    case '=':
    {
        carEnAvance = lireCar();
        if (carEnAvance == '=')
        {
            TUniteLexicale lexeme;
            lexeme.UL = EGAL;
            carEnAvance = lireCar();
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
        else
        {
            TUniteLexicale lexeme;
            lexeme.UL = AFFEC;

            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
    }
    case '<':
    {
        carEnAvance = lireCar();
        if (carEnAvance == '<')
        {
            TUniteLexicale lexeme;
            lexeme.UL = DEC_DROITE;
            carEnAvance = lireCar();
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
        else if (carEnAvance == '=')
        {
            TUniteLexicale lexeme;
            lexeme.UL = INFEGAL;
            carEnAvance = lireCar();
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
        else
        {
            TUniteLexicale lexeme;
            lexeme.UL = INF;

            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
    }
    case '>':
    {
        carEnAvance = lireCar();
        if (carEnAvance == '>')
        {
            TUniteLexicale lexeme;
            lexeme.UL = DEC_GAUCHE;
            carEnAvance = lireCar();
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
        else if (carEnAvance == '=')
        {
            TUniteLexicale lexeme;
            lexeme.UL = SUPEGAL;
            carEnAvance = lireCar();
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
        else
        {
            TUniteLexicale lexeme;
            lexeme.UL = SUP;
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
    }
    case '_':
    {
        carEnAvance = lireCar();
        TUniteLexicale lexeme;
        lexeme.UL = ERREUR;
        lexeme.attribut = 1;
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }

    case '.':
    {
        carEnAvance = lireCar();
        TUniteLexicale lexeme;
        lexeme.UL = POINT;
        lexicalStream << afficherUL(lexeme) + "\n";
        return (lexeme);
    }

    case EOF:
    {
        TUniteLexicale lexeme;
        lexeme.UL = ENDOF;
        return (lexeme);
    }
    default:
    {
        // Cas des chiffres et des lettres
        string lexemeLu = "";
        if (estChiffre(carEnAvance))
        {
            while (estChiffre(carEnAvance))
            {
                ajouterCar(lexemeLu);
                carEnAvance = lireCar();
            }
            TUniteLexicale lexeme;
            lexeme.UL = CONST_INT;
            lexeme.attribut = convertirChaineValeurEntier(lexemeLu);
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
        else if (estLettre(carEnAvance))
        {
            while (estChiffre(carEnAvance) || estLettre(carEnAvance) || carEnAvance == '_')
            {
                ajouterCar(lexemeLu);
                carEnAvance = lireCar();
            }

            //Si le mot clé existe on retourne l'unité lexicale et son attribut.
            if (rechercheDansMotCle(lexemeLu) != -1)
            {

                TUniteLexicale lexeme;
                lexeme.UL = MOT_CLE;
                lexeme.attribut = rechercheDansMotCle(lexemeLu);
                lexicalStream << afficherUL(lexeme) + "\n";
                return (lexeme);
            }
            else
            {
                TUniteLexicale lexeme;
                lexeme.UL = IDENT;
                lexeme.attribut = rechercheAjoutDansListeIdentificateurs(lexemeLu);
                lexeme.positionConflit = tableHachageID[lexeme.attribut].size() - 1;
                lexicalStream << afficherUL(lexeme) + "\n";
                return (lexeme);
            }
        }
        else
        {
            carEnAvance = lireCar();
            TUniteLexicale lexeme;
            lexeme.UL = ERREUR;
            lexeme.attribut = 2;
            lexicalStream << afficherUL(lexeme) + "\n";
            return (lexeme);
        }
    }
    }
}

int Lexical::convertirChaineValeurEntier(string lexeme)
// Convertit la chaine fournie en entier en utilisant stoi.
{
    return stoi(lexeme);
}

int Lexical::hashMotCle(string s)
{
    // Hashing simple des mots clés
    int val = 0;
    for (int i = 0; i < s.size(); i++)
    {
        val += s[i] * (i + 1);
    }
    return val % 250;
}

/* Les polynômes sont utilisés pour hacher les chaînes de caractères afin de minimiser le nombre de collisions.
Nous pouvons choisir une constante non nulle, a != 1, et calculer le code de hashage.
Il s'agit simplement d'un polynôme dans a qui prend les composantes (x0,x1,...,xk-1) comme les caractères de la chaîne de longueur k.
La valeur de a est généralement un nombre premier.
Les expériences ont montré que les nombres premiers comme 33, 37, 39, et 41
sont des choix particulièrement bons pour a quand on travaille avec des chaînes de caractères qui sont des mots anglais.
En fait, sur une liste de plus de 50 000 mots en anglais, 33, 37, 39 ou 41 ont produit moins de 7 collisions dans chaque cas.
*/

int Lexical::hashIdent(string s)
{
    int val = 0;
    int p = 1;
    for (int i = 0; i < s.size(); i++)
    {
        val = (val + s[i] * p) % 100000;
        p = (p * 37) % 100000;
    }
    return val % 100000;
}

int Lexical::rechercheDansMotCle(string lexeme)
{
    //Recherche le mot clé fourni dans la table des mots clés hashés
    int pos = hashMotCle(lexeme);
    if (tableHachageMC[pos] == lexeme)
        return pos;
    return -1;
}

void Lexical::enMiniscule(string &s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

int Lexical::rechercheAjoutDansListeIdentificateurs(string lexeme)
{
    //On transforme le léxème en miniscule avant de commencer les traitements
    enMiniscule(lexeme);
    int pos = hashIdent(lexeme);
    bool IDExistant = false;
    //On parcourt la table des ident, si l'ident existe on retourne sa position.
    for (int i = 0; i < tableHachageID[pos].size(); i++)
    {
        if (tableHachageID[pos][i] == lexeme)
            IDExistant = true;
    }
    if (!IDExistant) // si l'ident n'existe pas on l'ajoute
    {
        tableHachageID[pos].push_back(lexeme);
    }
    return pos;
}

void Lexical::afficheTableHachageID()
{
    cout << "========== Table des identificateurs ==========" << endl;
    for (int i = 0; i < 100000; i++)
    {
        if (tableHachageID[i].size() > 0)
        {
            cout << "[";
            for (int j = 0; j < tableHachageID[i].size(); j++)
            {
                // Si on est à l'élément l'avant dernier du tableau, on complète par une virgule.
                if (j < tableHachageID[i].size() - 1)
                    cout << tableHachageID[i].at(j) << ", ";
                else
                {
                    cout << tableHachageID[i].at(j) << "] ";
                }
            }
            cout << "Hash: " << i << endl;
            cout << endl;
        }
    }
    cout << "======= Fin Table des identificateurs ==========" << endl;
}

string Lexical::getIdentificateur(int pos, int positionConflit)
{
    return tableHachageID[pos][positionConflit];
}

string Lexical::afficherUL(TUniteLexicale u)
{
    switch (u.UL)
    {
    case IDENT:
        return "(IDENT, " + to_string(u.attribut) + ", " + to_string(u.positionConflit) + ", " + this->getIdentificateur(u.attribut, u.positionConflit) + ")";
    case CONST_INT:
        return "(CONST_INT, " + to_string(u.attribut) + ")";
    case MOT_CLE:
        return "(MOT_CLE, " + to_string(u.attribut) + ")";
    case VIRG:
        return "VIRG";
    case NON:
        return "NON";
    case PLUS:
        return "PLUS";
    case MOINS:
        return "MOINS";
    case MULT:
        return "MULT";
    case DIV:
        return "DIV";
    case DEC_DROITE:
        return "DEC_DROITE";
    case DEC_GAUCHE:
        return "DEC_GAUCHE";
    case BIN_ET:
        return "BIN_ET";
    case BIN_OU:
        return "BIN_OU";
    case ET:
        return "ET";
    case OU:
        return "OU";
    case INF:
        return "INF";
    case SUP:
        return "SUP";
    case INFEGAL:
        return "INFEGAL";
    case SUPEGAL:
        return "SUPEGAL";
    case EGAL:
        return "EGAL";
    case DIFF:
        return "PAR_OUVR";
    case AFFEC:
        return "AFFEC";
    case SEP:
        return "SEP";
    case PAR_OUV:
        return "PAR_OUV";
    case PAR_FER:
        return "PAR_FER";
    case CRO_OUV:
        return "CRO_OUV";
    case CRO_FER:
        return "CRO_FER";
    case ACC_OUV:
        return "ACC_OUV";
    case ACC_FER:
        return "ACC_FER";
    case DEB_COM:
        return "DEB_COM";
    case FIN_COM:
        return "FIN_COM";
    case POINT:
        return "POINT";
    case ERREUR:
        return "(ERREUR, " + to_string(u.attribut) + ")";
    }
}

Lexical::~Lexical()
{
    lexicalStream.close();
    programme.close();
}
