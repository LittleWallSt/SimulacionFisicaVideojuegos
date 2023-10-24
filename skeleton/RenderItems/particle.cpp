#include "particle.h"

// Constructora - Crea una particula definiendo todas sus propiedades
particle::particle(float m, Vector3 p, Vector3 vel, Vector3 ac, int lTime, Vector4 col, PxShape* shp) :
	pos(p), gravity(Vector3(0, -10.0f, 0)) {
	
	startTime = GetLastTime();
	setProperties(m, vel, ac, col, shp, lTime);
	renderItem = new RenderItem(shape, &pos, color);
}

// Constructora - Crea una partícula sin especificar posición y tiempo de vida
particle::particle(float m, Vector3 vel, Vector3 ac, Vector4 col, PxShape* shp) :
	gravity(Vector3(0, -10.0f, 0)) {
	
	startTime = GetLastTime();
	setProperties(m, vel, ac, col, shp, 0);
	renderItem = new RenderItem(shape, &pos, color);
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
	pos.p += vel * t;
	vel += (accl + gravity) * t;
	vel *= powf(damping, t);

	// Eliminar tras lifeTime segundos
	if (startTime + lifeTime < GetLastTime()) return false;
	
	return true;
}

// Clona la partícula actual modificando velocidad, aceleración y tiempo de vida
particle* particle::clone(Vector3 newRanVel, Vector3 newRanAccl, float newLifeTime) const {
	return new particle(mass, pos.p, newRanVel, newRanAccl, newLifeTime, color, shape);
}

// Clona la partícula actual modificando posición, velocidad, aceleración y tiempo de vida
particle* particle::clone(Vector3 newPos, Vector3 newRanVel, Vector3 newRanAccl, float newLifeTime) const {
	return new particle(mass, newPos, newRanVel, newRanAccl, newLifeTime, color, shape);
}