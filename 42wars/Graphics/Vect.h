/*************************************************************************
                           Vect  -  description
                             -------------------
    début                : 13 nov. 2009
    copyright            : (C) 2009 par nico
*************************************************************************/

//---------- Interface de la classe <Vect> (fichier Vect.h) ------
#ifndef VECT_H_
#define VECT_H_


#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Vect3 -----
//    This class is a classic 3-dimmensionnal vector not fully encapsulated
// for practical purposes
//------------------------------------------------------------------------

class Vect3
{
//----------------------------------------------------------------- PUBLIC

public:
//------------------------ ----------------------------- Méthodes publiques
    GLdouble x, y, z; // I do know it's not right to put public members but considering the
						//uses of that class, doing otherwise would be a great pain in the
						//ass!
	GLdouble GetNorm();		//returns the norm. note that it uses a square root
	GLdouble GetSquaredNorm(); //much faster id the exact value of the norm is not needed
	void Normalize();	//transform the vector so that it's norm is 1.0, keeping the direction
	Vect3 UnitVector(); //returns a normalized version of the vector without altering it

//------------------------------------------------- Surcharge d'opérateurs
    Vect3 & operator = ( const Vect3 & v );


//-------------------------------------------- Constructeurs - destructeur
    Vect3 ( const Vect3 & v );
    // Mode d'emploi (constructeur de copie) :
    Vect3 ( GLdouble ax = 0, GLdouble ay = 0, GLdouble az = 0 );


    virtual ~Vect3 ( );
    // Mode d'emploi :

};

class Vect2
{
public:
	GLdouble x,y;
};

class Vect3int
{
public:
	GLint a,b,c;
};

#endif // VECT_H_

