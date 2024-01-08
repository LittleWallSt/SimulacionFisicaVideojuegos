#include "ProyectoSystem.h"
ProyectoSystem::ProyectoSystem(PxScene* scene, PxPhysics* phys) {
	_scene = scene;
	_physics = phys;

	/*floor = _physics->createRigidStatic(physx::PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(physx::PxBoxGeometry(Vector3(2500, 1, 2500)));
	floor->attachShape(*shape);
	_scene->addActor(*floor);
	floorRenderItem = new RenderItem(shape, floor, { 0.3, 0.3, 0.3, 0 });*/
	
	
	
	tornado = new TornadoForceGen(spawnPos, 1, 1, 1);
	
}

ProyectoSystem::~ProyectoSystem() {
	for (auto it = _forceGens.begin(); it != _forceGens.end(); it = _forceGens.erase(it))
		delete* it;

	for (auto it = _RBGens.begin(); it != _RBGens.end(); it = _RBGens.erase(it))
		delete* it;

	for (auto it = _rigids.begin(); it != _rigids.end(); it = _rigids.erase(it))
		delete* it;

	for (ParticleGenerator* p : _particle_generators) delete p;
	_particle_generators.clear();

	for (particle* p : _particles) delete p;
	_particles.clear();
}

void ProyectoSystem::update(double t) {
	
#pragma region rigidbodies
	//Rigidbodies
	for (auto gen : _RBGens) {
		list<RigidBody*> rb = gen->generateRigidBodies(t);
		for (auto rigids : rb) {
			//Los añadimos a un mapa para luego poder recuperarlos en las colisiones
			SuikaInstance().reference.insert({ rigids->getActor(), rigids });
			
		}
		if (!rb.empty()) {
			_rigids.splice(_rigids.end(), rb);
		}

	}

	for (auto force : _forceGens) {
		addGen(force);
	}

	/*if (expl->active) {
		addGen(expl);
		expl->setActive();
	}*/

	_registry.updateForces(t);

	for (auto rigid : _rigids) {
		if (rigid->sendMessage()) {
			generateRB();
		}
	}

	auto it = _rigids.begin();
	while (it != _rigids.end()) {
		if (!(*it)->integrate(t)|| (*it)->getContact()) {
			SuikaInstance().reference.erase((*it)->getActor());
			_registry.deleteRBReg(*it);
			auto nextIt = std::next(it);
			delete* it;
			_rigids.erase(it);
			it = nextIt;
		}
		else {
			++it;
		}
	}
#pragma endregion

#pragma region Particles
	for (ParticleGenerator* p : _particle_generators) {
		list<particle*> prtcls = p->generateParticles();
		for (auto p : prtcls) {
			_registryP.addReg(tornado, p);
		}

		if (!prtcls.empty()) _particles.splice(_particles.end(), prtcls);
	}

	for (auto it = _particles.begin(); it != _particles.end(); it++) {
		//si hay una explosion por hacerlo mas dramatico
		/*if (explosion) {
			_registry.addReg(6, *it);
		}*/
		if (!(*it)->integrate(t)) _particlesToDelete.push_back(it);

	}

	//si ya se ha producido la explosion paramos
	//if (explosion) explosion = false;

	_registryP.updateForces(t);

	for (int i = 0; i < _particlesToDelete.size(); i++) {
		particle* p = *_particlesToDelete[i];
		_registryP.deletePartReg(p);
		_particles.erase(_particlesToDelete[i]);
		delete p;
	}
	_particlesToDelete.clear();
#pragma endregion




#pragma region Fireworks
	/*if (x) {
		Firework* f1 = new Firework(Vector3(-50, 0, -100), Vector3(0, 40, 0), Vector3(0), Vector4(0, 1, 255, 1), 4.0f, 3, 8);
		fireworks_pool.push_back(f1);

		Firework* f2 = new Firework(Vector3(-200, 0, -300), Vector3(0, 40, 0), Vector3(0, -10, 0), Vector4(255, 1, 0, 1), 5.0f, 3, 7);
		fireworks_pool.push_back(f2);

		spawnF();
	}*/

	for (auto it = fireworks_pool.begin(); it != fireworks_pool.end(); it++) {
		if (!(*it)->integrate(t)) {
			deadFireworks.push_back(it);
		}
	}

	for (int i = 0; i < deadFireworks.size(); i++) {
		if ((*deadFireworks[i])->getGeneration() > 1) {
			list<Firework*> fs = fireworkGen->generateFireworks(*deadFireworks[i]);
			if (!fireworks_pool.empty()) fireworks_pool.splice(fireworks_pool.end(), fs);
		}
		delete* deadFireworks[i];
		fireworks_pool.erase(deadFireworks[i]);
	}
	deadFireworks.clear();
#pragma endregion
}

void ProyectoSystem::demo() {
	floor = _physics->createRigidStatic(physx::PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(physx::PxBoxGeometry(Vector3(2500, 1, 2500)));
	floor->attachShape(*shape);
	_scene->addActor(*floor);
	floorRenderItem = new RenderItem(shape, floor, { 0.3, 0.3, 0.3, 0 });

	//Bounding box
	leftPlane = _physics->createRigidStatic(physx::PxTransform({ -75,100,0 }));
	PxShape* shap = CreateShape(physx::PxBoxGeometry(Vector3(1, 100, 30)));
	leftPlane->attachShape(*shap);
	_scene->addActor(*leftPlane);
	leftRender = new RenderItem(shap, leftPlane, { 0, 0, 1, 0 });

	rightPlane = _physics->createRigidStatic(physx::PxTransform({ 75,100,0 }));
	shap = CreateShape(physx::PxBoxGeometry(Vector3(1, 100, 30)));
	rightPlane->attachShape(*shap);
	_scene->addActor(*rightPlane);
	rightRender = new RenderItem(shap, rightPlane, { 0, 0, 1, 0 });

	backPlane = _physics->createRigidStatic(physx::PxTransform({ 0,100,-30 }));
	shap = CreateShape(physx::PxBoxGeometry(Vector3(75, 100, 1)));
	backPlane->attachShape(*shap);
	_scene->addActor(*backPlane);
	backRender = new RenderItem(shap, backPlane, { 0, 0, 1, 0 });

	frontPlane = _physics->createRigidStatic(physx::PxTransform({ 0,100,30 }));
	shap = CreateShape(physx::PxBoxGeometry(Vector3(75, 100, 1)));
	frontPlane->attachShape(*shap);
	_scene->addActor(*frontPlane);
	//frontRender = new RenderItem(shap, frontPlane, { 0, 0, 1, 0 });
	particle* model = new particle(100, Vector3(0), Vector3(0, -100.0f, 0), Vector3(0, 0, 0), 0.2, Vector4(1, 1, 0, 0), CreateShape(PxSphereGeometry(0.1)));

	//Indicador de donde se generan las "frutas"
	spawnPoint = new GaussianParticleGenerator(spawnPos, Vector3(1, 1, 1), 0.3, model, 3, false);

	spawnPoint->setRandomLifeTimeRange(2);
	spawnPoint->setRandomColor();
	spawnPoint->setMinimumLifeTime(2);
	spawnPoint->setRandomMass();
	spawnPoint->setMinimumMass(1);
	spawnPoint->setRandomMassRange(2);
	spawnPoint->setName("Avispero");
	spawnPoint->setActive();
	_particle_generators.push_back(spawnPoint);
}