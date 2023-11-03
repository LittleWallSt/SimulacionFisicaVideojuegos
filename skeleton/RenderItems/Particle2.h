#pragma once

//Particulas que no hieren al multiverso o sobretodo a los static casts o sobretodo a la herencia
//maldita herencia
#include <PxPhysicsAPI.h>

#include <vector>

#include "PxPhysics.h"
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "../callbacks.hpp"

#pragma once

//clase de particula expresamente para ser heredada para el firework y futuras herencias
//debido a que la mia original se rompe si se hace un static cast por razones que desconozco

const Vector3 GRAVITY = Vector3(0, -10, 0);
const float LIMIT = -50.0f;

class Particle {
protected:
	Vector3 vel;
	Vector3 acceleration;
	float damping;

	float lifeTime;
	physx::PxTransform pose;
	RenderItem* renderItem;
	float radious;

public:
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, float rad, Vector4 color, float lt, float dp = 0.998f);
	virtual ~Particle();

	virtual bool integrate(double t);

	// Getters
	Vector3 getPos() { return pose.p; }
	Vector3 getVel() { return vel; }
	Vector3 getAccel() { return acceleration; }
	Vector4 getColor() { return renderItem->color; }
	float getRadious() { return radious; }

	// Setters
	void setLifeTime(float const& lt) { lifeTime = lt; }
	void setPosition(Vector3 const& p) { pose.p = p; }

	virtual Particle* clone() const;
	virtual Particle* clone(Vector3 p, Vector3 v, Vector3 acc) const;
};