#ifndef WORLD_H
#define WORLD_H

#include "Actor.h"
#include <vector>
#include <OGRE/Ogre.h>

using namespace Ogre;

class World {

    std::vector<Actor*> actorList;
    Root *root;
    Vector3 oldPos, originalPos;

    World();

    void testMouseDrop(SceneManager *s);
    MovableObject *getNode(float mouseScreenX, float mouseScreenY);

    void loadTerrain();
    void addParticles(SceneNode *n);
    void addPUParticle(SceneNode *n);

    public:
        void init(Root *r);
        ~World();
        static World &getInstance() {
            static World w;
            return w;
        }

        void addActor(Actor *);
        std::vector<Actor *> &getActorList();
        void create();
};

#endif



