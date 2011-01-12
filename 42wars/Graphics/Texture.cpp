/*************************************************************************
                           Texture  -  description
                             -------------------
    début                : 24 nov. 2009
    copyright            : (C) 2009 par nico
*************************************************************************/

//---------- Réalisation de la classe <Texture> (fichier Texture.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
#include <SFML/Graphics.hpp>

//------------------------------------------------------ Include personnel
#include "Texture.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
using namespace std;

GLuint Texture::GetId() {return id;}



void Texture::Bind() {glBindTexture(GL_TEXTURE_2D, this->GetId() );}



bool Texture::LoadTexture(string path)
{
#ifdef appDEBUG
cout << "loading texture : " << path << endl;
#endif
sf::Image image;
  if (image.LoadFromFile(path)){ cout << "testing !!" << endl;
glGenTextures(1, &id);
glBindTexture(GL_TEXTURE_2D, id);
gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.GetWidth(), image.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixelsPtr());
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
cout << "chargement de la texture: ok " << endl;
return true;
    }
else { cout << "erreur au moment de charger l'image" << endl; return false;}
}



//------------------------------------------------- Surcharge d'opérateurs
Texture & Texture::operator = ( const Texture & tex )
// Algorithme :
//
{
	id = tex.id;
	return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Texture::Texture ( const Texture & tex )
// Algorithme :
//
{
	id = tex.id;
#ifdef appDEBUG
    cout << "Appel au constructeur de copie de <Texture>" << endl;
#endif
} //----- Fin de Texture (constructeur de copie)


Texture::Texture(string path)
{
this->LoadTexture(path);
}



Texture::Texture()
{
id = NULL;
#ifdef appDEBUG
    cout << "Appel au constructeur de <Texture>" << endl;
#endif
} //----- Fin de Texture



Texture::~Texture()
{
glDeleteTextures(1, &id);
#ifdef appDEBUG
    cout << "Appel au destructeur de <Texture>" << endl;
#endif
} //----- Fin de ~Texture


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
