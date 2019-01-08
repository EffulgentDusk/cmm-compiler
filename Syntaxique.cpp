#include "Lexical.h"
#include "Syntaxique.h"
#include "string.h"

Syntaxique::Syntaxique() : lex(), seman()
{
    //On stocke l'unité suivante retournée par le lexical, dans motCourant
    motCourant = lex.uniteSuivante();
}

bool Syntaxique::programme()
{
    return programmePrime();
}

bool Syntaxique::blocStruct()
{
    if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("struct"))
    {
        seman.setTypeCourant("struct");
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            seman.stockerIdentStruct(lex, motCourant, seman.getdansBlocFonction());
            motCourant = lex.uniteSuivante();
            return blocStructPrime();
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: identificateur attendu dans blocStruct" << endl;
            return false;
        }
    }
    else if (motCourant.UL == MOT_CLE && (motCourant.attribut == lex.hashMotCle("int") ||
                                          motCourant.attribut == lex.hashMotCle("extern") ||
                                          motCourant.attribut == lex.hashMotCle("void")))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Syntaxique::blocStructPrime()
{
    if (motCourant.UL == IDENT || motCourant.UL == ACC_OUV)
    {
        if (declarationPrime())
        {
            return blocStruct();
        }
        else
        {
            return false;
        }
    }
    else
    {
        cout << "**********************************" << endl
             << "Ligne : " << lex.getNbLignes() << endl
             << "Erreur: identificateur ou { non reconnue dans blocStruct" << endl;
        return false;
    }
}

bool Syntaxique::declarationPrime()
{
    if (motCourant.UL == IDENT)
    {
        if (seman.structDeclaree())
        {
            if (!seman.identDuplique(lex, motCourant))
            {
                if (seman.getdansBlocFonction())
                {
                    seman.stockerStructLocale(lex, motCourant);
                }
                else
                {
                    seman.stockerIdentStructTS(lex, motCourant);
                }

                seman.eliminerStruct();
                motCourant = lex.uniteSuivante();
                if (listeDeclarateursStruct())
                {

                    if (motCourant.UL == SEP)
                    {
                        motCourant = lex.uniteSuivante();
                        return true;
                    }
                    else
                    {
                        cout << "**********************************" << endl
                             << "Ligne : " << lex.getNbLignes() << endl
                             << "Erreur: ; attendu dans declarationPrime" << endl;
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: identificateur duplique" << endl;
                return false;
            }
        }
        else
        {
            seman.eliminerStruct();
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: la structure n'est pas declaree" << endl;
            return false;
        }
    }
    else if (motCourant.UL == ACC_OUV)
    {
        motCourant = lex.uniteSuivante();

        if (!seman.identStructDuplique())
        {
            if (listeAttributs())
            {
                if (motCourant.UL == ACC_FER)
                {
                    motCourant = lex.uniteSuivante();
                    if (motCourant.UL == SEP)
                    {
                        motCourant = lex.uniteSuivante();
                        return true;
                    }
                    else
                    {
                        cout << "**********************************" << endl
                             << "Ligne : " << lex.getNbLignes() << endl
                             << "Erreur: ; attendu dans declarationPrime" << endl;
                        return false;
                    }
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: } attendu dans declarationPrime" << endl;
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            cout << "Le nom de la structure existe deja" << endl;
            return false;
        }
        cout << "Le nom de la structure existe deja" << endl;
        return false;
    }
    else
    {
        return false;
    }
}

bool Syntaxique::listeDeclarateursStruct()
{
    if (motCourant.UL == VIRG)
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            if (!seman.identDuplique(lex, motCourant))
            {
                seman.stockerIdentTS(motCourant, lex);
                motCourant = lex.uniteSuivante();
                return listeDeclarateursStruct();
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: identificateur duplique" << endl;
                return false;
            }
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: identificateur attendu dans listeDeclarateursStruct" << endl;
            return false;
        }
    }
    else
    {
        return true;
    }
}

bool Syntaxique::structure()
{
    if (motCourant.UL == IDENT)
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == ACC_OUV)
        {
            motCourant = lex.uniteSuivante();
            if (listeAttributs()) // Mot en avance
            {
                if (motCourant.UL == ACC_FER)
                {
                    motCourant = lex.uniteSuivante();
                    if (motCourant.UL == SEP)
                    {
                        motCourant = lex.uniteSuivante();
                        return true;
                    }
                    else
                    {
                        cout << "**********************************" << endl
                             << "Ligne : " << lex.getNbLignes() << endl
                             << "Erreur: ; attendu dans structure" << endl;
                        return false;
                    }
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: } attendu dans structure" << endl;
                    return false;
                }
            }
            else // Erreur: liste d'attribut false
                return false;
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: ; attendu dans listeAttributs" << endl;
            return false;
        }
    }
    else // Erreur: identificateur incorrect
    {
        return false;
    }
}

bool Syntaxique::listeAttributs()
{
    if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("int"))
    {
        motCourant = lex.uniteSuivante();
        if (declarateur())
        {
            if (motCourant.UL == SEP)
            {
                motCourant = lex.uniteSuivante();
                return listeAttributsPrime();
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: ; attendu dans listeAttributs" << endl;
                return false;
            }
        }
        else // gestion erreur au sein de la fct declarateur
        {
            return false;
        }
    }
    else
    {
        cout << "**********************************" << endl
             << "Ligne : " << lex.getNbLignes() << endl
             << "Erreur: mot clé non reconnu" << endl;
        return false;
    }
}

bool Syntaxique::listeAttributsPrime()
{
    if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("int"))
    {
        motCourant = lex.uniteSuivante();
        if (declarateur())
        {
            if (motCourant.UL == SEP)
            {
                motCourant = lex.uniteSuivante();
                return listeAttributsPrime();
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: ; attendu dans listeAttributsPrime" << endl;
                return false;
            }
        }
        else // gestion erreur au sein de la fct declarateur
        {
            return false;
        }
    }
    else // epsilon
    {
        return true;
    }
}

bool Syntaxique::declarateur()
{
    if (motCourant.UL == IDENT)
    {
        if (seman.getTypeCourant() == "struct")
        {
            if (!seman.attributStructDuplique(lex, motCourant))
            {
                seman.stockerAttributsStruct(lex, motCourant);
                motCourant = lex.uniteSuivante();
                return declarateurPrime();
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: attribut de la structure duplique" << endl;
                return false;
            }
        }
        //Si on n'est pas dans blocFonction
        else if (seman.getTypeCourant() == "int")
        {
            if (!seman.getdansBlocFonction())
            {
                if (!seman.identDuplique(lex, motCourant))
                {

                    seman.stockerIdentTS(lex, motCourant);
                    motCourant = lex.uniteSuivante();
                    return declarateurPrime();
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: identificateur duplique" << endl;
                    return false;
                }
            }
            //Si on est dans blocFonction
            else
            {
                if (!seman.paramFonctionDuplique(lex, motCourant))
                {
                    seman.stockerVariableLocale(lex, motCourant);
                    motCourant = lex.uniteSuivante();
                    return declarateurPrime();
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: identificateur duplique" << endl;
                    return false;
                }
            }
        }
    }
    else // Erreur: identificateur incorrect
    {
        return false;
    }
}

bool Syntaxique::declarateurPrime()
{
    if (motCourant.UL == CRO_OUV)
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == CONST_INT)
        {
            if (seman.getTypeCourant() == "struct")
            {
                seman.changeTypeTailleAttributStruct(motCourant);
            }
            else if (seman.getTypeCourant() == "int")
            {
                if (seman.getdansBlocFonction())
                {
                    seman.changeTypeTailleVariableLocale(motCourant);
                }
                else
                {
                    seman.changeTypeTailleVariable(motCourant);
                }
            }
            motCourant = lex.uniteSuivante();
            if (motCourant.UL == CRO_FER)
            {
                motCourant = lex.uniteSuivante();
                return true;
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: ; attendu dans declarateurPrime" << endl;
                return false;
            }
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: constante incorrecte" << endl;
            return false;
        }
    }
    else // epsilon
    {
        return true;
    }
}

bool Syntaxique::programmePrime()
{
    if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("int"))
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            if (!seman.identFonctionDuplique(lex, motCourant))
            {
                seman.setTypeCourant("int");
                seman.stockerIdentTS(lex, motCourant);

                seman.stockerIdentFonction(lex, motCourant, "int");
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: identificateur duplique" << endl;
                return false;
            }
            motCourant = lex.uniteSuivante();
            return programmeSeconde();
        }
        else // Erreur: identifiant incorrect
            return false;
    }
    else if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("extern"))
    {
        seman.setdansBlocFonction(true);
        motCourant = lex.uniteSuivante();
        return programmeTierce();
    }
    else if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("void"))
    {
        seman.setdansBlocFonction(true);
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            seman.setTypeCourant("int");

            if (!seman.identFonctionDuplique(lex, motCourant))
            {
                seman.stockerIdentFonction(lex, motCourant, "void");
                motCourant = lex.uniteSuivante();
                if (motCourant.UL == PAR_OUV)
                {
                    motCourant = lex.uniteSuivante();
                    if (listeParams())
                    {
                        if (motCourant.UL == PAR_FER)
                        {
                            motCourant = lex.uniteSuivante();
                            if (motCourant.UL == ACC_OUV)
                            {
                                motCourant = lex.uniteSuivante();
                                if (listeDeclarations())
                                {
                                    if (listeInstructions())
                                    {
                                        if (motCourant.UL == ACC_FER)
                                        {
                                            seman.destructeurLocalFonction();
                                            motCourant = lex.uniteSuivante();
                                            return listeFonctionsPrime();
                                        }
                                        else
                                        {
                                            cout << "**********************************" << endl
                                                 << "Ligne : " << lex.getNbLignes() << endl
                                                 << "Erreur: } attendu dans programmePrime" << endl;
                                            return false;
                                        }
                                    }
                                    else // Erreur: liste instructions
                                    {
                                        return false;
                                    }
                                }
                                else // Erreur: liste Parametres
                                {
                                    return false;
                                }
                            }
                            else
                            {
                                cout << "**********************************" << endl
                                     << "Ligne : " << lex.getNbLignes() << endl
                                     << "Erreur: { attendu dans programmePrime" << endl;
                                return false;
                            }
                        }
                        else
                        {
                            cout << "**********************************" << endl
                                 << "Ligne : " << lex.getNbLignes() << endl
                                 << "Erreur: ) attendu dans programmePrime" << endl;
                            return false;
                        }
                    }
                    else // erreur listeParams
                    {
                        return false;
                    }
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: ( attendu dans programmePrime" << endl;
                    return false;
                }
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: identificateur duplique" << endl;
                return false;
            }
        }
        else // Erreur: identificateur incorrect
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: identificateur attendu dans programmePrime" << endl;
            return false;
        }
    }

    else if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("struct"))
    {
        if (blocStruct())
        {
            return programmePrime();
        }
        else
        {
            return false;
        }
    }
    else // erreur programmePrime
    {
        return false;
    }
}

bool Syntaxique::programmeSeconde()
{
    if (motCourant.UL == PAR_OUV)
    {
        seman.setdansBlocFonction(true);
        seman.eliminerVariable();
        motCourant = lex.uniteSuivante();
        if (listeParams())
        {
            if (motCourant.UL == PAR_FER)
            {
                motCourant = lex.uniteSuivante();
                if (motCourant.UL == ACC_OUV)
                {
                    motCourant = lex.uniteSuivante();
                    if (listeDeclarations())
                    {
                        if (listeInstructions())
                        {
                            if (motCourant.UL == ACC_FER)
                            {
                                seman.destructeurLocalFonction();
                                motCourant = lex.uniteSuivante();
                                return listeFonctionsPrime();
                            }
                            else
                            {
                                cout << "**********************************" << endl
                                     << "Ligne : " << lex.getNbLignes() << endl
                                     << "Erreur: } attendu dans programmeSeconde" << endl;
                                return false;
                            }
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: { attendu dans programmeSeconde" << endl;
                    return false;
                }
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: ) attendu dans programmeSeconde" << endl;
            }
            seman.setTypeCourant("int");
        }
        else
        {
            return false;
        }
    }
    else if (declarateurPrime())
    {
        seman.eliminerFonction();
        if (listeDeclarateursPrime())
        {
            if (motCourant.UL == SEP)
            {
                motCourant = lex.uniteSuivante();
                return programmePrime();
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: ; attendu dans programmeSeconde" << endl;
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Syntaxique::programmeTierce()
{
    if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("void"))
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            if (!seman.identFonctionDuplique(lex, motCourant))
            {
                seman.stockerIdentFonction(lex, motCourant, "void");
                motCourant = lex.uniteSuivante();

                if (motCourant.UL == PAR_OUV)
                {
                    motCourant = lex.uniteSuivante();
                    if (listeParams())
                    {
                        if (motCourant.UL == PAR_FER)
                        {
                            motCourant = lex.uniteSuivante();
                            if (motCourant.UL == SEP)
                            {
                                motCourant = lex.uniteSuivante();
                                return listeFonctionsPrime();
                            }
                            else
                            {
                                cout << "**********************************" << endl
                                     << "Ligne : " << lex.getNbLignes() << endl
                                     << "Erreur: ; attendu dans programmeTierce" << endl;
                                return false;
                            }
                        }
                        else
                        {
                            cout << "**********************************" << endl
                                 << "Ligne : " << lex.getNbLignes() << endl
                                 << "Erreur: ) attendu dans programmeTierce" << endl;
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: ( attendu dans programmeTierce" << endl;
                    return false;
                }
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: identificateur duplique" << endl;
                return false;
            }
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: indentificateur attendu dans programmeTierce" << endl;
            return false;
        }
    }

    else if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("int"))
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            if (!seman.identFonctionDuplique(lex, motCourant))
            {
                seman.stockerIdentFonction(lex, motCourant, "int");
                motCourant = lex.uniteSuivante();
                if (motCourant.UL == PAR_OUV)
                {
                    motCourant = lex.uniteSuivante();
                    if (listeParams())
                    {
                        if (motCourant.UL == PAR_FER)
                        {
                            motCourant = lex.uniteSuivante();
                            if (motCourant.UL == SEP)
                            {
                                motCourant = lex.uniteSuivante();
                                return listeFonctionsPrime();
                            }
                            else
                            {
                                cout << "**********************************" << endl
                                     << "Ligne : " << lex.getNbLignes() << endl
                                     << "Erreur: ; attendu dans programmeTierce" << endl;
                                return false;
                            }
                        }
                        else
                        {
                            cout << "**********************************" << endl
                                 << "Ligne : " << lex.getNbLignes() << endl
                                 << "Erreur: ) attendu dans programmeTierce" << endl;
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: ( attendu dans programmeTierce" << endl;
                    return false;
                }
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: identificateur duplique" << endl;
                return false;
            }
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: indentificateur attendu dans programmeTierce" << endl;
            return false;
        }
    }
    else
    {
        return false;
        seman.setTypeCourant("int");
    }
}

bool Syntaxique::listeParams()
{
    if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("int"))
    {

        if (parametre())
        {
            return listeParamsPrime();
        }
        else
            return false;
    }
    else
    {
        return true;
    }
}

bool Syntaxique::listeParamsPrime()
{
    if (motCourant.UL == VIRG)
    {
        motCourant = lex.uniteSuivante();
        if (parametre())
        {
            return listeParamsPrime();
        }
        else
            return false;
    }
    else
        return true;
}

bool Syntaxique::parametre()
{
    if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("int"))
    {
        //Ergonomie : pop la fct qui a des params dupliqués?
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            if (!seman.paramFonctionDuplique(lex, motCourant))
            {
                seman.stockerParamsFonction(lex, motCourant);
                motCourant = lex.uniteSuivante();
                return true;
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: parametre duplique" << endl;
                return false;
            }
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: identificateur attendu parametre" << endl;
            return false;
        }
    }
    else
    {
        cout << "**********************************" << endl
             << "Ligne : " << lex.getNbLignes() << endl
             << "Erreur: int attendu dans parametre" << endl;
        return false;
    }
}

bool Syntaxique::declaration()
{
    if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("int"))
    {
        seman.setTypeCourant("int");

        motCourant = lex.uniteSuivante();
        if (listeDeclarateurs())
        {
            if (motCourant.UL == SEP)
            {
                motCourant = lex.uniteSuivante();
                return true;
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: ; attendu dans declaration" << endl;
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("struct"))
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            seman.setTypeCourant("struct");
            seman.stockerIdentStruct(lex, motCourant, seman.getdansBlocFonction());
            motCourant = lex.uniteSuivante();
            return declarationPrime();
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: identificateur attendu dans declaration" << endl;
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Syntaxique::listeDeclarations()
{
    if (motCourant.UL == MOT_CLE && (motCourant.attribut == lex.hashMotCle("int") ||
                                     motCourant.attribut == lex.hashMotCle("struct")))
    {
        if (declaration())
        {
            return listeDeclarations();
        }
        else
            return false;
    }
    else
        return true;
}

bool Syntaxique::listeInstructions()
{
    if ((motCourant.UL == MOT_CLE && (motCourant.attribut == lex.hashMotCle("for") ||
                                      motCourant.attribut == lex.hashMotCle("while") ||
                                      motCourant.attribut == lex.hashMotCle("if") ||
                                      motCourant.attribut == lex.hashMotCle("return"))) ||
        motCourant.UL == IDENT ||
        motCourant.UL == ACC_OUV)
    {
        if (instruction())
        {
            return listeInstructions();
        }
        else
            return false;
    }
    return true;
}

bool Syntaxique::instruction()
{
    if (motCourant.UL == MOT_CLE && (motCourant.attribut == lex.hashMotCle("for") || motCourant.attribut == lex.hashMotCle("while")))
    {
        //Pas d'avncement : deux types d'iterations
        return iteration();
    }
    else if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("if"))
    {
        motCourant = lex.uniteSuivante();
        return selection();
    }
    else if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("return"))

    {
        motCourant = lex.uniteSuivante();
        return saut();
    }
    else if (motCourant.UL == ACC_OUV)
    {
        motCourant = lex.uniteSuivante();
        return bloc();
    }
    else if (motCourant.UL == IDENT)
    {
        if (seman.identExiste(lex, motCourant))
        {
            motCourant = lex.uniteSuivante();
            return instructionPrime();
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: variable manipulee sans etre declaree" << endl;
            return false;
        }
    }
    else
        return false;
}

bool Syntaxique::iteration()
{
    if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("for"))
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == PAR_OUV)
        {
            motCourant = lex.uniteSuivante();
            if (affectation())
            {
                if (motCourant.UL == SEP)
                {
                    motCourant = lex.uniteSuivante();
                    if (condition())
                    {
                        if (motCourant.UL == SEP)
                        {
                            motCourant = lex.uniteSuivante();
                            if (affectation())
                            {
                                if (motCourant.UL == PAR_FER)
                                {
                                    motCourant = lex.uniteSuivante();
                                    if (instruction())
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                }
                                else
                                {
                                    cout << "**********************************" << endl
                                         << "Ligne : " << lex.getNbLignes() << endl
                                         << "Erreur: ) attendu dans iteration" << endl;
                                    return false;
                                }
                            }
                            else
                            {
                                return false;
                            }
                        }
                        else
                        {
                            cout << "**********************************" << endl
                                 << "Ligne : " << lex.getNbLignes() << endl
                                 << "Erreur: ; attendu dans iteration" << endl;
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: ; attendu dans iteration" << endl;
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: ( attendu dans iteration" << endl;
            return false;
        }
    }
    else if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("while"))
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == PAR_OUV)
        {
            motCourant = lex.uniteSuivante();
            if (condition())
            {
                if (motCourant.UL == PAR_FER)
                {
                    motCourant = lex.uniteSuivante();
                    return instruction();
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: ) attendu dans iteration" << endl;
                    return false;
                }
            }
            else
                return false;
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: ( attendu dans iteration" << endl;
            return false;
        }
    }
    else
        return false;
}

bool Syntaxique::saut()
{
    return sautPrime();
}

bool Syntaxique::sautPrime()
{
    if (expression())
    {
        if (motCourant.UL == SEP)
        {
            motCourant = lex.uniteSuivante();
            return true;
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: ; attendu dans sautprime" << endl;
            return false;
        }
    }
    else if (motCourant.UL == SEP)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else
        return false;
}

bool Syntaxique::selection()
{
    if (motCourant.UL == PAR_OUV)
    {
        motCourant = lex.uniteSuivante();
        if (condition())
        {
            if (motCourant.UL == PAR_FER)
            {
                motCourant = lex.uniteSuivante();
                if (instruction())
                {
                    return selectionPrime();
                }
                else
                {
                    return false;
                }
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: ) attendu dans selection" << endl;
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        cout << "**********************************" << endl
             << "Ligne : " << lex.getNbLignes() << endl
             << "Erreur: ( attendu dans selection" << endl;
        return false;
    }
}

bool Syntaxique::selectionPrime()
{
    if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("else"))
    {
        motCourant = lex.uniteSuivante();
        return instruction();
    }
    else //epsilon
    {
        return true;
    }
}

bool Syntaxique::listeDeclarateurs()
{
    if (declarateur())
    {
        return listeDeclarateursPrime();
    }
    else
        return false;
}

bool Syntaxique::listeDeclarateursPrime()
{
    if (motCourant.UL == VIRG)
    {
        motCourant = lex.uniteSuivante();
        if (declarateur())
        {
            return listeDeclarateursPrime();
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool Syntaxique::bloc()
{
    if (listeInstructions())
    {
        if (motCourant.UL == ACC_FER)
        {
            motCourant = lex.uniteSuivante();
            return true;
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: } attendu dans bloc" << endl;
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Syntaxique::instructionPrime()
{
    if (motCourant.UL == CRO_OUV)
    {
        if (seman.getTypeVariableCourante() == "int_tableau" || seman.getTypeVariableCourante() == "int_tableau_fonction")
        {
            motCourant = lex.uniteSuivante();
            if (expression())
            {
                if (motCourant.UL == CRO_FER)
                {
                    motCourant = lex.uniteSuivante();
                    if (motCourant.UL == AFFEC)
                    {
                        motCourant = lex.uniteSuivante();
                        if (expression())
                        {
                            if (motCourant.UL == SEP)
                            {
                                motCourant = lex.uniteSuivante();
                                return true;
                            }
                            else
                            {
                                cout << "**********************************" << endl
                                     << "Ligne : " << lex.getNbLignes() << endl
                                     << "Erreur: ; attendu dans instruction prime" << endl;
                                return false;
                            }
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        cout << "**********************************" << endl
                             << "Ligne : " << lex.getNbLignes() << endl
                             << "Erreur: = attendu dans instruction prime" << endl;
                        return false;
                    }
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: ] attendu dans instruction prime " << endl;
                    return false;
                }
            }
            else
                return false;
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: affectation de types incompatibles" << endl;
            return false;
        }
    }
    else if (motCourant.UL == PAR_OUV)
    {
        motCourant = lex.uniteSuivante();
        if (listeExpressions())
        {
            if (motCourant.UL == PAR_FER)
            {
                motCourant = lex.uniteSuivante();
                if (motCourant.UL == SEP)
                {
                    motCourant = lex.uniteSuivante();
                    return true;
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: ; attendu dans instruction prime" << endl;
                    return false;
                }
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: ) attendu dans instruction prime" << endl;
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if (motCourant.UL == POINT)
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            //Vérification que les attributs appelés existent
            if (seman.attributStructExiste(lex, motCourant))
            {
                motCourant = lex.uniteSuivante();
                if (motCourant.UL == CRO_OUV)
                {
                    //Si on manipule des tableaux, ça marche
                    if (seman.getTypeAttributStruct() == "int_tableau" || seman.getTypeAttributStruct() == "int_tableau_fonction")
                    {
                        motCourant = lex.uniteSuivante();
                        if (expression())
                        {
                            if (motCourant.UL == CRO_FER)
                            {
                                motCourant = lex.uniteSuivante();
                                if (motCourant.UL == AFFEC)
                                {
                                    motCourant = lex.uniteSuivante();
                                    if (expression())
                                    {
                                        if (motCourant.UL == SEP)
                                        {
                                            motCourant = lex.uniteSuivante();
                                            return true;
                                        }
                                        else
                                        {
                                            cout << "**********************************" << endl
                                                 << "Ligne : " << lex.getNbLignes() << endl
                                                 << "Erreur: ; attendu dans instruction prime" << endl;
                                            return false;
                                        }
                                    }
                                    else
                                        return false;
                                }
                                else
                                {
                                    cout << "**********************************" << endl
                                         << "Ligne : " << lex.getNbLignes() << endl
                                         << "Erreur: = attendue dans instruction prime" << endl;
                                    return false;
                                }
                            }
                            else
                            {
                                cout << "**********************************" << endl
                                     << "Ligne : " << lex.getNbLignes() << endl
                                     << "Erreur: ] attendue dans instruction prime" << endl;
                                return false;
                            }
                        }
                        else
                        {
                            return false;
                        }
                    }
                    //Si on manipule pas des tableaux, erreur
                    else
                    {
                        cout << "**********************************" << endl
                             << "Ligne : " << lex.getNbLignes() << endl
                             << "Erreur: affectation de types incompatibles" << endl;
                        return false;
                    }
                }
                else
                {
                    if (motCourant.UL == AFFEC)
                    {
                        if (seman.getTypeAttributStruct() == "int" || seman.getTypeAttributStruct() == "int_fonction")
                        {
                            motCourant = lex.uniteSuivante();
                            if (expression())
                            {
                                if (motCourant.UL == SEP)
                                {
                                    motCourant = lex.uniteSuivante();
                                    return true;
                                }
                                else
                                {
                                    cout << "**********************************" << endl
                                         << "Ligne : " << lex.getNbLignes() << endl
                                         << "Erreur: ; attendu dans instruction prime" << endl;
                                    return false;
                                }
                            }
                            else
                            {
                                return false;
                            }
                        }
                        else
                        {
                            cout << "**********************************" << endl
                                 << "Ligne : " << lex.getNbLignes() << endl
                                 << "Erreur: affectation de types incompatibles" << endl;
                            return false;
                        }
                    }
                    else
                    {
                        cout << "**********************************" << endl
                             << "Ligne : " << lex.getNbLignes() << endl
                             << "Erreur: = attendue dans instruction prime" << endl;
                        return false;
                    }
                }
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: l'attribut manipule est inexistant" << endl;
                return false;
            }
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: identificateur attendu dans instruction prime" << endl;
            return false;
        }
    }
    else if (motCourant.UL == AFFEC)
    {
        if (seman.getTypeVariableCourante() == "int" || seman.getTypeVariableCourante() == "int_fonction")
        {
            motCourant = lex.uniteSuivante();
            if (expression())
            {
                if (motCourant.UL == SEP)
                {
                    motCourant = lex.uniteSuivante();
                    return true;
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: ; attendu dans instruction prime" << endl;
                    return false;
                }
            }
            else
                return false;
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: affectation de types incompatibles" << endl;
            return false;
        }
    }
    else
    {
        return false;
    }
}
bool Syntaxique::affectation()
{
    if (variable())
    {
        if (motCourant.UL == AFFEC)
        {
            motCourant = lex.uniteSuivante();
            return expression();
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: = attendu dans affectation" << endl;
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Syntaxique::variable()
{
    if (motCourant.UL == IDENT)
    {
        //On vérifie qu'une variable affectée a été déclarée
        //Changer le nom vers identexisteDeja
        if (seman.identExiste(lex, motCourant))
        {
            motCourant = lex.uniteSuivante();
            return variablePrime();
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: variable manipulee sans etre declaree" << endl;
            return false;
        }
    }
    else
        return false;
}

bool Syntaxique::variablePrime()
{
    if (motCourant.UL == CRO_OUV)
    {

        motCourant = lex.uniteSuivante();
        if (expression())
        {
            if (motCourant.UL == CRO_FER)
            {
                motCourant = lex.uniteSuivante();
                return true;
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: ] attendu dans variablePrime" << endl;
                return false;
            }
        }
        else
            return false;
    }
    else if (motCourant.UL == POINT)
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            motCourant = lex.uniteSuivante();
            return true;
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: Identificateur attendu dans variblePrime" << endl;
            return false;
        }
    }
    else
        return true;
}

bool Syntaxique::condition()
{
    if (motCourant.UL == NON)
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == PAR_OUV)
        {
            motCourant = lex.uniteSuivante();
            if (condition())
            {
                if (motCourant.UL == PAR_FER)
                {
                    motCourant = lex.uniteSuivante();
                    return conditionPrime();
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: ) attendue dans condition" << endl;
                    return false;
                }
            }
            return false;
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: ( attendue dans condition" << endl;
            return false;
        }
    }
    else if (motCourant.UL == PAR_OUV)
    {
        motCourant = lex.uniteSuivante();
        if (condition())
        {
            if (motCourant.UL == PAR_FER)
            {
                motCourant = lex.uniteSuivante();
                return conditionPrime();
            }
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: ) attendue dans condition" << endl;
            return false;
        }

        else
        {
            return false;
        }
    }

    else if (expression())
    {
        if (binaryComp())
        {
            if (expression())
            {
                return conditionPrime();
            }
            else
            {
                return false;
            }
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: binaryComp attendue dans condition" << endl;
            return false;
        }
    }

    else
    {
        return false;
    }
}

bool Syntaxique::conditionPrime()
{
    if (binaryRel())
    {
        if (condition())
        {
            return conditionPrime();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

bool Syntaxique::binaryOp()
{
    if (motCourant.UL == PLUS)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == MOINS)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == MULT)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == DIV)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == DEC_DROITE)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == DEC_GAUCHE)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == BIN_ET)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == BIN_OU)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else
    {
        return false;
    }
}

bool Syntaxique::binaryRel()
{
    if (motCourant.UL == ET)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == OU)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else
    {
        return false;
    }
}

bool Syntaxique::binaryComp()
{
    if (motCourant.UL == INF)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == SUP)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == SUPEGAL)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == INFEGAL)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == EGAL)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == DIFF)
    {
        motCourant = lex.uniteSuivante();
        return true;
    }
    else
    {
        return false;
    }
}

bool Syntaxique::listeExpressions()
{
    if (motCourant.UL == PAR_OUV || motCourant.UL == MOINS || motCourant.UL == IDENT || motCourant.UL == CONST_INT)
    {
        if (expression())
        {
            return listeExpressionsPrime();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

bool Syntaxique::listeExpressionsPrime()
{
    if (motCourant.UL == VIRG)
    {
        motCourant = lex.uniteSuivante();
        if (expression())
        {
            return listeExpressionsPrime();
        }
        else
        {
            return false;
        }
    }
    else
        return true;
}

bool Syntaxique::listeFonctions()
{
    if (fonction())
    {
        motCourant = lex.uniteSuivante();
        return listeFonctionsPrime();
    }
    else
    {
        return false;
    }
}

bool Syntaxique::listeFonctionsPrime()
{
    if (motCourant.UL == MOT_CLE && (motCourant.attribut == lex.hashMotCle("int") || motCourant.attribut == lex.hashMotCle("void") || motCourant.attribut == lex.hashMotCle("extern")))
    {
        if (fonction())
        {
            return listeFonctionsPrime();
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: fonction mal definit" << endl;
            return false;
        }
    }
    else if (motCourant.UL == ENDOF)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Syntaxique::fonction()
{
    if (type())
    {
        if (motCourant.UL == IDENT)
        {
            if (!seman.identFonctionDuplique(lex, motCourant))
            {
                seman.stockerIdentFonction(lex, motCourant, seman.getTypeCourant());

                motCourant = lex.uniteSuivante();
                if (motCourant.UL == PAR_OUV)
                {
                    motCourant = lex.uniteSuivante();
                    if (listeParams())
                    {
                        if (motCourant.UL == PAR_FER)
                        {
                            motCourant = lex.uniteSuivante();
                            if (motCourant.UL == ACC_OUV)
                            {
                                motCourant = lex.uniteSuivante();
                                if (listeDeclarations())
                                {
                                    if (listeInstructions())
                                    {
                                        if (motCourant.UL == ACC_FER)
                                        {
                                            seman.destructeurLocalFonction();
                                            motCourant = lex.uniteSuivante();
                                            return true;
                                        }
                                        else
                                        {
                                            cout << "**********************************" << endl
                                                 << "Ligne : " << lex.getNbLignes() << endl
                                                 << "Erreur: } attendue dans fonction" << endl;
                                            return false;
                                        }
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                }
                                else
                                {
                                    return false;
                                }
                            }
                            else
                            {
                                cout << "**********************************" << endl
                                     << "Ligne : " << lex.getNbLignes() << endl
                                     << "Erreur: { attendue dans fonction" << endl;
                                return false;
                            }
                        }
                        else
                        {
                            cout << "**********************************" << endl
                                 << "Ligne : " << lex.getNbLignes() << endl
                                 << "Erreur: ) attendue dans fonction" << endl;
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: ( attendue dans fonction" << endl;
                    return false;
                }
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: identificateur de fonction duplique" << endl;
                return false;
            }
        }
        else
        {
            //pop_back()?
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: identificateur attendu dans fonction" << endl;
            return false;
        }
    }

    else if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("extern"))
    {
        motCourant = lex.uniteSuivante();
        if (type())
        {
            if (motCourant.UL == IDENT)
            {
                if (!seman.identFonctionDuplique(lex, motCourant))
                {
                    seman.stockerIdentFonction(lex, motCourant, seman.getTypeCourant());
                    motCourant = lex.uniteSuivante();
                    if (motCourant.UL == PAR_OUV)
                    {
                        motCourant = lex.uniteSuivante();
                        if (listeParams())
                        {
                            if (motCourant.UL == PAR_FER)
                            {
                                motCourant = lex.uniteSuivante();
                                if (motCourant.UL == SEP)
                                {
                                    motCourant = lex.uniteSuivante();
                                    return true;
                                }
                                else
                                {
                                    cout << "**********************************" << endl
                                         << "Ligne : " << lex.getNbLignes() << endl
                                         << "Erreur: ; attendu dans fonction" << endl;
                                    return false;
                                }
                            }
                            else
                            {
                                cout << "**********************************" << endl
                                     << "Ligne : " << lex.getNbLignes() << endl
                                     << "Erreur: ) attendu dans fonction" << endl;
                                return false;
                            }
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        cout << "**********************************" << endl
                             << "Ligne : " << lex.getNbLignes() << endl
                             << "Erreur: ( attendu dans fonction" << endl;
                        return false;
                    }
                }
                else
                {
                    //pop.back()?
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: l'identificateur d'une fonction est duplique" << endl;
                    return false;
                }
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: identificateur attendu dans fonction" << endl;
                return false;
            }
        }
    }

    else
    {
        return false;
    }
}

bool Syntaxique::type()
{
    if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("void"))
    {
        seman.setTypeCourant("void");
        motCourant = lex.uniteSuivante();
        return true;
    }
    else if (motCourant.UL == MOT_CLE && motCourant.attribut == lex.hashMotCle("int"))
    {
        seman.setTypeCourant("int");
        motCourant = lex.uniteSuivante();
        return true;
    }

    else
    {
        return false;
    }
}

bool Syntaxique::expression()
{
    if (motCourant.UL == PAR_OUV)
    {
        motCourant = lex.uniteSuivante();
        if (expression())
        {
            if (motCourant.UL == PAR_FER)
            {
                motCourant = lex.uniteSuivante();
                return expressionSeconde();
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: ) attendu dans expression" << endl;
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if (motCourant.UL == IDENT)
    {
        if (seman.identExiste(lex, motCourant))
        {
            motCourant = lex.uniteSuivante();
            if (expressionPrime())
            {
                return expressionSeconde();
            }
            else
            {
                return false;
            }
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: la variable n'est pas declaree" << endl;
            return false;
        }
    }
    else if (motCourant.UL == CONST_INT)
    {
        motCourant = lex.uniteSuivante();
        return expressionSeconde();
    }

    else if (motCourant.UL == MOINS)
    {
        motCourant = lex.uniteSuivante();
        return expression();
    }

    else
    {
        return false;
    }
}

bool Syntaxique::expressionPrime()
{
    if (motCourant.UL == CRO_OUV)
    {
        if (seman.getTypeVariableCourante() == "int_tableau" || seman.getTypeVariableCourante() == "int_tableau_fonction")
        {
            motCourant = lex.uniteSuivante();
            if (expression())
            {
                if (motCourant.UL == CRO_FER)
                {
                    motCourant = lex.uniteSuivante();
                    return true;
                }
                else
                {
                    cout << "**********************************" << endl
                         << "Ligne : " << lex.getNbLignes() << endl
                         << "Erreur: ] attendu dans expression" << endl;
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: affectation de types incompatibles" << endl;
            return false;
        }
    }
    else if (motCourant.UL == POINT)
    {
        motCourant = lex.uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            if (seman.attributStructExiste(lex, motCourant))
            {
                motCourant = lex.uniteSuivante();
                if (motCourant.UL == CRO_OUV)
                {
                    if (seman.getTypeAttributStruct() == "int_tableau" || seman.getTypeAttributStruct() == "int_tableau_fonction")
                    {
                        motCourant = lex.uniteSuivante();
                        if (expression())
                        {
                            if (motCourant.UL == CRO_FER)
                            {
                                motCourant = lex.uniteSuivante();
                                return true;
                            }
                            else
                            {
                                cout << "**********************************" << endl
                                     << "Ligne : " << lex.getNbLignes() << endl
                                     << "Erreur: ] attendue dans instruction prime" << endl;
                                return false;
                            }
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        cout << "**********************************" << endl
                             << "Ligne : " << lex.getNbLignes() << endl
                             << "Erreur: affectation de types incompatibles" << endl;
                        return false;
                    }
                }
                else
                {
                    if (seman.getTypeAttributStruct() == "int" || seman.getTypeAttributStruct() == "int_fonction")
                    {
                        return true;
                    }
                    else
                    {
                        cout << "**********************************" << endl
                             << "Ligne : " << lex.getNbLignes() << endl
                             << "Erreur: affectation de types incompatibles" << endl;
                        return false;
                    }
                }
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: attribut manipule non existant" << endl;
            }
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: identificateur attendu dans expression" << endl;
            return false;
        }
    }
    else if (motCourant.UL == PAR_OUV)
    {
        motCourant = lex.uniteSuivante();
        if (listeExpressions())
        {
            if (motCourant.UL == PAR_FER)
            {
                motCourant = lex.uniteSuivante();
                return true;
            }
            else
            {
                cout << "**********************************" << endl
                     << "Ligne : " << lex.getNbLignes() << endl
                     << "Erreur: ) attendu dans expression" << endl;
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (seman.getTypeVariableCourante() == "int" || seman.getTypeVariableCourante() == "int_fonction")
        {
            return true;
        }
        else
        {
            cout << "**********************************" << endl
                 << "Ligne : " << lex.getNbLignes() << endl
                 << "Erreur: affectation de types incompatibles" << endl;
            return false;
        }
    }
}

bool Syntaxique::expressionSeconde()
{
    if (binaryOp())
    {
        return expression();
    }
    return true;
}
