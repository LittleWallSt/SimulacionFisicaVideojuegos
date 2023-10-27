#pragma once
#include "Particle2.h"
#include <list>

using namespace std;

const float FIREWORK_RAD = 3;

//clase que hereda de particle
class Firework : public Particle {
protected:
	//Generacion y numero de hijos por generacion
	int gen, nSons;
	float maxLife;

public:
	//constructora
	Firework(Vector3 p, Vector3 v, Vector3 a, Vector4 color, float lt, int g, int n);
	virtual ~Firework();

	//getters
	int getGeneration() { return gen; }
	int getNumberSons() { return nSons; }
	float getLifetime() { return maxLife; }

	//clonadora
	virtual Firework* clone(Vector3 p, Vector3 v, float lt, int s) const;
};