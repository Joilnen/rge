#ifndef PARTICLE_UNIVERSE_WRAPPER_H
#define PARTICLE_UNIVERSE_WRAPPER_H

#include <Ogre.h>
#include <ParticleUniverseSystemManager.h>
#include <ParticleUniversePlugin.h>
#include <vector>

class ParticleUniverseWrapper {

    ParticleUniverse::ParticleSystemManager *pManager {nullptr};
    
    // ParticleUniverse::ParticleSystem* pSys = pManager->createParticleSystem("pSys1", "mp_torch", mSceneMgr);
    std::vector<ParticleUniverse::ParticleSystem*> pSysList;

    ParticleUniverseWrapper();
    public:
        static ParticleUniverseWrapper &getInstance() {
            static ParticleUniverseWrapper p;
            return p;
        }

        void initPlugin(Ogre::Root *r, Ogre::SceneNode *sn = nullptr);
        virtual ~ParticleUniverseWrapper();

};

#endif


