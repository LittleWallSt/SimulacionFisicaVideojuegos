#include "RigidBodySystem.h"

RigidBodySystem::RigidBodySystem(PxScene* scene, PxPhysics* phys) {
	_scene = scene;
	_physics = phys;

	floor = _physics->createRigidStatic(physx::PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(physx::PxBoxGeometry(Vector3(250, 1, 250)));
	floor->attachShape(*shape);
	_scene->addActor(*floor);
	floorRenderItem = new RenderItem(shape, floor, { 0.3, 0.3, 0.3, 0 });
}

RigidBodySystem::~RigidBodySystem() {
	for (auto it = _forceGens.begin(); it != _forceGens.end(); it = _forceGens.erase(it))
		delete* it;

	for (auto it = _RBGens.begin(); it != _RBGens.end(); it = _RBGens.erase(it))
		delete* it;

	for (auto it = _rigids.begin(); it != _rigids.end(); it = _rigids.erase(it))
		delete* it;

}

void RigidBodySystem::update(double t) {
	for (auto gen : _RBGens) {
		list<RigidBody*> rb = gen->generateRigidBodies(t);
		if (!rb.empty()) {
			_rigids.splice(_rigids.end(), rb);
		}
		
	}

	for (auto force : _forceGens) {
		addGen(force);
	}
	
	addGen(wind);

	_registry.updateForces(t);

	auto it = _rigids.begin();
	while (it != _rigids.end()) {
		if (!(*it)->integrate(t)) {
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

	_forceGens.clear();
}

void RigidBodySystem::demo() {
	/*RigidBody* model = new RigidBody(_scene, _physics, { 0,10,0 }, { 0,1,1,1 }, { 0, 10, 0 }, { 4,4,4 }, 10, 5, Cube);
	RigidBodyGenerator* rbGen = new UniformRigidBodyGen("uniform", model, { 10, 50,-100 }, { 10,10,10 });
	rbGen->setActive();
	_RBGens.push_back(rbGen);*/

	RigidBody* model = new RigidBody(_scene, _physics, { 0,10,0 }, { 1,1,0,1 }, { 0, 10, 0 }, { 4,10,4 }, 1, 100, Cube);
	RigidBodyGenerator* rbGen = new GaussianRigidBodyGen("uniform", model, { 10, 50,-100 }, { 1,1,1 }, 0.2,false, {100,1,100});
	rbGen->setActive();
	_RBGens.push_back(rbGen);

	wind = new RigidBodyWindForceGen(Vector3(0,10,100), 100, 0);
	wind->setActive();
	
	
}