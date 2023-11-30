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
const int MASS_FACTOR = 100;


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

	particle* buoyancy_particle;
	particle* buoyancy_liquid;
	particle* spring_particle = nullptr;

	BuoyancyForceGen* buoyancy_gen;
	bool buoyancy = false;


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
		
		AnchoredSpringForceGen* spring = new AnchoredSpringForceGen(Vector3(0, 80, 0), 1, 5);
		_registry.addReg(spring, p);

		
		
		DragForceGen* drag = new DragForceGen(1.5f, 0);
		GravForceGen* grav = new GravForceGen(Vector3(0, -9.8, 0), 100);
		_registry.addReg(drag, p);
		_registry.addReg(grav, p);

		spring_particle = spring->getParticle();
		_particles.push_back(p);
	}

	void SlinkyGen() {
		particle* p = new particle(10, { 0,50,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 0, 1, 1, 1 }, CreateShape(physx::PxBoxGeometry(1, 1, 1)));

		AnchoredSpringForceGen* spring = new AnchoredSpringForceGen(Vector3(0, 70, 0), 1, 5);
		_registry.addReg(spring, p);

		DragForceGen* drag = new DragForceGen(1.5f, 0);
		GravForceGen* grav = new GravForceGen(Vector3(0, -9.8, 0), 100);
		_registry.addReg(drag, p);
		_registry.addReg(grav, p);
		
		spring_particle = spring->getParticle();
		
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
		
		DragForceGen* drag = new DragForceGen(1.5f, 0);
		_registry.addReg(drag, p1);
		_registry.addReg(drag, p2);
		_particles.push_back(p1);
		_particles.push_back(p2);
	}

	void RubberBandGenerator() {
		particle* p1 = new particle(10, { 0,20,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 1,0,1,0 }, CreateShape(PxBoxGeometry(1, 1, 1)));
		particle* p2 = new particle(10, { 0, 10,0 }, { 0,0,0 }, { 0,0,0 }, -300, { 1,0,1,0 }, CreateShape(PxBoxGeometry(1, 1, 1)));

		RubberBandGen* spring1 = new RubberBandGen(p1, 2, 5);
		RubberBandGen* spring2 = new RubberBandGen(p2, 2, 5);
		_registry.addReg(spring1, p2);
		_registry.addReg(spring2, p1);

		DragForceGen* drag = new DragForceGen(1.5f, 0);
		_registry.addReg(drag, p1);
		_registry.addReg(drag, p2);
		_particles.push_back(p1);
		_particles.push_back(p2);
	}

	void BuoyancyGen() {
		buoyancy_liquid = new particle(0, { 0, 0, 0 }, { 0,0,0 }, { 0,0,0}, -300, Vector4(0, 0, 0.3, 0),CreateShape(PxBoxGeometry(20, 2, 20)));
		buoyancy_particle = new  particle(100, { 0, 20, 0 }, Vector3(0, 0.0f, 0), Vector3(0, 0, 0), -300, Vector4(1, 1, 0, 0), CreateShape(PxBoxGeometry(3, 3, 3)));
		buoyancy_particle->setDamping(0.99);
		buoyancy_particle->setScale({ 3,3,3 });



		DragForceGen* drag = new DragForceGen(1.5f, 0);
		BuoyancyForceGen* bg = new BuoyancyForceGen(5, buoyancy_particle->getVolume(), 1000, buoyancy_liquid);
		GravForceGen* gg = new GravForceGen(Vector3(0, -9.8, 0), 0);

		buoyancy_gen = bg;

		_registry.addReg(bg, buoyancy_particle);
		_registry.addReg(gg, buoyancy_particle);
		_registry.addReg(drag, buoyancy_particle);

		_particles.push_back(buoyancy_particle);
	}

	void manuallyKillAllParticles() {
		for (auto it = _particles.begin(); it != _particles.end(); it++) {
			_particlesToDelete.push_back(it);
		}
		if (buoyancy) {
			particle* p = buoyancy_liquid;
			buoyancy_liquid = nullptr;
			delete p;
		}
		if (spring_particle != nullptr) {
			particle* p = spring_particle;
			spring_particle = nullptr;
			delete p;
		}
	}
	void keyPress(unsigned char key) {
		switch (toupper(key))
		{
		case 'I':
			manuallyKillAllParticles();
			buoyancy = false;
			SlinkyGen();
			break;
		case 'B':
			manuallyKillAllParticles();
			buoyancy = true;
			BuoyancyGen();
			break;
		case 'G':
			manuallyKillAllParticles();
			buoyancy = false;
			SpringGen();
			break;
		case 'H':
			manuallyKillAllParticles();
			buoyancy = false;
			AnchSpringGen();
			break;
		case 'R':
			manuallyKillAllParticles();
			buoyancy = false;
			AnchSpringGen();
			break;
		case 'T':
			manuallyKillAllParticles();
			buoyancy = false;
			RubberBandGenerator();
			break;

		//Controlador de volumen y masa de la particula a sumergir
		case 'M':
			if (buoyancy) {
				buoyancy_particle->setMass(buoyancy_particle->getMass() + MASS_FACTOR);
				cout << buoyancy_particle->getMass() << endl;
			}
			break;
		case 'L':
			if (buoyancy) {
				if(buoyancy_particle->getMass() > 10)buoyancy_particle->setMass(buoyancy_particle->getMass() - MASS_FACTOR);
				if (buoyancy_particle->getMass() < 0) { buoyancy_particle->setMass(1); }
			}
			break;
		
		//Incremento del tamaño en X
		case 'X':
			if (buoyancy) {
				
				buoyancy_particle->addScaleX();

				if (buoyancy_particle->getScale().x > 0) {
					buoyancy_particle->applyScaleBox();
					buoyancy_gen->setVolume(buoyancy_particle->getVolume());
				}
			}
			break;
		
		//Incremento del tamaño en Y
		case 'Y':
			if (buoyancy) {
				
				buoyancy_particle->addScaleY();

				if (buoyancy_particle->getScale().y > 0) {
					buoyancy_particle->applyScaleBox();
					buoyancy_gen->setVolume(buoyancy_particle->getVolume());
				}
			}
			break;
		
		//Incremento del tamaño en Z
		case 'Z':
			if (buoyancy) {
				
				buoyancy_particle->addScaleZ();

				if (buoyancy_particle->getScale().z > 0) { 
					buoyancy_particle->applyScaleBox();
					buoyancy_gen->setVolume(buoyancy_particle->getVolume());
				}
			}
			break;

		//Decremento de la X
		case 'F':
			if (buoyancy) {

				if(buoyancy_particle->getScale().x > 1)buoyancy_particle->removeScaleX();

				if (buoyancy_particle->getScale().x > 0) {
					buoyancy_particle->applyScaleBox();
					buoyancy_gen->setVolume(buoyancy_particle->getVolume());
				}
			}
			break;

		//Decremento de la Y
		case 'C':
			if (buoyancy) {

				if (buoyancy_particle->getScale().y > 1)buoyancy_particle->removeScaleY();

				if (buoyancy_particle->getScale().y > 0) {
					buoyancy_particle->applyScaleBox();
					buoyancy_gen->setVolume(buoyancy_particle->getVolume());
				}
			}
			break;
			//Decremento de la Z
		case 'V':
			if (buoyancy) {

				if (buoyancy_particle->getScale().z > 1)buoyancy_particle->removeScaleZ();

				if (buoyancy_particle->getScale().z > 0) {
					buoyancy_particle->applyScaleBox();
					buoyancy_gen->setVolume(buoyancy_particle->getVolume());
				}
			}
			break;
		
		}
		
	}

	
};
