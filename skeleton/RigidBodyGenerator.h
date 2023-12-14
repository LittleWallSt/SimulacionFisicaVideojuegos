#pragma once
#include "RigidBody.h"
#include "core.hpp"
#include <list>
#include <string>
#include <random>
#include <random>
#include <chrono>

using namespace std;

using namespace physx;

class RigidBodyGenerator {
protected:
	//Variables del generador
	string name;
	bool staticGenerator;
	bool active = false;
	//Modelo de la particula
	RigidBody* model;

	//variables para la generacion
	Vector3 pos, vel, var, offset;

	//frecuencia de generacion de rigid
	float fr;
	float cont = 0;

	//Random generator
	default_random_engine gen;

public:
	RigidBodyGenerator(string nombre, RigidBody* modelo, Vector3 p, Vector3 va, float f, bool st = true, Vector3 stOs = { 0,0,0 }) :
		name(nombre), model(modelo), pos(p), var(va), fr(f), staticGenerator(st), offset(stOs), 
		gen(default_random_engine(chrono::system_clock::now().time_since_epoch().count())) {
		srand(unsigned(time));
	};

	virtual ~RigidBodyGenerator() {};

	virtual list<RigidBody*> generateRigidBodies(double t) = 0;

	inline void setRigidBody(RigidBody* rb) {
		delete model;
		model = rb->clone();
	}
	inline string getName() { return name; }
	inline RigidBody* getModel() { return model; }

	inline void setActive() { active = !active; }

};


#pragma region Gaussiano
class GaussianRigidBodyGen : public RigidBodyGenerator {

protected:
	// Velocidad
	normal_distribution<float>* vX;
	normal_distribution<float>* vY;
	normal_distribution<float>* vZ;

	// Posición
	normal_distribution<float>* pX = nullptr;
	normal_distribution<float>* pY;
	normal_distribution<float>* pZ;

public:
	GaussianRigidBodyGen(string nombre, RigidBody* modelo, Vector3 p, Vector3 va = Vector3(0), float f = 0, bool st = true, Vector3 stOs = Vector3(0));
	virtual ~GaussianRigidBodyGen();

	virtual list<RigidBody*> generateRigidBodies(double t);
};
#pragma endregion

#pragma region Uniforme
class UniformRigidBodyGen : public RigidBodyGenerator {
protected:
	// Velocidad
	uniform_real_distribution<float>* vX;
	uniform_real_distribution<float>* vY;
	uniform_real_distribution<float>* vZ;

	// Posición
	uniform_real_distribution<float>* pX = nullptr;
	uniform_real_distribution<float>* pY;
	uniform_real_distribution<float>* pZ;

public:
	UniformRigidBodyGen(string name, RigidBody* model, Vector3 p, Vector3 var = { 0,0,0 }, float f = 0, bool st = true, Vector3 stOs = { 0,0,0 });
	virtual ~UniformRigidBodyGen();

	virtual list<RigidBody*> generateRigidBodies(double t);
};
#pragma endregion



