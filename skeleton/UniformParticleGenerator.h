#pragma once

#include <list>
#include "core.hpp"
#include "RenderItems/particle.h"
#include "ParticleGenerator.h"
#include <string>
#include <random>

using namespace std;
class UniformParticleGenerator : public ParticleGenerator {
private:
	uniform_real_distribution<float>* vX;
	uniform_real_distribution<float>* vY;
	uniform_real_distribution<float>* vZ;
	uniform_real_distribution<float>* pX;
	uniform_real_distribution<float>* pY;
	uniform_real_distribution<float>* pZ;

	//numero de particulas por update
	int _n_particles;
	

public:
	// Constructora y destructora
	UniformParticleGenerator(Vector3 iniPos, Vector3 var, float prob, particle* m,int nPart = 1 ,bool st = true);
	virtual ~UniformParticleGenerator();

	// Método abstracto
	virtual list<particle*> generateParticles();
};

