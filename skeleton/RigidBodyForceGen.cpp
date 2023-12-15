#include "RigidBodyForceGen.h"

void RigidBodyExplosionGen::updateForce(RigidBody* rb, double t)
{

	//si la particula tiene una masa minii
	if (fabs(rb->getUnMass()) < 1e-10) return;


	_R = (maxRadius / duration) * elapsedTime;

	float r = (rb->getPos() - _centre).magnitude();//distancia de explosion

	//si se sale del radio de la explosion
	if (r >= _R) return;
	//si sale desde el centro del generador
	if (r < 1e-10) r = 0.1;

	//Fuerza de la explosion
	Vector3 f = (_K / pow(r, 2)) * (rb->getPos() - _centre) * exp(-elapsedTime / duration);
	rb->addForce(f);

}

RigidBodyWindForceGen::RigidBodyWindForceGen(Vector3& v, float k1, float k2) : _windVel(v), _k1(k1), _k2(k2)
{
	//constructora para hacer un generador de viento sin limites
	origin = Vector3();
	areaX = INT_MAX;
	areaY = INT_MAX;
	areaZ = INT_MAX;

}

RigidBodyWindForceGen::RigidBodyWindForceGen(Vector3& v, float k1, float k2, Vector3 ori, double w, double h, double d) :_windVel(v), _k1(k1), _k2(k2),
origin(ori), areaX(w), areaY(h), areaZ(d) {
};

void RigidBodyWindForceGen::updateForce(RigidBody* particle, double duration)
{
	//si la particula tiene una masa enormee
	if (fabs(particle->getUnMass()) < 1e-10)
		return;

	//bounding box del generador de viento
	auto pos = particle->getPos();
	if (pos.x > origin.x + areaX || pos.x < origin.x - areaX ||
		pos.y > origin.y + areaY || pos.y < origin.y - areaY ||
		pos.z > origin.y + areaZ || pos.z < origin.y - areaZ)
		return;

	//el cambio con respecto al generador de drag, aqui 
	//se le resta la velocidad del viento para que pueda propulsar la particula
	Vector3 v = particle->getLinearVel() - _windVel;

	//sacamos el vector unitario de el coeficiente del drag
	float dragCoef = v.normalize();
	Vector3 windForce;

	//ecuacion del dragForce k1 depende de la fuerza del drag y k2 depende del coeficiente de rozamiento del objeto, cuanto mas bajo mejor
	dragCoef = _k1 * dragCoef + _k2 * dragCoef * dragCoef;
	windForce = -v * dragCoef;

	particle->addForce(windForce);
}
