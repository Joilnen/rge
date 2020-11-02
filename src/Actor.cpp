#include "Actor.h"
#include <iostream>

using namespace Ogre;
using namespace std;

void Actor::setSceneManager(SceneManager *nm) {
    sceneMgr = nm;
}

SceneManager *Actor::getSceneManager() {
    return sceneMgr;
}

void Actor::setEntity(Entity *e) {
    entity = e;
}

Entity *Actor::getEntity() {
    return entity;
}

void Actor::setAnimState(AnimationState *a) {
    animState = a;
}

AnimationState *Actor::getAnimState() {
    return animState;
}

void Actor::createEntity(std::string &&s) {
    entity = sceneMgr->createEntity(s.c_str());
    entity->getMesh()->buildEdgeList();
    entity->setCastShadows(true);
    auto pAnimSet = entity->getAllAnimationStates();
    if(pAnimSet) {
        Ogre::AnimationStateIterator animNames = pAnimSet->getAnimationStateIterator();
        animState = entity->getAnimationState(animStr.c_str());
        animState->setEnabled(true);
        animState->setLoop(true);
    }
    else
        animState = nullptr;
    node = sceneMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(entity);
    node->setPosition(Vector3(0, -12, 0));
}

void Actor::translate(Vector3 &&v) {
    node->translate(v);
}

void Actor::setScale(Vector3 &&v) {
    node->setScale(v);
}

void Actor::setAnimString(std::string &&s) {
    animStr = s;
}

void Actor::setAnimIndex(int i) {
    animStr = animNames[i];
}

void Actor::pitch(Radian &&angle) {
    node->pitch(angle);
}

void Actor::yaw(Radian &&angle) {
    node->yaw(angle);
}

void Actor::roll(Radian &&angle) {
    node->roll(angle);
}

void Actor::setMaterialName(std::string &&s) {
    if(entity)
        entity->setMaterialName(s.c_str());
}

Ogre::SceneNode *Actor::getNode() {
    return node;
}



