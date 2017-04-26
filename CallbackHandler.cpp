#include "CallbackHandler.h"

using namespace std;


extern int windowW;
extern int windowH;
extern float Near;
extern float Far;
extern float focale;
extern FreeFlyCamera camera;


// Definition de la fonction gerant les interruptions clavier
GLvoid clavier(unsigned char touche, int x, int y) 
{
	switch (touche) 
	{
	
	// Quitter l'application
	case 27:
		exit(0);
		break;
	}

	// Reaffichage de la scene
	glutPostRedisplay();
}

// Fonction de rappel de la souris
GLvoid souris(int bouton, int etat, int x, int y)
{
	if (bouton == GLUT_LEFT_BUTTON) {
		if (etat == GLUT_UP) 
		{
			
			camera.setBouttonUp();

		}
		else  
		{	

			camera.setBouttonDown(x,y);
			
		}
	}
}

// Fonction de gestion du deplacement de la souris
void deplacementSouris(int x, int y) 
{
	camera.ActualiserCamera(x, y);
	glutPostRedisplay();
}


void deplacementSourisPassif(int x, int y)
{
	
}

// Callback de redimensionnement de la fenêtre
GLvoid redimensionner(int w, int h) {
	// Garde les valeurs
	windowW = w;
	windowH = h;
	// eviter une division par 0
	if (windowH == 0)
		windowH = 1;

	float ratio = (float)windowW / (float)windowH;
	std::cout << "Ratio : " << ratio << std::endl;

	// Projection
	glMatrixMode(GL_PROJECTION);

	// Resetting matrix
	glLoadIdentity();

	// Gestion du viewport
	glViewport(0, 0, windowW, windowH);

	// Mise en place de la perspective
	gluPerspective(focale, ratio, Near, Far);

	glMatrixMode(GL_MODELVIEW);

}

// Fonction de gestion du relachement d'une touche clavier
void clavierUp(unsigned char key, int x, int y) 
{
	
}
