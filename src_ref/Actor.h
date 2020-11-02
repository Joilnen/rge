#include <iostream>
#include <OGRE/Ogre.h>
#include <OGRE/OgreSceneManager.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "ECS.h"

#ifndef ACTOR_H
#define ACTOR_H

ECS_TYPE_IMPLEMENTATION;

using namespace ECS;

struct Actor {
	ECS_DECLARE_TYPE;
	Actor(std::string &name) : name{name} {}
    void setName(std::string s) {
        name = s;
    }
    std::string name;
};
ECS_DEFINE_TYPE(Actor);

#endif


