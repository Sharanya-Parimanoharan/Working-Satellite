
#include <stdlib.h>
#include<stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
#include <time.h>
using namespace std;

GLfloat camx = 0 ,xaxis=0;
GLfloat camy = 0,yaxis=0;
GLfloat camz = 0,zaxis=0;



float cc[20][2];

static double x3 = 0.0;

static double x = 0.0;
int flag = 0, count2 = 0, count1 = 0;
float  h = 5, h1 = 6, d1 = 4, g = 1, g1 = 2;

//control waves
float p7 = 37.0, p8 = 75.0, p9 = 10, p10 = 220, p11 = 10, p12 = 220;

GLuint makeaTree;
float x1, y, z;

static double w1 = 0, w2 = 0, w3 = 0;
static bool transmit = false;

GLfloat  retrograde = 0, angle = 1, d = 0  , z_viewvol = -120;




void satellite() {
	

	glRotatef(90, 1, 0, 0);
	//body
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glScaled(1, 0.6, 1);
	glTranslatef(3.0, 0, 0.0);
	glutSolidCube(0.4);
	
	glPopMatrix();

	//Solar Panels

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslatef(3, 0, 0.0);
	//glRotatef(45,1,0,0);
	glScaled(3.7, 0.0, 1);
	glutSolidCube(0.4);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1.2, 0.1, 0.1);
	glTranslatef(3.0, 0, -0.4);
	glScaled(0.5, 0.5, 0.5);
	glutSolidSphere(0.3, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.6, 0.6, 0.3);
	glTranslatef(3.0, 0, 0.4);
	glScaled(0.4, 0.4, 0.3);
	glutSolidTorus(0.3, 0.2, 20, 20);
	glPopMatrix();

}


//screen 1

float z_dis = 100, z_viewPoint = -120;
GLUquadricObj* rocketBody, * rocketPlate;
GLUquadricObj* leftbooster, * maintank, * shuttle;
GLfloat amb[] = { 0.7, 0.7, 0.7, 1.0 };				//Ambient intensity 
GLfloat front_amb_diff[] = { 0.8, 0.7, 0.7,1.0 };	//Front side property
GLfloat back_amb_diff[] = { 0.4,0.7,0.1,1.0 };		//Back side property
GLfloat spe[] = { 0.25,0.25,0.25,1.0 };			//Property for front and back
GLfloat spe2[] = { 80 };			            //Property for front and back
GLfloat pos[] = { -10, 20, -60, 1 };						//light position   

// 0:Sun, 1:Jupiter, 2:RedPlanet, 3:Saturn, 4:BluePlanet, 5: LovePlanet 6: LastPlanet  {R, G, B, Tx, Ty, Tz, Radius}....eachplanet: SolidSphere
float planets[6][7] = { {0.96,0.96,0.5,0,65,-2400,60}, {1,0.1,0.1,80,-30,-3600,50}, {0.96,0.33,0.33,-300,0,-1800,30}
 , {0.67,0.95,0.365,100,0,-800,30} ,{0.16,0.7,0.96,10,-70,-1600,50} };


float random(int min, int max) {            // random function: self defined....needed to throw flames

again: int i = (rand() % 100) / 10;
	if (max < 7) {
		if (i == 8 || i == 7)
			i = -1;
		else if (i == 9)
			i = -2;
	}

	if (i >= min && i <= max)
		return i;
	else
		goto again;
}

float random2(int min, int max) {                // needed to throw flames

again: int i = (rand() % 100);
	if (i >= min && i <= max)
		return i;
	else
		goto again;
}
void fire(int j) {

	glPushMatrix();
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glEnable(GL_BLEND);

	float flamethrower[5][3] = { {7,-20, 8.5}, {6,-20,7.5}, {8,-20,7.5}, {0,-25,0}, {15,-25,0} };    // {T_x, T_y, T_z} for diferent boosters and shuttle

	for (int i = 0; i < 200; i++) {
		glPushMatrix();
		glTranslated(flamethrower[j][0] + random(-3, 3), flamethrower[j][1] - random2(0, 20), flamethrower[j][2] + random(0, 5));
		glTranslated(0, 0, z_viewvol);                // Translation ....must for cylinders

		if (i % 3 == 0) {
			glColor3f(1, 0.46, 0);
			glutWireSphere(0.5, 32, 32);
		}
		else if (i % 2 == 0)
		{
			glColor3f(1, 0.64, 0);
			glutWireTetrahedron();
		}
		else {
			glColor3f(0.95, 0.95, 0.2);
			glutSolidOctahedron();
		}
		glPopMatrix();
	}  // for loop ends here

	//glDisable(GL_BLEND);
	glPopMatrix();
}



void rocket_top() {
	glColor3f(0.6, 0.6, 0.6);
	glPushMatrix();
	glTranslated(7.5, 12, z_viewPoint);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(4.5, 10.0, 32, 32);
	glPopMatrix();
}


void rocket_bottom() {
	glColor3f(0.564, 0.541, 0.517);
	glPushMatrix();
	glTranslated(7.5, -18, z_viewPoint);// for spherical bottom of the rocket
	glRotated(-90, 1, 0, 0);                    // Rotate Cylinder along X-axis to make it look vertical
	glutSolidSphere(4.5, 32, 32);
	glPopMatrix();
}

void rocket_body() {
	glPushMatrix();
	rocketBody = gluNewQuadric();
	gluQuadricDrawStyle(rocketBody, GLU_FILL);
	gluQuadricNormals(rocketBody, GLU_SMOOTH);
	gluQuadricOrientation(rocketBody, GLU_OUTSIDE);

	glColor3f(0.694, 0.694, 0.686);// color for the body cylinder.
	glTranslated(7.5, -18, z_viewPoint);
	glRotated(-90, 1, 0, 0);
	gluCylinder(rocketBody, 4.5, 4.5, 30, 32, 32);

	// Code below draw 5 black windows on rocket body
	glColor3f(0, 0, 0);
	int windows[5] = { -5, -10,-15, -20,-25 };     // 5 windows in y direction
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glRotated(90, 0, 0, 1);//need to rotate twice(around x, then arond z)to keep the same direction with the rocket body.
		glRotated(-90, 1, 0, 0);
		glTranslated(0, windows[i], 0);
		glScalef(6.45, 1, 1); // scale the cube on x_axis. each cube is a little bit longer than the raduis of the cylinder. Therefore, we can see them outside the cylinder.
		glutSolidCube(1.4); // use cube to draw windows. 5 cubes inside the cylender.
		glPopMatrix();
	}

	glPopMatrix();
}



float Shuttle_Plates[3][4] = { {-6,10,1,0.5}, {-11,5,1.9,1}, {-14,3,2.1,1.9} };

GLfloat theta = 0, dt = 0.7, axes[3][3] = { {1,0,0},{0,1,0},{0,0,1} };

float BlackStripPlate[7][4] = { {1.9,-6,13,10.31},  {11.7,-6,-13,10.31}, {-2.7,-11,43,7}, {16.2,-11,-42,7},
		  {-3.8,-14,19,3.17}, {17.2,-14,-19,3.17}, {-3.8,-14,90,21} };

float tx = 0, ty = 0, tz = 0, Trans_y = 0, alpha = 0, T_z = 200, saturn_tx = 0;
unsigned char mainkey = 's';




void shuttle_exhaust() {                    // Use 7 cylindrical rings and 2 cones for each exhaust(Silencer) of Shuttle
	float r = 1, T_y = -16, height;
	float exhaust[3][2] = { {6.7, 12}, {5, 7}, {9, 7} };             // {T_x, T_y}

	for (int j = 0; j < 3; j++) {
		glColor3f(0, 0, 0);
		r = 1;
		T_y = -16;

		for (int i = 0; i < 7; i++) {
			glPushMatrix();                                // for shuttle exhaust
			glTranslated(exhaust[j][0], T_y, exhaust[j][1] + z_viewvol);
			glRotated(-90, 1, 0, 0);                      // Rotation.....must for cylinders
			gluCylinder(shuttle, r, r, 0.40, 32, 32);                  // Main cylinder of shuttle...white color...completes main cylinder
			glPopMatrix();
			T_y = T_y - 0.5;
			r = r + 0.15;
		}
		height = 0;
		glColor3f(0.3, 0.3, 0.3);

		for (int i = 0; i < 2; i++) {
			glPushMatrix();                                // for shuttle exhaust
			glTranslated(exhaust[j][0], T_y, exhaust[j][1] + z_viewvol);
			glRotated(-90, 1, 0, 0);                      // Rotation.....must for cylinders
			height = -T_y - 16;
			glutSolidCone(r, height, 32, 32);                  // One Cone in the exhaust ring
			glPopMatrix();

			glColor3f(.92, 0.75, 0.05);
			T_y = T_y - 0.2;
		}
	}// Main for loop ends here
}

/*  This function builds the main cylndrical body of space shuttle
 */


void rocket_assembly() {
	//rocket_plates();
	rocket_top();
	rocket_body();
	rocket_bottom();
	//shuttleTail();
	//shuttle_exhaust();

}


void AllPlanets() {                              // All planets and Sun

	for (int i = 0; i < 6;i++) {
		glPushMatrix();
		glColor3f(planets[i][0], planets[i][1], planets[i][2]);
		if (i == 3) {
			glTranslated(planets[i][3] + saturn_tx, planets[i][4], planets[i][5]);
			saturn_tx += 1;
		}
		else {
			glTranslated(planets[i][3], planets[i][4], planets[i][5]);                // centre at Tx, Ty, Tz
		}
		glutSolidSphere(planets[i][6], 32, 32);
		glPopMatrix();
	}
}

/// Shuttle code (that launches the satellite)


void shuttle_Discovery(GLfloat theta) {
	glTranslated(0, -3, 0);
	shuttle = gluNewQuadric();
	GLfloat size = 0;
	theta = theta - 45;
	gluQuadricDrawStyle(shuttle, GLU_FILL);
	gluQuadricNormals(shuttle, GLU_SMOOTH);
	gluQuadricOrientation(shuttle, GLU_OUTSIDE);

	glPushMatrix();

	glRotated(theta / 6, 1, 0, 0);
	glTranslated(0.1, 14.7, 0);

	glPushMatrix();
	glScalef(0.5 + size, 0.5 + size, 0.5 + size);// Shuttle Seperate
	glPopMatrix();


	glColor3f(0, 0, 0);
	glPushMatrix();                                // for hemispherical topmost front of shuttle...
	glTranslated(6.7, 13.5, 9 + z_viewvol);
	glutSolidSphere(1.4, 32, 32);
	glPopMatrix();

	glColor3f(0.7, 0.7, 0.7);
	glPushMatrix();                               // for front curve of shuttle...where we have windscreen and stuff
	glTranslated(6.7, 7, 9 + z_viewvol);
	glRotated(-90, 1, 0, 0);
	gluCylinder(shuttle, 3.2, 1.4, 6.5, 32, 32);
	glPopMatrix();

	glColor3f(0.3, 0.3, 0.3);                  // Color for Windscreen
	// 0: middle windscreen, 1: left windscreen, 2: right windscreen {T_x, T_y, T_z, R_y}  R_y: Rotation along y-axis 
	float windscreens[3][4] = { {6.7, 9, 10.9, 0}, {5.3, 8.4, 10.7, 1}, {8, 8.4, 10.7, -1} };

	for (int i = 0; i < 3; i++) {
		glPushMatrix();                     // for front windscreen middle
		glTranslated(windscreens[i][0], windscreens[i][1], windscreens[i][2] + z_viewvol);
		glRotated(45, 1, windscreens[i][3], 0);              // Rotation.....must for cylinders
		gluCylinder(shuttle, 1, 0.5, 1, 32, 32);
		glPopMatrix();
	}


	theta = theta + 45;
	size = size + 0.5;

	glPopMatrix();



	glColor3f(0.7, 0.7, 0.7);
	glPushMatrix();                         // Main Cylindrical Body of Shuttle
	glTranslated(6.7, -12, 9 + z_viewvol);
	glRotated(-90, 1, 0, 0);
	gluCylinder(shuttle, 3.2, 3.2, 19, 32, 32);     // Main cylinder of Shuttle
	glPopMatrix();

	glColor3f(0, 0, 0);                   // Color for Windows
	int windowsY[5] = { 3, 0, -3, -6, -9 };                 // Window pipes in horizontal direction.... 5 Windows in Shuttle
	for (int i = 0; i < 5; i++) {
		glPushMatrix();                     // Cubic Windows 
		glTranslated(6.7, windowsY[i], 10 + z_viewvol);       // change 6 to new value..after using cube.....
		glScalef(6.1, 1, 1);
		glutSolidCube(1);
		glPopMatrix();
	}

	glColor3f(0.6, 0.6, 0.6);

	// merging cylinders
	glPushMatrix();                     // Tail Bottom Tank...1st merging cylinder
	glTranslated(6.7, -15, 9 + z_viewvol);
	glRotated(-90, 1, 0, 0);
	gluCylinder(shuttle, 3.2, 3.2, 3, 32, 32);
	glPopMatrix();

	glPushMatrix();                     // Tail Bottom Tank...2nd merging Cylinder
	glTranslated(6.7, -15, 10 + z_viewvol);
	glRotated(-90, 1, 0, 0);
	gluCylinder(shuttle, 3.2, 3.2, 3, 32, 32);
	glPopMatrix();


	// for shuttle....exhaust....
	shuttle_exhaust();
	//glColor3f(0.4, 0.4, 0.4);
	
}

int BsterCylOrder[] = { 0, 1, 2, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 5, 6, 5, 6, 5, 6, 7, 8 };             // Total 19

// {Base_Radius, Top_Radius, height, all-color}   // Seperate Color for array...
float BsterCylTypes[9][4] = { {1, 0.1, 3, 0.6}, {1, 0.9, 0.5, 0}, {2, 1, 3, 0.6}, {2, 2, 6, 0.6}, {2.05, 2.05, 0.3, 0},
	  {2.2, 1.7, 1, 0}, {2.2, 1.7, 1, 0.4}, {2.7, 2.2, 1.5, 0.4}, {2.4, 1.8, 2, 0.6} };                        // total 9 rings

/*  This function builds the left solid booster of shuttle
 */
void shuttle_leftBooster(bool callfromRight) {               // left solid booster

	leftbooster = gluNewQuadric();				//creates a quadrics object
	gluQuadricDrawStyle(leftbooster, GLU_FILL);		//polygon primitives
	gluQuadricNormals(leftbooster, GLU_SMOOTH);
	gluQuadricOrientation(leftbooster, GLU_OUTSIDE);

	int j, height = 0;       // j to control other array.....height(in the upcoming loop) from prev. loop case...used in next case...
	for (int i = 0; i < 21; i++) {
		j = BsterCylOrder[i];
		height = height + BsterCylTypes[j][2];         // Total Height needed for translation
		glPushMatrix();
		glColor3f(BsterCylTypes[j][3], BsterCylTypes[j][3], BsterCylTypes[j][3]);
		glTranslated(0, 20 - height, 0);         // Flexible to take it up and down        
		glTranslated(0, 0, z_viewvol);
		glRotated(-90, 1, 0, 0);              // Rotation.....must for cylinders
		gluCylinder(leftbooster, BsterCylTypes[j][0], BsterCylTypes[j][1], BsterCylTypes[j][2], 40, 100);
		glPopMatrix();
	}
	if (callfromRight == true)
		return;

	fire(3);
}
/*  This function builds the right solid booster of shuttle
 */

void shuttle_rightBooster() {              // right solid booster
	glPushMatrix();
	glTranslated(15, 0, 0);
	shuttle_leftBooster(true);
	glPopMatrix();
	fire(4);                            // Starts fire for Right Booster
}



// Assembles all part of Space Shuttle: L and R Boosters, Main Tank, Main Shuttle-Discovery
void shuttle_main() {
	shuttle_leftBooster(false);        // false: for not calling from right booster function...
	shuttle_rightBooster();
	rocket_assembly();

	shuttle_Discovery(0);
}




/*  This function gives effect of shuttle seperating from solid boosters & orange color tank
 */
void shuttle_seperate() {
	glPushMatrix();
	

	theta = theta - 45;
	glPushMatrix(); 				    // for left booster
	glRotated(theta, 1, 1, 0);
	shuttle_leftBooster(false);
	glPopMatrix();

	glPushMatrix(); 				    //  for right booster
	glRotated(theta, 1, -1, 0);
	shuttle_rightBooster();
	glPopMatrix();

	glPushMatrix(); 				   //for Orange main tank
	glRotated(theta, -1, 0, 1);
	rocket_assembly();
	
	glPopMatrix();

	glPushMatrix(); 				       //for shuttle
	glRotated(theta / 3, 1, 0, 0);
	shuttle_Discovery(theta);
	glPopMatrix();

	theta = theta + 45;    // Resetting theta

	glPopMatrix();

}

void idle(void) {
	theta = (theta < 360) ? theta + dt : dt; //increment rotation angle
	tx = tx - 0.05;
	ty = ty + 0.08;
	glutPostRedisplay();
}






















































// Second Screen

void spin()
{
	d = d + 0.15;
	if (d > 360)
		d = 0;

	glutPostRedisplay();
}

void moon() {
	glPushMatrix();


	if (retrograde == 0)
	{
		glPushMatrix();

		//Angled Motion
		//if (angle == 0)

		glTranslatef(5.5, 0.2, -1.0);
		glScalef(0.1, 0.1, 0.1);
		glutSolidSphere(3.0, 32, 32);
		glPopMatrix();
	}
	glPopMatrix();
}



void screen2(double ang)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(5+xaxis, 1+yaxis, -10+zaxis, 0, 0, 0, 0, 1, 0);
	glPushMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	GLfloat mat_ambient[] = { 0.0f,1.0f,2.0f,1.0f };
	GLfloat mat_diffuse[] = { 0.0f,1.5f,.5f,1.0f };
	GLfloat mat_specular[] = { 5.0f,1.0f,1.0f,1.0f };
	GLfloat mat_shininess[] = { 50.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	GLfloat lightIntensity[] = { 1.7f,1.7f,1.7f,1.0f };
	GLfloat light_position3[] = { 0.0f,8.0f,10.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position3);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	GLfloat lightIntensity1[] = { 1.7f,1.7f,1.7f,1.0f };
	GLfloat light_position31[] = { -2.0f,8.0f,10.0f,0.0f };

	//glLightfv(GL_LIGHT1, GL_POSITION, light_position31);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity1);

	glEnable(GL_COLOR_MATERIAL);


	glTranslatef(0.0f, 0.0f, -13.0f);

	glRotatef(ang, 0.0f, 1.0f, 0.0f);

	//earth

	glPushMatrix();
	glColor3f(0.3, 0.6, 1);
	//glScaled(0.8,0.04,0.8);
	//glTranslatef(0.0,0,0.0);
	glScalef(45, 45, 45);
	glutSolidSphere(2.0, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glScalef(35, 35, 35);
	satellite();

	//moon revolving
	moon();
	glPopMatrix();

	glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}























//THIRD SCREEN

void waves()
{

	glPushMatrix();
	glTranslatef(0, 20, 0);
	glScaled(0.05, 0.5, 0.1);
	glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-8, 0, 0, 1);
	glTranslatef(-30, 20, 0);
	glScaled(0.05, 0.5, 0.1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(8, 0, 0, 1);
	glTranslatef(-30, 20, 0);
	glScaled(0.05, 0.6, 0.1);
	glutSolidCube(0.5);
	glPopMatrix();

}


void makeCylinder(float height, float base) {
	GLUquadric* obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_LINE);
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, base, base - (0.2 * base), height, 20, 20);
	glPopMatrix();
	glutSwapBuffers();
}

void makeTree(float height, float base) {

	float angle;
	makeCylinder(height, base); 
	glTranslatef(0.0, height, 0.0);
	height -= height * 0.2; 
	base -= base * 0.3;
	for (int a = 0; a < 3; a++) {
		angle = rand() % 50 + 20;
		if (angle > 48)
			angle = -(rand() % 50 + 20);
		if (height > 1) {
			glPushMatrix();
			glRotatef(angle, 1, 0.0, 1);
			makeTree(height, base);
			glPopMatrix();

		}
		else glColor3f(0.0, 1.0 / a, 0.0);
		glutSolidSphere(.2, 10, 10);
	}

}


void twotwoD(int v)//download function for dish.
{
	if (p9 <= 10 && p10 <= 220 && p10 > 105 || p11 <= 10 && p12 <= 220 && p12 > 115)
	{
		p10 = p10 - 9.8;
		p12 = p12 - 9.8;

		//glutPostRedisplay();
	}

	else
	{
		if (p9 <= 10 && p9 > -90)
		{
			p9 = p9 - 9.8;
			//p11 = p11 + 0.08;
			
		}
		if (p11 >= 10 && p11 < 130)
		{
			//p9 = p9 - 0.08;
			p11 = p11 + 9.8;
			
		}
	}

	glutTimerFunc(10, twotwoD, 0);
}


void twotwoU(int v)//upload function for client 2.
{
	if (p7 == 37 && p8 >= 75 && p8 < 225)
	{
		p8 = p8 + 13.4;
	

		//glutPostRedisplay();
	}
	else
	{
		if (p8 >= 220 && p7 > 10)
		{
		p7 = p7 - 13.4;
	
			//glutPostRedisplay();
		}
	}

	if (p7 < 172.0)
	{
		glPushMatrix();
		glColor3f(0.6, 0.6, 0.6);
		//uploading2();
		glPopMatrix();

	}


	else
	{
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		//uploading2();
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.6, 0.6, 0.6);
		//upload2();
		glPopMatrix();
		glEnd();
	}
	glutTimerFunc(10, twotwoU, 0);

}
void three()//displays points as it increments.
{

	glPushMatrix();
	//glPointSize(4.0);
	glPointSize(7.0);
	glColor3f(0.20, 0.20, 2.0);
	glBegin(GL_POINTS);
	glVertex2f(p7, p8);

	glEnd();
	glPopMatrix();
	glFlush();

}
void four()//displays points as it increments.
{

	glPushMatrix();
	//glPointSize(4.0);
	glPointSize(7.0);
	glColor3f(2.0, 0.20, 0.20);
	glBegin(GL_POINTS);
	glVertex2f(p9, p10);
	glVertex2f(p11, p12);
	glEnd();
	glPopMatrix();
	glFlush();

}

void keyboardfun(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		camy += 3;
	}
	if (key == GLUT_KEY_DOWN) {
		camy -= 3;
	}
	if (key == GLUT_KEY_RIGHT) {
		camx += 3;
	}
	if (key == GLUT_KEY_LEFT) {
		camx -= 3;
	}
	//glutPostRedisplay();
}

void apart(float x, float y, float z)
{
	int i;
	int j;
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z + 0.5);
	glVertex3f(x + 45, y, z + 0.5);
	glVertex3f(x + 45, y + 100, z + 0.5);
	glVertex3f(x, y + 100, z + 0.5);
	glEnd();
	glColor3f(0.8, 0.8, 0.8);
	for (j = 0;j < 8;j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0;i < 4;i++)
		{
			glPushMatrix();
			glTranslatef(11 * i, 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(x + 2, y + 98, z);
			glVertex3f(x + 10, y + 98, z);
			glVertex3f(x + 10, y + 88, z);
			glVertex3f(x + 2, y + 88, z);
			glEnd();
			glPopMatrix();
		}
		glPopMatrix();
	}
	glColor3f(0, 0, 0);
	for (j = 0;j < 8;j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0;i < 4;i++)
		{
			glPushMatrix();
			glTranslatef(11 * i, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(x + 2, y + 98, z);
			glVertex3f(x + 10, y + 98, z);
			glVertex3f(x + 10, y + 88, z);
			glVertex3f(x + 2, y + 88, z);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	//front facing camera

	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z + 45 - 0.5);
	glVertex3f(x + 45, y, z + 45 - 0.5);
	glVertex3f(x + 45, y + 100, z + 45 - 0.5);
	glVertex3f(x, y + 100, z + 45 - 0.5);
	glEnd();  	
	glColor3f(0.8, 0.8, 0.8);

	for (j = 0;j < 8;j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0;i < 4;i++)
		{
			glPushMatrix();
			glTranslatef(11 * i, 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(x + 2, y + 98, z + 45);
			glVertex3f(x + 10, y + 98, z + 45);
			glVertex3f(x + 10, y + 88, z + 45);
			glVertex3f(x + 2, y + 88, z + 45);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}glColor3f(0, 0, 0);

	for (j = 0;j < 8;j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0;i < 4;i++)
		{
			glPushMatrix();
			glTranslatef(11 * i, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(x + 2, y + 98, z + 45);
			glVertex3f(x + 10, y + 98, z + 45);
			glVertex3f(x + 10, y + 88, z + 45);
			glVertex3f(x + 2, y + 88, z + 45);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	//back
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_POLYGON);
	glVertex3f(x + 0.5, y, z);
	glVertex3f(x + 0.5, y, z + 45);
	glVertex3f(x + 0.5, y + 100, z + 45);
	glVertex3f(x + 0.5, y + 100, z);
	glEnd();
	glColor3f(0.8, 0.8, 0.8);
	for (j = 0;j < 8;j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0;i < 4;i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, 11 * i);
			glBegin(GL_POLYGON);
			glVertex3f(x, y + 98, z + 2);
			glVertex3f(x, y + 98, z + 10);
			glVertex3f(x, y + 88, z + 10);
			glVertex3f(x, y + 88, z + 2);
			glEnd();
			glPopMatrix();
		}
		glPopMatrix();
	}
	glColor3f(0, 0, 0);
	for (j = 0;j < 8;j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0;i < 4;i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, 11 * i);
			glBegin(GL_LINE_LOOP);
			glVertex3f(x, y + 98, z + 2);
			glVertex3f(x, y + 98, z + 10);
			glVertex3f(x, y + 88, z + 10);
			glVertex3f(x, y + 88, z + 2);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	glColor3f(0.6, 0.6, 0.6);

	glBegin(GL_POLYGON);
	glVertex3f(x + 45 - 0.5, y, z - 0.5);
	glVertex3f(x + 45 - 0.5, y, z + 45 - 0.5);
	glVertex3f(x + 45 - 0.5, y + 100, z + 45 - 0.5);
	glVertex3f(x + 45 - 0.5, y + 100, z - 0.5);
	glEnd(); glColor3f(0.8, 0.8, 0.8);
	for (j = 0;j < 8;j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0;i < 4;i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, 11 * i);
			glBegin(GL_POLYGON);
			glVertex3f(x + 45, y + 98, z + 2);
			glVertex3f(x + 45, y + 98, z + 10);
			glVertex3f(x + 45, y + 88, z + 10);
			glVertex3f(x + 45, y + 88, z + 2);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}
	glColor3f(0, 0, 0);
	for (j = 0;j < 8;j++)
	{

		glPushMatrix();
		glTranslatef(0, -12 * j, 0);
		for (i = 0;i < 4;i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, 11 * i);
			glBegin(GL_LINE_LOOP);
			glVertex3f(x + 45, y + 98, z + 2);
			glVertex3f(x + 45, y + 98, z + 10);
			glVertex3f(x + 45, y + 88, z + 10);
			glVertex3f(x + 45, y + 88, z + 2);
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z - 0.5);
	glVertex3f(x + 45, y, z - 0.5);
	glVertex3f(x + 45, y, z + 45 - 0.5);
	glVertex3f(x, y, z + 45 - 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x, y + 100, z);
	glVertex3f(x + 45, y + 100, z);
	glVertex3f(x + 45, y + 100, z + 45);
	glVertex3f(x, y + 100, z + 45);
	glEnd();
}


void house(float x, float y, float z)
{
	glColor3f(0.01, 0.05, 0.3);  //front wall
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + 30);
	glVertex3f(x, y + 15, z + 30);
	glVertex3f(x, y + 15, z);
	glEnd();

	glColor3f(0.01, 0.05, 0.3);   //back
	glBegin(GL_POLYGON);
	glVertex3f(x - 15, y, z);
	glVertex3f(x - 15, y + 15, z);
	glVertex3f(x - 15, y + 15, z + 30);
	glVertex3f(x - 15, y, z + 30);
	glEnd();

	glColor3f(0.01, 0.05, 0.3);   //side wall (front facing)
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z + 30);
	glVertex3f(x - 15, y, z + 30);
	glVertex3f(x - 15, y + 15, z + 30);
	glVertex3f(x, y + 15, z + 30);
	glEnd();

	glColor3f(0.01, 0.05, 0.3);  //side wall
	glBegin(GL_POLYGON);
	glVertex3f(x - 15, y, z);
	glVertex3f(x - 15, y + 15, z);
	glVertex3f(x, y + 15, z);
	glVertex3f(x, y, z);
	glEnd();

	glColor3f(0.01, 0.05, 1.5);  //basement
	glBegin(GL_POLYGON);
	glVertex3f(x - 15, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + 30);
	glVertex3f(x - 15, y, z + 30);
	glEnd();


	glColor3f(0.51, 0.015, 0.008);  //brown roof
	glBegin(GL_POLYGON);
	glVertex3f(x + 1.69 * 3, y + 3.5 * 3, z);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z + 30);
	glVertex3f(x + 1.69 * 3, y + 3.5 * 3, z + 30);
	glEnd();


	glColor3f(0.51, 0.015, 0.008);
	glBegin(GL_POLYGON);
	glVertex3f(x - 6.69 * 3, y + 3.5 * 3, z);
	glVertex3f(x - 6.69 * 3, y + 3.5 * 3, z + 30);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z + 30);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z);
	glEnd();


	glColor3f(0.1, 0.015, 0.13);  //blue side roof
	glBegin(GL_POLYGON);
	glVertex3f(x, y + 15, z);
	glVertex3f(x - 15, y + 5, z);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z);
	glEnd();

	glColor3f(0.1, 0.015, 0.13);
	glBegin(GL_POLYGON);
	glVertex3f(x, y + 15, z + 30);
	glVertex3f(x - 15, y + 15, z + 30);
	glVertex3f(x - 2.5 * 3, y + 7.5 * 3, z + 30);
	glEnd();
}


void house1()
{
	glPushMatrix();
	house(120, 0.1, 50);

	house(120, 0.1, 90);

	house(160, 0.1, 90);

	house(80, 0.1, 90);

	house(160, 0.1, 50);

	house(80, 0.1, 50);

	house(-130, 0.1, 120);

	house(-130, 0.1, 160);

	house(-90, 0.1, 120);

	house(-60, 0.1, 120);

	house(-90, 0.1, 160);

	house(-60, 0.1, 160);


	apart(150, 0, -150);
	apart(80, 0, -90);

	apart(150, 0, -90);
	apart(150, 0, -30);
	apart(-150, 0, -30);
	apart(-150, 0, -110);

	apart(-150, 0, -180);
	glPopMatrix();
}





void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(2.0f);
	glLoadIdentity();				//identity matrix for preojection 
	gluPerspective(45, 1, 20, 9000);

	makeaTree = glGenLists(1);
	glNewList(makeaTree, GL_COMPILE);
	makeTree(4, 0.2);
	glEndList();

}



void screen3() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_MODELVIEW);
	gluLookAt(0 + camx, 0 + camy, 100+camz, 0, 0, 0, 0, 1, 0);

	

	/* draw the floor */
	/*	glBegin(GL_QUADS);
	glColor3f(0.8, 0.6, 0.4);
	glVertex3f(-200.0, 0.0, -200.0);
	glColor3f(0.8, 0.6, 0.4);
	glVertex3f(-200.0, 0.0, 200.0);
	glColor3f(0.8, 0.6, 0.4);
	glVertex3f(200.0, 0.0, 200.0);
	glColor3f(0.8, 0.6, 0.4);
	glVertex3f(200.0, 0.0, -200.0);
	glEnd();*/
	glFlush();

	glColor3f(0.3, 0.015, 0.13);
	glPushMatrix();
	glTranslatef(-15, 1, -40);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3, 0.015, 0.13);
	glPushMatrix();
	glTranslatef(-15, 1, 20);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3, 0.015, 0.13);
	glPushMatrix();
	glTranslatef(-15, 1, -10);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3, 0.015, 0.13);
	glPushMatrix();
	glTranslatef(-15, 1, -80);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3, 0.015, 0.13);
	glPushMatrix();
	glTranslatef(-15, 1, -120);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3, 0.015, 0.13);
	glPushMatrix();
	glTranslatef(-15, 1, -160);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3, 0.015, 0.13);
	glPushMatrix();
	glTranslatef(190, 1, 90);
	glutSolidCube(7);
	glPopMatrix();

	glColor3f(0.3, 0.015, 0.13);
	glPushMatrix();
	glTranslatef(210, 1, 90);
	glutSolidCube(7);
	glPopMatrix();


	//Tower
	
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(30, 0, 0);
	glRotatef(270, 1, 0, 0);
	glScaled(1.0, 1, 2.0);
	glutWireCone(10, 30, 4, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(30, 65,-2);
	glRotatef(60, 1, 0, 0);
	glScaled(0.7, 1.3, 0.7);
	glutSolidCone(10, 15, 20, 20);
	glPopMatrix();

	//From the tower

	glPushMatrix();
	if (count2 == 1)
	{
		three();
	}
	glPopMatrix();

	//Ack to right building

	glPushMatrix();
	if (count1 == 1)
	{
		four();
	}
	glPopMatrix();


	//Dish
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(160, 110, -80);
	glRotatef(60, 1, 0, 0);
	glScaled(0.7, 1.3, 0.7);
	glutSolidCone(10, 15, 20, 20);
	glPopMatrix();

	//Dish
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-110, 110, -90);
	glRotatef(60, 1, 0, 0);
	glScaled(0.7, 1.3, 0.7);
	glutSolidCone(10, 15, 20, 20);
	glPopMatrix();

	//Saltellite

	glPushMatrix();
	glTranslatef(-100, 280, -90);
	glScalef(35, 35, 35);
	satellite();
	glPopMatrix();


	//Tree


	glPushMatrix();
	glTranslatef(-15, 3, -40);
	glScalef(4, 6, 4);
	glRotatef(x1, 1.0, 0.0, 0.0);
	glRotatef(y, 0.0, 1.0, 0.0);
	glRotatef(z, 0.0, 0.0, 1.0);
	glCallList(makeaTree);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 3, 20);
	glScalef(4, 6, 4);
	glRotatef(x1, 1.0, 0.0, 0.0);
	glRotatef(y, 0.0, 1.0, 0.0);
	glRotatef(z, 0.0, 0.0, 1.0);
	glCallList(makeaTree);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 3, -10);
	glScalef(4, 6, 4);
	glRotatef(x1, 1.0, 0.0, 0.0);
	glRotatef(y, 0.0, 1.0, 0.0);
	glRotatef(z, 0.0, 0.0, 1.0);
	glCallList(makeaTree);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 3, -80);
	glScalef(4, 6, 4);
	glRotatef(x1, 1.0, 0.0, 0.0);
	glRotatef(y, 0.0, 1.0, 0.0);
	glRotatef(z, 0.0, 0.0, 1.0);
	glCallList(makeaTree);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 3, -120);
	glScalef(4, 6, 4);
	glRotatef(x1, 1.0, 0.0, 0.0);
	glRotatef(y, 0.0, 1.0, 0.0);
	glRotatef(z, 0.0, 0.0, 1.0);
	glCallList(makeaTree);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 3, -160);
	glScalef(4, 6, 4);
	glRotatef(x1, 1.0, 0.0, 0.0);
	glRotatef(y, 0.0, 1.0, 0.0);
	glRotatef(z, 0.0, 0.0, 1.0);
	glCallList(makeaTree);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(190, 3, 90);
	glScalef(4, 6, 4);
	glRotatef(x1, 1.0, 0.0, 0.0);
	glRotatef(y, 0.0, 1.0, 0.0);
	glRotatef(z, 0.0, 0.0, 1.0);
	glCallList(makeaTree);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(210, 3, 90);
	glScalef(4, 6, 4);
	glRotatef(x1, 1.0, 0.0, 0.0);
	glRotatef(y, 0.0, 1.0, 0.0);
	glRotatef(z, 0.0, 0.0, 1.0);
	glCallList(makeaTree);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(0, 0.01, -200); /* road */ //main
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(0, 0.01, 200);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(18, 0.01, 200);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(18, 0.01, -200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(8.5, 0.02, -200); /* road */ //white line on the center
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(8.5, 0.02, 200);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(9.5, 0.02, 200);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(9.5, 0.02, -200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(44, 0.01, -200); /* road */  //right middle straight
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(44, 0.01, 160);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(54, 0.01, 160);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(54, 0.01, -200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(54, 0.01, -180); /* road */  //back side right
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(54, 0.01, -160);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(200, 0.01, -160);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(200, 0.01, -180);
	glEnd();




	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(18, 0.01, 160); /* road */  //front right
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(18, 0.01, 170);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(200, 0.01, 170);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(200, 0.01, 160);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-200, 0.01, 90); /* road */  //left front
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-200, 0.01, 100);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(0, 0.01, 100);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(0, 0.01, 90);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-90, 0.01, -200); /* road */  //left middle straight
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-90, 0.01, 90);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-80, 0.01, 90);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(-80, 0.01, -200);
	glEnd();

	house1();
	glutSwapBuffers();

	glFlush();

}


void e()
{

	x3 -= 0.07;
	//sat2(x3);
	screen3();

}

void s()
{

	x3 -= 0.07;
	screen2(x3);
	

}

void S()
{
	if (transmit)
	{
		if (w1 <=80)
			w1 += 0.01;

		if (w1 >= 50 && w2 <= 26.9)
			w2 += 0.01;

		if (w1 >= 12.5 && w3 <= 35)
			w3 += 0.01;
	}

	screen3();
}




void resize(int width, int height)
{
	if (height == 0) height = 1;

	 GLfloat aspect = (GLfloat)width / (GLfloat)height;
	 glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(80.0, width / height, 1.0, 9000.0);

	glTranslatef(0.0, -15.0, -320.0);

	glMatrixMode(GL_MODELVIEW);
}
void dis() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_MODELVIEW);
	glPushMatrix();		//Preserve the CTM that Puts the objects in View Volume.

	glLightfv(GL_LIGHT0, GL_POSITION, pos);   // lighting on shuttle
	

	//glTranslatef(5, 10, -10);
	//rocket_assembly();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);    //Front side
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);      //Back side
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);                //Front and back
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, spe2);              //Front and back

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb); 	//light source
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); 	//for solid cone

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();				//Identity matrix for Modelview 

	glLightfv(GL_LIGHT0, GL_POSITION, pos); //light postion is affected by current modelview
	glEnable(GL_LIGHTING); 	//enable light
	glEnable(GL_LIGHT0); 		//enable gl_light0
	glEnable(GL_COLOR_MATERIAL);
	glScalef(4.5, 4.5, 4.5);

	switch (mainkey) {

	case 's': {
		// Displays all Planets 
		glPushMatrix();
		glTranslated(0, 0, T_z);
		AllPlanets();

		glPopMatrix();

		T_z = T_z + 10;                               // To Move along z-axis towards origin.....for moving effect

		if (theta > 359 && theta < 360)                  // just for resetting the values....when theta reaches 360
		{
			T_z = 0;
			z_viewvol = -120;
		}
		if (theta < 46)
		{
			glPushMatrix(); 				//Preserve CTM for object       
			glTranslated(tx, ty, 0);
			glTranslated(6, 0, -120);
			glRotated(-theta * 1.3, 1, 0, 0);
			glTranslated(-6, 0, 120);
			shuttle_main();                  // Shuttle Main(whole rocket)
			glPopMatrix();

		}
		
		else if (theta >= 46 && theta < 80) {
			glPushMatrix();
			glTranslated(6.7, 0, -120);
			glRotated(-62, 1, 0, 0); 	//rotate light around z
			glTranslated(-6.7, 0, 120);
			shuttle_seperate();

			glPopMatrix();
		}
	
		else {
			glPushMatrix();

			glTranslated(random(-1, 1) * 0.05, Trans_y + random(-1, 1) * 0.05, random(-1, 1) * 0.05);

			glTranslated(6.7, 0, -120);
			glRotated(-48, 1, 0, 0);
			glTranslated(-6.7, 0, 120);

			glPushMatrix();
			glTranslated(6.7, 0, -120);
			glRotated(alpha, 0, 1, 0);
			alpha = alpha + 1;                // for rotation angle...
			glTranslated(-6.7, 0, 120);

			shuttle_Discovery(0);          // Only Shuttle......no boosters
			fire(1);
			if (T_z > 3600)
				z_viewvol -= 0.20;

			glTranslatef(-0.5, 5, -100);
			glScalef(15.5, 15.5, 15.5);
			satellite();					//RELEASING SATELLITE
			glPopMatrix();
			

			glPopMatrix();
		}
		break;        // case 's': start ends here
	}

	case 'o': shuttle_main();                   // Case: 'o'  for only shuttle....display shuttle only
		break;
	case 'p':glPushMatrix();glRotatef(-90, 0, 0, 1); shuttle_seperate();  glPopMatrix();  // case: 'p' for space shuttle seperate view
		break;
	case 'l': shuttle_leftBooster(false);
		break;
	case 'k': shuttle_Discovery(0);
		break;
	
	} 
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHT1);

	glPopMatrix();  //restore CTM for object
	glFlush();
	glutSwapBuffers();

}
void s1() {
	//mainkey = 's';
	theta = 0;
	T_z = 200;
	dis();
}

void print(int x, int y,const char* string)
{
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);
	//get the length of the string to display
	int len = (int)strlen(string);

	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

const char* c = "CS308 Project";
const char* c2= "Working Satellite";
const char* c3 = "S/17/441";

void first() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-5, 10, 0);
	glScalef(1.5, 1.5, 1.5);
	print(-10, 50,c);
	print(-15, 30, c2);
	print(-1, 10, c3);
	glutSwapBuffers();
	glFlush();

}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'z':
		zaxis++;
		break;
	case 'Z':
		zaxis--;
		break;
	case 'x':
		xaxis++;
		break;
	case 'X':
		xaxis--;
		break;
	case 'y':
		yaxis++;
		break;
	case 'Y':
		yaxis--;
		break;
	case 'n':
		glutIdleFunc(s);
		break;
	case 'N':
		camx = 0;
		camy = 0;
		p7 = 37.0; p8 = 75.0; p9 = 10; p10 = 220; p11 = 10; p12 = 220;
		glutIdleFunc(S);
		break;
	case 's':
		mainkey = 's';
		theta = 0;
		T_z = 200;
		break;
	case 'S':
		//mainkey = 's';
		theta = 0;
		glutDisplayFunc(dis);
		break;
	case 'o':
		mainkey = key;
		break;
	case 'q':
		exit(0);
		break;
	case't':
		count2 = 1;
		glutTimerFunc(200, twotwoU, 0);
		break;
	case 'T':
		count1 = 1;
		glutTimerFunc(200, twotwoD, 0);
		break;
	

	}

	//glutPostRedisplay();
}
void m1(int OP) {
	
}
void m(int OP)//function for menu option 5.
{
	if (OP == 1) {
		theta = 0;
		glutDisplayFunc(dis);
	}
	if (OP == 2) {
		glutIdleFunc(s);
	}
	if (OP == 3) {
		camx = 0;
		camy = 0;
		p7 = 37.0; p8 = 75.0; p9 = 10; p10 = 220; p11 = 10; p12 = 220;
		glutIdleFunc(S);
	}
	if (OP == 4) {
		count2 = 1;
		glutTimerFunc(200, twotwoU, 0);
		count1 = 1;
		glutTimerFunc(200, twotwoD, 0);

	}
	if (OP == 6)
	{
		exit(0);
	}
}
void Display_Contol_Menu() {

	fprintf(stdout, "Satellite");
	cout << "\n\nPress 'S' to Start Main Project...." << endl;
	cout << "Press 'n' to see satellite revolving..." << endl;
	cout << "Press 'N' for the third screen" << endl;
	cout << "Press 'z' & 'Z'  'x' & 'X'  'y' & 'Y' to move along z ,x and y axis in screen 2 ..\n";
	cout << "Press Arrow Keys to move along screen 3 ..\n";
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1100, 1100);
	glutInitWindowPosition(100, 10);
	glutCreateWindow("Working Satellite");
	init();
	glutIdleFunc(spin);
	glutIdleFunc(idle);
	Display_Contol_Menu();

	
	glutCreateMenu(m);
	glutAddMenuEntry("To screen 1(Launching of satellite)", 1);
	glutAddMenuEntry("To screen 2(Revolving around earth) ", 2);
	glutAddMenuEntry("To screen 3 (City View)", 3);
	glutAddMenuEntry("To Transfer Data to satellite ", 4);
	glutAddMenuEntry("To Tansfer Data from satellite ", 5);
	glutAddMenuEntry("Exit ", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutSpecialFunc(keyboardfun);
	glutDisplayFunc(first);
	glutKeyboardFunc(keyboard);
	//glutCreateMenu(menu);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;
}