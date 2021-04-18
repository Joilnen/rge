#include <OGRE/Ogre.h>
#include <SDL2/SDL.h>
#include "resources.h"
#include <iostream>

using namespace Ogre;

static bool loadResourceFile() {

    // Load resource paths from config file
    ConfigFile cf;
    bool r {false};

    cf.load("resources.cfg");
    // Go through all sections & settings in the file
    ConfigFile::SectionIterator seci = cf.getSectionIterator();
    String secName, typeName, archName;

    while (seci.hasMoreElements()) {

        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;

        for (i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(
            archName, typeName, secName);
        }

        r = true;
    }

    if(r)
        ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    return r;
}

void setResources() {
    loadResourceFile();
}



