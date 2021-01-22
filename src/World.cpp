#include <Ogre.h>
#include <iostream>
#include <exception>
#include "World.h"
#include "OgreDotScenePlugin.h"
#include <OgreSceneLoaderManager.h>
#include <Terrain/OgreTerrainGroup.h>
#include <Terrain/OgreTerrain.h>
#include "ParticleUniverseWrapper.h"

World::World() {

}

World::~World() {

}

void World::init(Root *r) {
    root = r;

    /**** DotScene
    Ogre::StringUtil::splitFilename(scene, mSceneFile, mResourcePath);
    Ogre::SceneLoaderManager::getSingleton().load(mSceneFile, "Scene", scnMgr->getRootSceneNode());
    ****/
}

void World::addActor(Actor *a) {
    actorList.push_back(a);
}

std::vector<Actor *> &World::getActorList() {
    return actorList;
}

void World::addPUParticle(SceneNode *n) {

}

void World::addParticles(SceneNode *n) {
    auto sceneMgr = root->getSceneManagers().begin()->second;
    auto sunParticle = sceneMgr->createParticleSystem("Particle", "MyExamples/PurpleFountain");
    auto particleNode = n->createChildSceneNode();

    particleNode->attachObject(sunParticle);
}

void World::create() {
    auto sm = root->getSceneManagers().begin()->second;
    sm->setAmbientLight(ColourValue(0.8, 0.8, 0.8));

    MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, 0), 400, 400, 10, 10, true, 1, 10, 10, Vector3::UNIT_Z);

    auto floor = sm->createEntity("floor");
    floor->setMaterialName("Panels");
    SceneNode *nodePlane= sm->getRootSceneNode()->createChildSceneNode("Floor");
    sm->getRootSceneNode()->getChild("Floor")->setPosition(Vector3(0, -20, 0));
    nodePlane->attachObject(floor);
    
    auto a1 = new Actor;
    a1->setSceneManager(sm);
    a1->setAnimString("ArmatureAction");
    a1->createEntity("Fighter1.mesh");
    a1->translate({-30, 0, -24});

    auto a2 = new Actor;
    a2->setSceneManager(sm);
    a2->setAnimString("Dance1");
    a2->createEntity("Fighter2.mesh");
    a2->translate({30, 0, -24});

    auto robot = new Actor;
    robot->setSceneManager(sm);
    robot->setAnimString("Walk");
    robot->createEntity("robot.mesh");
    robot->translate({0, -8, -12});
    robot->setScale({0.25, 0.25, 0.25});
    robot->yaw(Radian(-Math::HALF_PI));
    robot->setMaterialName("Examples/Material4");

    auto a3 = new Actor;
    a3->setSceneManager(sm);
    a3->setAnimString("ArmatureAction");
    a3->createEntity("tenta.mesh");
    // a3->translate({15, 0, -24});
    a3->translate({-50, 0, 0});
    a3->setScale({1.7, 1.7, 1.7});
    a3->pitch(Radian(-Math::HALF_PI));
    a3->setMaterialName("Material4");

    // Actor *a4 = new Actor;
    // a4->setSceneManager(sm);
    // a4->createEntity("spidermonster.mesh");
    // a4->translate({0, 0, 0});
    // a4->setScale({1.7, 1.7, 1.7});
    // a4->setMaterialName("spmonster");

    addActor(a1);
    addActor(a2);
    addActor(a3);
    addActor(robot);
    // addActor(a4);
    // addParticles(a4->getNode());
    // loadTerrain();

    // auto ps = sm->createParticleSystem("Smoke", "MySmoke1");
    // ps->removeQueryFlags(32);
    // auto a = robot->getNode()->createChildSceneNode(Vector3(0, 50, 0));
    // a->attachObject(ps);

    // Ogre::SceneLoaderManager::getSingleton().load("testbola.scene", "General", sm->getRootSceneNode());
    // Ogre::SceneLoaderManager::getSingleton().load("terrain.scene", "General", sm->getRootSceneNode());
}

void World::loadTerrain() {
    auto sm = root->getSceneManagers().begin()->second;
    auto mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(sm, Ogre::Terrain::ALIGN_X_Z, 512, 12000.0f);
    mTerrainGroup->setFilenameConvention("terrain", "dat");
    mTerrainGroup->setOrigin(Vector3(1000, 0, 5000));

    Ogre::SceneLoaderManager::getSingleton().load("terrain.scene", "General", sm->getRootSceneNode());

}



