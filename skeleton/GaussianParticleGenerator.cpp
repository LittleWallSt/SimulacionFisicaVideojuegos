#include "GaussianParticleGenerator.h"
// Constructora - Setea la partícula modelo y las distribuciones según proceda
GaussianParticleGenerator::GaussianParticleGenerator(Vector3 iniPos, Vector3 var, float prob, particle* m, int nParticles, bool st)
	: ParticleGenerator(iniPos, m->getVelocity(), var, prob, st), _n_particles(nParticles) {

	// Partícula modelo
	m->setPos(iniPos);
	setParticle(m);

	// Distribuciones de velocidad
	vX = new normal_distribution<float>(m->getVelocity().x, var.x);
	vY = new normal_distribution<float>(m->getVelocity().y, var.y);
	vZ = new normal_distribution<float>(m->getVelocity().z, var.z);

	// Distribuciones de posición
	if (!st) {
		pX = new normal_distribution<float>(iniPos.x, var.x / 2.0f);
		pY = new normal_distribution<float>(iniPos.y, var.y / 2.0f);
		pZ = new normal_distribution<float>(iniPos.z, var.z / 2.0f);
	}
}

// Destructora
GaussianParticleGenerator::~GaussianParticleGenerator() {
	delete vX, vY, vZ;
	if (pX != nullptr) delete pX, pY, pZ;
}

// Genera partículas que se devuelven en la lista
list<particle*> GaussianParticleGenerator::generateParticles() {
	// Lista de partículas
	list<particle*> prtcls;

	// Generar según un aleatorio
	
	if (active) {
		for (int i = 0; i < _n_particles; i++) {
			float random = (rand() % 101) / 100.0f;
			if (random < probability) {
				// Variables aleatorias
				Vector3 vel = Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));
				//Vector3 accl = Vector3(0);
				int lifeTime;
				if (randomLifeTime) {
					lifeTime = rand() % RandomLifeTimeRange + minimumLifeTime;
				}
				else lifeTime = -1;

				// Crear partícula
				if (!staticGenerator) {
					Vector3 pos = Vector3((*pX)(gen), (*pY)(gen), (*pZ)(gen));
					prtcls.push_back(model->clone(pos, vel, model->getAcceleration(), lifeTime));
				}
				else prtcls.push_back(model->clone(vel, model->getAcceleration(), lifeTime));
			}
		}
	}
	

	return prtcls;
}