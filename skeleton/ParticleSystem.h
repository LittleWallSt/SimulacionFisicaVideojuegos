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
const int EXPLOSION = 5;
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

	void AnchSpringGen() {
		particle* p = new particle(10, { 0,50,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 0, 1, 1, 1 }, CreateShape(physx::PxBoxGeometry(1, 1, 1)));
			//new particle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 5, 1e10);
		
		AnchoredSpringFG* spring = new AnchoredSpringFG(Vector3(0, 70, 0), 1, 5);
		_registry.addReg(spring, p);
		
		DragForceGen* drag = new DragForceGen(1.5f, 0);
		GravForceGen* grav = new GravForceGen(Vector3(0, -9.8, 0), 100);
		_registry.addReg(drag, p);
		_registry.addReg(grav, p);
		_particles.push_back(p);
	}

	void SlinkyGen() {
		particle* p = new particle(10, { 0,50,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 0, 1, 1, 1 }, CreateShape(physx::PxBoxGeometry(1, 1, 1)));
		//new particle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 5, 1e10);

		AnchoredSpringFG* spring = new AnchoredSpringFG(Vector3(0, 70, 0), 1, 5);
		_registry.addReg(spring, p);

		DragForceGen* drag = new DragForceGen(1.5f, 0);
		GravForceGen* grav = new GravForceGen(Vector3(0, -9.8, 0), 100);
		_registry.addReg(drag, p);
		_registry.addReg(grav, p);
		_particles.push_back(p);

		particle* p2 = new particle(10, { 0,40,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 0,1,1,1 }, CreateShape(PxBoxGeometry(1, 1, 1)));

		SpringForceGen* spring1 = new SpringForceGen(p, 1, 5);
		SpringForceGen* spring2 = new SpringForceGen(p2, 1, 5);
		_registry.addReg(spring1, p2);
		_registry.addReg(spring2, p);
		
		_registry.addReg(drag, p2);
		_registry.addReg(grav, p2);
		_particles.push_back(p2);

		p = new particle(10, { 0,30,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 0, 1, 1, 1 }, CreateShape(physx::PxBoxGeometry(1, 1, 1)));

		spring1 = new SpringForceGen(p, 1, 5);
		spring2 = new SpringForceGen(p2, 1, 5);
		_registry.addReg(spring1, p2);
		_registry.addReg(spring2, p);

		_registry.addReg(drag, p);
		_registry.addReg(grav, p);
		_particles.push_back(p);

		p2 = new particle(10, { 0,20,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 0, 1, 1, 1 }, CreateShape(physx::PxBoxGeometry(1, 1, 1)));

		spring1 = new SpringForceGen(p, 1, 5);
		spring2 = new SpringForceGen(p2, 1, 5);
		_registry.addReg(spring1, p2);
		_registry.addReg(spring2, p);

		_registry.addReg(drag, p2);
		_registry.addReg(grav, p2);
		_particles.push_back(p2);

		p = new particle(10, { 0,10,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 0, 1, 1, 1 }, CreateShape(physx::PxBoxGeometry(1, 1, 1)));

		spring1 = new SpringForceGen(p, 1, 5);
		spring2 = new SpringForceGen(p2, 1, 5);
		_registry.addReg(spring1, p2);
		_registry.addReg(spring2, p);

		_registry.addReg(drag, p);
		_registry.addReg(grav, p);
		_particles.push_back(p);
	}

	void SpringGen() {
		particle* p1 = new particle(10, { 10,10,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 0,0,1,0}, CreateShape(PxBoxGeometry(1,1,1)));
		particle* p2 = new particle(10, { -10, 10,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 0,0,1,0 }, CreateShape(PxBoxGeometry(1, 1, 1)));
		
		SpringForceGen* spring1 = new SpringForceGen(p1, 2, 5);
		SpringForceGen* spring2 = new SpringForceGen(p2, 2, 5);
		_registry.addReg(spring1, p2);
		_registry.addReg(spring2, p1);
		
		DragForceGen* drag = new DragForceGen(0.5, 0);
		_registry.addReg(drag, p1);
		_registry.addReg(drag, p2);
		_particles.push_back(p1);
		_particles.push_back(p2);
	}

	void BungeeGen() {
		particle* p1 = new particle(10, { 10,10,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 0,0,0,0 }, CreateShape(PxBoxGeometry(1, 1, 1)));
		particle* p2 = new particle(10, { -10,10,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 0,0,0,0 }, CreateShape(PxBoxGeometry(1, 1, 1)));
		BungeeForceGen* spring1 = new BungeeForceGen(p1, 2, 10);
		BungeeForceGen* spring2 = new BungeeForceGen(p2, 2, 10);
		_registry.addReg(spring1, p2);
		_registry.addReg(spring2, p1);
		DragForceGen* drag = new DragForceGen(0.05, 0);
		_registry.addReg(drag, p1);
		_registry.addReg(drag, p2);
		_particles.push_back(p1);
		_particles.push_back(p2);
	}

	void BuoyancyGen() {
		particle* liquid = new particle(0, { 0, 0, 0 }, { 0,0,0 }, { 0,0,0}, -300, Vector4(0, 0, 0.3, 0),CreateShape(PxBoxGeometry(20, 2, 20)));
		particle* p = new  particle(10, { 0, 20, 0 }, Vector3(0, 0.0f, 0), Vector3(0, 0, 0), -300, Vector4(1, 1, 0, 0), CreateShape(PxBoxGeometry(3, 3, 3)));
			//particle(10, { 1, 40, 1 }, { 0,0,0 }, { 0,0,0,0 }, CreateShape(PxBoxGeometry(3, 3, 3)));
		p->setDamping(0.99);


		DragForceGen* drag = new DragForceGen(1.5f, 0);
		BuoyancyForceGen* bg = new BuoyancyForceGen(5, 27, 1, liquid);
		GravForceGen* gg = new GravForceGen(Vector3(0, -9.8, 0), 0);
		_registry.addReg(bg, p);
		_registry.addReg(gg, p);
		_registry.addReg(drag, p);

		_particles.push_back(p);
	}
};
