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
#include "SuikaSingleton.h"
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
	//RigidBody* fruit;

	//RigidBodyForceGen* wind;
	//RigidBodyExplosionGen* expl;

	RigidBodyForceRegistry _registry;
	PxRigidStatic* floor;
	RenderItem* floorRenderItem;
	//Particulas
	list<particle*> _particles;
	list<ParticleGenerator*> _particle_generators;
	vector<list<particle*>::iterator> _particlesToDelete;

	particle* model;

	//Flotacion
	particle* buoyancy_particle;
	particle* buoyancy_liquid; 
	BuoyancyForceGen* buoyancy_gen;

	particle* buoyancy_particle2;
	particle* buoyancy_liquid2;
	//BuoyancyForceGen* buoyancy_gen2;

	GaussianParticleGenerator* spawnPoint;
	ParticleForceReg _registryP;
	TornadoForceGen* tornado;
	ExplosionGen* expl;
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

	int n = 2;
	int c = 0;
	int highestColor = 0;
	int nextColor = 1;
	//variables especiales para el juego
	PxVec3 spawnPos = { 0,200,0 };
	bool explosion = false;
	//int explosions = 3;
	//int windCounter = 3;
	int points = 0;
	double timer = 0;

	//Generador de rigidbodies para el suika
	void generateRB() {
		//explosion = true;
		//expl->refreshDuration();
		//expl->updateCenter(spawnPos);
		tornado->setActive();
		
		RigidBody* fruit = new RigidBody(_scene, _physics, spawnPos, fruitColors[color(c)], {0, -10, 0}, {3*(float(c+1)), 3* (float(c + 1)), 3 * (float(c + 1)) }, 10, -100.0f, (type)n);
		_rigids.push_back(fruit);
		fruit->setCouleur((color)c);
		SuikaInstance().reference.insert({ fruit->getActor(), fruit });
		points += (c + 1) * 10;
		n = rand() % 3;
		c = rand() % 3;
		model->setColor(fruitColors[color(c)]);
		pointsPrintOut();
		if (highestColor < c) {
			highestColor = c;
			buoyancy_liquid->setColor2(fruitColors[highestColor]);
			buoyancy_particle->setColor2(fruitColors[highestColor]);

			buoyancy_liquid2->setColor2(fruitColors[highestColor]);
			buoyancy_particle2->setColor2(fruitColors[highestColor]);

			Firework* f1 = new Firework(Vector3(-100, 0, 0), Vector3(0, 60, 0), Vector3(0), fruitColors[highestColor], 4.0f, 4, 8);
			fireworks_pool.push_back(f1);

			Firework* f2 = new Firework(Vector3(100, 0, 0), Vector3(0, 60, 0), Vector3(0, -10, 0), fruitColors[highestColor], 5.0f, 4, 7);
			fireworks_pool.push_back(f2);
		}

	}

	void generateNextFruit(int nextColor, Vector3 pos) {
		if (highestColor < nextColor) {
			highestColor = nextColor;
			buoyancy_liquid->setColor2(fruitColors[highestColor]);
			buoyancy_particle->setColor2(fruitColors[highestColor]);

			buoyancy_liquid2->setColor2(fruitColors[highestColor]);
			buoyancy_particle2->setColor2(fruitColors[highestColor]);

			Firework* f1 = new Firework(Vector3(100, 0, 0), Vector3(0, 60, 0), Vector3(0), fruitColors[highestColor], 4.0f, 4, 8);
			fireworks_pool.push_back(f1);

			Firework* f2 = new Firework(Vector3(-100, 0, 0), Vector3(0, 60, 0), Vector3(0, -10, 0), fruitColors[highestColor], 5.0f, 4, 7);
			fireworks_pool.push_back(f2);
		}
		if (nextColor <= green) {
			RigidBody* fruit = new RigidBody(_scene, _physics, pos, fruitColors[nextColor], { 0, -10, 0 }, { 3 * (float(nextColor + 1)), 3 * (float(nextColor + 1)), 3 * (float(nextColor + 1))}, 10, -100.0f, Sphere);
			_rigids.push_back(fruit);
			fruit->setCouleur(nextColor);
			SuikaInstance().reference.insert({ fruit->getActor(), fruit });
			points += (nextColor + 1) * 10;
			
		}
		pointsPrintOut();

	}

	void pointsPrintOut() {
		system("CLS");
		cout << "SCORE: " << points << endl;
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
			//std::cout << spawnPos.x<<endl;
			
			break;
		case 'K':
			if (spawnPos.x < 70) {
				spawnPos.x += 5;
				spawnPoint->setPos(spawnPos);
				tornado->moveCenter(spawnPos);
				spawnPoint->newVars();

			}
			//std::cout << spawnPos.x << endl;

			break;


		}
	}
};

