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

void DragForceGen::updateForce(particle* particle, double duration)
{
	if (particle->getUnMass() <= 0.0f) return;

	Vector3 force = k * particle->getVelocity();
	particle->addForce(force);
}

void TornadoForceGen::updateForce(particle* particle, double duration)
{
	Vector3 pos = particle->getPos();
	Vector3 dist = pos - _center;
	_windVel = _Kt * Vector3(-(dist.z) - (dist.x), 50 - (dist.y), dist.x - (dist.z));
	WindForceGen::updateForce(particle, duration);
}