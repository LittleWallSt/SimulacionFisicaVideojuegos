#pragma once
#include "RigidBody.h"
#include "Singleton.h"
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>
#include <unordered_map>

class SuikaSingleton: public Singleton<SuikaSingleton>
{
private:
	SuikaSingleton() {};
public:
	friend Singleton<SuikaSingleton>;
	
	std::unordered_map<physx::PxRigidActor*, RigidBody*> reference;

	bool gameOver = false;

};

inline SuikaSingleton& SuikaInstance() { return *SuikaSingleton::instance(); };