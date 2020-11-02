#include <OGRE/Ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <cstdlib>
#include <iostream>
#include <memory>

#include <iostream>
#include "FrameListener.h"
#include "EngineManager.h"
#include "Event.h"

MovableObject *mSelectedEntity = nullptr;
float mSelectedEntityDist = 0.0f;

void Event::getKeyboardEvent() {

}

void Event::getMouseEvent() {

}

void Event::getEvent() {
    
}

void Event::parcialLoop() {
    Timer t;
    while(!renderWindow->isClosed()) {
        // WindowEventUtilities::messagePump();
        root->renderOneFrame();
        t.reset();
    }
}

/****
Event* Event::create(EngineManager &g) {
    Event *ev = new Event(g)();
    root = g.getRootSceneNode();
    renderWindow = g.getRenderWindow();
    sm = g.getSceneManager();
    root->addFrameListener(new EngineFrameListener());
    root->getRenderSystem()->setNormaliseNormals(true);

    return ev;
}
****/

void getEvent(RenderWindow *w,  Root *r, SceneManager *sceneMgr) {

    const uint8_t  *mod = nullptr;
    SDL_Event event;
    Timer t;
    r->addFrameListener(new EngineFrameListener);
    r->getRenderSystem()->setNormaliseNormals(true);

    while(!w->isClosed()) {
        // WindowEventUtilities::messagePump();
        r->renderOneFrame();
        if(t.getMilliseconds() < 25)
            continue;
        t.reset();

        mod = SDL_GetKeyboardState(nullptr);

        if(mod[SDL_SCANCODE_LSHIFT] && mod[SDL_SCANCODE_UP]) {
            for (auto &a : EngineManager::getInstance().getVectorActor()) {
                if(a->getEntity()->getParentSceneNode()->getShowBoundingBox()) {
                    a->getEntity()->
                        getParentSceneNode()->
                        translate(Vector3(0, 0, -0.4),
                        Node::TransformSpace::TS_WORLD);
                }
            }
        }
        else if(mod[SDL_SCANCODE_LCTRL] && mod[SDL_SCANCODE_UP]) {
            for (auto &a : EngineManager::getInstance().getVectorActor()) {
                if(a->getEntity()->getParentSceneNode()->getShowBoundingBox()) {
                    a->getEntity()->
                        getParentSceneNode()->
                        yaw(Radian(1/(2*Math::PI)));
                }
            }
        }
        else if(mod[SDL_SCANCODE_UP]) {
            for (auto &a : EngineManager::getInstance().getVectorActor()) {
                if(a->getEntity()->getParentSceneNode()->getShowBoundingBox()) {
                    a->getEntity()->
                        getParentSceneNode()->
                        translate(Vector3(0, 0.4 ,0),
                        Node::TransformSpace::TS_WORLD);
                }
            }
        }

        if(mod[SDL_SCANCODE_LSHIFT] && mod[SDL_SCANCODE_DOWN]) {
            for (auto &a : EngineManager::getInstance().getVectorActor()) {
                if(a->getEntity()->getParentSceneNode()->getShowBoundingBox()) {
                    a->getEntity()->
                        getParentSceneNode()->
                        translate(Vector3(0, 0, 0.4),
                        Node::TransformSpace::TS_WORLD);

                }
            }
        }
        else if(mod[SDL_SCANCODE_LCTRL] && mod[SDL_SCANCODE_DOWN]) {
            for (auto &a : EngineManager::getInstance().getVectorActor()) {
                if(a->getEntity()->getParentSceneNode()->getShowBoundingBox()) {
                    a->getEntity()->
                        getParentSceneNode()->
                        yaw(Radian(-1/(2*Math::PI)));
                }
            }
        }
        else if(mod[SDL_SCANCODE_DOWN]) {
            for (auto &a : EngineManager::getInstance().getVectorActor()) {
                if(a->getEntity()->getParentSceneNode()->getShowBoundingBox()) {

                    a->getEntity()->
                        getParentSceneNode()->
                        translate(Vector3(0, -0.4, 0),
                        Node::TransformSpace::TS_WORLD);

                }
            }
        }

        if(mod[SDL_SCANCODE_RIGHT]) {
            for (auto &a : EngineManager::getInstance().getVectorActor()) {
                if(a->getEntity()->getParentSceneNode()->getShowBoundingBox()) {

                    a->getEntity()->
                        getParentSceneNode()->
                        translate(Vector3(0.4, 0 ,0),
                        Node::TransformSpace::TS_WORLD);

                }
            }
        }

        if(mod[SDL_SCANCODE_LEFT]) {
            for (auto &a : EngineManager::getInstance().getVectorActor()) {
                if(a->getEntity()->getParentSceneNode()->getShowBoundingBox()) {
                    a->getEntity()->
                        getParentSceneNode()->
                        translate(Vector3(-0.4, 0, 0),
                        Node::TransformSpace::TS_WORLD);
                }
            }
        }

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_MOUSEMOTION:
                    std::cout << "Mouse moving\n";
                    std::cout << "X: " << event.motion.x << "\nY: " << event.motion.y << "\n";
                    // SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
                    // SDL_WarpMouseInWindow(Render::getInstance().getWindow(), x, y);
                    // SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
                    dragObject(event.motion.x, event.motion.y, sceneMgr, w);
                    MyGUI::InputManager::getInstance().injectMouseMove(
                            event.motion.x,
                            event.motion.y,
                            0
                    );
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouseClick(event.button.x, event.button.y, sceneMgr, w);
                    MyGUI::InputManager::getInstance().injectMousePress(
                            event.button.x,
                            event.button.y,
                            MyGUI::MouseButton::Enum(0)
                    );
                    break;
                case SDL_QUIT:
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                        goto OUT;
                    else if(event.key.keysym.sym == SDLK_w) {
                        Camera *c = sceneMgr->getCamera("MainCam");
                        if(c && c->getPolygonMode() == PM_WIREFRAME)
                            c->setPolygonMode(PM_SOLID);
                        else
                            c->setPolygonMode(PM_WIREFRAME);
                    }
                    else if(event.key.keysym.sym == SDLK_RETURN) {
                        for (auto &a : EngineManager::getInstance().getVectorActor()) {
                            if(a->getEntity()->
                                  getParentSceneNode()->
                                  getShowBoundingBox()) {
                            a->getEntity()->
                                  getParentSceneNode()->
                                  showBoundingBox(false);
                            }
                        }
                    }
            }
        }
    }
OUT:;
}


void mouseClick(unsigned int absoluteX, unsigned int absoluteY, SceneManager *sm, RenderWindow *rw) {

    auto width = static_cast<float>(rw->getViewport(0)->getActualWidth());
    auto height = static_cast<float>(rw->getViewport(0)->getActualHeight());

    auto ray = sm->getCamera("MainCam")->getCameraToViewportRay((float) absoluteX / width, (float) absoluteY / height);

    // Set up the ray query - you will probably not want to create this every time
    auto rq = sm->createRayQuery(ray);

    // Sort by distance, and say we're only interested in the first hit; also, only pick entities
    rq->setSortByDistance(true, 1);
    rq->setQueryTypeMask(Ogre::SceneManager::ENTITY_TYPE_MASK);

    // Execute
    // RaySceneQueryResult res = rq->execute();
    auto res = rq->execute();
    auto it = res.begin();

    // these two things should probably be encapsulated in their own class/struct
    mSelectedEntity = nullptr;
    mSelectedEntityDist = 0.0f; 

    if (it != res.end()) {
        mSelectedEntity = it->movable;
        mSelectedEntityDist = it->distance;
        mSelectedEntity->setDebugDisplayEnabled(
            !mSelectedEntity->isDebugDisplayEnabled()       
        );

        if(mSelectedEntity->getName().compare("Ogre/MO1")) {
            mSelectedEntity->
                getParentSceneNode()->
                showBoundingBox(mSelectedEntity->isDebugDisplayEnabled());
        }
        printf("clicked: %s\n", mSelectedEntity->getName().c_str());
    }
    else {
        printf("cleared selection.\n");
    }

    sm->destroyQuery(rq);
}

void dragObject(unsigned int x, unsigned int y, SceneManager *sm, RenderWindow *rw) {

  if (mSelectedEntity) {
    auto p = mSelectedEntity->getParentSceneNode();

    if (p && p->getShowBoundingBox()) {
      auto width = rw->getViewport(0)->getActualWidth();
      auto height = rw->getViewport(0)->getActualHeight();

      auto ray = sm->getCamera("MainCam")->
          getCameraToViewportRay(
              (float) x / width,
              (float) y / height
      );

      auto pos = ray.getPoint(mSelectedEntityDist);
      pos.y = p->getPosition()[1];

      p->setPosition(pos);
    }
  }
}




