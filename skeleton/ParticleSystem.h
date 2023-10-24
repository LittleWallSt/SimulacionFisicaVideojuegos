#pragma once
#include <iostream>
#include <list>
#include "RenderItems/particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"

#pragma once



using namespace std;

class ParticleSystem {
private:
	// Listas de objetos
	list<particle*> _particles;
	list<ParticleGenerator*> _particle_generators;

	// Vector de objetos a destruir
	vector<list<particle*>::iterator> _particlesToDelete;

public:
	// Constructora y destructora
	ParticleSystem();
	~ParticleSystem();

	// Update
	void update(double t);

	// Getters
	ParticleGenerator* getParticleGenerator(string name);

	void generateFireworkSystem();
};
