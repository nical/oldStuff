/*************************************************************************
                           Mat4  -  description
                             -------------------
    début                : 13 nov. 2009
    copyright            : (C) 2009 par nico
*************************************************************************/

//---------- Interface de la classe <Mat4> (fichier Mat4.h) ------
#if ! defined ( MAT4_H_ )
#define MAT4_H_

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Mat4>
//
//
//------------------------------------------------------------------------

class Mat4
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    Mat4 & operator = ( const Mat4 & unMat4 );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Mat4 ( const Mat4 & unMat4 );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Mat4 ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Mat4 ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <Mat4>

#endif // MAT4_H_
