/*************************************************************************
                           Cell  -  description
                             -------------------
    Creation             : 15 nov. 2009
    copyright            : (C) 2009 by Nical
*************************************************************************/

#ifndef CELL_H_
#define CELL_H_

#include "Mesh.h"
#include "Color3.h"
#include <string>
#include <map>
//--------------------------------------------------------------- Constants
const int NUMBER_OF_UNIT_TYPES = 4;
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Each instance of this class represents a Cell of the game board
//
//
//------------------------------------------------------------------------

class Cell
{
//----------------------------------------------------------------- PUBLIC

public:
//--------------------------------------------------------- Public methods
	bool Display(bool useVbo = true);
	bool Load();
	bool UnLoad();
	double GetHP();
	int GetType();
	GLdouble GetAngle();
	double GetDisplacementCoef(int characterType);
	double GetVariable(std::string varName);
	Color3 GetColor();
	bool setVariable(std::string varName, double value);

//------------------------------------------------- operator overloading
    Cell & operator = ( const Cell & c );
//-------------------------------------------- Constructors - destructor
    Cell ( const Cell & c );
    Cell ( );
    Cell(int id, std::string aName, double c0, double c1, double c2, double c3, Mesh* meshPtr, Color3 aColor, GLdouble aAngle);
    virtual ~Cell ( );

protected:
//----------------------------------------------------- Protected Methods

//-------------------------------------------------- Protected Attributes
	int type;
	bool drawLine;
	std::string name;
	double hp;
	 //displacement coefficients, determine how fast
	  // units can move across the cell
	  // 0-> Infantry
	  // 1-> allTerrain
	  // 2-> road
	  // 3-> boat
	double coefs[NUMBER_OF_UNIT_TYPES];
	Color3 color;
	GLdouble angle;
	std::map<std::string,double> additionalParam; //can be used at any purpose (ex: capture)

	Mesh* mesh;

};

//-------------------------------------------------- Other definitions

#endif // CELL_H_
