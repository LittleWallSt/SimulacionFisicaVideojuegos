#pragma once

#include <PxPhysicsAPI.h>

#include <vector>

#include "PxPhysics.h"
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "../callbacks.hpp"

using namespace physx;
class particle {
public:
	particle(Vector3 Pos, Vector3 Vel):pose(Pos), vel(Vel) {
		
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(4)), &pose, Vector4(125, 0, 0, 1));
	};

	~particle() {
		delete renderItem;
	};

	void integrate(double t) {
		pose.p += vel*t;
	};
private:
	Vector3 vel;
	PxTransform pose; 
	RenderItem* renderItem;
	

};