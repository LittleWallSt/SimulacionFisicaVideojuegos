#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "RenderItems/particle.h"
using namespace physx;
class RigidBody
{
protected:
	PxRigidDynamic* _rDynamic = nullptr;
	PxRigidStatic* _rStatic = nullptr;
	bool staticRB = false;
	RenderItem* _renderItem;
	double lifeTime;

public:
	enum type{
		 Cube = 0
		,Capsule
		,Sphere
	};

	RigidBody(PxRigidDynamic* rigid, double lifeTime, Vector4 colour);
	RigidBody(PxRigidDynamic* rigid, Vector4 colour);
	RigidBody(PxScene* scene, PxPhysics* phys, Vector3 p, Vector4 colour = { 0, 1, 1, 1 }, Vector3 v = Vector3(),  Vector3 d = Vector3(), double m = 1, double lTime = -100, bool stat = true, type tipo = Cube);

	virtual ~RigidBody();

	void addForce(Vector3 f) { _rDynamic->addForce(f); }

	void addTorque(Vector3 t) { _rDynamic->addTorque(t); }

	Vector3 getPos() {
		if(!staticRB)return _rDynamic->getGlobalPose().p;
		else return _rStatic->getGlobalPose().p;
	};

	PxQuat getRotation() { return _rDynamic->getGlobalPose().q; };

	Vector3 getLinearVel() const { return _rDynamic->getLinearVelocity(); }

	bool integrate(double t) {
		if (lifeTime > -100) lifeTime -= t;
		if (lifeTime < 0 && lifeTime> -100) return false;
		return true;
	}

	void setRotation(physx::PxQuat q) {_rDynamic->setGlobalPose(physx::PxTransform(getPos(), q));}


};

