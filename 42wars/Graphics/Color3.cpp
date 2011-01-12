/*************************************************************************
                           Color3  -  description
                             -------------------
    creation             : 21 nov. 2009
    copyright            : (C) 2009 by Nicolas Silva
*************************************************************************/
//#define appDEBUG

//---------------------------------------------------------------- INCLUDE

using namespace std;
#include <iostream>
#include "Color3.h"

//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public methods


ColorComponent Color3::SetR(ColorComponent ar)
{
	if (ar > 1.0) ar = 1.0;
	if (ar < 0.0) ar = 0.0;
	return r = ar;
}

ColorComponent Color3::SetG(ColorComponent ag)
{

	if (ag > 1.0) ag = 1.0;
	else if (ag < 0.0) ag = 0.0;
	return g = ag;
}

ColorComponent Color3::SetB(ColorComponent ab)
{

	if (ab > 1.0) ab = 1.0;
	else if (ab < 0.0) ab = 0.0;
	return b = ab;
}

ColorComponent Color3::GetR() {return r;}

ColorComponent Color3::GetG() {return g;}

ColorComponent Color3::GetB() {return b;}



//-------------------------------------------------- Operator overloading
Color3 & Color3::operator = ( const Color3 & color )
{
	r=color.r;
	g=color.g;
	b=color.b;
	return *this;
}

void Color3::DbgPrintContent()
{
	cout << "colorDebug: R="<< r << " G=" <<g<< " B=" << b<<endl;
}

//-------------------------------------------- Constructors - destructor

Color3::Color3 ( const Color3 & aColor )
{
#ifdef appDEBUG
    cout << "<Color3>'s copy constuructor called" << endl;
#endif
    r = aColor.r;
    g = aColor.g;
    b = aColor.b;
}


Color3::Color3 (ColorComponent ar, ColorComponent ag, ColorComponent ab)
{
#ifdef appDEBUG
    cout << " <Color3>'s constructor called" << endl;
#endif
    r = ar;
    g = ag;
    b = ab;
}


Color3::~Color3 ( )
{
#ifdef appDEBUG
    cout << "<Color3>'s destructor called" << endl;
#endif
}



//----------------------------------------------------- Protected Methods
