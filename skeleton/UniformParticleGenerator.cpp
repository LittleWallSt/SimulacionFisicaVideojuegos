#include "UniformParticleGenerator.h"
// Constructora - Setea la partícula modelo y las distribuciones según proceda
UniformParticleGenerator::UniformParticleGenerator(Vector3 iniPos, Vector3 var, float prob, particle* m,int nPart, bool st)
	: ParticleGenerator(iniPos, m->getVelocity(), var, prob, st), _n_particles(nPart) {

	// Partícula modelo
	m->setPos(iniPos);
	setParticle(m);

	// Distribuciones de velocidad
	vX = new uniform_real_distribution<float>(m->getVelocity().x - var.x, m->getVelocity().x + var.x);
	vY = new uniform_real_distribution<float>(m->getVelocity().y - var.y, m->getVelocity().y + var.y);
	vZ = new uniform_real_distribution<float>(m->getVelocity().z - var.z, m->getVelocity().z + var.z);

	// Distribuciones de posición
	if (!st) {
		pX = new uniform_real_distribution<float>(iniPos.x - var.x * 2, iniPos.x + var.x / 2.0f);
		pY = new uniform_real_distribution<float>(iniPos.y - var.y * 2, iniPos.y + var.y / 2.0f);
		pZ = new uniform_real_distribution<float>(iniPos.z - var.z * 2, iniPos.z + var.z / 2.0f);
	}
}

// Destructora
UniformParticleGenerator::~UniformParticleGenerator() {
	delete vX, vY, vZ;
	if (pX != nullptr) delete pX, pY, pZ;
}

// Genera partículas que se devuelven en la lista
list<particle*> UniformParticleGenerator::generateParticles() {
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