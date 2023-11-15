#pragma once
#include "../skeleton/RenderItems/particle.h"
#include <list>
#include <string>

class ForceGen
{
public:
	virtual void updateForce(particle* particle, double duration) = 0;
	std::string name;
	double t = -1;
};

class GravForceGen : public ForceGen {
public:
	GravForceGen(Vector3& G, double t);
	virtual ~GravForceGen() {};
	void updateForce(particle* particle, double duration) override;
protected:
	Vector3 g;
};

class DragForceGen : public ForceGen {
public:
	DragForceGen(float k1, float k2);
	virtual ~DragForceGen() {};
	void updateForce(particle* particle, double duration) override;
protected:
	float _k1; // Coeficiente velocidad
	float _k2;
};


class WindForceGen : public ForceGen {
public:
	WindForceGen(Vector3& v, float k1, float k2);
	WindForceGen(Vector3& v, float k1, float k2, Vector3 ori, double w, double h, double d);
	virtual ~WindForceGen() {};
	void updateForce(particle* particle, double duration) override;
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
	void updateForce(particle* particle, double duration) override;
protected:
	Vector3 _center;
	float _Kt;
};
