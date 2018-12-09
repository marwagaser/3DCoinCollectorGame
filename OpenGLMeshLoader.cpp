#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include "iostream"
#include <glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include<iostream>
#include <string.h>

int WIDTH = 1280;
int HEIGHT = 720;
int lives = 100;
int score = 0;
GLuint tex;
char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;
float carx = 40;
float carlr = 2;
float lr = 2;
float rotAng = 0;
float carxcam = 40;

float rndx1 = -50;
float rndx2 = -50;
float rndx3 = -50;
float rndx4 = -50;
float rndx5 = -50;
float rndx6 = -50;
float rndx7 = -50;
float rndx8 = -50;
float rndx9 = -50;
float rndx10 = -50;
float rndx11 = -50;
float rndx12 = -50;
float rndx13 = -50;
float rndx14 = -50;
float rndx15 = -50;

float rndy1 = 25;
float rndy2 = 35;
float rndy3 = 8;
float rndy4 = 12;
float rndy5 = 25;
float rndy6 = 20;
float rndy7 = 15;
float rndy8 = 10;
float rndy9 = 5;
float rndy10 = 0;
float rndy11 = -5;
float rndy12 = -10;
float rndy13 = -15;
float rndy14 = -20;
float rndy15 = -18;

int levelrocks = 0;


float rockx1 = 0;
float rockz1 = 0;

float rockx2 = 0;
float rockz2 = 0;

float rockx3 = 0;
float rockz3 = 0;

float rockx4 = 0;
float rockz4 = 0;

float rockx5 = 0;
float rockz5 = 0;

float rockx6 = 0;
float rockz6 = 0;

float rockx7 = 0;
float rockz7 = 0;

float rockx8 = 0;
float rockz8 = 0;

bool flagcam1 = false;
bool flagcam2 = false;
bool flagcam3 = true;
bool flagcam4 = false;

int laps = 25;


float camx = 45;
float camy = 3;
float camz = 2.2;
float xcar = 40;
float ycar = 2;
float zcar = 0;

float px = -40;

float py1 = 2;
float py2 = 4;
float py3 = 6;


bool scene1 = true;
bool  won = false;

float rndy[15] = { rndy1,rndy2,rndy3,rndy4,rndy5,rndy6,rndy7,rndy8,rndy9,rndy10,rndy11,rndy12,rndy13,rndy14,rndy15 };
float rndx[15] = { rndx1,rndx2,rndx3,rndx4,rndx5,rndx6,rndx7,rndx8,rndx9,rndx10,rndx11,rndx12,rndx13,rndx14,rndx15 };

float rx[8] = { rockx1,rockx2,rockx3,rockx4,rockx5,rockx6,rockx7,rockx8 };
float rz[8] = { rockz1,rockz2,rockz3,rockz4,rockz5,rockz6,rockz7,rockz8 };
float coinAng = 0;
float rockAng = 0;

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(51.9, 8, 2.2);
Vector At(40, 2, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

// Model Variables
Model_3DS model_coin;
Model_3DS model_car;
Model_3DS model_rock;

// Textures
GLTexture tex_ground;
GLTexture tex_ground2;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);



	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT1);

	// Define Light source 0 ambient light
	//GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	//GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	//GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	//GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
}
//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	if (flagcam1 == true)
	{
		float CamXthird = carx + 1 + cos(100)*(0);
		//from the sides
		float x1 = carx + 1 + cos(100)*(0);
		camx = x1;
		camy = 7;
		camz = 0;
		xcar = carx;
		ycar = 0.1;
		zcar = carlr;

		px = carx;
		py1 = 1;
		py2 = 2;
		py3 = 3;
	}

	if (flagcam2 == true)
	{
		//from up
		float x2 = carx + 1 + cos(100)*(5);
		camx = x2;
		camy = 5;
		camz = carlr;
		xcar = carx;
		ycar = 0.1;
		zcar = carlr;

		px = carx;
		py1 = 1;
		py2 = 2;
		py3 = 3;
	}


	if (flagcam3 == true)
	{
		//float CamXAway = carx + 1 + cos(100)*(10);
		//gluLookAt(CamXAway, 1.9, carlr, carx, 0.1, carlr, 0, 1, 0);
		//from away
		float x3 = carx + 1 + cos(100)*(10);
		camx = x3;
		camy = 1.9;
		camz = carlr;
		xcar = carx;
		ycar = 0.1;
		zcar = carlr;
	}

	if (flagcam4 == true)
	{
		//float CamXAway = carx + 1 + cos(100)*(10);
		//gluLookAt(CamXAway, 1.9, carlr, carx, 0.1, carlr, 0, 1, 0);
		//from away
		float x3 = 51.9;
		camx = x3;
		camy = 8;
		camz = 2.2;
		xcar = 40;
		ycar = 2;
		zcar = 0;
	}

	gluLookAt(camx, camy, camz, xcar, ycar, zcar, 0, 1, 0);





	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	//InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

////// 
// PRINT
//////////
void print(int x, int y, char *string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}


void key(unsigned char k, int x, int y)//keyboard function, takes 3 parameters
									   // k is the key pressed from the keyboard									// x and y are mouse postion when the key was pressed.
{


	switch (k) {
	case 'b':
		glDisable(GL_LIGHT0);
		break;
	case 'n':
		glEnable(GL_LIGHT0);
		break;

	case 't':
		glDisable(GL_LIGHT1);
		break;
	case 'y':
		glEnable(GL_LIGHT1);
		break;
	case 27: //Escape key
		exit(0);
	default:
		break;
	}

	if (k == 'u')
	{
		flagcam1 = true;
		flagcam2 = false;
		flagcam3 = false;
		flagcam4 = false;
	}
	if (k == 'j')
	{
		flagcam1 = false;
		flagcam2 = true;
		flagcam3 = false;
		flagcam4 = false;

	}
	if (k == 'i')
	{
		flagcam1 = false;
		flagcam2 = false;
		flagcam3 = true;
		flagcam4 = false;
		px = -40;
		py1 = 2;
		py2 = 4;
		py3 = 6;
	}
	if (k == 'k')
	{
		flagcam1 = false;
		flagcam2 = false;
		flagcam3 = false;
		flagcam4 = true;
		px = 40;
		py1 = 1;
		py2 = 2;
		py3 = 3;

	}


	glutPostRedisplay();

	if (lives > 0 & laps>0)
	{
		if (k == 'a')//if the letter d is pressed, then the object will be translated in the x axis by 10 (moving to the right).
		{
			if (rotAng <= 10)
				rotAng += 2;
			if (carlr < 8.7)
				carlr += 0.1;
			std::cout << carlr << " ";
		}
		if (k == 'd')//if the letter a is pressed, then the object will be translated in the x axis by -10 (moving to the left).
		{
			if (rotAng >= -10)
				rotAng -= 2;
			if (carlr > -8.7)
				carlr -= 0.1;
			std::cout << carlr << " ";
		}
	}
	glutPostRedisplay();//redisplay to update the screen with the changes
}

void KeyUp(unsigned char key, int x, int y) {
	// reset the selectedBar value to 0 to unselect the selected bar
	if (key == 'd' || key == 'a')
		rotAng = 0;
	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();
}

//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	if (scene1 == true)
	{
		glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);
	}
	// Bind the ground texture
	else
	{
		glBindTexture(GL_TEXTURE_2D, tex_ground2.texture[0]);	// Bind the ground texture
	}
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-50, 0, -10);
	glTexCoord2f(5, 0);
	glVertex3f(50, 0, -10);
	glTexCoord2f(5, 5);
	glVertex3f(50, 0, 10);
	glTexCoord2f(0, 5);
	glVertex3f(-50, 0, 10);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

int ranged_rand(int min, int max) {
	return min + (int)((double)(max - min) * (rand() / (RAND_MAX + 1.0)));
}


//=======================================================================
// Display Function
//=======================================================================


//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}


//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	/*std::cout << "Camera's eye x :" << Eye.x << "\n";
	std::cout << "Camera's eye y :" << Eye.y << "\n";
	std::cout << "Camera's eye z :" << Eye.z << "\n";

	std::cout << "Camera's at x :" << At.x << "\n";
	std::cout << "Camera's at y :" << At.y << "\n";
	std::cout << "Camera's at z :" << At.z << "\n";

	std::cout << "Camera's up x :" << Up.x << "\n";
	std::cout << "Camera's up y :" << Up.y << "\n";
	std::cout << "Camera's up z :" << Up.z << "\n";*/


	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}


//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	// Loading Model files
	model_coin.Load("Models/coin/Bell Coin/Bells.3DS");
	model_car.Load("Models/car/purplecar/beetle.3DS");
	model_rock.Load("Models/rock/Mesh.3DS");
	// Loading texture files

	tex_ground.Load("Textures/road.bmp");
	tex_ground2.Load("Textures/road2.bmp");
	//tex_ground2.Load("Textures/road2.bmp");
	if (scene1 == true)
		loadBMP(&tex, "Textures/pink.bmp", true);
	else
		loadBMP(&tex, "Textures/galaxy.bmp", true);
}
bool started = true;
bool flagcolor = false;
void  contAnim() {
	if (flagcolor)
	{
		glEnable(GL_LIGHT1);
	}
	else
	{
		glDisable(GL_LIGHT1);
	}
	flagcolor = !flagcolor;
	coinAng += 1;
	rockAng += 1;
	if (won != true) {
		if (started)
		{
			for (int j = 0; j < 15; j++)
			{
				rndx[j] = (float)ranged_rand(-9, 9);
				std::cout << rndx[j];

			}
			if (scene1 == true)
			{
				for (int j = 0; j < 5; j++)
				{
					rx[j] = (float)ranged_rand(-15, 20);
					rz[j] = (float)ranged_rand(-9, 9);
				}

			}
			else {
				for (int j = 0; j < 8; j++)
				{
					rx[j] = (float)ranged_rand(-25, 45);
					rz[j] = (float)ranged_rand(-9, 9);
				}

			}


		}
		started = false;
		if (lives > 0 & laps > 0)
		{
			if (levelrocks == 5)
			{
				carx -= 0.12;
			}
			else
			{
				carx -= 0.15;
			}
		}
		if (score >= 50 && scene1 == true) {
			levelrocks = 8;
			carx = 40;
			score = 0;
			lives = 100;
			laps = 20;
			scene1 = false;
		}
		if (carx <= -25) {
			laps = laps - 1;
			carx = 40;
			started = true;
		}

		//Collisions Part
		for (int k = 0; k < 15; k++) {
			float collisioncoinwithcarud = carx - rndy[k];
			float collisioncoinwithcarlr = carlr - rndx[k];

			if (collisioncoinwithcarud < 0)
			{
				collisioncoinwithcarud *= -1;
			}

			if (collisioncoinwithcarlr < 0)
			{
				collisioncoinwithcarlr *= -1;
			}

			if ((collisioncoinwithcarud < 1 & collisioncoinwithcarud>0)&(collisioncoinwithcarlr < 0.9 & collisioncoinwithcarlr>0))
			{
				rndx[k] = -100;
				score += 1;
			}

		}

		if (scene1 == true) {
			for (int k = 0; k < 5; k++) {
				float collisionrockwithcarud = carx - rx[k];
				float collisionrockwithcarlr = carlr - rz[k];

				if (collisionrockwithcarud < 0)
				{
					collisionrockwithcarud *= -1;
				}

				if (collisionrockwithcarlr < 0)
				{
					collisionrockwithcarlr *= -1;
				}

				if ((collisionrockwithcarud < 1 & collisionrockwithcarud>0)&(collisionrockwithcarlr < 0.9 & collisionrockwithcarlr>0))
				{
					rz[k] = -100;
					lives -= 20;
				}

			}
		}


		else if (scene1 == false) {
			for (int k = 0; k < 8; k++) {
				float collisionrockwithcarud = carx - rx[k];
				float collisionrockwithcarlr = carlr - rz[k];

				if (collisionrockwithcarud < 0)
				{
					collisionrockwithcarud *= -1;
				}

				if (collisionrockwithcarlr < 0)
				{
					collisionrockwithcarlr *= -1;
				}

				if ((collisionrockwithcarud < 1 & collisionrockwithcarud>0)&(collisionrockwithcarlr < 0.9 & collisionrockwithcarlr>0))
				{
					rz[k] = -100;
					lives -= 25;
				}

			}
		}

		//Collisions Part
	}

	glutPostRedisplay();
}


void myDisplay(void)
{
	myInit();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat lightIntensity1[] = { 0.2, 1.0, 1.0, 1.0f };
	GLfloat lightPosition1[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightIntensity1);


	// Draw Ground
	RenderGround();


	//Draw rocks
	if (scene1 == true & laps>0) {
		char* level[20];
		sprintf((char *)level, "Level : 1", "");
		print(px, py3, (char *)level);
		for (int n = 0; n < 5; n++)
		{
			glPushMatrix();
			glTranslatef(rx[n], 0.5, rz[n]);
			glScalef(0.009, 0.009, 0.009);
			glRotatef(rockAng, 0, 1, 0);
			model_rock.Draw();
			glPopMatrix();
		}
	}
	else if (scene1 == false) {
		if (lives > 0) {
			char* level[20];
			sprintf((char *)level, "Level : 2", "");
			print(px, py3, (char *)level);
		}
		for (int n = 0; n < 8; n++)
		{
			glPushMatrix();
			glTranslatef(rx[n], 0.5, rz[n]);
			glScalef(0.009, 0.009, 0.009);
			model_rock.Draw();
			glPopMatrix();
		}
	}


	// Draw Car Model
	glPushMatrix();
	glTranslatef(carx, 0.1, carlr);
	float rotation = 270.0 + rotAng;
	glRotatef(rotation, 0, 1, 0);
	glScalef(0.009, 0.009, 0.009);
	model_car.Draw();
	glPopMatrix();

	// Draw Coin Model
	for (int a = 0; a < 15; a = a + 1) {
		glPushMatrix();
		glTranslatef(rndy[a], 0.5, rndx[a]);
		glRotatef(90.0f, 0, 0, 1);
		glRotatef(coinAng, 0, 1, 0);
		model_coin.Draw();
		glPopMatrix();
	}

	glPushMatrix();


	//draw lives left


	if (lives <= 0)
	{
		char* theLives[20];
		sprintf((char *)theLives, "GAME OVER! NO MORE LIVES!", lives);
		print(px, 4.5, (char *)theLives);
	}
	if (scene1 == false & score >= 50)
	{
		won = true;
		char* won[20];
		sprintf((char *)won, "CONGRATULATIONS YOU WON THE GAME!");
		print(px, 4.5, (char *)won);
	}
	if (laps <= 0)
	{
		char* theLives[20];
		sprintf((char *)theLives, "GAME OVER! REACHED END LINE BEFORE 50 COINS!", lives);
		print(px, 4.5, (char *)theLives);
	}
	if (lives > 0 & laps>0 & won != true)
	{
		char* theLivess[20];
		sprintf((char *)theLivess, "Lives left= %d", lives);
		print(px, py1, (char *)theLivess);

		char* theLaps[20];
		sprintf((char *)theLaps, "Laps left= %d", laps);
		print(px, py1 - 1.5, (char *)theLaps);

		//draw score 
		char* theScore[20];
		sprintf((char *)theScore, "Coin Count = %d", score);
		print(px, py2, (char *)theScore);
		GLUquadricObj * qobj;
		qobj = gluNewQuadric();
		glTranslated(50, 0, 0);
		glRotated(90, 1, 0, 1);
		glBindTexture(GL_TEXTURE_2D, tex);
		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 100, 100, 100);
		gluDeleteQuadric(qobj);
	}


	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(KeyUp);

	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);
	glutKeyboardFunc(key);
	glutIdleFunc(contAnim);

	glutMainLoop();
}