#pragma once
#include <iostream>
#include <list>
#include "RenderItems/particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "CircleGenerator.h"
#include "FireworkGenerator.h"
#include "ForceGenerator.h"
#include "ParticleForceRegistry.h"
#pragma once



using namespace std;
const int N_FORCES = 6;
class ParticleSystem {
private:
	// Listas de objetos
	list<particle*> _particles;
	list<ParticleGenerator*> _particle_generators;
	vector<list<particle*>::iterator> _particlesToDelete;

	std::list<Firework*> fireworks_pool;
	FireworkGenerator* fireworkGen;
	std::vector<list<Firework*>::iterator> deadFireworks;

	ParticleForceReg _registry;

	int activeForce = 2;
	bool forcesActive[N_FORCES] = {false};

	bool explosion = false;

	bool x = false;
public:
	// Constructora y destructora
	ParticleSystem();
	~ParticleSystem();

	// Update
	void update(double t);

	// Getters
	ParticleGenerator* getParticleGenerator(string name);

	void generateFireworkSystem();

	void spawnF() { x = !x; }
	void explode() { explosion = !explosion; };

	void setActiveForce(int n) { forcesActive[n] = !forcesActive[n]; };
};
