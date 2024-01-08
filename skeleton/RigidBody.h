#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "RenderItems/particle.h"
#include <iostream>
using namespace physx;
enum color {
	red = 0,
	pink,
	purple,
	yellow,
	orange, 
	lightBlue, 
	Blue, 
	brown, 
	lightGreen, 
	green
};
enum type {
	Cube = 0
	, Capsule
	, Sphere
};

const std::vector<Vector4> fruitColors{
	Vector4(1.0f, 0.0f, 0.0f, 1.0f),   // Red
	Vector4(1.0f, 0.41f, 0.71f, 1.0f), // Pink
	Vector4(0.5f, 0.0f, 0.5f, 1.0f),   // Purple
	Vector4(1.0f, 1.0f, 0.0f, 1.0f),   // Yellow
	Vector4(1.0f, 0.5f, 0.0f, 1.0f),   // Orange
	Vector4(0.68f, 0.85f, 0.9f, 1.0f), // Light Blue
	Vector4(0.0f, 0.0f, 1.0f, 1.0f),   // Blue
	Vector4(0.6f, 0.4f, 0.2f, 1.0f),   // Brown
	Vector4(0.56f, 0.93f, 0.56f, 1.0f),// Light Green
	Vector4(0.0f, 1.0f, 0.0f, 1.0f)    // Green
};
class RigidBody
{
public:
	
protected:
	PxRigidActor* _actor = nullptr;
	PxRigidDynamic* _rDynamic = nullptr;
	RenderItem* _renderItem;
	double lifeTime;
	Vector4 _color;
	type tipo;
	color couleur;
	Vector3 dimensions, iniPos, limits = {500, 500, 500};
	bool contactFlag = false;
	bool sendMessage = false;


	// Físicas
	PxPhysics* Physics;
	PxScene* Scene;

public:
	

	RigidBody(PxRigidDynamic* rigid, double lifeTime, Vector4 colour);
	RigidBody(PxRigidDynamic* rigid, Vector4 colour);
	RigidBody(PxScene* scene, PxPhysics* phys, Vector3 p, Vector4 colour = { 0, 1, 1, 1 }, Vector3 v = Vector3(),  Vector3 d = Vector3(), double m = 1, double lTime = -100, type tipo = Cube);

	virtual ~RigidBody();

	void addForce(Vector3 f) { _rDynamic->addForce(f); }

	void addTorque(Vector3 t) { _rDynamic->addTorque(t); }

	//Para el suikalike
	void flag() { contactFlag = true; };
	bool getContact() { return contactFlag; };

	void setCouleur(int newColor) { 
		couleur = static_cast<color>(newColor);
	};

	//Quien va a mandar el mensaje
	void activateMessage() { sendMessage = !sendMessage; };

	bool getMessage(){ return sendMessage; };
	//Para indicar a que fruta pasar
	int sendMensaje() { return couleur+1; };

	PxRigidActor* getActor() { return _actor; };

	Vector3 getPos() {
		return _rDynamic->getGlobalPose().p;
		
	};

	Vector3 getIniPos() { return iniPos; }

	PxQuat getRotation() { return _rDynamic->getGlobalPose().q; };

	Vector3 getLinearVel() const { return _rDynamic->getLinearVelocity(); }

	float getMass() const {
		return _rDynamic->getMass();
	};
	float getUnMass() const {
		if (_rDynamic->getMass() <= 0) return -1;
		return _rDynamic->getInvMass();
	};

	bool integrate(double t) {
		//std::cout<<getPos().y<<std::endl;
		if (lifeTime > -100) lifeTime -= t;
		if (lifeTime < 0 && lifeTime> -100) return false;
		else if (!(getPos().y < limits.y + iniPos.y
			&& getPos().y > -limits.y + iniPos.y
			&& getPos().x < limits.x + iniPos.x
			&& getPos().x > -limits.x + iniPos.x
			&& getPos().z < limits.z + iniPos.z
			&& getPos().z > -limits.z + iniPos.z)) return false;
		return true;
	}

	void setRotation(PxQuat q) {_rDynamic->setGlobalPose(physx::PxTransform(getPos(), q));}

	void setPosition(Vector3 p){ _rDynamic->setGlobalPose(physx::PxTransform(p, getRotation())); }

	RigidBody* clone() {
		return new RigidBody(this->Scene, this->Physics, this->iniPos, this->_color, 
			this->getLinearVel(), this->dimensions, this->getMass(), this->lifeTime, this->tipo);
	}

	RigidBody* clone(Vector3 pos, Vector3 vel) {
		return new RigidBody(this->Scene, this->Physics, pos, this->_color,
			vel, this->dimensions, this->getMass(), this->lifeTime, this->tipo);
	}

	int getCouleur() {
		return couleur;
	}
};

//class StaticRigidBody {
//protected:
//	PxRigidStatic* _rStatic = nullptr;
//	RenderItem* _renderItem;
//	double lifeTime;
//
//public:
//	enum type {
//		Cube = 0
//		, Capsule
//		, Sphere
//	};
//
//	StaticRigidBody(PxScene* scene, PxPhysics* phys, Vector3 p, Vector3 d,  Vector4 colour = { 0, 1, 1, 1 }, type typ = Cube);
//	virtual ~StaticRigidBody();
//
//};

