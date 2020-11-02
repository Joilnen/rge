#include <iostream>
#include <OGRE/Ogre.h>
#include <OGRE/OgreSceneManager.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "ECS.h"

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

ECS_TYPE_IMPLEMENTATION;

using namespace Ogre;
using namespace ECS;

struct SceneManagerEnt {
	ECS_DECLARE_TYPE;
	SceneManagerEnt(Ogre::SceneManager *r) : root{r} {}
    Ogre::SceneManager *root {nullptr};
};
ECS_DEFINE_TYPE(SceneManagerEnt);

#endif


