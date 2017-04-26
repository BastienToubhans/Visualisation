#define _USE_MATH_DEFINES
#include "FreeFlyCamera.h"

// CONSTRUCTOR
FreeFlyCamera::FreeFlyCamera(float _rayon, float atPosX, float atPosY, float atPosZ)
{

	//Initialisation
	deltaTheta = 0.0f;
	deltaPhi = 0.0f;
	xOrigin = -1;
	yOrigin = -1;
	mouseRotSensitivity = 0.01f;
	rayon = _rayon;

	// Initialisation de  la position de la camera
	Eye = Vector3D(rayon,0,0);

	Up = Vector3D(0, 1, 0);
	
	// Initialisation de la cible a partir de la camera et du vecteur vision
	At = Vector3D(atPosX, atPosY, atPosZ);

	// Initialisation des angles de rotation (coordonnees spheriques) pour calculer le vecteur vision de la camera
	angleTheta = 0.0f;
	anglePhi = 0.0f;
}

// DESTRUCTOR
FreeFlyCamera::~FreeFlyCamera()
{
}

// GETTERS
Vector3D FreeFlyCamera::getEye(){return Eye;}
Vector3D FreeFlyCamera::getAt(){ return At; }
Vector3D FreeFlyCamera::getUp(){ return Up; }

// SETTERS
void FreeFlyCamera::setMouseSensitivity(float MouseSensitivity){ mouseRotSensitivity = MouseSensitivity; }


void FreeFlyCamera::setcamPos(float camPosX, float camPosY, float camPosZ)
{
	Eye.setVx(camPosX);
	Eye.setVy(camPosY);
	Eye.setVz(camPosZ);
}
void FreeFlyCamera::settargetPos(float atPosX, float atPosY, float atPosZ)
{
	At.setVx(atPosX);
	At.setVy(atPosY);
	At.setVz(atPosZ);
}


// Fonction de calcul des angles de rotation de la camera lorsque le clic gauche de la souris est enfonce
void FreeFlyCamera::setBouttonUp()
{
	angleTheta += deltaTheta;
	anglePhi += deltaPhi;

	cout << "theta : " << angleTheta << endl;
	cout << "phi : " << anglePhi << endl;
	xOrigin = -1;
	yOrigin = -1;
}

// Fonction de stockage des coordonnees de la souris au moment d'un clic gauche
void FreeFlyCamera::setBouttonDown(int x, int y)
{
	xOrigin = x;
	yOrigin = y;
}


// Fonction de mise a jour des reglages de la camera
bool FreeFlyCamera::ActualiserCamera(int x, int y)
{
	if (xOrigin >= 0 || yOrigin >= 0) 
	{
		// Mise a jour des deltas des angles theta et phi
		deltaTheta = (x - xOrigin)*mouseRotSensitivity;
		deltaPhi = -(y - yOrigin)*mouseRotSensitivity;

		// Calcul du nouveau vecteur vision :
		Eye.setVx(rayon*sin(anglePhi + deltaPhi)*cos(angleTheta + deltaTheta));
		Eye.setVy(-rayon*cos(anglePhi + deltaPhi));
		Eye.setVz(rayon*sin(anglePhi + deltaPhi)*sin(angleTheta + deltaTheta));


		return true;
	}

	return false;
}