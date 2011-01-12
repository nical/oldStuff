/*************************************************************************
                           Vect  -  description
                             -------------------
    début                : 13 nov. 2009
    copyright            : (C) 2009 par nico
*************************************************************************/

//---------- Réalisation de la classe <Vect> (fichier Vect.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <math.h>
//------------------------------------------------------ Include personnel
#include "Vect.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Vect::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
GLdouble Vect3::GetNorm() {return sqrt(x*x + y*y + z*z);}
GLdouble Vect3::GetSquaredNorm() {return (x*x + y*y + z*z);}

void Vect3::Normalize()
	{
		GLdouble m = GetNorm();
	    x = x/m;
	    y = y/m;
	    z = z/m;

	}

//------------------------------------------------- Surcharge d'opérateurs
Vect3 & Vect3::operator = ( const Vect3 & v )
{
	x=v.x;
	y=v.y;
	z=v.z;
	return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Vect3::Vect3 ( const Vect3 & v )
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Vect3>" << endl;
#endif
    x = v.x;
    y = v.y;
    z = v.z;
} //----- Fin de Vect (constructeur de copie)


Vect3::Vect3 (GLdouble ax, GLdouble ay, GLdouble az )
{
#ifdef MAP
    cout << "Appel au constructeur de <Vect3>" << endl;
#endif
	x = ax;
	y = ay;
	z = az;
}


Vect3::~Vect3 ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Vect>" << endl;
#endif
} //----- Fin de ~Vect


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
