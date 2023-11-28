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

	//formula para parar la particula por drag
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

SpringForceGen::SpringForceGen(particle* other, float k, float resting_length) : _other(other), _k(k), _resting_length(resting_length)
{
}

void SpringForceGen::updateForce(particle* p, double duration)
{
	if (fabs(p->getUnMass()) <= 0.0f) return;

	Vector3 f = _other->getPos() - p->getPos();

	const float length = f.normalize();
	const float delta_x = length - _resting_length;

	f *= delta_x * _k / duration;

	p->addForce(f);
}

AnchoredSpringFG::AnchoredSpringFG( Vector3& position, float k, float resting_length) :
	SpringForceGen(nullptr, k, resting_length)
{
	_other = new particle(100, position, { 0,0,0 }, { 0,0,0 }, -300,  {1, 1, 1, 1}, CreateShape(physx::PxBoxGeometry(1, 1, 1)));
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete _other;
}

BungeeForceGen::BungeeForceGen(particle* other, float k, float resting_length) :
	SpringForceGen(other, k, resting_length) {}

void BungeeForceGen::updateForce(particle* p, double duration)
{
	if (fabs(p->getUnMass()) <= 0.0f) return;

	Vector3 f = _other->getPos() - p->getPos();

	const float length = f.normalize();
	const float delta_x = length - _resting_length;

	if (delta_x <= 0.0f) return;

	f *= delta_x * _k;

	p->addForce(f);
}

BuoyancyForceGen::BuoyancyForceGen(float height, float V, float d, particle* liquid_surface) :
	_height(height), _volume(V), _density(d), _liquid_particle(liquid_surface)
{
}

void BuoyancyForceGen::updateForce(particle* p, double duration)
{
	if (fabs(p->getUnMass()) <= 0.0f) return;

	float h = p->getPos().y;
	float h0 = _liquid_particle->getPos().y;

	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h0 - h > _height * 0.5) immersed = 1.0;
	else if (h - h0 > _height * 0.5) immersed = 0.0;
	else immersed = (h0 - h) / _height + 0.5;

	f.y = _density * _volume * immersed*9.8;
	p->addForce(f);
}

