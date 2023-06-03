#include "NPC.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "SceneGameplay.h"
#include "Player.h"

NPC::NPC() : Entity(EntityType::NPC)
{
	name.Create("npc");

	dialogueIterator = NULL;

	firstConversation.id = NULL;
	firstConversation.size = NULL;
	firstConversation.dialogues = nullptr;
	firstDialogue = nullptr;

	secondConversation.id = NULL;
	secondConversation.size = NULL;
	secondConversation.dialogues = nullptr;
	secondDialogue = nullptr;

	thirdConversation.id = NULL;
	thirdConversation.size = NULL;
	thirdConversation.dialogues = nullptr;
	thirdDialogue = nullptr;

	playerSampleText = nullptr;
	loremIpsum = nullptr;

	dialogueUI_npc_medieval = nullptr;
	dialogueUI_npc_prehistoric = nullptr;
	dialogueUI_npc_cyberpunk = nullptr;
	dialogueUI_npc_apocalypse = nullptr;

	dialogueUI_player_medieval = nullptr;
	dialogueUI_player_prehistoric = nullptr;
	dialogueUI_player_cyberpunk = nullptr;
	dialogueUI_player_apocalypse = nullptr;

	name_npc = nullptr;
	name_player = nullptr;
	name_npc_transparent = nullptr;
	name_player_transparent = nullptr;

	selectorIterator = NULL;

	selector = nullptr;

	npcIcon = nullptr;
	npcIcon_Transparent = nullptr;

	playerInteraction = false;
	dialogueActivated = false;

	interactButton = nullptr;

	texture = nullptr;
	texturePath = nullptr;

	ntype = NPC_Types::UNKNOWN;

	pbody = nullptr;
	npcSensor = nullptr;

	currentAnimation = nullptr;

	openDialogue = NULL;
	closeDialogue = NULL;
	dialogueOptions = NULL;
	npcTalking = NULL;
	npcMap = NULL;

}

NPC::~NPC() 
{

}

bool NPC::Awake() {

	// Assign NPC Type

	if (SString(parameters.attribute("type").as_string()) == SString("rogue"))
		ntype = NPC_Types::ROGUE;
	if (SString(parameters.attribute("type").as_string()) == SString("wizard"))
		ntype = NPC_Types::WIZARD;
	if (SString(parameters.attribute("type").as_string()) == SString("orc"))
		ntype = NPC_Types::ORC;

	// Assign NPC Position and Texture

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	npcMap = parameters.attribute("map").as_int();
	aparicion = npcMap;

	// Assign NPC Animation

	for (int i = 0; i < 4; i++) {

		idle_right.PushBack({ 32 * (0 + i), 32 * 0, 32, 32 });

	}
	idle_right.loop = true;
	idle_right.speed = 0.06f;

	return true;
}

bool NPC::Start() {

	// NPC Texture

	texture = app->tex->Load(texturePath);

	name_player = app->tex->Load("Assets/Textures/Names/Kleos_Name.png");
	name_player_transparent = app->tex->Load("Assets/Textures/Names/Kleos_Name_Transparent.png");

	if (ntype == NPC_Types::ROGUE) {

		npcIcon = app->tex->Load("Assets/Textures/RogueIcon.png");
		npcIcon_Transparent = app->tex->Load("Assets/Textures/RogueIcon_Transparent.png");

		name_npc = app->tex->Load("Assets/Textures/Names/Rogue_Name.png");
		name_npc_transparent = app->tex->Load("Assets/Textures/Names/Rogue_Name_Transparent.png");

	}

	if (ntype == NPC_Types::WIZARD) {

		npcIcon = app->tex->Load("Assets/Textures/WizardIcon.png");
		npcIcon_Transparent = app->tex->Load("Assets/Textures/WizardIcon_Transparent.png");

		name_npc = app->tex->Load("Assets/Textures/Names/Wiwi_Name.png");
		name_npc_transparent = app->tex->Load("Assets/Textures/Names/Wiwi_Name_Transparent.png");

	}
		
	if (ntype == NPC_Types::ORC) {

		npcIcon = app->tex->Load("Assets/Textures/SkippyIcon.png");
		npcIcon_Transparent = app->tex->Load("Assets/Textures/SkippyIcon_Transparent.png");

		name_npc = app->tex->Load("Assets/Textures/Names/Skippy_Name.png");
		name_npc_transparent = app->tex->Load("Assets/Textures/Names/Skippy_Name_Transparent.png");

	}

	// NPC Physics

	pbody = app->physics->CreateRectangle(position.x, position.y, 32, 32, bodyType::STATIC);
	npcSensor = app->physics->CreateCircleSensor(position.x, position.y, 40, bodyType::STATIC, ColliderType::NPC_SENSOR);
	npcSensor->listener = this;

	// NPC Animation

	currentAnimation = &idle_right;

	// NPC Sensor Booleans and Texture

	interactButton = app->tex->Load("Assets/Textures/Dialogue.png");

	// Dialogue UI

	dialogueUI_npc_medieval = app->tex->Load("Assets/Textures/DialogueUI_Medieval.png");
	dialogueUI_npc_prehistoric = app->tex->Load("Assets/Textures/DialogueUI_Prehistoric.png");
	dialogueUI_npc_cyberpunk = app->tex->Load("Assets/Textures/DialogueUI_Cyberpunk.png");
	dialogueUI_npc_apocalypse = app->tex->Load("Assets/Textures/DialogueUI_Apocalypse.png");

	dialogueUI_player_medieval = app->tex->Load("Assets/Textures/DialogueUI_Player_Medieval.png");
	dialogueUI_player_prehistoric = app->tex->Load("Assets/Textures/DialogueUI_Player_Prehistoric.png");
	dialogueUI_player_cyberpunk = app->tex->Load("Assets/Textures/DialogueUI_Player_Cyberpunk.png");
	dialogueUI_player_apocalypse = app->tex->Load("Assets/Textures/DialogueUI_Player_Apocalypse.png");

	// Player Dialogue Selector

	selector = app->tex->Load("Assets/Textures/DialogueSelector.png");
	selectorIterator = 0;

	// NPC Conversations

	dialogueIterator = 0;

	loremIpsum = app->tex->Load("Assets/Textures/TextoNPC.png");
	playerSampleText = app->tex->Load("Assets/Textures/Texto.png");

	firstConversation.id = 1;
	firstConversation.size = 5;

	firstDialogue = new Dialogue[firstConversation.size];
	firstConversation.dialogues = firstDialogue;

	firstDialogue[0].text = app->tex->Load("Assets/Dialogue/Conversacion1_Texto1_Skippy.png");
	firstDialogue[0].whoIsTalking = DialogueType::NPC;

	firstDialogue[1].text = app->tex->Load("Assets/Dialogue/Conversacion1_Texto2_Player.png");
	firstDialogue[1].whoIsTalking = DialogueType::PLAYER_SELECTOR;

	firstDialogue[2].text = app->tex->Load("Assets/Dialogue/Conversacion1_Texto3_Skippy.png");
	firstDialogue[2].whoIsTalking = DialogueType::NPC;

	firstDialogue[3].text = app->tex->Load("Assets/Dialogue/Conversacion1_Texto4_Player.png");
	firstDialogue[3].whoIsTalking = DialogueType::PLAYER_SELECTOR;

	firstDialogue[4].text = app->tex->Load("Assets/Dialogue/Conversacion1_Texto5_Skippy.png");
	firstDialogue[4].whoIsTalking = DialogueType::NPC;

	// ---------------------------------------------------------------------------------

	secondConversation.id = 2;
	secondConversation.size = 3;

	secondDialogue = new Dialogue[secondConversation.size];
	secondConversation.dialogues = secondDialogue;

	secondDialogue[0].text = app->tex->Load("Assets/Dialogue/Conversacion2_Texto1_Rogue.png");
	secondDialogue[0].whoIsTalking = DialogueType::NPC;

	secondDialogue[1].text = app->tex->Load("Assets/Dialogue/Conversacion2_Texto2_Player.png");
	secondDialogue[1].whoIsTalking = DialogueType::PLAYER_SELECTOR;

	secondDialogue[2].text = app->tex->Load("Assets/Dialogue/Conversacion2_Texto3_Rogue.png");
	secondDialogue[2].whoIsTalking = DialogueType::NPC;

	// ---------------------------------------------------------------------------------

	thirdConversation.id = 3;
	thirdConversation.size = 1;

	thirdDialogue = new Dialogue[thirdConversation.size];
	thirdConversation.dialogues = thirdDialogue;

	thirdDialogue[0].text = app->tex->Load("Assets/Dialogue/Conversacion3_Texto1_Wizard.png");
	thirdDialogue[0].whoIsTalking = DialogueType::PLAYER;

	openDialogue = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/OpenDialogue.wav");
	closeDialogue = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/CloseDialogue.wav");
	dialogueOptions = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/DialogueOptions.wav");
	npcTalking = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/NpcTalking.wav");

	return true;
}

bool NPC::Update()
{
	// NPC Position Handling
	 
	b2Transform transform = pbody->body->GetTransform();
	b2Vec2 pos = transform.p;

	position.x = METERS_TO_PIXELS(pos.x) - 16;
	position.y = METERS_TO_PIXELS(pos.y) - 18;

	// NPC Animation Handling

	currentAnimation->Update();

	SDL_Rect npcRect = currentAnimation->GetCurrentFrame();

	app->render->DrawTexture(texture, position.x, position.y, &npcRect);


	// NPC Sensor Logic

	if (playerInteraction) {

		app->render->DrawTexture(interactButton, position.x + 8, position.y - 25);

		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_X] == KEY_DOWN) {
			
			dialogueActivated = true;

			app->audio->PlayFx(openDialogue);

			app->audio->PlayFx(npcTalking);

		}
	}

	// Start Conversation
	 
	if (dialogueActivated) {

		if (ntype == NPC_Types::ROGUE) DialogueGenerator(secondConversation);
		if (ntype == NPC_Types::WIZARD) DialogueGenerator(thirdConversation);
		if (ntype == NPC_Types::ORC)
		{
			app->sceneGameplay->trigger_1 = true;
			DialogueGenerator(firstConversation);
		}
	}
	else {

		dialogueIterator = 0;
		

	}

	return true;
}

bool NPC::CleanUp()
{
	delete[] secondDialogue;
	delete[] firstDialogue;

	return true;
}

void NPC::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLATFORM:
		

		break;
	case ColliderType::UNKNOWN:
		

		break;

	case ColliderType::PLAYER:
		
		playerInteraction = true;

		break;

	}

}

void NPC::OnCollisionEnd(PhysBody* physA, PhysBody* physB) {

	playerInteraction = false;
	dialogueActivated = false;

}

void NPC::DialogueGenerator(Conversation conversation) {

	// Skip to next dialogue when pressing Space

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

		if (dialogueIterator < conversation.size - 1) {

			dialogueIterator++;
			app->audio->PlayFx(openDialogue);

			if (conversation.dialogues[dialogueIterator].whoIsTalking == DialogueType::NPC) app->audio->PlayFx(npcTalking);

		}
		else {

			dialogueActivated = false;
			app->audio->PlayFx(closeDialogue);

		}
			
	}

	// Dialogue Manager

	switch (conversation.dialogues[dialogueIterator].whoIsTalking) {

		case DialogueType::PLAYER: {

			switch (app->sceneGameplay->player->playerChange) {
			case 0:
				app->render->DrawTexture(dialogueUI_player_medieval, 202, 389);
				break;
			case 1:
				app->render->DrawTexture(dialogueUI_player_prehistoric, 202, 389);
				break;
			case 2:
				app->render->DrawTexture(dialogueUI_player_cyberpunk, 202, 389);
				break;
			case 3:
				app->render->DrawTexture(dialogueUI_player_apocalypse, 202, 389);
				break;
			}

			if (ntype == NPC_Types::ROGUE) {

				app->render->DrawTexture(npcIcon_Transparent, 876, 409);
				app->render->DrawTexture(name_npc_transparent, 714 , 485);

			}
			if (ntype == NPC_Types::WIZARD) {

				app->render->DrawTexture(npcIcon_Transparent, 869, 407);
				app->render->DrawTexture(name_npc_transparent, 748, 485);

			}
			if (ntype == NPC_Types::ORC) {

				app->render->DrawTexture(npcIcon_Transparent, 864, 397);
				app->render->DrawTexture(name_npc_transparent, 705, 485);

			}
				
			app->render->DrawTexture(name_player, 437, 485);

			app->render->DrawTexture(conversation.dialogues[dialogueIterator].text, 261, 557);

			break;
		}

		case DialogueType::PLAYER_SELECTOR: {

			// Change between dialogue options when pressing T

			if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {

				if (selectorIterator < 3) selectorIterator++;
				else selectorIterator = 0;

				app->audio->PlayFx(dialogueOptions);

			}

			switch (app->sceneGameplay->player->playerChange) {
			case 0:
				app->render->DrawTexture(dialogueUI_player_medieval, 202, 389);
				break;
			case 1:
				app->render->DrawTexture(dialogueUI_player_prehistoric, 202, 389);
				break;
			case 2:
				app->render->DrawTexture(dialogueUI_player_cyberpunk, 202, 389);
				break;
			case 3:
				app->render->DrawTexture(dialogueUI_player_apocalypse, 202, 389);
				break;
			}

			if (ntype == NPC_Types::ROGUE) {

				app->render->DrawTexture(npcIcon_Transparent, 876, 409);
				app->render->DrawTexture(name_npc_transparent, 714, 485);

			}
			if (ntype == NPC_Types::WIZARD) {

				app->render->DrawTexture(npcIcon_Transparent, 869, 407);
				app->render->DrawTexture(name_npc_transparent, 748, 485);

			}
			if (ntype == NPC_Types::ORC) {

				app->render->DrawTexture(npcIcon_Transparent, 864, 397);
				app->render->DrawTexture(name_npc_transparent, 705, 485);

			}

			app->render->DrawTexture(selector, selectorPositions[selectorIterator].x, selectorPositions[selectorIterator].y);
			
			app->render->DrawTexture(name_player, 437, 485);

			app->render->DrawTexture(conversation.dialogues[dialogueIterator].text, 261, 557);

			break;
		}

		case DialogueType::NPC: {

			selectorIterator = 0; // Reset player's dialogue options

			switch (app->sceneGameplay->player->playerChange) {
			case 0:
				app->render->DrawTexture(dialogueUI_npc_medieval, 202, 389);
				break;
			case 1:
				app->render->DrawTexture(dialogueUI_npc_prehistoric, 202, 389);
				break;
			case 2:
				app->render->DrawTexture(dialogueUI_npc_cyberpunk, 202, 389);
				break;
			case 3:
				app->render->DrawTexture(dialogueUI_npc_apocalypse, 202, 389);
				break;
			}

			if (ntype == NPC_Types::ROGUE) {

				app->render->DrawTexture(npcIcon, 876, 409);
				app->render->DrawTexture(name_npc, 714, 485);

			}
			if (ntype == NPC_Types::WIZARD) {

				app->render->DrawTexture(npcIcon, 869, 407);
				app->render->DrawTexture(name_npc, 748, 485);

			}
			if (ntype == NPC_Types::ORC) {

				app->render->DrawTexture(npcIcon, 864, 397);
				app->render->DrawTexture(name_npc, 705, 485);

			}

			app->render->DrawTexture(name_player_transparent, 437, 485);

			app->render->DrawTexture(conversation.dialogues[dialogueIterator].text, 266, 553);

			break;
		}

	}

}

void NPC::Death()
{
	Disable();
	pbody->body->DestroyFixture(pbody->body->GetFixtureList());
	npcSensor->body->DestroyFixture(npcSensor->body->GetFixtureList());
}