#include "OgreBulletDebugDrawer.h"
#include "OgreBulletUtils.h"

OgreBulletDebugDrawer::OgreBulletDebugDrawer(Ogre::SceneManager* scene_manager)
{
   this->scene_manager = scene_manager;
	
   manual_object =  scene_manager->createManualObject("PhysicsLines");
   manual_object->setDynamic(true);
   static const char* matName = "OgreBulletCollisionsDebugDefault";
   Ogre::MaterialPtr manual_object_material = Ogre::MaterialManager::getSingleton().getDefaultSettings()->clone(matName);
   manual_object_material->setReceiveShadows(false); 
   manual_object_material->getTechnique(0)->setLightingEnabled(false); 
   manual_object_node = scene_manager->getRootSceneNode()->createChildSceneNode();
   manual_object_node->attachObject(manual_object);
	
   count = (int*)malloc(sizeof(int));
   count[0] = 0;
}

OgreBulletDebugDrawer::~OgreBulletDebugDrawer()
{
   //delete scene_manager;
   //delete manual_object;
   free(count);
}

void OgreBulletDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
   Ogre::ColourValue c(0, 1, 0);  
   if (count[0] == 2000)
   {
      manual_object->clear();
      count[0] = 0;
   }
	
   manual_object->begin("OgreBulletCollisionsDebugDefault", Ogre::RenderOperation::OT_LINE_LIST);
   manual_object->position(cvt(from)); 
   manual_object->colour(c);
   manual_object->position(cvt(to));
   manual_object->colour(c);
   manual_object->end();
   count[0]++;
}

void OgreBulletDebugDrawer::drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color)
{

}

void OgreBulletDebugDrawer::reportErrorWarning(const char *warningString)
{
   std::cout << warningString << "\n";
}

void OgreBulletDebugDrawer::draw3dText(const btVector3 &location, const char *textString)
{

}

void OgreBulletDebugDrawer::setDebugMode(int debug_mode)
{
   this->debug_mode = debug_mode;
}

int OgreBulletDebugDrawer::getDebugMode() const
{
   return (DebugDrawModes) debug_mode;
}

void OgreBulletDebugDrawer::clearLines()
{
	manual_object->clear();
}