#pragma once
#include <list>
#include <string>
#include "RigidBody.h"

class RigidBodyForceGen
{
public:
	virtual void updateForce(RigidBody* rb, double t) = 0;
	std::string name;

	//Gestion de tiempo del generateur
	double t = -1;
	double elapsedTime = 0;
	bool alive = false;
	bool active = true;

	inline void updateTime(double t) {
		elapsedTime += t;
		alive = (elapsedTime < t || t == -1);
	}

	inline void setActive() {
		active = !active;
	}
};

class RigidBodyExplosionGen :public  RigidBodyForceGen {

public:
	RigidBodyExplosionGen(float radio, float intensidad, Vector3 centro, float d) :
		_R(radio), _K(intensidad), _centre(centro), duration(d), maxRadius(radio) {

			 };

	virtual void updateForce(RigidBody* rb, double t);



protected:
	float _R; // radio de la explosión 
	float _K; // intensidad 
	float duration;
	Vector3 _centre; // centro

	float maxRadius;

	bool _enabled = false;
};

class RigidBodyWindForceGen : public RigidBodyForceGen {
public:
	RigidBodyWindForceGen(Vector3& v, float k1, float k2);
	RigidBodyWindForceGen(Vector3& v, float k1, float k2, Vector3 ori, double w, double h, double d);
	virtual ~RigidBodyWindForceGen() {};
	void updateForce(RigidBody* rb, double t) override;
protected:
	Vector3 _windVel;
	float _k1;
	float _k2;

	// Area
	double areaX, areaY, areaZ;
	Vector3 origin;
};