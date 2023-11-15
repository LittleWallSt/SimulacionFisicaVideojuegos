#include "particle.h"

// Constructora - Crea una particula definiendo todas sus propiedades
particle::particle(float m, Vector3 p, Vector3 vel, Vector3 ac, double lTime, Vector4 col, PxShape* shp) :
	pos(p), gravity(Vector3(0, -10.0f, 0)) {
	
	lifeTime = lTime;
	//startTime = GetLastTime();
	setProperties(m, vel, ac, col, shp, lTime);
	renderItem = new RenderItem(shape, &pos, color);

	force = { 0,0,0 };
	
	m > 0.0f ? unMass = 1.0f / m : unMass = 0.0f;

	limits = { 1000, 1000, 1000 };
	iniPos = pos.p;
}

// Constructora - Crea una partícula sin especificar posición y tiempo de vida
particle::particle(float m, Vector3 vel, Vector3 ac, Vector4 col, PxShape* shp) :
	gravity(Vector3(0, -10.0f, 0)) {
	
	lifeTime = 1;
	//startTime = GetLastTime();
	setProperties(m, vel, ac, col, shp, 0);
	renderItem = new RenderItem(shape, &pos, color);

	force = { 0,0,0 };
	m > 0.0f ? unMass = 1.0f / m : unMass = 0.0f;

}

particle::particle(Vector3 pose, Vector3 v, Vector3 acc, float rad, Vector4 color, float lt, float dp) :
	pos(pose), vel(v), accl(acc), damping(dp),
	lifeTime(lt), radius(rad),
	renderItem(new RenderItem(CreateShape(physx::PxSphereGeometry(rad)),
		&pos, color)) {
	force = { 0,0,0 };


}

// Destructora
particle::~particle() {
	renderItem->release();
};

// Settea las propiedades de la partícula
void particle::setProperties(float m, Vector3 v, Vector3 a, Vector4 c, PxShape* s, float l, float d) {
	setMass(m); setVelocity(v); setAcceleration(a); setDamping(d); setColor(c); setShape(s); setLifeTime(l);
}

// Update
bool particle::integrate(double t) {
	// Actualizar físicas
	
	if (unMass <= 0.0f) return false;


	pos.p += vel * t;
	Vector3 resultingAccel = force * unMass;
	vel += resultingAccel * t;
	vel *= powf(damping, t);
	lifeTime -= t;
	clearForce();//limpiamos la fuerza

	// Eliminar tras lifeTime segundos
	if (lifeTime < 0) return false;
	
	//eliminar si se sale de los limites
	else if (!(pos.p.y < limits.y + iniPos.y
		&& pos.p.y > -limits.y + iniPos.y
		&& pos.p.x < limits.x + iniPos.x
		&& pos.p.x > -limits.x + iniPos.x
		&& pos.p.z < limits.z + iniPos.z
		&& pos.p.z > -limits.z + iniPos.z)) return false;
	
	return true;
}

// Clona la partícula actual modificando velocidad, aceleración y tiempo de vida
particle* particle::clone(Vector3 newRanVel, Vector3 newRanAccl, float newLifeTime, Vector4 colour) const {
	if (newLifeTime < 0) { newLifeTime = this->lifeTime; }
	return new particle(mass, pos.p, newRanVel, newRanAccl, newLifeTime, colour, shape);
}

// Clona la partícula actual modificando posición, velocidad, aceleración y tiempo de vida
particle* particle::clone(Vector3 newPos, Vector3 newRanVel, Vector3 newRanAccl, float newLifeTime, Vector4 colour) const {
	if (newLifeTime < 0) { newLifeTime = this->lifeTime; }
	return new particle(mass, newPos, newRanVel, newRanAccl, newLifeTime, colour, shape);
}
