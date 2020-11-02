#include <OGRE/Ogre.h>

using namespace Ogre;

void makeQuadObj(SceneManager *sm, String &&s, String &&mat) {
    auto manual = sm->createManualObject(s);
    manual->begin(mat, RenderOperation::OT_TRIANGLE_LIST);
        manual->position(5.0, 0.0, 0.0);
        manual->textureCoord(0,1);
        manual->position(-5.0, 10.0, 0.0);
        manual->textureCoord(1,0);
        manual->position(-5.0, 0.0, 0.0);
        manual->textureCoord(1,1);
        manual->position(5.0, 10.0, 0.0);
        manual->textureCoord(0,0);

        manual->index(0);
        manual->index(1);
        manual->index(2);
        manual->index(0);
        manual->index(3);
        manual->index(1);
    manual->end();
    manual->convertToMesh(s);
}

SceneNode *addQuad(SceneManager *sm, String &&s) {
    auto ent0 = sm->createEntity(s);
    auto n0 = sm->getRootSceneNode()->createChildSceneNode();
    n0->attachObject(ent0);
    return n0;
}

SceneNode *addQuad(SceneManager *sm, SceneNode *parent,  String &&s) {
    auto ent0 = sm->createEntity(s);
    auto n0 = parent->createChildSceneNode();
    n0->attachObject(ent0);
    return n0;
}

int main()
{
    auto root = new Root("plugins.cfg");
    ResourceGroupManager::getSingleton().addResourceLocation(".", "FileSystem", "General", false);
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    auto rs = root->getAvailableRenderers()[0];
    root->setRenderSystem(rs);
    auto window = root->initialise(true, "HelloOgre");
    auto sceneMgr = root->createSceneManager();

    auto cameraNode = sceneMgr->createSceneNode();
    sceneMgr->getRootSceneNode()->addChild(cameraNode);
    auto camera = sceneMgr->createCamera("Cam");
    camera->setNearClipDistance(5);
    cameraNode->attachObject(camera);
    cameraNode->setPosition(Vector3(0, 0, 50));
    cameraNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);

    auto vp = window->addViewport(camera);
    vp->setBackgroundColour(ColourValue(0.0, 0.3, 0.0));
    camera->setAspectRatio(Real(vp->getActualWidth()) / vp->getActualHeight());

    makeQuadObj(sceneMgr, "Q0", "Examples/Material4");
    makeQuadObj(sceneMgr, "Q1", "Examples/Material5");

    auto n0 = addQuad(sceneMgr, "Q0");
    n0->setPosition(0, 0, 0);

    auto n1 = addQuad(sceneMgr, n0, "Q1");
    n1->setPosition(-20, -15, 0);

    auto n2 = addQuad(sceneMgr, n1, "Q0");
    n2->setPosition(40, 0, 0);
    n2->roll(Ogre::Degree(45.0f));

    root->startRendering();

    return 0;
}



