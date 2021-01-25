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

    EngineManager em;
    em.initApp();
    em.getRoot()->startRendering();
    em.closeApp();

    return 0;
}



