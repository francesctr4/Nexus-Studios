#pragma once

#include "Module.h"
#include "Point.h"
#include <vector>
#include <list>
#include "SDL/include/SDL_rect.h"

enum class EVENT_TYPE
{

	KILL_EVENT = 0,
	GATHER_EVENT,
	INTERACT_EVENT
};

class Event
{

public:
	Event(EVENT_TYPE type_) :type(type_) {};
	~Event();

	EVENT_TYPE type;
	int orderNumber;
	SDL_Rect Object;
	bool completed = false;
};

class Quest
{
public:

	Quest() {};
	~Quest();

	int id;
	int trigger;	//whether or not a quest is active
	int reward;
	int requisites;
	int type;		//category of the quest

	std::string title;
	std::string description;

	bool completed = false;
};

class QuestManager : public Module
{
public:

	QuestManager(bool startEnabled);
	~QuestManager();

	bool Awake(pugi::xml_node& file);
	bool Start();

	pugi::xml_node LoadQuests(pugi::xml_document& quest_file) const;

	pugi::xml_document quest_data;

	std::list<Quest*> quests_list;
	std::list<Quest*> loaded_quests;
	std::list<Quest*> active_quests;
	std::list<Quest*> finished_quests;
};