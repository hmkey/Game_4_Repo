#include "AudioManager.h"
#include "AudioPlayer.h"
#include "AudioResource.h"
#include "GameManager.h"

#include <iostream>
using namespace std;

struct AudioResourceInfo
{
   HSAMPLE sample_data;
   HSAMPLE stream_data;
   HSAMPLE channel_data;

   //bool loaded;
};

AudioResourceInfo* AudioManager::createAudioResourceInfo()
{
   AudioResourceInfo* ar_info = (AudioResourceInfo*) malloc(sizeof(AudioResourceInfo));
   ar_info->sample_data = 0;
   ar_info->channel_data = 0;
   //ar_info->loaded = false;
   return ar_info;
}

void AudioManager::unloadSampleAudioResource(AudioResourceInfo* ar_info)
{
   //if (!ar_info->loaded) return;

   if(!BASS_ChannelIsActive(ar_info->channel_data) == BASS_ACTIVE_STOPPED)
   {
      BASS_ChannelStop(ar_info->channel_data);
   }

   BASS_SampleFree(ar_info->sample_data);
   ar_info->sample_data = 0;
   ar_info->channel_data = 0;
   //ar_info->loaded = false;
}

void AudioManager::unloadStreamAudioResource(AudioResourceInfo* ar_info)
{
   //if (!ar_info->loaded) return;

   if(!BASS_ChannelIsActive(ar_info->channel_data) == BASS_ACTIVE_STOPPED)
   {
      BASS_ChannelStop(ar_info->channel_data);
   }

   BASS_StreamFree(ar_info->stream_data);
   ar_info->stream_data = 0;
   ar_info->channel_data = 0;
   //ar_info->loaded = false;
}

void AudioManager::loadSampleAudioResource(std::string file_name, AudioResourceInfo* ar_info)
{
   ar_info->sample_data = BASS_SampleLoad(FALSE, file_name.c_str(),0,0,1,0);
   if (ar_info->sample_data)
   {
      ar_info->channel_data = BASS_SampleGetChannel(ar_info->sample_data, false);
      //ar_info->loaded = true;
   }
   else
   {
      game_manager->logComment("Sample Audio Resource Initialization Error: " + file_name);
      ASSERT(false);
   }
}

void AudioManager::loadStreamAudioResource(std::string file_name, AudioResourceInfo* ar_info)
{
   ar_info->stream_data = BASS_StreamCreateFile(FALSE, file_name.c_str(),0,0,0);
   if (ar_info->stream_data)
   {
      ar_info->channel_data = ar_info->stream_data;
      //ar_info->loaded = true;
   }
   else
   {
      game_manager->logComment("Stream Audio Resource Initialization Error: " + file_name);
      ASSERT(false);
   }
}

AudioManager::AudioManager(GameManager* gm)
{
   game_manager = gm;
   audio_players = new ListArray<AudioPlayer>();
   init();
}

AudioManager::~AudioManager()
{
   game_manager = NULL;

   free();

   ListArrayIterator<AudioPlayer>* iter = audio_players->iterator();
   while(iter->hasNext())
   {
      AudioPlayer* ap = iter->next();
      delete ap;
   }

   delete iter;
   delete audio_players;  //why does this line crash?
   audio_players = NULL;
}

void AudioManager::init(int Device, DWORD SampleRate, DWORD flags, HWND win)
{
   //default values passed to BASS
   //int Device = 1, DWORD SampleRate = 44100, DWORD flags = 0, HWND win = 0
   BOOL bassActive = BASS_Init(Device, SampleRate, flags, win, NULL);
   if (!bassActive)
   {
      game_manager->logComment("Audio Manager Initialization Problem");
      ASSERT(false);
   }

   std::stringstream DeviceStringStream;
   if (BASS_GetDeviceInfo(Device, &device_info))
   {
      DeviceStringStream << "Audio Device Info. Name: " << device_info.name << "Driver: " << device_info.driver;
      device_info_str = DeviceStringStream.str();
std::cout << device_info_str << std::endl;
   }

   else
   {
      BASS_Free();  //clean up after failed initialization
      game_manager->logComment("Audio Manager Initialization Problem");
      ASSERT(false);
   }
}

void AudioManager::free()
{
   BASS_Free();
}

void AudioManager::playAudio(AudioResource* ar, uint32 num_repeats)
{
   AudioPlayer* ap = new AudioPlayer(ar, num_repeats);
   addAudioPlayer(ap);
}

void AudioManager::stopAudio(uint32 id)
{
   int num_players = audio_players->size();
   int curr_ar_ID = 0;
   AudioResource* curr_ar = NULL;
   AudioPlayer* curr_ap = NULL;
   AudioResourceInfo* curr_ari = NULL;

   for (int i = 1; i <= num_players; i++)
   {
      curr_ap = audio_players->get(i);
      curr_ar = curr_ap->getAudioResource();
      curr_ari = curr_ar->getAudioResourceInfo();
      curr_ar_ID = curr_ar->getAudioResourceID();
      if (curr_ar_ID == id)
      {
         BASS_ChannelStop(curr_ari->channel_data);
         audio_players->remove(i);
      }
   }
}

void AudioManager::addAudioPlayer(AudioPlayer* audio_player)
{
   audio_players->add(audio_player);

   AudioResource* audio_resource = audio_player->getAudioResource();
   AudioResourceInfo* ar_info = audio_resource->getAudioResourceInfo();
   BASS_ChannelPlay(ar_info->channel_data, false);
}

void AudioManager::updateAudio()
{
   //audio plays on its own, this method repeats if necessary
   int num_players = audio_players->size();

   for (int i = 1; i <= num_players; i++)
   {
      AudioPlayer* audio_player = audio_players->get(i);
      AudioResource* audio_resource = audio_player->getAudioResource();
      AudioResourceInfo* ar_info = audio_resource->getAudioResourceInfo();

      //has the sound completed playing?  if so, repeat if required or remove it from the list
      if (BASS_ChannelIsActive(ar_info->channel_data) == BASS_ACTIVE_STOPPED)
      {
         if (audio_player->getRepeatCount() >= audio_player->getNumRepeats())  //tricky
         {
            audio_players->remove(i);
            audio_player->onMediaComplete();  //eventually, notify listeners that the audio has completed
            i--;
            num_players--;
         }

         else
         {
            audio_player->incRepeatCount();
            BASS_ChannelPlay(ar_info->channel_data, false);
         }
      }
   }

}
