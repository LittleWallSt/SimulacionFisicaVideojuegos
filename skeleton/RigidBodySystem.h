#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "RigidBodyForceRegistry.h"
#include "RigidBodyForceGen.h"
#include <vector>
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
			RigidBodyForceGen* expl = new RigidBodyExplosionGen(50, 5000000000, { 0,0,0 }, 3);
			_forceGens.push_back(expl); }

			break;
		case 'Q': 
			wind->setActive(); 
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
	RigidBodyWindForceGen* wind;

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
};

