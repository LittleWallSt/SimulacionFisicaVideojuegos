#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "RigidBodyForceRegistry.h"
#include "RigidBodyForceGen.h"
#include <vector>
#define EXPLOSION_DURATION 2.0f

using namespace std;
using namespace physx;



class RigidBodySystem
{
public:
	RigidBodySystem(PxScene* scene, PxPhysics* phys);
	void update(double t);
	void demo();
	~RigidBodySystem();

	void keyPress(unsigned char key) {
		switch (toupper(key)) {
		case '6': {
			expl->setActive();
			expl->resetDuration(EXPLOSION_DURATION);
		}

			break;
		case 'Q': 
			wind->setActive(); 
		break;
		case 'G':
			getParticleGenerator("gaussian")->setActive();

			break;
		case 'U':
			getParticleGenerator("uniform")->setActive();


			break;

		
		}
	}

protected:
	PxScene* _scene;
	PxPhysics* _physics;

	list<RigidBody*> _rigids;
	list<RigidBodyGenerator*> _RBGens;
	list<RigidBodyForceGen*> _forceGens;
	RigidBodyGenerator* gen = nullptr;
	
	
	RigidBodyForceGen* wind;
	RigidBodyExplosionGen* expl;
	//RigidBodyBuoyancyGen* pool;


	RigidBodyForceRegistry _registry;	
	PxRigidStatic* floor;
	RenderItem* floorRenderItem;

	



	void addGen(RigidBodyForceGen* gen) {
		if (gen->active) {
			for (auto rb : _rigids) {
				_registry.addReg(gen, rb);

			}
		}

	}

	RigidBodyGenerator* getParticleGenerator(string name);
};

