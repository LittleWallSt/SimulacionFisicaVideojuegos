#pragma once
#include <PxPhysicsAPI.h>
#include "RigidBody.h"

class SuikaCallback : public physx::PxSimulationEventCallback {
public:
    virtual void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override {
        for (physx::PxU32 i = 0; i < nbPairs; i++) {
            const physx::PxContactPair& cp = pairs[i];

            //Ha habido contacto?
            if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {
                //printf("O: \n");
                
                //Primera comprobacion es si son dinamicos los dos
                if (pairHeader.actors[0]->getType() == physx::PxActorType::eRIGID_DYNAMIC &&
                    pairHeader.actors[1]->getType() == physx::PxActorType::eRIGID_DYNAMIC) {
                    //printf("O:++ \n");
                    
                    //La segunda es si son los dinamicos que me interesan, es decir, estan en mi mapa?
                    if (SuikaInstance().reference.count(pairHeader.actors[0]) > 0 &&
                        SuikaInstance().reference.count(pairHeader.actors[1]) > 0) {
                       
                        //Ha habido contacto ya? Si es asi no tenemos que comprobar otra vez
                        if (!SuikaInstance().reference[pairHeader.actors[0]]->getContact() && 
                            !SuikaInstance().reference[pairHeader.actors[1]]->getContact()) {
                            
                            
                            if (SuikaInstance().reference[pairHeader.actors[0]]->getCouleur() ==
                                SuikaInstance().reference[pairHeader.actors[1]]->getCouleur()) {
                                //Activamos el flag para los dos rigidbodies que se borren y no spawneen mas frutas
                                SuikaInstance().reference[pairHeader.actors[0]]->flag();
                                SuikaInstance().reference[pairHeader.actors[1]]->flag();

                                //Activamos el mensaje de la fruta
                                SuikaInstance().reference[pairHeader.actors[0]]->activateMessage();
                            }
                            
                        }
                        
                        //printf("O:# \n");
                    }
                };
            }
        }
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
