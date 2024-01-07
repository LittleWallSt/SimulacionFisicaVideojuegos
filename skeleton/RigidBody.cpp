#include "RigidBody.h"

//RigidBody con lifeTime por copia
RigidBody::RigidBody(PxRigidDynamic* rigid, double time, Vector4 colour) {
	lifeTime = time;
	physx::PxShape* shape;
	_rDynamic->getShapes(&shape, 1);
	_renderItem = new RenderItem(shape, _rDynamic, colour);
}

//RigidBody infinito por copia
RigidBody::RigidBody(PxRigidDynamic* rigid, Vector4 colour):_rDynamic(rigid) {
	lifeTime = -100;
	physx::PxShape* shape;
	_rDynamic->getShapes(&shape, 1);
	_renderItem = new RenderItem(shape, _rDynamic, colour);
}

//Constructora de rigidBody inicial
RigidBody::RigidBody(PxScene* scene, PxPhysics* phys, Vector3 p, Vector4 colour, Vector3 v, Vector3 d , double m, double lTime , type typ)
{
	Scene = scene;
	Physics = phys;
	_color = colour;
	tipo = typ;
	dimensions = d;
	iniPos = p;
	//Le asignamos una forma con respecto al tipo indicado, si no se especifica sera un cubo
	physx::PxShape* forma;
	switch (typ)
	{
	case Cube:	forma = CreateShape(physx::PxBoxGeometry(d)); break;

	case Capsule:forma = CreateShape(physx::PxCapsuleGeometry(d.x, d.y)); break;

	case Sphere:forma = CreateShape(physx::PxSphereGeometry(d.x)); break;

	default:forma = CreateShape(physx::PxBoxGeometry(d)); break;
	}

	//Creamos el solido rigido dinamico con su velocidad inicial, su masa inicial
	_rDynamic = phys->createRigidDynamic(physx::PxTransform(p));
	_rDynamic->setLinearVelocity(v);
	_rDynamic->setMass(m);
	_rDynamic->setAngularVelocity({ 0,0,0 });

	lifeTime = lTime;
	
	//Le añadimos la forma
	_rDynamic->attachShape(*forma);

	//Masa entre volumen es igual a densidad
	physx::PxRigidBodyExt::updateMassAndInertia(*_rDynamic, m / (d.x * d.y * d.z));


	//Lo agregamos a la escena
	scene->addActor(*_rDynamic);
	_renderItem = new RenderItem(forma, _rDynamic, colour);

		
	
}

RigidBody::~RigidBody() {
	_rDynamic->release();
	_renderItem->release();
}

//StaticRigidBody::StaticRigidBody(PxScene* scene, PxPhysics* phys, Vector3 p, Vector3 d,  Vector4 colour = { 0, 1, 1, 1 }, type typ) {
//	
//	_rStatic = phys->createRigidStatic(physx::PxTransform(p));
//
//	lifeTime = -100;
//
//	physx::PxShape* forma;
//	switch (typ)
//	{
//	case Cube:	forma = CreateShape(physx::PxBoxGeometry(d)); break;
//
//	case Capsule:forma = CreateShape(physx::PxCapsuleGeometry(d.x, d.y)); break;
//
//	case Sphere:forma = CreateShape(physx::PxSphereGeometry(d.x)); break;
//
//	default:forma = CreateShape(physx::PxBoxGeometry(d)); break;
//	}
//	//Le añadimos la forma
//	_rStatic->attachShape(*forma);
//
//	//Lo agregamos a la escena
//	scene->addActor(*_rStatic);
//	_renderItem = new RenderItem(forma, _rStatic, colour);
//}
//
//StaticRigidBody::~StaticRigidBody() {
//	_rStatic->release();
//	DeregisterRenderItem(_renderItem);
//}