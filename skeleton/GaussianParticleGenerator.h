#pragma once
#include "ParticleGenerator.h"
#include "RenderItems/particle.h"
#include <iostream>

class GaussianParticleGenerator : public ParticleGenerator {
private:
	normal_distribution<float>* vX;
	normal_distribution<float>* vY;
	normal_distribution<float>* vZ;
	normal_distribution<float>* pX;
	normal_distribution<float>* pY;
	normal_distribution<float>* pZ;

	//numero de particulas a generar por update
	int _n_particles;

public:
	// Constructora y destructora
	GaussianParticleGenerator(Vector3 iniPos, Vector3 var, float prob, particle* m,  int _n = 1, bool st = true);
	virtual ~GaussianParticleGenerator();

	void newVars() {
		// Distribuciones de posición
		
		pX = new normal_distribution<float>(iniPos.x, meanVar.x / 2.0f);
		pY = new normal_distribution<float>(iniPos.y, meanVar.y / 2.0f);
		pZ = new normal_distribution<float>(iniPos.z, meanVar.z / 2.0f);
		//std::cout << iniPos.x << "!" << std::endl;
	}
	// Método abstracto
	virtual list<particle*> generateParticles();
};

