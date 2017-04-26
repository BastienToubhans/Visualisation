#ifndef FREEFLYCAMERA_H
#define FREEFLYCAMERA_H

#include "vector3d.h"
#include <string>
#include <cmath>
using namespace std;

class FreeFlyCamera
{

private:
	// angles de rotation (coordonnees spheriques) pour calculer le vecteur vision de la camera
	float angleTheta;
	float anglePhi;
	float rayon;

	// Camera position
	Vector3D Eye;
	//Camera Aim
	Vector3D At;
	//Camera Upworld (always (0,1,0)
	Vector3D Up;

	// les increments des angles theta et phi
	// egales a 0 quand on n'appuie sur aucune touche
	float deltaTheta;
	float deltaPhi;

	// coordonnes de la souris au moment du clic gauche
	int xOrigin;
	int yOrigin;

	// Sensibilite de deplacement
	float mouseRotSensitivity;

	// Near and Far Plane
	float close;
	float distant;

	// Focale
	float focale;

public:
	void setMouseSensitivity(float MouseSensitivity);
	

	Vector3D getEye();
	Vector3D getAt();
	Vector3D getUp();

	void setcamPos(float camPosX, float camPosY, float camPosZ);
	void settargetPos(float atPosX, float atPosY, float atPosZ);
	void setBouttonUp();
	void setBouttonDown(int x, int y);

	bool ActualiserCamera(int x, int y);

	FreeFlyCamera(float _rayon, float atPosX, float atPosY, float atPosZ);
	~FreeFlyCamera();
};

#endif // FREEFLYCAMERA_H