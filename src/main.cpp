#include <OGRE/Ogre.h>
#include "EngineManager.h"
#include <iostream>

using namespace Ogre;

int main(int argc, char *argv[])
{
    try {
        EngineManager em;
        em.initApp();
        em.getRoot()->startRendering();
        // em.closeApp(); // I got double cleaning crash
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}



