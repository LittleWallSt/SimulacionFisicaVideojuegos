#pragma once

#include <PxPhysicsAPI.h>

#include <vector>

#include "PxPhysics.h"
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "../callbacks.hpp"

enum particleType {
	SPHERE= 0, 
	BLOCK, 
	FLOOR
};

enum proyectileType {
	BULLET = 0,
	FIREBALL,
	ARTILLERY,
	LASER
};

using namespace physx;
class particle {
protected:

	RenderItem* renderItem;
	PxShape* shape;
	Vector4 color;

	// Properties
	Vector3 vel, accl, gravity;
	PxTransform pos;
	float unMass, mass, damping, radius;

	Vector3 force;

	// Tiempo
	double lifeTime;

public:
#pragma region Constructoras
	particle* operator=(particle* const& other) {
		this->vel = other->vel;
		this->accl = other->accl;
		this->gravity = other->gravity;
		this->pos = other->pos;
		this->mass = other->mass;
		this->damping = other->damping;
		this->color = other->color;
		this->lifeTime = other->lifeTime;
		this->renderItem = other->renderItem;
		this->force = other->force;

	}
	particle(float m, Vector3 p, Vector3 vel, Vector3 ac, double lTime, Vector4 col, PxShape* shp);
	particle(float m, Vector3 vel, Vector3 ac, Vector4 col, PxShape* shp);
	particle() :vel({ 0,0,0 }), accl{ (0,0,0) }, gravity({ 0,0,0 }), pos({ 0,0,0 }), mass(0), damping(0) {};

	particle(Vector3 pose, Vector3 vel, Vector3 acc, float rad, Vector4 color, float lt, float dp = 0.998f);

	//Constructora por casos //No funciona ahora nose muy bien pq
	/*particle(particleType t) {
		switch (t) {
		case FLOOR:
			pos.p = { 0.0,0.0,0.0 };
			renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(500, 1.0, 500)), &pos, { 1.0, 1.0, 1.0, 1.0 });

			lifeTime = -1;
			break;
		};
		
	};*/
#pragma endregion
	~particle();
	

	// Actualizar
	bool integrate(double t);

	// Clonar partícula
	virtual particle* clone(Vector3 v, Vector3 acc, float lT = -1) const;
	virtual particle* clone(Vector3 p, Vector3 v, Vector3 acc, float lT = -1) const;
	//virtual particle* clone();

	// Getters y setters
	void setProperties(float m, Vector3 v, Vector3 a, Vector4 c, PxShape* s, float l, float d = 0.998);
#pragma region setters
	inline void setDamping(float d) { damping = d; }
	inline void setLifeTime(float l) { lifeTime = l; }

	virtual void setMass(float Mass) {
		if (Mass <= 0) unMass = 0;
		else unMass = 1 / Mass;

		mass = Mass;
	}
	
	inline void setPos(Vector3 p) { pos.p = p; }
	inline void setVelocity(Vector3 v) { vel = v; }
	inline void setAcceleration(Vector3 a) { accl = a; }
	
	inline void setColor(Vector4 c) { color = c; }
	inline void setShape(PxShape* s) { shape = s; }
#pragma endregion
	
#pragma region Getters
	inline Vector3 getVelocity() { return vel; }
	inline Vector3 getAcceleration() { return accl; }
	inline Vector3 getPos() { return pos.p; };

	inline Vector4 getColor() { return color; }
	inline PxShape* getShape() { return shape; }

	inline float getLifeTime() { return lifeTime; }
	virtual float getMass() { return mass; };
	virtual float getUnMass() { return unMass; };
	inline float getDamping() { return damping; }
	inline float getRadius() { return radius; };
#pragma endregion
	virtual void clearForce() { force *= 0; }
	virtual void addForce(Vector3 f) { force += f; }

	


};