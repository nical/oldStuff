/*************************************************************************
                           Mat4  -  description
                             -------------------
    début                : 13 nov. 2009
    copyright            : (C) 2009 par nico
*************************************************************************/

//---------- Réalisation de la classe <Mat4> (fichier Mat4.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Mat4.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Mat4::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
Mat4 & Mat4::operator = ( const Mat4 & unMat4 )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Mat4::Mat4 ( const Mat4 & unMat4 )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Mat4>" << endl;
#endif
} //----- Fin de Mat4 (constructeur de copie)


Mat4::Mat4 ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Mat4>" << endl;
#endif
} //----- Fin de Mat4


Mat4::~Mat4 ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Mat4>" << endl;
#endif
} //----- Fin de ~Mat4


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
