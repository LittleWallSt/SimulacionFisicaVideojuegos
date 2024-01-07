#pragma once
#include <PxPhysicsAPI.h>
#include "RigidBody.h"

class SuikaCallback : public physx::PxSimulationEventCallback {
public:
    virtual void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override {
        for (physx::PxU32 i = 0; i < nbPairs; i++) {
            const physx::PxContactPair& cp = pairs[i];

            if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {
               
            }
        }

        //for (PxU32 i = 0; i < nbPairs; i++) {
        //    const PxContactPair& cp = pairs[i];
        //    // Check if objects have collided
        //    if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND) {
        //        // Handle collision
        //        // Example: Print collision information
        //        const PxRigidActor* actor0 = pairHeader.actors[0];
        //        const PxRigidActor* actor1 = pairHeader.actors[1];
        //        printf("Collision detected between %s and %s\n", actor0->getName(), actor1->getName());
        //    }
        //}
    }

    virtual void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override {
    }

    virtual void onWake(physx::PxActor** actors, physx::PxU32 count) override {
    }

    virtual void onSleep(physx::PxActor** actors, physx::PxU32 count) override {
    }

    virtual void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override {
    }

    virtual void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override {
    }

    
};
