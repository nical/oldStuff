/*************************************************************************
                           Cell  -  description
                             -------------------
    creation             : 18 nov. 2009
    copyright            : (C) 2009 by Nicolas Silva
 *************************************************************************/

//#define appDEBUG
//---------------------------------------------------------------- INCLUDE

using namespace std;
#include <iostream>
#include "Cell.h"
#include "Color3.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public methods




bool Cell::Display(bool useVbo)
{
	glColor3f(color.GetR(), color.GetG(), color.GetB());
	if (!mesh->Display(useVbo))
	{
		cout << "error displaying the cell's mesh" << endl;
		return false;
	}
	if(drawLine)
	{
		glColor3f(0.0,0.0,0.0);
		glEnable (GL_BLEND);				// Enable Blending
		glBlendFunc (GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA); // Set The Blend Mode
		glPolygonMode (GL_BACK, GL_LINE);		// Draw Backfacing Polygons As Wireframes
		glCullFace (GL_FRONT);				// Don't Draw Any Front-Facing Polygons
		glDepthFunc (GL_LEQUAL);

		bool success = mesh->Display(useVbo, true);

		glDepthFunc (GL_LESS);				// Reset The Depth-Testing Mode
		glCullFace (GL_BACK);				// Reset The Face To Be Culled
		glPolygonMode (GL_BACK, GL_FILL);		// Reset Back-Facing Polygon Drawing Mode
		glDisable (GL_BLEND);

		if(!success)
		{
			cout << "error displaying the cell's outline" << endl;
			return false;
		}
	}
return true;
}

bool Cell::Load()//TODO
{
	return false;
}

bool Cell::UnLoad()
{
	delete mesh;
	type = 0;
	hp= 100;
	for (unsigned i=NUMBER_OF_UNIT_TYPES-1; i>=0; i--) coefs[i]=1.0;
	mesh = NULL;
	return true;//TODO
}

double Cell::GetHP()
{
	return hp;
}

int Cell::GetType()
{
	return type;
}

GLdouble Cell::GetAngle()
{
	return angle;
}

Color3 Cell::GetColor()
{
	return color;
}

double Cell::GetDisplacementCoef(int characterType)
{
	return coefs[characterType];
}

double Cell::GetVariable(string varName)
{
	return additionalParam[varName];
}

bool Cell::setVariable(string varName, double value)
{
	additionalParam[varName] = value;
	return true; //TODO: test the existence of the key before
}





//-------------------------------------------------- Operator overloading
Cell & Cell::operator = ( const Cell & c )
{
	type = c.type;
	hp= c.hp;
	for (int i=NUMBER_OF_UNIT_TYPES-1; i>=0; i--) coefs[i]=c.coefs[i];
	additionalParam=c.additionalParam;
	mesh = new Mesh(*c.mesh); // !!!! be careful with that!
	return *this;
	color = c.color;
	drawLine = c.drawLine;
	angle = c.angle;
}


//-------------------------------------------- Constructors - destructor
Cell::Cell ( const Cell & c )
{
#ifdef appDEBUG
	cout << "<Cell>'s copy constuructor called" << endl;
#endif
	type = c.type;
	hp= c.hp;
	for (int i=NUMBER_OF_UNIT_TYPES-1; i>=0; i--) coefs[i]=c.coefs[i];
	additionalParam=c.additionalParam;
	//mesh = new Mesh(*c.mesh); // !!!! be careful with that!
	mesh = c.mesh;
	//TODO: !!!! think wether or not we do need to copy the mesh
	color=c.color;
	angle=c.angle;
	drawLine = c.drawLine;
}


Cell::Cell ( )
{
#ifdef appDEBUG
	cout << " <Cell>'s constructor called" << endl;
#endif
	type = 0;
	angle = 0;
	hp= 100;
	for (int i=NUMBER_OF_UNIT_TYPES-1; i>=0; i--) coefs[i]=1.0;
	mesh = NULL;
}

Cell::Cell(int id,std::string aName,
		double c0, double c1, double c2, double c3,
		Mesh* meshPtr, Color3 aColor, GLdouble aAngle)
{
	type = id;
	name = aName;
	coefs[0] = c0;
	coefs[1] = c1;
	coefs[2] = c2;
	coefs[3] = c3;
	mesh = meshPtr;
	color = aColor;//at this point the color is ok...
	angle = aAngle;
	drawLine = true;

}

Cell::~Cell ( )
{
#ifdef appDEBUG
	cout << "<Cell>'s destructor called" << endl;
#endif
	//delete mesh;
}



//----------------------------------------------------- Protected Methods
