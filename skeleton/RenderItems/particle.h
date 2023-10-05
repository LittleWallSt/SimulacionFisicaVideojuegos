#pragma once

#include <PxPhysicsAPI.h>

#include <vector>

#include "PxPhysics.h"
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "../callbacks.hpp"

using namespace physx;
class particle {
private:

	Vector3 vel;
	Vector3 accel;
	Vector3 grav;
	float damping;
	float mass;
	PxTransform pose;
	RenderItem* renderItem;


public:
	particle(Vector3 Pos = Vector3(), Vector3 Vel = Vector3(), Vector3 acc = Vector3(), Vector3 gr = Vector3(),
		float damp = 0.f, float m = 0.f):pose(Pos), vel(Vel), accel(acc),grav(gr), damping(damp), mass(m) {
		
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(4)), &pose, Vector4(125, 0, 0, 1));
	};

	~particle() {
		renderItem->release();
	};

	void integrate(double t) {
		pose.p += vel*t;
		vel += accel * t;
		vel += grav * t;
		vel *= powf(damping, t);

	};

	inline void setPosition(Vector3 newPos) { pose.p = newPos; };
	inline void setMass(float masa) { mass = masa; };
	inline void setVelocity(Vector3 newVel) { vel = newVel; };
	inline void setAcceleration(Vector3 newAccel) { accel = newAccel; };
	inline void setDamping(float damp) { damping = damp; };


};