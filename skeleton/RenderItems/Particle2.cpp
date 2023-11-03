#include "Particle2.h"

Particle::Particle(Vector3 pos, Vector3 v, Vector3 acc, float rad, Vector4 color, float lt, float dp) :
	pose(pos), vel(v), acceleration(acc), damping(dp),
	lifeTime(lt),  radious(rad),
	renderItem(new RenderItem(CreateShape(physx::PxSphereGeometry(rad)),
		&pose, color)) {

}

Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
}

bool Particle::integrate(double t) {
	pose.p += vel * t;

	vel += acceleration * t;

	vel *= powf(damping, t);
	 
	// Eliminar tras lifeTime segundos
	if (lifeTime < 0 || pose.p.y < LIMIT) return false;

	lifeTime -= t;
	return true;
}

Particle* Particle::clone() const {
	return new Particle(pose.p, vel, acceleration, radious, renderItem->color, lifeTime);
}

Particle* Particle::clone(Vector3 p, Vector3 v, Vector3 acc) const {
	return new Particle(p, v, acc, radious, renderItem->color, lifeTime);
}