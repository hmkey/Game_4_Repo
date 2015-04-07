#if !defined AUDIO_RESOURCE
#define AUDIO_RESOURCE

#include "GameResource.h"
#include <iostream>

class GameManager;
struct AudioResourceInfo;

enum AudioType{STREAM, SAMPLE};

class AudioResource : public GameResource
{
   private:
      AudioResourceInfo* ar_info;
      AudioType audio_type;
      GameManager* game_manager;
      uint32 ar_id;

   public:
      AudioResource(uint32 id, std::string scope, std::string file_name, GameResourceType type, AudioType audio_type, GameManager* gm);
      virtual ~AudioResource();

      virtual void load();
      virtual void unload();

      AudioResourceInfo* getAudioResourceInfo();
      uint32 getAudioResourceID();
};

#endif