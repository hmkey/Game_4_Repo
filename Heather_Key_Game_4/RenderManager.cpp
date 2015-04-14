#include "RenderManager.h"
#include "GUIManager.h"
#include "ScriptManager.h"
#include "PhysicsManager.h"

#include "GameManager.h"
#include "AnimationRenderListener.h"
#include "InputRenderListener.h"
#include "PhysicsRenderListener.h"

#include <iostream>
using namespace std;

using namespace Ogre;


void RenderManager::executeScript(std::string file_name, std::string script_name, std::string object_name)
{
/*
   try
   {
      selected_node = scene_manager->getSceneNode(object_name);
   }
   catch (Ogre::Exception& e)
   {
      game_manager->logComment(e.what());
      ASSERT(false);
   } 

   double input[3];
   input[0] = 0;
   input[1] = 0;
   input[2] = 0;

   double output[3];

   script_manager->executeScript(file_name, script_name, 3, 3, input, output);

   selected_node->pitch(Degree(output[0]));
   selected_node->yaw(Degree(output[1]));
   selected_node->roll(Degree(output[2]));*/

}
// ** MY FUNTIONS START HERE ** //

void RenderManager::setCurrBgMusicID(uint32 id)
{
   currBgMusicID = id;
}

uint32 RenderManager::getCurrBgMusicID()
{
   return currBgMusicID;
}

void RenderManager::processGUIButton(std::string btn_name)
{
   //bool oceanOn = false;
   /*if (btn_name == "MerryAnimation")
   {
      //enableBoatAnimation("MerryAnimation");
   }
   else if (btn_name == "WindAnimation")
   {
     // enableWindAnimation("WindAnimation");
   }
   else if (btn_name == "Ocean")
   {
         game_manager->playAudio(9, 1);
   }*/
   if (btn_name == "MerryAnimation")
   {
      //if (!boatSelected)
      //{
        //setSelectedNode(btn_name);
        AnimationState* as = scene_manager->getAnimationState(btn_name);
       // AnimationState* cam_as = scene_manager->getAnimationState("CameraAnimation");
        as->setEnabled(true);
        as->setTimePosition(0);

        /*cam_as->setEnabled(true);
        cam_as->setTimePosition(0);*/

       // boatSelected = true; 
      //}
      /*else
      {
        selected_node = NULL;
        boatSelected = false; 
      }*/
   }
   else
   {
      std::cout<<"Button not pressed" << endl;
   }
}



void RenderManager::processComboBox(std::string item_name)
{
   if (item_name == "Bink's Sake - Default")
   {
       if(currBgMusicID != 1)
       {
         game_manager->stopAudio(currBgMusicID);
         currBgMusicID = 1;
         game_manager->playAudio(1, 5);
       }
       else
       {
         cout << "Bink's Sake is alredy playing." << endl;
       }
   }
   else if (item_name == "Opening 5: Kokoro No Chizu")
   {
      if(currBgMusicID != 2)
       {
         game_manager->stopAudio(currBgMusicID);
         currBgMusicID = 2;
         game_manager->playAudio(2, 5);
       }
       else
       {
         cout << "Kokoro No Chizu is alredy playing." << endl;
       }
   }
   else if (item_name == "Opening 10: We Are!")
   {
      if(currBgMusicID != 3)
       {
         cout <<"Curr ID Before clicking we are: " << currBgMusicID << endl;
         game_manager->stopAudio(currBgMusicID);
         currBgMusicID = 3;
         cout <<"Curr ID After clicking we are: " << currBgMusicID << endl;
         game_manager->playAudio(3, 5);
       }
       else
       {
         cout << "We Are! is alredy playing." << endl;
       }
   }
   else if (item_name == "Opening 11: Share the World")
   {
      if(currBgMusicID != 4)
       {
         game_manager->stopAudio(currBgMusicID);
         currBgMusicID = 4;
         game_manager->playAudio(4, 5);
       }
       else
       {
         cout << "Share the World is alredy playing." << endl;
       }
   }
   else if (item_name == "Opening 13: One Day")
   {
      if(currBgMusicID != 5)
       {
         game_manager->stopAudio(currBgMusicID);
         currBgMusicID = 5;
         game_manager->playAudio(5, 5);
       }
       else
       {
         cout << "One Day is alredy playing." << endl;
       }
   }
   else if (item_name == "Opening 14: Fight Together")
   {
      if(currBgMusicID != 6)
       {
         game_manager->stopAudio(currBgMusicID);
         currBgMusicID = 6;
         game_manager->playAudio(6, 5);
       }
       else
       {
         cout << "Fight Together is alredy playing." << endl;
       }
   }
   else if (item_name == "Opening 16: Hands Up!")
   {
      if(currBgMusicID != 7)
       {
         game_manager->stopAudio(currBgMusicID);
         currBgMusicID = 7;
         game_manager->playAudio(7, 5);
       }
       else
       {
         cout << "Hands Up! is alredy playing." << endl;
       }
   }

}


// ** MY FUNCTIONS END HERE ** //

void RenderManager::destroySceneNodeMotion(SceneNodeMotion* snm)
{
   free(snm);
}

void RenderManager::stepPhysicsSimulation(float elapsed_time)
{
   physics_manager->stepPhysicsSimulation(elapsed_time);
}

void RenderManager::applyTorque(std::string name, float pitch, float yaw, float roll)
{
   physics_manager->applyTorque(name, pitch, yaw, roll);
}

void RenderManager::setOrientation(SceneNodeMotion* scene_node_motion, double w, double x, double y, double z)
{
   Ogre::SceneNode* scene_node = scene_node_motion->scene_node;
   scene_node->setOrientation(w, x, y, z);
}

void RenderManager::setPosition(SceneNodeMotion* scene_node_motion, double x, double y, double z)
{
   Ogre::SceneNode* scene_node = scene_node_motion->scene_node;
   scene_node->setPosition(x, y, z);
}

float* RenderManager::getOrientation(SceneNodeMotion* scene_node_motion)
{
   Ogre::SceneNode* scene_node = scene_node_motion->scene_node;

   Ogre::Quaternion q = scene_node->getOrientation();
   Ogre::Real w = q.w;
   Ogre::Real x = q.x;
   Ogre::Real y = q.y;
   Ogre::Real z = q.z;

   float* rot = new float[4];
   rot[3] = w;
   rot[0] = x;
   rot[1] = y;
   rot[2] = z;
   return rot;
}

float* RenderManager::getPosition(SceneNodeMotion* scene_node_motion)
{
   Ogre::SceneNode* scene_node = scene_node_motion->scene_node;

   Ogre::Vector3 pos = scene_node->getPosition();
   float* pos_ = new float[3];
   pos_[0] = pos.x;
   pos_[1] = pos.y;
   pos_[2] = pos.z;
   return pos_;
}

void RenderManager::executeRotateScript(string script_file_name, string script_function_name, string object_name, int degrees)
{
   try
   {
      selected_node = scene_manager->getSceneNode(object_name);
   }
   catch (Ogre::Exception& e)
   {
      game_manager->logComment(e.what());
      ASSERT(false);
   }

   const Quaternion& current_quat = selected_node->getOrientation();
   const int num_inputs = 5;
   const int num_outputs = 4;

   const char** inputs = new const char*[num_inputs];
   inputs[0] = GameManager::f_to_a(current_quat.w);
   inputs[1] = GameManager::f_to_a(current_quat.x);
   inputs[2] = GameManager::f_to_a(current_quat.y);
   inputs[3] = GameManager::f_to_a(current_quat.z);
   inputs[4] = GameManager::f_to_a(degrees);             //amount to rotate in degrees

   char** outputs = new char*[num_outputs];

   int output_len = 20;
   for (int i = 0; i < num_outputs; i++)
   {
      outputs[i] = new char[output_len + 1];
   }

   script_manager->executeScript(script_file_name, script_function_name, num_inputs, num_outputs, inputs, outputs);

   float w = GameManager::a_to_f(outputs[0]);
   float x = GameManager::a_to_f(outputs[1]);
   float y = GameManager::a_to_f(outputs[2]);
   float z = GameManager::a_to_f(outputs[3]);
   selected_node->setOrientation(w, x, y, z);

   for (int i = 0; i < num_inputs; i++)
   {
      delete[] inputs[i];
   }

   for (int i = 0; i < num_outputs; i++)  //why does this delete crash?
   {
      delete[] outputs[i];
   }

   delete[] inputs;
   delete[] outputs;
}

void RenderManager::logComment(std::string comment_message)
{
   game_manager->logComment(comment_message);
}

void RenderManager::setSelectedNode(std::string item)
{
   try
   {
      selected_node = scene_manager->getSceneNode(item);
   }
   catch (Ogre::Exception& e)
   {
      game_manager->logComment(e.what());
      ASSERT(false);
   }
}


void RenderManager::joystickAxisMoved(int* amount)
{
    //It should be noted that most axis inputs range between ~-32720 and ~32720
    //Control stick axis tend to equal +-~500 when they are idle (as in not beig touched)
    //Triggers start at one extreme and end at the other as they are pulled down.

    Camera* camera = scene_manager->getCamera("Camera");
    const Vector3& camera_pos = camera->getPosition();
    const Vector3& camera_dir = camera->getDirection();

    float sticks[6];
    for (int i = 0; i < 6; i++)
    {
       if (abs(amount[i]) < 5000) //dead zone
       {
          amount[i] = 0;
       }

       sticks[i] = amount[i]/10000.0f;
    }

                                 //left stick n/s            left stick e/w
    float x_pos = camera_pos.x + (camera_dir.x*-sticks[0]) + (camera_dir.z*-sticks[1]);
    float y_pos = camera_pos.y;  //doesn't change
    float z_pos = camera_pos.z + (camera_dir.z*-sticks[0]) - (camera_dir.x*-sticks[1]);

    float yaw = atan2(camera_dir.z, camera_dir.x);   //current yaw
    yaw = yaw + sticks[3]/60.0f;  //right stick e/w
   
    float x_dir = cos(yaw);
    float y_dir = camera_dir.y - sticks[2]/60.0f;  //right stick n/s
    float z_dir = sin(yaw);
   
    Vector3 dir_vector = Vector3(x_dir, y_dir, z_dir);  
    dir_vector.normalise();

    Vector3 pos_vector = Vector3(x_pos, y_pos, z_pos);
      
    camera->setDirection(dir_vector);
    camera->setPosition(pos_vector);
}

void RenderManager::updateAudio()
{
   game_manager->updateAudio();
}

void RenderManager::mousePressed(uint32 mouse_x, uint32 mouse_y, uint32 game_mouse)
{
   gui_manager->mousePressed(mouse_x, mouse_y, game_mouse);
}

void RenderManager::mouseReleased(uint32 mouse_x, uint32 mouse_y, uint32 game_mouse)
{
   gui_manager->mouseReleased(mouse_x, mouse_y, game_mouse);
}

void RenderManager::mouseMoved(uint32 mouse_x, uint32 mouse_y, int mouse_rel_x, int mouse_rel_y)
{
/*
   if (selected_node)
   {
      //get root's (one) child and change its rotation based on mouse movement
      //SceneNode* root = scene_manager->getRootSceneNode();
      //SceneNode* scene_parent_node = (SceneNode*) root->getChild(0);
      const Quaternion& current_quat = selected_node->getOrientation();

      Vector3 x_axis(1, 0, 0);
      Vector3 y_axis(0, 1, 0);
      Vector3 z_axis(0, 0, 1);
      int x_degree = mouse_rel_x;
      int y_degree = mouse_rel_y;

      Quaternion x_quat(Degree(y_degree), x_axis);
      Quaternion y_quat(Degree(x_degree), y_axis);
      Quaternion z_quat(Degree(x_degree), z_axis);

      Quaternion new_quat = x_quat*y_quat*current_quat;  //quaternions to the right are applied first
      //scene_parent_node->rotate(new_quat);  //here, new_quat is applied to the right
      selected_node->setOrientation(new_quat);
   }
*/
   gui_manager->mouseMoved(mouse_x, mouse_y);
}

void RenderManager::checkForInput(float time_step)
{
   game_manager->checkForInput(time_step);
}

void RenderManager::initialiseResourceGroup(std::string group_name)
{
   try
   {
      ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
      rgm.initialiseResourceGroup(group_name);  //pre-load the resources located in the specific paths (parse scripts)
      game_manager->logComment("Scripts parsed successfully.");
   }
   catch (Ogre::Exception& e)
   {
      game_manager->logComment(e.what());
      ASSERT(false);
   }
}

void RenderManager::loadResourceGroup(std::string group_name)
{
   try
   {
      ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
      rgm.loadResourceGroup(group_name, true, true);  //load the resources in the specific paths
      game_manager->logComment("Meshes loaded successfully.");

      gui_manager->loadResourceGroup(group_name);
   }
   catch (Ogre::Exception& e)
   {
      game_manager->logComment(e.what());
      ASSERT(false);
   }
}

void RenderManager::unloadResourceGroup(std::string group_name)
{
   try
   {
      //need to destroy the scene graph as well
      scene_manager->clearScene();  //pretty much destroys everything

      //root->removeAndDestroyAllChildren();
      gui_manager->unloadResourceGroup();

      ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
      //rgm.clearResourceGroup(group_name);
      rgm.destroyResourceGroup(group_name);   //completely remove resource information (could use clear instead of destroy)

      game_manager->logComment("Resources unloaded successfully.");
   }
   catch (Ogre::Exception& e)
   {
      game_manager->logComment(e.what());
      ASSERT(false);
   }
}

void RenderManager::addPathResource(std::string file_name, std::string path_type, std::string group_name)
{
   ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
   rgm.addResourceLocation(file_name, path_type, group_name);  //"file_name" is the path
}
      
void RenderManager::addMeshResource(std::string file_name, std::string mesh_str, std::string group_name)
{
   ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();
   rgm.declareResource(file_name, mesh_str, group_name);
}

void RenderManager::init()
{
   root = NULL;
   window = NULL;
   scene_manager = NULL;

   animation_render_listener = NULL;
   input_render_listener = NULL;
   physics_render_listener = NULL;

   selected_node = NULL;

   try
   {
      root = OGRE_NEW Ogre::Root("","");    //resource/config files go here (we aren't using them)
      root->loadPlugin("RenderSystem_GL");  //prepares external dlls for later use

      Ogre::RenderSystem* render_system = root->getRenderSystemByName("OpenGL Rendering Subsystem"); //just returns a pointer to an uninialized render system
      if (!render_system)
      {
         //log that OpenGL is not available (probably can't continue)
         return;
      }

      root->setRenderSystem(render_system);
      //manually set configuration options
      render_system->setConfigOption("Full Screen", "No");
      render_system->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

      //initialize render system
      //automatically create the window and give it a title
      window = root->initialise(true, "Game Engine Programming");  

      //can create BSP or octree scene managers
      scene_manager = root->createSceneManager(Ogre::ST_GENERIC, "Default Scene Manager");
      window->getCustomAttribute("WINDOW", &window_handle);

      //the Ogre viewport corresponds to a clipping region into which the contents of the camera view will be rendered in the window on each frame
      //by default, the size of the viewport matches the size of the window, but the viewport can be cropped
      //the camera represents a view into an existing scene and the viewport represents a region into which an existing camera will render its contents
      camera = scene_manager->createCamera("Camera");

      //z-order (for possible overlapping), left, top, width, height
      viewport = window->addViewport(camera, 0, 0, 0, 1.0, 1.0);  //assign a camera to a viewport (can have many cameras and viewports in a single window)
      viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

      float actual_width = Ogre::Real(viewport->getActualWidth());
      float actual_height = Ogre::Real(viewport->getActualHeight());
      float aspect_ratio = actual_width/actual_height;
      camera->setAspectRatio(aspect_ratio);

/*
      Ogre::Camera* camera2 = scene_manager->createCamera("Camera 2");
      camera2->setPosition(Ogre::Vector3(0, 9.99, 0.01));
      camera2->lookAt(Ogre::Vector3(0, 0, 0));
      camera2->setNearClipDistance(2);
      camera2->setFarClipDistance(50);
      Ogre::Viewport* viewport2 = window->addViewport(camera2, 1, 0.5, 0, 0.5, 1.0);  //assign a camera to a viewport (can have many cameras and viewports in a single window)
      viewport2->setBackgroundColour(Ogre::ColourValue(0.1,0.1,0.1));
      camera2->setAspectRatio(aspect_ratio);
*/
   }

   catch (Ogre::Exception& e)
   {
      game_manager->logComment(e.what());
      ASSERT(false);
   }
}

RenderManager::RenderManager(GameManager* gm)
{
   game_manager = gm;
   init();

   //register the listener
   //the listener is notified before and after each frame
   animation_states = new ListArray<Ogre::AnimationState>();

   animation_render_listener = new AnimationRenderListener(this);
   root->addFrameListener(animation_render_listener);

   input_render_listener = new InputRenderListener(this);
   root->addFrameListener(input_render_listener);

   gui_manager = new GUIManager(this);
   script_manager = new ScriptManager(this);
   physics_manager = new PhysicsManager(this, scene_manager);

   physics_render_listener = new PhysicsRenderListener(this);
   root->addFrameListener(physics_render_listener);

    currBgMusicID = -1; 

}

RenderManager::~RenderManager()
{
   delete physics_manager;
   physics_manager = NULL;

   delete script_manager;
   script_manager = NULL;
   delete gui_manager;
   gui_manager = NULL;

   delete animation_states;  //the ListArray containing the animations

   delete animation_render_listener;
   delete input_render_listener;
   delete physics_render_listener;

   game_manager = NULL;

   stopRendering();

   window->removeAllViewports();
   window->destroy();
   window = NULL;

   delete root;
   root = NULL;
}

size_t RenderManager::getRenderWindowHandle()
{
   return window_handle;
}

int RenderManager::getRenderWindowWidth()
{
   return viewport->getActualWidth();
}

int RenderManager::getRenderWindowHeight()
{
   return viewport->getActualHeight();
}

void RenderManager::stopRendering()
{
   input_render_listener->stopRendering();
}

void RenderManager::startRendering()
{
   root->startRendering();
}

void RenderManager::setTimeSinceLastFrame(Ogre::Real tslf)
{
   time_since_last_frame = tslf;
}

Ogre::RenderWindow* RenderManager::getRenderWindow()
{
   return window;
}

Ogre::SceneManager* RenderManager::getSceneManager()
{
   return scene_manager;
}

void RenderManager::processAnimations(float time_step)
{
   ListArrayIterator<Ogre::AnimationState>* anim_iter = animation_states->iterator();
   while(anim_iter->hasNext())
   {
      Ogre::AnimationState* animation_state = anim_iter->next();
      animation_state->addTime(time_step);
   }
   delete anim_iter;
}

void RenderManager::buildSceneFromXML(std::string file_name)
{
   TiXmlDocument doc(file_name.c_str());

   if (doc.LoadFile())
   {
      TiXmlNode* scene_node = doc.FirstChild("scene");

      if (scene_node)
      {
         std::string scope_text = GameManager::textFromChildNode(scene_node, "scope");
         game_manager->loadResources(scope_text);

         float values[4];

         TiXmlNode* camera_node = scene_node->FirstChild("camera");

         std::string camera_position_text = GameManager::textFromChildNode(camera_node, "position");
         GameManager::parseFloats(camera_position_text, values);
         Vector3 camera_position(values[0], values[1], values[2]);
         camera->setPosition(camera_position);

         std::string camera_look_at_text = GameManager::textFromChildNode(camera_node, "look_at");
         GameManager::parseFloats(camera_look_at_text, values);
         Vector3 camera_look(values[0], values[1], values[2]);
         camera->lookAt(camera_look);

         std::string camera_clip_distance_text = GameManager::textFromChildNode(camera_node, "clip_distance");
         GameManager::parseFloats(camera_clip_distance_text, values);
         camera->setNearClipDistance(values[0]);
         camera->setFarClipDistance(values[1]);

         scene_manager->setSkyBox(true, "Skybox", 500, false);

         TiXmlNode* light_node = scene_node->FirstChild("light");

         std::string light_name_text = GameManager::textFromChildNode(light_node, "name");
         Light* light = scene_manager->createLight(light_name_text);

         std::string light_type_text = GameManager::textFromChildNode(light_node, "type");
         if (light_type_text == "directional")
         {
            light->setType(Light::LT_DIRECTIONAL);
         }
         else
         {
            light->setType(Light::LT_POINT);
         }

         std::string light_position_text = GameManager::textFromChildNode(light_node, "position");
         GameManager::parseFloats(light_position_text, values);
         Vector3 light_pos(values[0], values[1], values[2]);
         if (light_type_text == "directional")
         {
            light->setDirection(light_pos);
         }
         else
         {
            light->setPosition(light_pos);
         }

         std::string light_color_text = GameManager::textFromChildNode(light_node, "color");
         GameManager::parseFloats(light_color_text, values);
         light->setDiffuseColour(values[0], values[1], values[2]);

         std::string gravity_text = GameManager::textFromChildNode(scene_node, "gravity");
         GameManager::parseFloats(gravity_text, values);
         physics_manager->setGravity(values);

         TiXmlNode* scene_graph_node = scene_node->FirstChild("scene_graph");
         TiXmlNode* scene_graph_root_node = scene_graph_node->FirstChild("root");
         TiXmlNode* scene_graph_children = scene_graph_root_node->FirstChild("children");
         
         //children will be attached to the root scene node
         addSceneNodeChildren(scene_graph_children, scene_manager->getRootSceneNode(), values);
      }
   }
   else
   {
      game_manager->logComment("Invalid XML file: " + file_name);
      ASSERT(false);
   }
}

void RenderManager::addSceneNodeChildren(TiXmlNode* xml_node, SceneNode* parent_node, float* values)
{

   for(TiXmlNode* child_xml_node = xml_node->FirstChild("child"); child_xml_node; child_xml_node = child_xml_node->NextSibling())
   {
      //check for a child animation node
      TiXmlNode* curr_child_animation_xml = child_xml_node->FirstChild("animation");
      if (curr_child_animation_xml)
      {
         std::string animation_name_text = GameManager::textFromChildNode(curr_child_animation_xml, "name");

         SceneNode* animation_node = scene_manager->createSceneNode(animation_name_text);
         parent_node->addChild(animation_node);

         addSceneNodeAnimation(curr_child_animation_xml, animation_node, animation_name_text, values);
         addSceneNodeChildren(child_xml_node->FirstChild("children"), animation_node, values);
      }

      else  //regular child node
      {
         // Create the child node
         std::string child_name_text = GameManager::textFromChildNode(child_xml_node, "name");

         SceneNode* curr_child_node = scene_manager->createSceneNode(child_name_text);
         parent_node->addChild(curr_child_node);
      
         //process the node entity
         TiXmlNode* scene_graph_child_entity = child_xml_node->FirstChild("entity");
         if (scene_graph_child_entity)
         {
            std::string child_entity_name = GameManager::textFromChildNode(scene_graph_child_entity, "name");
            std::string child_entity_mesh = GameManager::textFromChildNode(scene_graph_child_entity, "mesh");
            std::string child_entity_material = GameManager::textFromChildNode(scene_graph_child_entity, "material");
            Ogre::Entity* child_entity;
            try
            {
               child_entity = scene_manager->createEntity(child_entity_name, child_entity_mesh);
               child_entity->setMaterialName(child_entity_material);
               game_manager->logComment("Entity " + child_entity_name + " successfully placed in scene graph.");
            }
            catch (Ogre::Exception& e)
            {
               game_manager->logComment(e.what());
               ASSERT(false);
            }
         
            curr_child_node->attachObject(child_entity);
         }

         // translate
         std::string child_translation_text = GameManager::textFromChildNode(child_xml_node, "translation");
         GameManager::parseFloats(child_translation_text, values);
         Vector3 child_translation(values[0], values[1], values[2]);
         curr_child_node->translate(child_translation, Node::TS_LOCAL);

         // rotate
         std::string child_rotation_text = GameManager::textFromChildNode(child_xml_node, "rotation");
         GameManager::parseFloats(child_rotation_text, values);
         Vector3 vr(values[1], values[2], values[3]);
         Quaternion q(Degree(values[0]), vr);
         curr_child_node->rotate(q);

         // scale
         std::string child_scale_text = GameManager::textFromChildNode(child_xml_node, "scale");
         GameManager::parseFloats(child_scale_text, values);
         Vector3 child_scale(values[0], values[1], values[2]);
         curr_child_node->scale(child_scale);

         //process the node physics
         TiXmlNode* scene_graph_child_physics = child_xml_node->FirstChild("physics");

         if (scene_graph_child_physics)
         {
            std::string child_physics_collision_shape = GameManager::textFromChildNode(scene_graph_child_physics, "collision_shape");
            std::string child_physics_collision_parameters = GameManager::textFromChildNode(scene_graph_child_physics, "collision_parameters");

            GameManager::parseFloats(child_physics_collision_parameters, values);
            double* collision_shape_params = new double[3];
            collision_shape_params[0] = values[0];
            collision_shape_params[1] = values[1];
            collision_shape_params[2] = values[2];

            std::string child_physics_mass = GameManager::textFromChildNode(scene_graph_child_physics, "mass");
            float mass = GameManager::parseFloat(child_physics_mass);

            SceneNodeMotion* scene_node_motion = (SceneNodeMotion*) malloc(sizeof(SceneNodeMotion));
            scene_node_motion->scene_node = curr_child_node;
            physics_manager->createRigidBody(scene_node_motion, child_name_text, child_physics_collision_shape, collision_shape_params, mass);
         }

         addSceneNodeChildren(child_xml_node->FirstChild("children"), curr_child_node, values);
      }
   }
}

void RenderManager::addSceneNodeAnimation(TiXmlNode* animation_node_xml, SceneNode* animation_node, std::string animation_name_text, float* values)
{
   std::string animation_seconds_text = GameManager::textFromChildNode(animation_node_xml, "seconds");

   Ogre::Animation* animation = scene_manager->createAnimation(animation_name_text, GameManager::parseInt(animation_seconds_text));
   animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);

   //indicate that we want a scene node to be animated (affecting everything lower than it in the scene graph)
   Ogre::NodeAnimationTrack* animation_track = animation->createNodeTrack(1, animation_node);

   TiXmlNode* keyframes_xml = animation_node_xml->FirstChild("keyframes");
   for(TiXmlNode* keyframe_xml = keyframes_xml->FirstChild("keyframe"); keyframe_xml; keyframe_xml = keyframe_xml->NextSibling())
   {  
      std::string keyframe_xml_time = GameManager::textFromChildNode(keyframe_xml, "time");
      float time = GameManager::parseFloat(keyframe_xml_time);

      std::string keyframe_xml_translation = GameManager::textFromChildNode(keyframe_xml, "translation");
      GameManager::parseFloats(keyframe_xml_translation, values);
      Vector3 vt(values[0], values[1], values[2]);

      std::string keyframe_xml_rotation = GameManager::textFromChildNode(keyframe_xml, "rotation");
      GameManager::parseFloats(keyframe_xml_rotation, values);
      Vector3 vr(values[1], values[2], values[3]);
      Quaternion q(Degree(values[0]), vr);

      Ogre::TransformKeyFrame* animation_key = animation_track->createNodeKeyFrame(time); 
      animation_key->setTranslate(vt);
      animation_key->setRotation(q);
   }

   Ogre::AnimationState* animation_state = scene_manager->createAnimationState(animation_name_text);
   //animation_state->setEnabled(true);
  //animation_state->setLoop(true);
   animation_state->setEnabled(false);
   animation_state->setLoop(false);

   animation_states->add(animation_state);
}

