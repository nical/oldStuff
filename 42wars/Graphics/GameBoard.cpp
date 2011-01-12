/*
 * GameBoard.cpp
 *
 *  Created on: 19 nov. 2009
 *      Author: nico
 */
//#define appDEBUG

#include "GameBoard.h"
#include "Color3.h"


#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


// the idea is to first load all the meshes
// then make the cells and link them to meshes
// then store the cell's id in an array using the filse order
// then copy the cells in the correct order
bool GameBoard::Load(std::string path)
{
#ifdef appDEBUG
	std::cout<<"chargement du fichier "<<path<<std::endl;
#endif
	std::ifstream fichier(path.c_str(), ios::in);  // open the file in reading mode
	if(fichier.fail())
	{ std::cout << "Impossible d'ouvrir le fichier " <<path << std::endl;
	return false;	// error
	}
	// if the file is opened correctly
	fichier.seekg(0, ios::beg);

	string tag; // will contain the first word of each line
	string ligne;  // will contain each line
	vector<Cell> vCells; //contain the cell when loading (befor filling the board with copies)
	vector<int> tab; //will contain the id of the cells before sorting
	//in fact openGL coordinates do not correspond to the order of arrival of the indices in the file
	//so i first get all the indices in the file's order and then switch the rows before copying
	//the cells objects
	vector<Mesh*> meshes; //to avoid loading the meshes several times
	vector<string> meshNames;
	//fichier>>tag;
	//while (tag== "#") {fichier>>tag;}

	while(!fichier.eof() )
	{
		fichier >> tag;
#ifdef appDEBUG
		cout << "Tag = " << tag <<endl;
#endif
		if (tag == ">meshes")
		{

			while(tag != "end")
			{
				fichier >> tag;
				if (tag[0] != '#')
				{
					string mPath;
					string mName= tag;
					fichier>> mPath;
					meshes.push_back(new Mesh(mPath));
					meshNames.push_back(mName);
				}
			}
		}
		else if (tag == ">cell")
		{
#ifdef appDEBUG
			cout << "tag: >cell" <<endl;
#endif
			int id;
			string name = "defaultname";
			string meshPath;
			Mesh* meshPtr = NULL;
			Color3 color;
			double c0 = 1.0;
			double c1 = 1.0;
			double c2 = 1.0;
			double c3 = 1.0;
			GLdouble angle = 0;

			do
			{
				fichier>>tag;
#ifdef appDEBUG
				cout << "   tag = " << tag << endl;
#endif


				if(tag == "name")
				{
					fichier>>name;
#ifdef appDEBUG
					cout << "    name -> "<< name <<endl;
#endif
				}
				else if(tag == "id")
				{
					fichier>>id;
#ifdef appDEBUG
					cout << "    id -> "<< id <<endl;
#endif
				}
				else if(tag == "mesh")
				{
					fichier>>tag;

#ifdef appDEBUG
					cout << "    mesh -> "<< tag <<endl;
#endif
					int mIndex =-1;
					for (unsigned i = 0; i<meshNames.size();++i)
						if (meshNames[i] == tag)
							mIndex = i;
					if(mIndex == -1)
					{
						meshPtr = meshes[0];
#ifdef appDEBUG
						cout << "    default mesh used"<<endl;
#endif
					}
					else
					{
						meshPtr = meshes[mIndex];
#ifdef appDEBUG
						cout << "    mesh found"<<endl;
#endif
					}


				}
				else if(tag == "color")
				{
					ColorComponent tmp;
					fichier>>tmp;
					color.SetR(tmp);
					fichier>>tmp;
					color.SetG(tmp);
					fichier>>tmp;
					color.SetB(tmp);
#ifdef appDEBUG
					cout << "    color -> " << color.GetR() <<" "<< color.GetG() <<" "<< color.GetB() <<endl;
#endif
				}
				else if(tag == "coefs")
				{
					fichier>>c0;
					fichier>>c1;
					fichier>>c2;
					fichier>>c3;
#ifdef appDEBUG
					cout << "    coefs -> " << c0 <<" "<< c1 <<" "<< c2 <<" "<< c3 <<endl;
#endif
				}
				if(tag == "angle")
				{
					fichier>>angle;
#ifdef appDEBUG
					cout << "    angle -> "<< angle <<endl;
#endif
				}
				else if(tag == "end")
				{
					vCells.push_back(Cell(id, name, c0, c1, c2, c3, meshPtr, color, angle));
#ifdef appDEBUG
					cout << "cell.end" << endl;
					cout << "|  id " << id << endl
					<< "|  name " << name << endl
					<< "|  coefs " << c0 <<" "<< c1 <<" "<< c2 <<" "<< c3 << endl
					<< "|  angle " << angle << endl
					<< "|  color " << color.GetR() <<" "<<color.GetG()<<" "<< color.GetB() << endl;
#endif
				}
			}
			while(tag != "end");
		}
		else if (tag == ">terrain")
		{
#ifdef appDEBUG
			cout << "start working on the terrain itself" <<endl;
#endif
			// get width & height
			fichier>>tag;
			if(tag == "width")
			{
				fichier>>width;
#ifdef appDEBUG
				cout << "    width " << width <<endl;
#endif
			}
			else
			{
				cout << "    error: tag should be width, got " << tag << " instead" << endl;
				return false;
			}
			fichier>>tag;
			if(tag == "height")
			{
				fichier>>height;
#ifdef appDEBUG
				cout << "width " << width <<endl;
#endif
			}
			else
			{
				cout << "    error: tag should be height, got " << tag << " instead" << endl;
				return false;
			}


			// now catch all the ids and build cells
			// keeping in mind that we need to stop when "end" is encontered
			int tempId = 0;
			int selectedCell = 0;
			unsigned filePos;
			bool endReached = false;
			unsigned size = width*height;
#ifdef appDEBUG
			cout <<"    size = " << size << endl;
#endif
			for (unsigned i = 0; i < size; ++i)
			{
#ifdef appDEBUG
				cout << "terrain.looping... ("<<i<<")" << endl;
#endif
				if( !endReached)
				{
					filePos = fichier.tellg();
					fichier>>tag;
					if (tag != "end")
					{
						fichier.seekg(filePos, ios::beg);
						fichier>>tempId;
						//find the corresponding cell
						selectedCell = 0;
						for(unsigned j = 0; j<vCells.size(); ++j)
						{
							if(vCells[j].GetType() == tempId)
							{
								selectedCell = j;
								break;
							}

						}

						//add the corresponding cell to the board using
						//Cell's copy constructor
						tab.push_back(selectedCell);
						//array.push_back(Cell(vCells[selectedCell]));

					}
					else
					{
						endReached = true;
#ifdef appDebug
						cout << "terrain.end" << endl;
#endif
					}
				}
				else //if end's been reached already, we fill the terrain with the default cell
				{
					//add the corresponding cell to the board using
					//Cell's copy constructor
					tab.push_back(0);
					//array.push_back(Cell(vCells[0]));
#ifdef appDebug
					cout << "(!) filling with default cells" << endl;
#endif
				}
			}
			int correctIndex = 0;
			for(unsigned j=0; j<height; j++)
				for(unsigned i=0; i<width; i++)
				{
					correctIndex = i+(height-j-1)*width;
					//the idea is: orderedTab.push_back(tab[correctIndex]);
					array.push_back(Cell(vCells[tab[correctIndex]]));
				}

			fichier >> tag;
#ifdef appDEBUG
			cout << "after the loop, next tag is " << tag <<endl;
#endif
		}
		else
		{
			cout << "unknown tag" <<endl;
		}
	}

	return true;
}






/*
bool GameBoard::UnLoad()
{
	return false; //TODO!!
}
 */

GLuint GameBoard::GetWidth()
{
	return width;
}


GLuint GameBoard::GetHeight()
{
	return height;
}


Cell & GameBoard::GetCell(GLuint x, GLuint y)
{
	x = (x-1) % width;
	y = (y-1) % height;
	return array[x+y*width];
}

bool GameBoard::DisplayAll(bool outline, bool useVbo)
{
	for(unsigned i = 1; i<=height; ++i)
		for(unsigned j = 1; j<=width; ++j)
		{
			if(!DisplayCell(j,i,useVbo))
				return false;

		}
	return true;
}

bool GameBoard::DisplayCell(unsigned x, unsigned y,bool useVbo)
{
	int index = (x-1)+(y-1)*width;
	glPushMatrix();
	glTranslatef(x-1, y-1, 0.0);
	if(array[index].GetAngle() != 0.0)
	{
		glRotated(array[index].GetAngle(),0.0,0.0,1.0);
	}
	bool result = array[(x-1)+(y-1)*width].Display(useVbo);
	glPopMatrix();
	return result;
}


GameBoard::GameBoard(bool useVBO)
{
	useVbo = useVBO;
	loaded = false;
	width = 0;
	height = 0;
}
