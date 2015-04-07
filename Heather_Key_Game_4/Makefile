AutomatedMakefile = am
CC = g++ -g -O0


GAME_PATH=/$(GAME_DRIVE_LETTER)/Heather_Key_Game_4

INC_DIRS=-I./ -I$(GAME_DRIVE_LETTER)/Ogre/include/ -I$(GAME_DRIVE_LETTER)/boost/include/ -I$(GAME_DRIVE_LETTER)/Ogre/ogredeps/include/ -I$(GAME_DRIVE_LETTER)/Ogre/ogredeps/include/OIS -I$(GAME_PATH)/bass_2.4 -I$(GAME_PATH)/MyGUI_3.2.2/MyGUIEngine/include -I$(GAME_PATH)/MyGUI_3.2.2/Platforms/Ogre/OgrePlatform/include -I$(GAME_PATH)/lua_5.3.0 -I$(GAME_PATH)
LIB_DIRS=-L./ -L$(GAME_DRIVE_LETTER)/Ogre/lib/ -L$(GAME_DRIVE_LETTER)/boost/lib/ -L$(GAME_DRIVE_LETTER)/Ogre/ogredeps/lib/ -L$(GAME_PATH)/bass_2.4 -L$(GAME_PATH)/MyGUI_3.2.2 -L$(GAME_PATH)/lua_5.3.0/lib
LIBS=-lboost_system-mgw48-mt-1_57 -ltinyxml -lOIS -lbass -llua -lMyGUI.OgrePlatform -lMyGUIEngine -lOgreMain -lfreetype

COMPILE = $(CC) $(INC_DIRS) -c 
LINK = $(CC) $(LIB_DIRS) -o

GAME_FILES = Main.o GameManager.o RenderListener.o InputRenderListener.o AnimationRenderListener.o RenderManager.o LogManager.o GameResource.o PathResource.o MeshResource.o ResourceManager.o InputManager.o AudioResource.o AudioPlayer.o AudioManager.o GUIManager.o ScriptManager.o GUIWidgetScript.o
QUAT_FILES = Quaternion.o

all:	Ogre

Ogre:   		$(GAME_FILES)
			$(LINK) Game.exe $(GAME_FILES) $(LIBS)

Quaternion:		$(QUAT_FILES)
			$(LINK) Quaternion.exe $(QUAT_FILES)

Main.o:			Main.cpp
			$(COMPILE) Main.cpp

GameManager.o:		GameManager.h GameManager.cpp
			$(COMPILE) GameManager.cpp

RenderManager.o:	RenderManager.h RenderManager.cpp
			$(COMPILE) RenderManager.cpp

RenderListener.o:	RenderListener.h RenderListener.cpp
			$(COMPILE) RenderListener.cpp

AnimationRenderListener.o:	AnimationRenderListener.h AnimationRenderListener.cpp
				$(COMPILE) AnimationRenderListener.cpp

InputRenderListener.o:		InputRenderListener.h InputRenderListener.cpp
				$(COMPILE) InputRenderListener.cpp

LogManager.o:		LogManager.h LogManager.cpp
			$(COMPILE) LogManager.cpp

Quaternion.o:		Quaternion.h Quaternion.cpp
			$(COMPILE) Quaternion.cpp

GameResource.o:		GameResource.h GameResource.cpp
			$(COMPILE) GameResource.cpp

PathResource.o:		PathResource.h PathResource.cpp
			$(COMPILE) PathResource.cpp

MeshResource.o:		MeshResource.h MeshResource.cpp
			$(COMPILE) MeshResource.cpp

ResourceManager.o:	ResourceManager.h ResourceManager.cpp
			$(COMPILE) ResourceManager.cpp

InputManager.o:		InputManager.h InputManager.cpp InputListener.h
			$(COMPILE) InputManager.cpp

AudioResource.o:	AudioResource.h AudioResource.cpp
			$(COMPILE) AudioResource.cpp

AudioPlayer.o:		AudioPlayer.h AudioPlayer.cpp
			$(COMPILE) AudioPlayer.cpp

AudioManager.o:		AudioManager.h AudioManager.cpp
			$(COMPILE) AudioManager.cpp

GUIManager.o:		GUIManager.h GUIManager.cpp
			$(COMPILE) GUIManager.cpp

ScriptManager.o:	ScriptManager.h ScriptManager.cpp
			$(COMPILE) ScriptManager.cpp

GUIWidgetScript.o:	GUIWidgetScript.h GUIWidgetScript.cpp
			$(COMPILE) GUIWidgetScript.cpp



