/*************************************************************************
                           Texture  -  description
                             -------------------
    début                : 24 nov. 2009
    copyright            : (C) 2009 par nico
 *************************************************************************/

//---------- Interface de la classe <Texture> (fichier Texture.h) ------
#if ! defined ( TEXTURE_H_ )
#define TEXTURE_H_

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Texture>
//
//
//------------------------------------------------------------------------

class Texture
{
	//----------------------------------------------------------------- PUBLIC


public:
	//----------------------------------------------------- Méthodes publiques
	bool LoadTexture(std::string path);
	GLuint GetId();
	void Bind();

	//------------------------------------------------- Surcharge d'opérateurs
	Texture & operator = ( const Texture & tex );


	//-------------------------------------------- Constructeurs - destructeur
	Texture ( const Texture & tex );
	Texture(std::string path);
	Texture ( );

	virtual ~Texture ( );

	//------------------------------------------------------------------ PRIVE

protected:
	//----------------------------------------------------- Méthodes protégées

	//----------------------------------------------------- Attributs protégés

	GLuint id;




};

//--------------------------- Autres définitions dépendantes de <Texture>

#endif // TEXTURE_H_
