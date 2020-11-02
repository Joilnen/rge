#ifndef ACTOR_H
#define ACTOR_H

#include <OGRE/Ogre.h>
#include <OGRE/OgreSceneManager.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

using namespace Ogre;

class Actor {

    SceneManager *sceneMgr {nullptr};
    Entity *entity;
    Ogre::AnimationState *animState;
    boost::uuids::uuid id {boost::uuids::random_generator()()};
    std::string idStr;
    std::vector<std::string> animNames{"Idle", "Shoot", "Slump", "Walk"};
    std::string animStr;
    SceneNode *node {nullptr};

    public:
        Actor() = default;
        ~Actor() = default;

        SceneManager *getSceneManager();
        void setSceneManager(SceneManager *nm);
        SceneNode *getNode();
        void setEntity(Entity *e);
        void createEntity(std::string &&s);
        Entity *getEntity();
        void setAnimState(AnimationState *a);
        AnimationState *getAnimState();
        void translate(Vector3 &&v);
        void setScale(Vector3 &&v);
        void setAnimString(std::string &&s);
        void setAnimIndex(int i);
        void pitch(Radian &&angle);
        void yaw(Radian &&angle);
        void roll(Radian &&angle);
        void setMaterialName(std::string &&s);
};

#endif



