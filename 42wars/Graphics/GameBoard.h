/*************************************************************************
                           GameBoard  -  description
                             -------------------
    début                : 13 nov. 2009
    copyright            : (C) 2009 par nico
*************************************************************************/

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include <GL/gl.h>
#include "Cell.h"

//	the cells coordinates are indexed from 1 and not 1 !
//
//
class GameBoard
{
public:
	GameBoard(bool useVbo = true);


	bool resize(unsigned boardWidth, unsigned boardHeight);
	bool Load(std::string path);
	bool UnLoad();
	GLuint GetWidth();
	GLuint GetHeight();
	Cell & GetCell(GLuint x, GLuint y);
	bool DisplayCell(unsigned x, unsigned y, bool useVbo = true);
	bool DisplayCellOutline(unsigned x, unsigned y,bool useVbo = true);
	bool DisplayAll(bool outline, bool useVbo = true);

protected :
	GLuint width, height;
	bool loaded, useVbo;
	std::vector<Cell> array;
};



#endif /* GAMEBOARD_H_ */
