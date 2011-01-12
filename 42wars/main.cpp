
////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
#define appDEBUG


#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
//#include <algorithm>

#include "Graphics/Vect.h"
#include "Graphics/Mesh.h"
#include "Graphics/GameBoard.h"
#include "Graphics/Texture.h"
//#include "inits.h"


void displayBasis();

using namespace std;

const int SCREENWIDTH = 800;
const int SCREENHEIGHT = 500;

int main()
{


	bool drawLine = true;


	// Create the main window

	sf::RenderWindow App(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "42wars");
	// Create a clock for measuring elapsed time
	sf::Clock Clock;

	//bool USEVBO = initGlew();
	bool USEVBO = false;
	// a set of coordinates for the cursor and the viewer
	Vect3 cursorPos(0,0,0);
	Vect3 cam(0,0,0);
	Vect3 eyeTarget(5.0,5.0,0.0);
	double zoom = 4.0;

	GameBoard terrain(USEVBO);
	cout << "testing !!" << endl;
	terrain.Load("Misc/GameBoardFormat.txt");
	cout << "...ok, terrain chargé!" <<endl;


	// load a mesh
	Mesh tank;
	tank.LoadOBJ("Graphics/Models/tankMesh.obj");
	cout << "Graphics/Models/tankMesh.obj loaded ok" << endl;
	if (USEVBO)
	{
		tank.BuildVbo(GL_STREAM_DRAW); //crashes on eeepc1005ha
		std::cout << "vbo built" << std::endl;
	}
	// TODO !!! load only when vbo empty

	// load a mesh
	Mesh truck;
	truck.LoadOBJ("Graphics/Models/truck.obj");
	cout << "Graphics/Models/truck.obj loaded ok" << endl;
	if (USEVBO)
	{
		tank.BuildVbo(GL_STREAM_DRAW); //crashes on eeepc1005ha
		std::cout << "vbo built" << std::endl;
	}

	// load a mesh
	Mesh vtb;
	vtb.LoadOBJ("Graphics/Models/vtb.obj");
	cout << "Graphics/Models/vtb.obj loaded ok" << endl;
	if (USEVBO)
	{
		vtb.BuildVbo(GL_STREAM_DRAW); //crashes on eeepc1005ha
		std::cout << "vbo built" << std::endl;
	}


	Mesh floor;
	floor.LoadOBJ("Graphics/Models/flatfloor.obj");
	cout << "Graphics/Models/flatfloor.obj loaded ok" << endl;
	floor.printContent();


	Texture tex1("Graphics/Textures/tex01.png");
	Texture cityTex("Graphics/Textures/city01.tga");
	//Texture blockTex("Graphics/Textures/block2.png");

	cityTex.Bind();

	bool lightMvt=true;

	//setupGL();

    // Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.5f, 0.5f);



	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(1.0,2.0);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.f, 1.5f, 1.f, 500.f);

	// Light stuff
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	// Create light components
	GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9, 0.4f };
	GLfloat specularLight[] = { 0.8f, 0.8f, 0.8f, 0.3f };
	GLfloat position[] = { 5.5f, 1.0f, 15.0f, 1.0f };

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);


	// Start game loop
	while (App.IsOpened())
	{
		// Process events
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			// Close window : exit
			if (Event.Type == sf::Event::Closed)
				App.Close();

			// Escape key : exit
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				App.Close();


			// Resize event : adjust viewport
			if (Event.Type == sf::Event::Resized)
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);

			// key mapping:
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left))
			{
				cursorPos.x -= 1;
			}
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right))
			{
				cursorPos.x += 1;
			}
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
			{
				cursorPos.y += 1;
			}
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
			{
				cursorPos.y -= 1;
			}
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Q))
			{
				zoom += 1;
			}
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::W))
			{
				zoom -= 1;
			}
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::X))
			{
				drawLine = !drawLine;
			}

		}

		// Set the active window before using OpenGL commands
		// It's useless here because active window is always the same,
		// but don't forget it if you use multiple windows or controls
		App.SetActive();




		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		eyeTarget.x+=(cursorPos.x-eyeTarget.x)*0.2;
		eyeTarget.y+=(cursorPos.y-eyeTarget.y)*0.2;
		eyeTarget.z=cursorPos.z;
		cam.x=eyeTarget.x;
		cam.y=eyeTarget.y - 2 - zoom * 0.8;
		cam.z=eyeTarget.z +  zoom * zoom * 0.2;


		gluLookAt(cam.x+0.5,cam.y+0.5,cam.z, (cursorPos.x+eyeTarget.x+1)*0.5, eyeTarget.y+0.5, eyeTarget.z, 0,0,1);
		glPushMatrix();
		glTranslated(cursorPos.x,cursorPos.y,0.0);
		displayBasis();
		glPopMatrix();

		//moving light, some dirty code here to make it move
		// this is temporary of course
		if (position[0] < -2.0) lightMvt = true;
		if (position[0] > 20.0) lightMvt = false;
		position[0] = position[0]+Clock.GetElapsedTime()*10.0*(lightMvt-!lightMvt);
		position[1] = 10.0;
		position[2] = 3.0;
		Clock.Reset(); //todo..

		glLightfv(GL_LIGHT0, GL_POSITION, position);




		if (!terrain.DisplayAll(drawLine, false)) cout << "erreur lors de l'affichage du terrain! " << endl;



		glLineWidth(2.0);
		glTranslated(5.0,10.0,0.0);
		glColor3f(1.0,0.3,0.1);
		tank.Display(USEVBO);
		if( drawLine)
		{
			glColor3f(0.0,0.0,0.0);
			glDisable(GL_LIGHTING);
			tank.DisplayOutline(USEVBO);
			glEnable(GL_LIGHTING);
		}

		//draw another time the mesh
		glTranslatef(10.0f,6.0,0.0);
		glRotatef(90.0f, 0, 0,1);
		glColor3f(0.0, 1.0, 1.0);
		tank.Display(USEVBO);
		glColor3f(0.0,0.0,0.0);
		glPolygonOffset(1.0,2.0);
		if( drawLine)
		{
			glColor3f(0.0,0.0,0.0);
			glDisable(GL_LIGHTING);
			tank.DisplayOutline(USEVBO);
			glEnable(GL_LIGHTING);
		}

		//draw the truck
		glTranslatef(3.0f,6.0,0.0);
		glColor3f(0.2, 0.4, 0.5);
		truck.Display(USEVBO);
		glColor3f(0.0,0.0,0.0);
		glPolygonOffset(1.0,2.0);
		if( drawLine)
		{
			glColor3f(0.0,0.0,0.0);
			glDisable(GL_LIGHTING);
			truck.DisplayOutline(USEVBO);
			glEnable(GL_LIGHTING);
		}

		//draw the vtb
		glTranslatef(1.0f,-2.0,0.0);
		glColor3f(0.4f, 0.8f, 0.5f);
		vtb.Display(USEVBO);
		glColor3f(0.0,0.0,0.0);
		glPolygonOffset(1.0,2.0);
		if( drawLine)
		{
			glColor3f(0.0,0.0,0.0);
			glDisable(GL_LIGHTING);
			vtb.DisplayOutline(USEVBO);
			glEnable(GL_LIGHTING);
		}

		/*
		// Draw some text on top of our OpenGL object
		sf::String Text("HUD text");
		Text.SetPosition(250.f, 300.f);
		Text.SetColor(sf::Color(128, 0, 128));
		App.Draw(Text);
		 */

		// Finally, display rendered frame on screen
		App.Display();
	}
	//glDeleteTextures(1, &Texture);
	return EXIT_SUCCESS;
}

void displayBasis()
{
	// display the basis
	glDisable(GL_LIGHTING);
	glLineWidth(2.0);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
	glEnable(GL_LIGHTING);
	glEnable(GL_LINE_SMOOTH);
}
