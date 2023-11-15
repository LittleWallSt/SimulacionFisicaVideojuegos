#include "ForceGenerator.h"

GravForceGen::GravForceGen(Vector3& G, double t) {
	g = G;
	this->t = t;
}

void GravForceGen::updateForce(particle* particle, double duration) {
	//si la particula tiene una masa enormee
	if (fabs(particle->getUnMass()) < 1e-10)
		return;

	particle->addForce(g * particle->getMass());
}

WindForceGen::WindForceGen(Vector3& v, float k1, float k2) : _windVel(v), _k1(k1), _k2(k2)
{
	//constructora para hacer un generador de viento sin limites
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
	Vector3 v = particle->getVelocity() - _windVel; 

	//sacamos el vector unitario de el coeficiente del drag
	float dragCoef = v.normalize();
	Vector3 windForce;

	//ecuacion del dragForce k1 depende de la fuerza del drag y k2 depende del coeficiente de rozamiento del objeto, cuanto mas bajo mejor
	dragCoef = _k1 * dragCoef + _k2 * dragCoef * dragCoef;
	windForce = -v * dragCoef;
	
	particle->addForce(windForce);
}

DragForceGen::DragForceGen(float k1, float k2) : _k1(k1), _k2(k2) {};

void DragForceGen::updateForce(particle* particle, double duration)
{
	//si la particula tiene una masa enormee
	if (fabs(particle->getUnMass()) < 1e-10)
		return;

	//funcion para parar la particula por fuerza de rozamiento
	Vector3 v = particle->getVelocity();
	float dragCoef = v.normalize();
	Vector3 dragForce;
	dragCoef = _k1 * dragCoef + _k2 * dragCoef * dragCoef;
	dragForce = -v * dragCoef;

	particle->addForce(dragForce);
};

void TornadoForceGen::updateForce(particle* particle, double duration)
{
	
	//sacamos la posicion de la particula
	Vector3 p = particle->getPos();

	//la velocidad de la particula dependera de donde se ubique con respecto al centro del generador de fuerzas
	_windVel = _Kt * Vector3(origin.z - p.z, 50 + origin.y - p.y, p.x - origin.x);

	//usamos el updateforce del viento con el _windVel modificado
	WindForceGen::updateForce(particle, t);
}

void ExplosionGen::updateForce(particle* particle, double t)
{
	
		//si la particula tiene una masa enormee
		if (fabs(particle->getUnMass()) < 1e-10) return;
		
		
		_R = (maxRadius / duration) * elapsedTime; 

		float r = (particle->getPos() - _centre).magnitude();//distancia de explosion
		
		//si se sale del radio de la explosion
		if (r >= _R) return;
		//si sale desde el centro del generador
		if (r < 1e-10) r = 0.1; 
		
		//Fuerza de la explosion
		Vector3 f = (_K / pow(r, 2)) * (particle->getPos() - _centre) * exp(-elapsedTime / duration);
		particle->addForce(f);
	
}

