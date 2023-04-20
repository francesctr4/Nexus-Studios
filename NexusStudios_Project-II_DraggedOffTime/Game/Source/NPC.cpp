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
}

NPC::~NPC() 
{

}

bool NPC::Awake() {

	// Assign NPC Type

	if (SString(parameters.attribute("type").as_string()) == SString("rogue"))
		type = NPC_Types::ROGUE;
	if (SString(parameters.attribute("type").as_string()) == SString("wizard"))
		type = NPC_Types::WIZARD;
	if (SString(parameters.attribute("type").as_string()) == SString("orc"))
		type = NPC_Types::ORC;

	// Assign NPC Position and Texture

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

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

	if (type == NPC_Types::ROGUE) {

		npcIcon = app->tex->Load("Assets/Textures/RogueIcon.png");
		npcIcon_Transparent = app->tex->Load("Assets/Textures/RogueIcon_Transparent.png");

	}

	if (type == NPC_Types::WIZARD) {

		npcIcon = app->tex->Load("Assets/Textures/WizardIcon.png");
		npcIcon_Transparent = app->tex->Load("Assets/Textures/WizardIcon_Transparent.png");

	}
		
	if (type == NPC_Types::ORC) {

		npcIcon = app->tex->Load("Assets/Textures/SkippyIcon.png");
		npcIcon_Transparent = app->tex->Load("Assets/Textures/SkippyIcon_Transparent.png");

	}

	// NPC Physics

	pbody = app->physics->CreateRectangle(position.x, position.y, 32, 32, bodyType::STATIC);
	npcSensor = app->physics->CreateCircleSensor(position.x, position.y, 40, bodyType::STATIC, ColliderType::NPC_SENSOR);
	npcSensor->listener = this;

	// NPC Animation

	currentAnimation = &idle_right;

	// NPC Sensor Booleans and Texture

	playerInteraction = false;
	dialogueActivated = false;

	interactButton = app->tex->Load("Assets/Textures/Dialogue.png");

	// Dialogue UI

	dialogueUI_npc = app->tex->Load("Assets/Textures/DialogueUI.png");
	dialogueUI_player = app->tex->Load("Assets/Textures/DialogueUI_Player.png");

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

	firstDialogue[0].text = loremIpsum;
	firstDialogue[0].whoIsTalking = DialogueType::NPC;

	firstDialogue[1].text = playerSampleText;
	firstDialogue[1].whoIsTalking = DialogueType::PLAYER;

	firstDialogue[2].text = app->tex->Load("Assets/Textures/Dialogo2.png");
	firstDialogue[2].whoIsTalking = DialogueType::NPC;

	firstDialogue[3].text = playerSampleText;
	firstDialogue[3].whoIsTalking = DialogueType::PLAYER;

	firstDialogue[4].text = app->tex->Load("Assets/Textures/Dialogo3.png");
	firstDialogue[4].whoIsTalking = DialogueType::NPC;

	// ---------------------------------------------------------------------------------

	secondConversation.id = 2;
	secondConversation.size = 2;

	secondDialogue = new Dialogue[secondConversation.size];
	secondConversation.dialogues = secondDialogue;

	secondDialogue[0].text = loremIpsum;
	secondDialogue[0].whoIsTalking = DialogueType::NPC;

	secondDialogue[1].text = playerSampleText;
	secondDialogue[1].whoIsTalking = DialogueType::NPC;

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

		}
	}

	// Start Conversation
	 
	if (dialogueActivated) {

		if (type == NPC_Types::ROGUE) DialogueGenerator(firstConversation);
		if (type == NPC_Types::WIZARD) DialogueGenerator(secondConversation);
		if (type == NPC_Types::ORC) DialogueGenerator(firstConversation);

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
		LOG("Collision PLATFORM");

		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");

		break;

	case ColliderType::PLAYER:
		LOG("Collision PLAYER");

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

		if (dialogueIterator < conversation.size - 1) dialogueIterator++;
		else dialogueActivated = false;

	}

	// Dialogue Manager

	switch (conversation.dialogues[dialogueIterator].whoIsTalking) {

		case DialogueType::PLAYER: {

			// Change between dialogue options when pressing T

			if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {

				if (selectorIterator < 3) selectorIterator++;
				else selectorIterator = 0;

			}

			app->render->DrawTexture(dialogueUI_player, 202, 389);

			if (type == NPC_Types::ROGUE) app->render->DrawTexture(npcIcon_Transparent, 876, 409);
			if (type == NPC_Types::WIZARD) app->render->DrawTexture(npcIcon_Transparent, 869, 407);
			if (type == NPC_Types::ORC) app->render->DrawTexture(npcIcon_Transparent, 864, 397);

			app->render->DrawTexture(selector, selectorPositions[selectorIterator].x, selectorPositions[selectorIterator].y);
	
			app->render->DrawTexture(conversation.dialogues[dialogueIterator].text, 261, 557);

			break;
		}

		case DialogueType::NPC: {

			selectorIterator = 0; // Reset player's dialogue options

			app->render->DrawTexture(dialogueUI_npc, 202, 389);

			if (type == NPC_Types::ROGUE) app->render->DrawTexture(npcIcon, 876, 409);
			if (type == NPC_Types::WIZARD) app->render->DrawTexture(npcIcon, 869, 407);
			if (type == NPC_Types::ORC) app->render->DrawTexture(npcIcon, 864, 397);

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
