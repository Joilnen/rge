#include <OGRE/Ogre.h>
#include "FrameListener.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "resources.h"
#include "Event.h"
#include "EngineManager.h"
#include "World.h"
#include "Ui.h"
#include "RgeGui.h"
#include <OgreOverlaySystem.h>

using namespace Ogre;

int main()
{
    EngineManager &gm = EngineManager::getInstance();
    gm.init("plugins.cfg", "ogre.cfg");

    auto root = gm.getRootSceneNode();
    auto window = gm.getRenderWindow();
    auto sceneMgr = gm.getSceneManager();
    sceneMgr->addRenderQueueListener(new OverlaySystem);

    setResources();

    auto world = World::getInstance();
    world.init(root);
    world.create();

    for_each(world.getActorList().cbegin(),
        world.getActorList().cend(),
        [&gm](Actor *a) {
            gm.addActor(a);
        }
    );

    // create scene
    sceneMgr->setAmbientLight(ColourValue(.25, .25, .25));

    // Ui::getInstance().addUiComponents(window, sceneMgr);
    // getEvent and mainLoop;
    auto imGuiOverlay = new ImGuiOverlay;
    auto rgeGui = new RgeGui;
    rgeGui->setUp();
    imGuiOverlay->setZOrder(0);
    imGuiOverlay->show();
    OverlayManager::getSingleton().addOverlay(imGuiOverlay);
    window->addListener(rgeGui); 

    getEvent(window, root, sceneMgr);

    delete rgeGui;
    delete imGuiOverlay;

    SDL_Quit();
    // Crashing I don't know why 
    // root->shutdown();
    // OGRE_DELETE root;

    return 0;
}



