#include "QuestManager.h"
#include "Module.h"
#include "Point.h"
#include "Log.h"
#include <vector>
#include "App.h"

QuestManager::QuestManager(bool startEnabled) : Module(startEnabled) {}

QuestManager::~QuestManager()
{
	for (std::list <Quest*>::iterator it = quests_list.begin(); it != quests_list.end(); it++)
	{
		quests_list.erase(it);
	}
	for (std::list <Quest*>::iterator it = loaded_quests.begin(); it != loaded_quests.end(); it++)
	{
		loaded_quests.erase(it);
	}
	for (std::list <Quest*>::iterator it = active_quests.begin(); it != active_quests.end(); it++)
	{
		active_quests.erase(it);
	}
	for (std::list <Quest*>::iterator it = finished_quests.begin(); it != finished_quests.end(); it++)
	{
		finished_quests.erase(it);
	}
}

bool QuestManager::Awake(pugi::xml_node& config)
{
	LOG("STARTING QUEST_MANAGER");

	pugi::xml_node quest_node;
	quest_node = LoadQuests(quest_data);  //Loads the xml file that you pass in the "xmlfile" and returns a node

	if (quest_node == NULL)
	{
		LOG("Could not load quests_file.xml");
	}

	//Iterator creating the quests
	for (quest_node = quest_node.child("quest"); quest_node; quest_node = quest_node.next_sibling("quest"))
	{

		Quest* new_quest = new Quest();

		new_quest->id = quest_node.attribute("id").as_int();
		new_quest->title = quest_node.attribute("title").as_string();
		new_quest->type = quest_node.attribute("type").as_int();
		new_quest->trigger = quest_node.attribute("trigger").as_int();
		new_quest->description = quest_node.attribute("description").as_string();
		new_quest->reward = quest_node.attribute("reward").as_int();
		new_quest->requisites = quest_node.attribute("requisites").as_int();


		if (new_quest->trigger == 1)
		{
			active_quests.push_back(new_quest);
		}
		else
		{
			loaded_quests.push_back(new_quest);
		}
		quests_list.push_back(new_quest);
	}

	return true;
}

bool QuestManager::Start()
{


	return true;

}

pugi::xml_node QuestManager::LoadQuests(pugi::xml_document& file) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = file.load_file("quest_data.xml");

	if (result == NULL)
		LOG("Could not load  xml file <loadxmlfunction> pugi error: %s", result.description());
	else
		ret = file.child("quests");
	LOG("XML LOADED");

	return ret;
}