#ifndef EVENT_H
#define EVENT_H

#include <OGRE/Ogre.h>
#include <SDL2/SDL.h>


using namespace Ogre;

class Event {
    protected:
        const uint8_t  *mod {nullptr};
        SDL_Event event;
        Timer t;
        RenderWindow *renderWindow {nullptr};
        Ogre::Root *root {nullptr};

        Event(Event const&) = delete;
        Event(Event const&&) = delete;
        Event() = default;

    public:
        void getKeyboardEvent();
        void getMouseEvent();
        void getEvent();
        void parcialLoop();
        virtual void loop() = 0;
};

void getEvent(RenderWindow *w, Root *r, SceneManager *mySceneMgr);
void dragObject(unsigned int x, unsigned int y, SceneManager *sm, RenderWindow *rw); 
void mouseClick(unsigned int absoluteX, unsigned int absoluteY, SceneManager *sm, RenderWindow *rw);

#endif



