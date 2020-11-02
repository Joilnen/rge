#include <iostream>
#include <OGRE/Ogre.h>
#include <OGRE/OgreSceneManager.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "ECS.h"

#ifndef ROOTGAME_H
#define ROOTGAME_H

ECS_TYPE_IMPLEMENTATION;

using namespace Ogre;
using namespace ECS;

struct RootGame {
	ECS_DECLARE_TYPE;
	RootGame(Ogre::Root *r) : root{r} {}
    Ogre::Root *root {nullptr};
};
ECS_DEFINE_TYPE(RootGame);

#endif


