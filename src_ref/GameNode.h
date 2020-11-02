#include <iostream>
#include <OGRE/Ogre.h>
#include <OGRE/OgreSceneManager.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "ECS.h"

#ifndef NODE_H
#define NODE_H

ECS_TYPE_IMPLEMENTATION;

using namespace ECS;
using namespace Ogre;

struct GameNode {
	ECS_DECLARE_TYPE;
	GameNode(SceneManager *sm) : sm{sm} {}
    private:
        SceneManager *sm {nullptr};
};
ECS_DEFINE_TYPE(GameNode);

#endif


