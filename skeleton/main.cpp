#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "RenderItems/particle.h"
#include "RenderItems/particle.h"
#include "Objects/ProyectileLauncher.h"
#include "ParticleGenerator.h"
#include "ParticleSystem.h"
#include "RigidBodySystem.h"
#include "ProyectoSystem.h"
#include <iostream>
#include "suikaCallback.h"

std::string display_text = "SUIKA PHYSX";


using namespace physx;


PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
SuikaCallback callback;
particle* parti;
ProyectileLauncher* gun;
ParticleSystem* pSys;
RigidBodySystem* rbSys;
ProyectoSystem* prSys;



// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -90.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &callback;
		//&gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	//SuikaCallback myCB;
	//gScene->setSimulationEventCallback(&myCB);
	//parti = new particle(10, Vector3(0), Vector3(50), Vector3(0), 0, Vector4(1, 1, 1, 1), CreateShape(PxBoxGeometry(500, 1, 500)));
	//pSys = new ParticleSystem();
	//rbSys = new RigidBodySystem(gScene, gPhysics);
	//rbSys->demo();
	prSys = new ProyectoSystem(gScene, gPhysics);
	prSys->demo();


}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	//parti->integrate(t);
	//gun->integrate(t);
	
	//pSys->update(t);
	//rbSys->update(t);
	prSys->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	//rbSys->keyPress(key);
	//pSys->keyPress(key);
	prSys->keyPress(key);
	//gun->OnKeyPress(key, camera, GetCamera()->getDir());
	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	/*case 'G':
	{
		pSys->getParticleGenerator("Geyser")->setActive();
		break;
	}
	case 'P':
	{
		pSys->getParticleGenerator("GeyserINV")->setActive();
		break;
	}
	case 'C':
	{
		pSys->getParticleGenerator("Circles")->setActive();
		break;
	}
	case 'B':
	{
		pSys->getParticleGenerator("Avispero")->setActive();
		break;
	}
	case 'F':{
		pSys->spawnF();
		break;

	}
	case '1': {
		pSys->setActiveForce(0);
		break;
	}
	case '2': {
		pSys->setActiveForce(1);

		break;
	}
	case '3': {
		pSys->setActiveForce(2);

		break;
	}
	case '4': {
		pSys->setActiveForce(3);

		break;
	}
	case '5': {
		pSys->setActiveForce(4);

		break;
	}*/
	/*case '6': {
		pSys->explode();
		pSys->setActiveForce(5);

		break;
	}*/

	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}