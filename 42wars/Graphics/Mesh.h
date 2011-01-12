/*************************************************************************
                           Mesh  -  description
                             -------------------
    début                : 13 nov. 2009
    copyright            : (C) 2009 par nico
*************************************************************************/

//---------- Interface de la classe <Mesh> (fichier Mesh.h) ------
#if ! defined ( MESH_H_ )
#define MESH_H_

//--------------------------------------------------- Interfaces utilisées
#include <GL/gl.h>
//#include <GL/glew.h>
#include <string>
#include <map>
#include <vector>

#include "Texture.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Mesh>
//
//
//------------------------------------------------------------------------

class Mesh
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

bool LoadOBJ(std::string path, bool useMaterial=true, bool useNormals = true);
bool Unload();
bool BuildVbo(GLenum target);
bool Display(bool useVbo);
bool Display(bool useVbo, bool PositionsOnly); // TODO: DEPRECATED
bool DisplayOutline(bool useVbo);
bool UseVbo(bool state); // defines wether or not vertex buffer should be used for next displays
std::string GetName();
GLuint GetNVertices();
GLuint GetNTriangles();
GLuint GetNSegments();
GLuint GetVboTarget();
bool HasNormals();
bool HasTexture();
bool HasVbo();
// bool updateVBO();


void printContent();



//------------------------------------------------- Surcharge d'opérateurs
//    Mesh & operator = ( const Mesh & m );


//-------------------------------------------- Constructeurs - destructeur
    //Mesh ( const Mesh & m );

    Mesh (std::string Path, bool useNormals = true);

    Mesh ( );

    Mesh (const Mesh & m);
    // makes a copy without VBO (which can build it's own vbo afterwise)

    virtual ~Mesh ( );


protected:
//----------------------------------------------------- Méthodes protégées
//----------------------------------------------------- Attributs protégés
	std::string name;	//should be it's path
	unsigned int nVertices;
	unsigned int nTriangles;
	unsigned int nLines;
	GLenum vboTarget;
	bool hasNormals, hasTexture, hasVbo;// hasOutline;
	Texture texture;
	std::vector<GLdouble> vertexArray;
	std::vector<GLuint> indexArray;
	GLuint vbo, ibo;//Identifiers

};

//--------------------------- Autres définitions dépendantes de <Mesh>

#endif // MESH_H_
