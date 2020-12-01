#ifndef __SAMPLEGUI_H
#define __SAMPLEGUI_H

#include <OGRE/Ogre.h>
#include <OGRE/Bites/OgreInput.h>

using namespace Ogre;
using namespace OgreBites;

class SampleUI : public InputListener, public RenderTargetListener {

    public:
        SampleUI();
        ~SampleUI();
};

#endif
