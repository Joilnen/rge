#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <OGRE/Ogre.h>
#include <vector>
#include "GameNode.h"
#include "Actor.h"
#include "ECS.h"

ECS_TYPE_IMPLEMENTATION;

using namespace ECS;

class GameManager : public EntitySystem {
    Root *root;
    void mainLoop();
    public:
        GameManager();
        virtual ~GameManager();
};

#endif



