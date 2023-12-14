#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
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

protected:
	PxScene* _scene;
	PxPhysics* _physics;

	list<RigidBody*> _rigids;
	list<RigidBodyGenerator*> _RBGens;
	RigidBodyGenerator* gen = nullptr;

	PxRigidStatic* floor;
	RenderItem* floorRenderItem;

};

