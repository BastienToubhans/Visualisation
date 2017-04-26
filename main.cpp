
#include <Windows.h>
#include "CallbackHandler.h"
#include <math.h> 
#include <vector>


#define PI 3.14159265


GLboolean boutonClick = false;

// Taille de la fenêtre
int windowW = 640;
int windowH = 480;
float focale = 65.0f;
float Near = 0.1f;
float Far = 100.0f;

//VBO
VBO monVBO;

//Camera
//FreeFlyCamera camera(5.0f,0.6f,0.6f,-0.2f);
FreeFlyCamera camera(5.0f, 0,0,0);

//Les vecteurs de data
vector<float> pos;
vector<float> col;
vector<float> tex;
vector<float> barycentre;

// Déclarations des fonctions de rappel (callbacks)
GLvoid affichage();



//
// Dessine un rectangle avec comme point de reference
// le milieu du cote gauche
void dessineRectangle()
{
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1);
	glVertex2f(0, 0);
	glVertex2f(0, 1);
	glVertex2f(1, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 1, 0);
	glVertex2f(1, 1);
	glVertex2f(0, 1);
	glVertex2f(1, 0);
	glEnd();
}

void generateData()
{
	col.clear();
	tex.clear();
	pos.clear();
	
	//P1
	pos.push_back(0);
	pos.push_back(0);
	pos.push_back(0);
	//P2
	pos.push_back(1);
	pos.push_back(0);
	pos.push_back(0);
	//P3
	pos.push_back(0);
	pos.push_back(1);
	pos.push_back(0);
	//P4
	pos.push_back(1);
	pos.push_back(1);
	pos.push_back(0);
	//P4
	pos.push_back(1);
	pos.push_back(1);
	pos.push_back(-1);
	


}

void calculBarycentre()
{
	//Initialisation
	barycentre.clear();

	float x = 0;
	float y = 0;
	float z = 0;

	//Sommation
	for (int i = 0; i < pos.size()/3; i++)
	{
		x += pos[3 * i];
		y += pos[3 * i	+	1];
		z += pos[3 * i	+	2];
	}

	//Moyenne
	x = 3 * x / pos.size();
	y = 3 * y / pos.size();
	z = 3 * z / pos.size();

	//Assignation
	barycentre.push_back(x);
	barycentre.push_back(y);
	barycentre.push_back(z);

}

// Definition de la fonction d'affichage
GLvoid affichage(){
   // Effacement du frame buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // Definition de la position de la camera et ou elle regarde
   gluLookAt(	camera.getEye().getVx()	, camera.getEye().getVy()	, camera.getEye().getVz()	,
				camera.getAt().getVx()	, camera.getAt().getVy()	, camera.getAt().getVz()	,
				camera.getUp().getVx()	, camera.getUp().getVy()	, camera.getUp().getVz());

   monVBO.DrawBuffer();
   
   glFlush();
   glutSwapBuffers();
}


int main (int argc, char *argv[])
{
   // Initialisation de GLUT
   glutInit(&argc, argv);
   // Choix du mode d'affichage (ici RVB)
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   // Position initiale de la fenetre GLUT
   glutInitWindowPosition(200, 200);
   // Taille initiale de la fenetre GLUT
   glutInitWindowSize(windowW, windowH);
   // Creation de la fenetre GLUT
   glutCreateWindow("Automate Cellulaire");
   
   // Initialisation de GLEW
   glewInit();

   // Définition de la couleur d'effacement du framebuffer
   glClearColor(0.7f, 0.8f, 1.0f, 0.0f);
   
   // Initialement on active le Z-buffer
   glEnable(GL_DEPTH_TEST);
   
   // Shading model
   glShadeModel(GL_SMOOTH);

   //Initialisation
   generateData();
   calculBarycentre();
   cout << barycentre[0] << ", " << barycentre[1] << ", " << barycentre[2] << endl;
   camera.settargetPos(barycentre[0], barycentre[1], barycentre[2]);
   monVBO.FeedPos(pos);
   monVBO.FeedCol(col);
   monVBO.BuildBuffer();
   
   // Definition des fonctions de callback
   glutDisplayFunc(affichage);
   glutKeyboardFunc(clavier);
   glutKeyboardUpFunc(clavierUp);
   glutMouseFunc(souris);
   glutMotionFunc(deplacementSouris);
   glutReshapeFunc(redimensionner);
   glutPassiveMotionFunc(deplacementSourisPassif);
   
   // Lancement de la boucle infinie GLUT
   glutMainLoop();
   
   return 0;
}


