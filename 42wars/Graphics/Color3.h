/*************************************************************************
                           Color3  -  description
                             -------------------
    début                : 21 nov. 2009
    copyright            : (C) 2009 par nico
*************************************************************************/

//---------- Interface de la classe <Color3> (fichier Color3.h) ------
#ifndef COLOR3_H_
#define COLOR3_H_

//--------------------------------------------------- Interfaces utilisées
#include <GL/gl.h>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef GLdouble ColorComponent;
//------------------------------------------------------------------------
// Rôle de la classe <Color3>
//
//
//------------------------------------------------------------------------

class Color3
{
//----------------------------------------------------------------- PUBLIC
public:
ColorComponent GetR();
ColorComponent GetG();
ColorComponent GetB();
ColorComponent GetR255();
ColorComponent GetG255();
ColorComponent GetB255();
ColorComponent SetR(ColorComponent ar);
ColorComponent SetG(ColorComponent ag);
ColorComponent SetB(ColorComponent ab);
void DbgPrintContent();

//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    Color3 & operator = ( const Color3 & color);

//-------------------------------------------- Constructeurs - destructeur
    Color3 ( const Color3 & color );

    Color3 (ColorComponent ar = 1.0, ColorComponent ag = 1.0, ColorComponent ab = 1.0 );

    virtual ~Color3 ( );


protected:
//----------------------------------------------------- Attributs protégés
	ColorComponent r;
	ColorComponent g;
	ColorComponent b;
};

//--------------------------- Autres définitions dépendantes de <Color3>

#endif // COLOR3_H_
