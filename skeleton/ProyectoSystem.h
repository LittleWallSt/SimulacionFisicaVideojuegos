#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "RigidBodyForceRegistry.h"
#include "RigidBodyForceGen.h"
#include "RenderItems/particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "CircleGenerator.h"
#include "FireworkGenerator.h"
#include "ForceGenerator.h"
#include "ParticleForceRegistry.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <vector>

using namespace physx;

class ProyectoSystem
{
protected:
	PxScene* _scene;
	PxPhysics* _physics;

	//RigidBodies
	list<RigidBody*> _rigids;
	list<RigidBodyGenerator*> _RBGens;
	list<RigidBodyForceGen*> _forceGens;
	RigidBodyGenerator* gen = nullptr;

	RigidBodyForceGen* wind;
	RigidBodyExplosionGen* expl;

	RigidBodyForceRegistry _registry;
	PxRigidStatic* floor;
	RenderItem* floorRenderItem;
	//Particulas
	list<particle*> _particles;
	list<ParticleGenerator*> _particle_generators;
	vector<list<particle*>::iterator> _particlesToDelete;

	GaussianParticleGenerator* spawnPoint;
	ParticleForceReg _registryP;
	TornadoForceGen* tornado;
	//Fireworks
	std::list<Firework*> fireworks_pool;
	FireworkGenerator* fireworkGen;
	std::vector<list<Firework*>::iterator> deadFireworks;
	
	//Bounding box para el suika
	RenderItem* frontRender;
	RenderItem* backRender;
	RenderItem* leftRender;
	RenderItem* rightRender;

	PxRigidStatic* frontPlane;
	PxRigidStatic* backPlane;
	PxRigidStatic* leftPlane;
	PxRigidStatic* rightPlane;

	//temporizador
	chrono::steady_clock::time_point lastSpawnTime = chrono::steady_clock::now();

	//variables especiales para el juego
	PxVec3 spawnPos = { 0,200,0 };
	int explosions = 3;
	int windCounter = 3;

	void generateRB() {
		RigidBody* fruit = new RigidBody(_scene, _physics, spawnPos, { 1,0,0,1 }, { 0, -10, 0 }, { 10, 10, 10 }, 10, -100.0f, Sphere);
		_rigids.push_back(fruit);
	}

	void addGen(RigidBodyForceGen* gen) {
		if (gen->active) {
			for (auto rb : _rigids) {
				_registry.addReg(gen, rb);

			}
		}

	}

public:
	ProyectoSystem(PxScene* scene, PxPhysics* phys);
	void update(double t);
	void demo();
	~ProyectoSystem();

	void keyPress(unsigned char key) {
		switch (toupper(key)) {
		case '6': {
			//expl->setActive();
			//expl->resetDuration(EXPLOSION_DURATION);
		}

				break;
		case 'Q':
			generateRB();
			break;
		case 'J':
			if (spawnPos.x > -70) {
				spawnPos.x -= 5;
				spawnPoint->setPos(spawnPos);
				tornado->moveCenter(spawnPos);
				spawnPoint->newVars();
			}
			std::cout << spawnPos.x<<endl;
			
			break;
		case 'K':
			if (spawnPos.x < 70) {
				spawnPos.x += 5;
				spawnPoint->setPos(spawnPos);
				tornado->moveCenter(spawnPos);
				spawnPoint->newVars();

			}
			std::cout << spawnPos.x << endl;

			break;


		}
	}
};

