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

    /****
    if(loadResourceFile())
        return;

    ResourceGroupManager::getSingleton().addResourceLocation("media", "FileSystem", "General", false);
    ResourceGroupManager::getSingleton().addResourceLocation("media/ShadowVolume", "FileSystem", "General", false);
    ResourceGroupManager::getSingleton().addResourceLocation("media/schemes", "FileSystem", "General", false);
    ResourceGroupManager::getSingleton().addResourceLocation("media/layouts", "FileSystem", "General", false);
    ResourceGroupManager::getSingleton().addResourceLocation("media/looknfeel", "FileSystem", "General", false);
    ResourceGroupManager::getSingleton().addResourceLocation("media/models", "FileSystem", "General", false);
    ResourceGroupManager::getSingleton().addResourceLocation("media/images", "FileSystem", "General", false);
    ResourceGroupManager::getSingleton().addResourceLocation("media/imagesets", "FileSystem", "General", false);
    ResourceGroupManager::getSingleton().addResourceLocation("media/fonts", "FileSystem", "General", false);
    // ResourceGroupManager::getSingleton().addResourceLocation("media/particle", "FileSystem", "General", false);

    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/fonts", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/models", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/programs", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/scripts", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/textures", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/textures/nvidia", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/particle", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/DeferredShadingMedia", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/Rmaterials/scripts/SSAO", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/Rmaterials/textures/SSAO", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/volumeTerrain", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/ShadowVolume", "FileSystem", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/packs/cubemap.zip", "Zip", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/packs/cubemapsJS.zip", "Zip", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/packs/dragon.zip", "Zip", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/packs/fresneldemo.zip", "Zip", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/packs/ogretestmap.zip", "Zip", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/packs/Sinbad.zip", "Zip", "Popular", false);
    ResourceGroupManager::getSingleton().addResourceLocation("/usr/local/share/OGRE/Media/packs/skybox.zip", "Zip", "Popular", false);

    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    for(auto &a : ResourceGroupManager::getSingleton().getResourceDeclarationList("General")) {
        std::cout << "----oo---->> " <<  a.resourceName << std::endl;
    }

    std::cout << " =======*****^^^^^^^>>>>> Passei aqui\n";
    ****/
}



