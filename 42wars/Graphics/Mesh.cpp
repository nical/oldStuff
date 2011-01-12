/*************************************************************************
                           Mesh  -  description
                             -------------------
    début                : 13 nov. 2009
    copyright            : (C) 2007 par Nical
 *************************************************************************/

//---------- Réalisation de la classe <Mesh> (fichier Mesh.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

#include <math.h>
#include <string>
#include <vector>

#include <iostream>
#include <GL/glew.h>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "Mesh.h"
#include "Vect.h"

//------------------------------------------------------------- Constantes
#define appDEBUG

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

bool Mesh::LoadOBJ(std::string path, bool useMaterials, bool useNormals)
{
	name = path;
	hasNormals = false; // will be set true if we meet the "vn" tag
	hasTexture = useMaterials; // for the moment let's consider that if there's a material there's a texture
	nTriangles = 0; //member of clas Mesh3
	nVertices = 0; //member of clas Mesh3
	Vect3 tmp3; // temporary vectors
	Vect2 tmp2;
	vector<Vect3> positions, tmpPos;
	vector<Vect2> texcoords, tmpTex;
	vector<Vect3> normals, tmpNor;
	vector<Vect3int> indexTest;   // used to test if vertices already exist before being added to the vertex array

	{
	int slash = path.find_last_of("/")+1;
	int nchars = path.size()-slash-4;
	string pathTex = "Graphics/Textures/"+path.substr(slash, nchars )+".png";
	if( !texture.LoadTexture(pathTex))
	{
		cerr << "couldn't load texture "<< pathTex <<endl;
	}

	}

	std::cout<<"chargement du fichier "<<path<<std::endl;
	std::ifstream fichier(path.c_str(), std::ios::in);  // open the file in reading mode
	if(fichier.fail())  // si l'ouverture a échouée
	{ std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
	return false;	// retourne l'index null
	}
	// if the file is opened correctly

	std::string tag; // contiendra le premier mot de chaque ligne
	std::string ligne;  // déclaration d'une chaîne qui contiendra la ligne lue
	std::string materialFile;
	fichier>>tag;
	while (tag== "#") {fichier>>tag; getline(fichier,ligne);}
	if ( tag == "mtllib" ) fichier>> materialFile;  // TODO load the mtl file

	// TODO loadMTL(materialFile);


	while(!fichier.eof())
	{
		fichier>>tag;
		///// chargement des sommets ////////////////////////////////////////////////////
		if (tag == "v")
		{
			fichier>>tmp3.x;
			fichier>>tmp3.y;
			fichier>>tmp3.z;
			positions.push_back(tmp3);

#ifdef appDEBUG
			std::cout << "add a vertex: ok -> " << tmp3.x << " # " << tmp3.y << " # " << tmp3.z << std::endl;

#endif

		}
		///// chargement des coordonnées de texture ///////////////////////////////////////
		else if (tag == "vt")
		{

			fichier>>tmp2.x;
			fichier>>tmp2.y;
			texcoords.push_back(tmp2);
#ifdef appDEBUG
			std::cout << "add a texCoord: ok -> " << tmp2.x << " # " << tmp2.y << std::endl;
			;
#endif

		}
		///// chargement des normales  ///////////////////////////////////////
		else if ((tag == "vn") && (useNormals))
		{
			hasNormals = true;
			fichier>>tmp3.x;
			fichier>>tmp3.y;
			fichier>>tmp3.z;
			normals.push_back(tmp3);
#ifdef appDEBUG
			cout << "add a normal: ok -> " << tmp3.x << " # " << tmp3.y << " # " << tmp3.z << endl;
#endif
		}
		else if (tag == "f")        //build a vertex picking the correct position, normal and uv
		{
#ifdef appDEBUG
			cout << "build a triangle "<< endl;
#endif
			Vect3int ptn;
			char dummy; // the dummy is '/'
			nTriangles++;
			for(int i = 0; i< 3; i++) //only works with triangulated models
			{
#ifdef appDEBUG
				cout << "* get each vertex "<< endl;
#endif
				fichier >> ptn.a >> dummy >> ptn.b >> dummy >> ptn.c;
#ifdef appDEBUG
				cout << ptn.a << " +++++ " << ptn.b << " +++++ " << ptn.c <<endl;
#endif
				int testSuccess = 0;
				//optimisation here : look through the collected data before adding new ones to avoid redundancies
				if(indexTest.size() == 0)
				{
					indexTest.push_back(ptn);
					indexArray.push_back(nVertices);
					tmpPos.push_back(positions[ptn.a-1]);               // add position normal and uv
					if(hasTexture) tmpTex.push_back(texcoords[ptn.b-1]);
					if(hasNormals) tmpNor.push_back(normals[ptn.c-1]);
					nVertices++;
				}
				else
				{for(unsigned int k = 0; k< indexTest.size(); k++)  //test if the vertex is already stored
				{
					if( (ptn.a == indexTest[k].a) && (ptn.b == indexTest[k].b) && (ptn.b == indexTest[k].b) )
					{
						testSuccess = k;
						break;
					}
				}
				if(testSuccess > 0) //if the vertex already exists
				{
					indexArray.push_back(testSuccess);
					// no need to add the position, normal and uv as they're already stored
				}
				else{               //if the vertex doesn't exist yet
					indexTest.push_back(ptn);
					indexArray.push_back(nVertices); // not nevertices-1 because this variable is incrmented at the end of the loop
					tmpPos.push_back(positions[ptn.a-1]);               // add position normal and uv
					if(hasTexture) tmpTex.push_back(texcoords[ptn.b-1]);
					if(hasNormals) tmpNor.push_back(normals[ptn.c-1]);
					nVertices++;
				}
				}

			}
#ifdef appDEBUG
			cout << "vertex added" << endl;
#endif
		}//vertex Built
#ifdef appDEBUG
		cout <<"-------face built------" << endl;
#endif
	}//end of the first loop


	//build the final array containing all the data
	for(unsigned int i=0; i< nVertices; i++)
	{
		vertexArray.push_back(tmpPos[i].x);
		vertexArray.push_back(tmpPos[i].y);
		vertexArray.push_back(tmpPos[i].z);
	}

	if(hasTexture)
		for(unsigned int i=0; i< nVertices; i++)
		{
			vertexArray.push_back(tmpTex[i].x);
			vertexArray.push_back(tmpTex[i].y);
		}

	if(hasNormals)
		for(unsigned int i=0; i< nVertices; i++)
		{
			vertexArray.push_back(tmpNor[i].x);
			vertexArray.push_back(tmpNor[i].y);
			vertexArray.push_back(tmpNor[i].z);
		}


#ifdef appDEBUG
	cout <<"number of elements in vertexArray: " << vertexArray.size() << " which makes us :"<< vertexArray.size()/8 << " vertices"<< endl;
	cout << "nVertices : " << nVertices << " indexArray.size() : " << indexArray.size() << " which makes  "<< indexArray.size()/3 << "triangles" << endl;
	cout << "ntriangles : " << nTriangles << endl;
	cout<< "indexTest.size() : " <<indexTest.size() << endl;

	cout << endl;
#endif
	fichier.close();
	return true;
}




bool Mesh::Unload()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

	return true;}


bool Mesh::Display(bool useVbo)
{

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	if(hasNormals) glEnableClientState(GL_NORMAL_ARRAY);
	if(hasTexture) glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	texture.Bind();//TODO: decide wether we should unbind the texture afterwise
	if (useVbo)
	{

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexPointer(3, GL_DOUBLE, 0, BUFFER_OFFSET(0)); //not sure... !!
		if(hasNormals) glNormalPointer(GL_DOUBLE, 0 , BUFFER_OFFSET(nVertices*(hasTexture*2+3)*sizeof(GLdouble)));
		if(hasTexture) glTexCoordPointer(2,GL_DOUBLE, 0 , BUFFER_OFFSET(nVertices*3*sizeof(GLdouble)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glDrawElements(GL_TRIANGLES, indexArray.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0)); //render the triangles

		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind the buffers
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
	else { //without vbo

		glVertexPointer(3, GL_DOUBLE, 0 , &vertexArray[0]); //not sure... !!
		if(hasNormals) glNormalPointer(GL_DOUBLE, 0 , &vertexArray[0]+(3+hasTexture*2)*nVertices);
		if(hasTexture) glTexCoordPointer(2, GL_DOUBLE, 0 , &vertexArray[0]+nVertices*3);

		glDrawElements(GL_TRIANGLES, indexArray.size(),GL_UNSIGNED_INT, &indexArray[0]);


	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	//glUseProgram(0);
	return true;
}




bool Mesh::DisplayOutline(bool useVbo)
{

	glEnable (GL_BLEND);				// Enable Blending
	glBlendFunc (GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA); // Set The Blend Mode
	glPolygonMode (GL_BACK, GL_LINE);		// Draw Backfacing Polygons As Wireframes
	glCullFace (GL_FRONT);				// Don't Draw Any Front-Facing Polygons
	glDepthFunc (GL_LEQUAL);

	bool success = Display(useVbo, true);

	glDepthFunc (GL_LESS);				// Reset The Depth-Testing Mode
	glCullFace (GL_BACK);				// Reset The Face To Be Culled
	glPolygonMode (GL_BACK, GL_FILL);		// Reset Back-Facing Polygon Drawing Mode
	glDisable (GL_BLEND);

	return success;
}


bool Mesh::Display(bool useVbo, bool PositionsOnly)
{
	bool hasNormals2 = hasNormals, hasTexture2 = hasTexture;
	hasNormals = false;
	hasTexture = false;

	bool success = Display(useVbo);

	hasNormals = hasNormals2;
	hasTexture = hasTexture2;

	return success;
}







//pass the data stored in vertexArray[] and indexArray[] to the GPU using one VBO and one IBO
bool Mesh::BuildVbo(GLenum target)
{
	//init VBO
	glGenBuffers(1, &vbo); // crashes on my eeepc 1005ha netbook


	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLuint dataSize = vertexArray.size()*sizeof(GLdouble);
	//allocate memory in the gpu
	glBufferData(GL_ARRAY_BUFFER,dataSize,NULL, target);
	//transfert the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, &vertexArray[0]);

	////////////////////////Index buffer

	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	dataSize = this->indexArray.size()*sizeof(GLuint);
	//allocation mémoire coté serveur
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,dataSize,NULL, target);
	//transfert des données de sommet
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, dataSize, &indexArray[0]);

	///// to finish, unbind" the buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	hasVbo = true;
	return true;
}


bool Mesh::HasVbo()
{
	return hasVbo;
}

#ifdef appDEBUG
void Mesh::printContent()
{

	unsigned i = 0;
	cout<<"vertices: " << endl;
	for(; i < nVertices*3; i+=3)
	{
		cout<<"v->" << vertexArray[i] <<"  "<< vertexArray[i+1] << "  " << vertexArray[i+2]<<endl;
	}
	if(hasTexture)
	{
		cout<<"ntexCoords: " << endl;
		for(; i < nVertices*5; i+=2)
		{
			cout<<"vt->" << vertexArray[i] <<"  "<< vertexArray[i+1] << endl;

		}
	}
	if(hasNormals)
	{
		cout<<"normals: " << endl;
		for(; i < nVertices*8; i+=3)
		{
			cout << "vn-> "<<vertexArray[i] <<"  "<< vertexArray[i+1] << "  " << vertexArray[i+2] << endl;
		}
	}
}
#endif
////////////////////////////////////////
// Some of the following functions and operators
// have been commented because I haven't figured
// whether they should be used or not
// -> TODO: Figure this out!
////////////////////////////////////////


//------------------------------------------------- Surcharge d'opérateurs
/*
Mesh & Mesh::operator = ( const Mesh & unMesh )
// Algorithme :
//
{

} //----- Fin de operator =
 */

//-------------------------------------------- Constructeurs - destructeur

Mesh::Mesh ( const Mesh & m )
// Algorithme :
//
{
#ifdef appDebug
	cout << "Appel au constructeur de copie de <Mesh>" << endl;
#endif
	name = m.name;
	nVertices = m.nVertices;
	nTriangles = m.nTriangles;
	nLines = m.nLines;
	vboTarget = m.vboTarget;
	hasNormals = m.hasNormals;
	hasTexture = m.hasTexture;
	hasVbo = false;
	vertexArray = m.vertexArray;
	indexArray = m.indexArray;
	vbo = ibo = 0;

} //----- Fin de Mesh (constructeur de copie)


Mesh::Mesh ( )
// Algorithme :
//
{
#ifdef appDebug
	cout << "Appel au constructeur de <Mesh>" << endl;
#endif
	name = "emptyMesh";
	nVertices=nTriangles=nLines=0;

	//vboTarget = //TODO
	hasNormals = hasTexture = hasVbo = false;

} //----- End de Mesh



Mesh::Mesh(string path, bool useNormal)
{
	LoadOBJ(path, true, useNormal);
}



Mesh::~Mesh ( )
{
#ifdef appDEBUG
	cout << "Appel au destructeur de <Mesh>" << endl;
#endif
} //----- Fin de ~Mesh





//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
