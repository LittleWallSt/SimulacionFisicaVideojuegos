#pragma once
#include "ParticleGenerator.h"
#include "RenderItems/particle.h"

class GaussianParticleGenerator : public ParticleGenerator {
private:
	// Velocidad
	normal_distribution<float>* vX;
	normal_distribution<float>* vY;
	normal_distribution<float>* vZ;

	// Posición
	normal_distribution<float>* pX;
	normal_distribution<float>* pY;
	normal_distribution<float>* pZ;

	int _n_particles;

public:
	// Constructora y destructora
	GaussianParticleGenerator(Vector3 iniPos, Vector3 var, float prob, particle* m,  int _n = 1, bool st = true);
	virtual ~GaussianParticleGenerator();

	// Método abstracto
	virtual list<particle*> generateParticles();
};

