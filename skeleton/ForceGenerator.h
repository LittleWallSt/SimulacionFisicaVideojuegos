#pragma once
#include "../skeleton/RenderItems/particle.h"
#include <list>
#include <string>

class ForceGen
{
public:
	virtual void updateForce(particle* particle, double t) = 0;
	std::string name;
	double t = -1;
	double elapsedTime = 0;
	bool alive = false;
	
	inline void updateTime(double t) {
		elapsedTime += t;
		alive = (elapsedTime < t|| t == -1); 
	}
};

class GravForceGen : public ForceGen {
public:
	GravForceGen(Vector3& G, double t);
	virtual ~GravForceGen() {};
	void updateForce(particle* particle, double t) override;
protected:
	Vector3 g;
};

class DragForceGen : public ForceGen {
public:
	DragForceGen(float k1, float k2);
	virtual ~DragForceGen() {};
	void updateForce(particle* particle, double t) override;
protected:
	float _k1; // Coeficiente velocidad
	float _k2;
};


class WindForceGen : public ForceGen {
public:
	WindForceGen(Vector3& v, float k1, float k2);
	WindForceGen(Vector3& v, float k1, float k2, Vector3 ori, double w, double h, double d);
	virtual ~WindForceGen() {};
	void updateForce(particle* particle, double t) override;
protected:
	Vector3 _windVel;
	float _k1;
	float _k2;
	
	// Area
	double areaX, areaY, areaZ;
	Vector3 origin;
};

class TornadoForceGen : public WindForceGen {
public:
	TornadoForceGen(Vector3 center, float k1, float k2, float kt) : WindForceGen(Vector3(0), k1, k2, center, INT_MAX, INT_MAX, INT_MAX), _center(center), _Kt(kt) {};
	~TornadoForceGen() {};
	void updateForce(particle* particle, double t) override;
protected:
	Vector3 _center;
	float _Kt;
};


class ExplosionGen : public ForceGen
{
public:
	ExplosionGen(float radio, float intensidad, Vector3 centro, float d) :
		_R(radio), _K(intensidad), _centre(centro), duration(d), maxRadius(radio) {
		
	};

	virtual void updateForce(particle* particle, double t);



protected:
	float _R; // radio de la explosión 
	float _K; // intensidad 
	float duration;
	Vector3 _centre; // centro

	float maxRadius;

	bool _enabled = false;
};