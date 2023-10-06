#pragma once
#include <PxPhysicsAPI.h>

#include <vector>

#include "PxPhysics.h"
#include "../core.hpp"
#include "../RenderUtils.hpp"
#include "../callbacks.hpp"
#include "../RenderItems/particle.h"

using namespace physx;

enum projectiles {
	PISTOL = 0,
	ARTILLERY,
	FIREBALL,
	LASER
};

class ProyectileLauncher {
private:
	particle* part;
	
	std::vector<particle*> particles;
public:

	ProyectileLauncher() {};
	~ProyectileLauncher() {};
	
	void OnKeyPress(char key, const PxTransform& camTransform,Vector3 dir) {
		switch (toupper(key)) {
		case 'G': //pistola
			part = new particle();
			
			part->setPosition(camTransform.p);
			part->setMass(2.0f); // 2.0 Kg //Real 0,022 kg o 22g
			part->setVelocity(dir *35.0f); // 35 m/s //Real 330 m/s
			part->setAcceleration(Vector3(0.0f, -1.0f, 0.0f));
			part->setDamping(0.99f);
			
			particles.push_back(part);
			break;

		case 'C':  //artilleria
			part = new particle();
			
			part->setPosition(camTransform.p);
			part->setMass(200.0f); // 200.0 Kg // 8kg real
			part->setVelocity(dir*50.0f); //50 m/s //250m/s real
			part->setAcceleration(Vector3(0.0f, -10.0f, 0.0f));
			part->setDamping(0.99f);

			particles.push_back(part);
			break;
		case 'F': //bola de fuego
			part = new particle();
			
			part->setPosition(camTransform.p);
			part->setMass(1.0f); // 1.0 Kg //0.04 kg real
			part->setVelocity(dir*10.0f);//10 m/s // 50m/s real
			part->setAcceleration(Vector3(0.0f, 0.6f, 0.0f));
			part->setDamping(0.9f);
			
			particles.push_back(part);
			break;
			
		case 'L':
			part = new particle();
			
			part->setPosition(camTransform.p);
			part->setMass(0.1f); // 0.1 Kg //1.11*10^-14 kg
			part->setVelocity(dir* 100.0f);//100m/s // 299 792 458 m/s
			part->setAcceleration(Vector3(0.0f, 0.0f, 0.0f));
			part->setDamping(0.99f);
			
			particles.push_back(part);
			break;
		}
	}

	void integrate(float t) {
		for (int i = 0; i < particles.size(); i++) {
			particles[i]->integrate(t);
		}
	}
};