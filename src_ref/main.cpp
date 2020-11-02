#include "ECS.h"
#include "GameNode.h"
#include <string>
#include "Actor.h"
#include <OGRE/Ogre.h>
#include "GameManager.h"
#include "SceneManager.h"
#include "RootGame.h"

using namespace Ogre;

int main()
{
    auto world { World::createWorld() };
    auto gameSystem { world->registerSystem(new GameManager) };

    auto rootEntity { world->create() };
    auto rootAssign { rootEntity->assign<RootGame>(new Ogre::Root) };

    auto sceneManager { world->create() };
    rootEntity->assign<SceneManagerEnt>(rootAssign->root->createSceneManager());

    // ent->assign<GameNode>(root->createSceneManager());

    return 0;
}



