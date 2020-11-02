#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H

#include <OGRE/Ogre.h>
#include "Actor.h"
#include "Event.h"
#include <vector>
#include <SDL2/SDL.h>

class EngineManager : public Event {

    std::vector<Actor*> actorsStack;
    SDL_Window *window {nullptr};
    RenderWindow *renderWindow {nullptr};
    SceneManager *sceneMgr {nullptr};
    Ogre::Root *root {nullptr};
    Ogre::Camera *camera {nullptr};
    EngineManager() = default;
    Ogre::Viewport *vpTop{nullptr}, *vpBottom{nullptr};
    void _createParticle();
    void _addLights();
    void _initSceneManager();
    void _init(const std::string &pcfg, const std::string &ocfg);

    public:
        static EngineManager &getInstance() {
            static EngineManager g;
            return g;
        }
        virtual ~EngineManager() = default;
        void init(const std::string &pcfg, const std::string &ocfg);
        void setResources();
        void addActor(Actor *a);
        // void addActor(std::shared_ptr<Actor> &a);
        std::vector<Actor *> &getVectorActor();

        void loop() override;

        RenderWindow *getRenderWindow();
        SceneManager *getSceneManager();
        Ogre::Root *getRootSceneNode() {
            return root;
        }
};

#endif



