#include "ForceGenerator.h"

GravForceGen::GravForceGen(Vector3& G, double t) {
	g = G;
	this->t = t;
}

void GravForceGen::updateForce(particle* particula, double duration) {
	if (particula->getUnMass() <= 0.0f)
		return;

	particula->addForce(g * particula->getMass());
}

WindForceGen::WindForceGen(Vector3& v, float k1, float k2) : _windVel(v), _k1(k1), _k2(k2)
{
	origin = Vector3();
	areaX = INT_MAX;
	areaY = INT_MAX;
	areaZ = INT_MAX;

}

WindForceGen::WindForceGen(Vector3& v, float k1, float k2, Vector3 ori, double w, double h, double d) :_windVel(v), _k1(k1), _k2(k2), 
origin(ori), areaX(w), areaY(h), areaZ(d){
};

void WindForceGen::updateForce(particle* particle, double duration)
{
	if (particle->getUnMass() <= 0.0f)
			return;

	
	auto pos = particle->getPos();
	if (pos.x > origin.x + areaX || pos.x < origin.x - areaX ||
		pos.y > origin.y + areaY || pos.y < origin.y - areaY ||
		pos.z > origin.y + areaZ || pos.z < origin.y - areaZ)
		return;

	
	Vector3 v = particle->getVelocity() - _windVel; 
	float dragCoef = v.normalize();
	Vector3 windForce;
	dragCoef = _k1 * dragCoef + _k2 * dragCoef * dragCoef;
	windForce = -v * dragCoef;
	
	particle->addForce(windForce);
}

DragForceGen::DragForceGen(float k1, float k2) : _k1(k1), _k2(k2) {};

void DragForceGen::updateForce(particle* particle, double duration)
{
	if (particle->getUnMass() <= 0.0f) return;


	Vector3 v = particle->getVelocity();
	float dragCoef = v.normalize();
	Vector3 dragForce;
	dragCoef = _k1 * dragCoef + _k2 * dragCoef * dragCoef;
	dragForce = -v * dragCoef;

	particle->addForce(dragForce);
};

void TornadoForceGen::updateForce(particle* particle, double duration)
{
	/*auto pos = particle->getPos();

	Vector3 v = particle->getVelocity() - (_Kt * Vector3(
		-(pos.z - origin.z) - 0.9 * (pos.x - origin.x),
		20 - (pos.y - origin.y),
		(pos.x - origin.x) - 0.9 * (pos.z - origin.z)));


	float dragCoef = v.normalize();
	Vector3 windForce;
	dragCoef = _k1 * dragCoef + _k2 * dragCoef * dragCoef;
	windForce = -v * dragCoef;

	particle->addForce(windForce);*/
	auto p = particle->getPos();
	_windVel = _Kt * Vector3(origin.z - p.z, 50 + origin.y - p.y, p.x - origin.x);

	WindForceGen::updateForce(particle, t);
}