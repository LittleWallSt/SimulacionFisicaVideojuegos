#include "RigidBodyGenerator.h"



#pragma region Gaussiano
GaussianRigidBodyGen::GaussianRigidBodyGen(string n, RigidBody* rb, Vector3 iniPos, Vector3 var, float f, bool st,
	Vector3 stOffset) : RigidBodyGenerator(n, rb, iniPos, var, f, st, stOffset) {

	rb->setPosition(iniPos);

	vX = new normal_distribution<float>(rb->getLinearVel().x, var.x);
	vY = new normal_distribution<float>(rb->getLinearVel().y, var.y);
	vZ = new normal_distribution<float>(rb->getLinearVel().z, var.z);

	if (!st) {
		pX = new normal_distribution<float>(iniPos.x, stOffset.x);
		pY = new normal_distribution<float>(iniPos.y, stOffset.y);
		pZ = new normal_distribution<float>(iniPos.z, stOffset.z);
	}
}

list<RigidBody*> GaussianRigidBodyGen::generateRigidBodies(double t) {
	// Lista de rigidBodies
	list<RigidBody*> rigidBodies;
	if (active) {
		cont += t;
		if (cont > fr) {
			Vector3 vel = Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));

			// Pushear RigidBody
			if (!staticGenerator) {
				auto tr = Vector3((*pX)(gen), (*pY)(gen), (*pZ)(gen));
				rigidBodies.push_back(model->clone(tr, vel));
			}
			else rigidBodies.push_back(model->clone(model->getIniPos(), vel));

			cont = 0;
		}
	}

	return rigidBodies;
}

GaussianRigidBodyGen::~GaussianRigidBodyGen() {
	delete vX, vY, vZ;
	if (pX != nullptr) delete pX, pY, pZ;
	delete model;
}

#pragma endregion

#pragma region Uniforme
UniformRigidBodyGen::UniformRigidBodyGen(string n, RigidBody* rb, Vector3 iniPos, Vector3 var, float f, bool st,
	Vector3 stOffset) : RigidBodyGenerator(n, rb, iniPos, var, f, st, stOffset) {

	rb->setPosition(iniPos);

	vX = new uniform_real_distribution<float>(rb->getLinearVel().x - var.x, rb->getLinearVel().x + var.x);
	vY = new uniform_real_distribution<float>(rb->getLinearVel().y - var.y, rb->getLinearVel().y + var.y);
	vZ = new uniform_real_distribution<float>(rb->getLinearVel().z - var.z, rb->getLinearVel().z + var.z);

	if (!st) {
		pX = new uniform_real_distribution<float>(iniPos.x - stOffset.x, iniPos.x + stOffset.x);
		pY = new uniform_real_distribution<float>(iniPos.y - stOffset.y, iniPos.y + stOffset.y);
		pZ = new uniform_real_distribution<float>(iniPos.z - stOffset.z, iniPos.z + stOffset.z);
	}
}

UniformRigidBodyGen::~UniformRigidBodyGen() {
	delete vX, vY, vZ;
	if (pX != nullptr) delete pX, pY, pZ;
	delete model;
}

list<RigidBody*> UniformRigidBodyGen::generateRigidBodies(double t) {
	// Lista de rigidBodies
	list<RigidBody*> rigidBodies;

	if (active) {
		cont += t;
		if (cont > fr) {
			Vector3 vel = Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));

			// Pushear RigidBody
			if (!staticGenerator) {
				auto tr = Vector3((*pX)(gen), (*pY)(gen), (*pZ)(gen));
				rigidBodies.push_back(model->clone(tr, vel));
			}
			else rigidBodies.push_back(model->clone(model->getIniPos(), vel));

			cont = 0;
		}
	}


	return rigidBodies;
}
#pragma endregion
