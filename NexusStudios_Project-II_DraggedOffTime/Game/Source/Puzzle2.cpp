#include "Puzzle2.h"
#include "Textures.h"
#include "App.h"
#include "Render.h"
#include "Audio.h"

Puzzle2::Puzzle2()
{
}

Puzzle2::~Puzzle2()
{
}

void Puzzle2::Load()
{
	texture = app->tex->Load("Assets/Textures/Puzzles/Puzzle2_CajaMovible.png");
	TopSensor = app->physics->CreateRectangleSensor(Box_Position.x + 8, Box_Position.y, 16, 3, bodyType::KINEMATIC, ColliderType::SENSOR_TOP_BOX_PUZZLE2);
	BottomSensor = app->physics->CreateRectangleSensor(Box_Position.x + 8, Box_Position.y + 27, 16, 3, bodyType::KINEMATIC, ColliderType::SENSOR_TOP_BOX_PUZZLE2);

	Box_Collider= app->physics->CreateRectangle(Box_Position.x + 8, Box_Position.y + 13.5, 16, 27, bodyType::KINEMATIC);
}

void Puzzle2::Update()
{

	if (top_collision) {

		Box_Position.y = Box_Position.y + 2;

		float NewPosX_Top = Box_Position.x + 8;
		float NewPosY_Top = Box_Position.y + (float)13.5;
		TopSensor->body->SetTransform({ PIXEL_TO_METERS(NewPosX_Top),PIXEL_TO_METERS(Box_Position.y) }, 0);

		float NewPosX_Bot = Box_Position.x + 8;
		float NewPosY_Bot = Box_Position.y + 27 + (float)13.5;
		BottomSensor->body->SetTransform({ PIXEL_TO_METERS(NewPosX_Bot),PIXEL_TO_METERS(Box_Position.y) }, 0);


		Box_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX_Top),PIXEL_TO_METERS(NewPosY_Top) }, 0);

	}

	if (bottom_collision) {

		Box_Position.y = Box_Position.y - 2;

		float NewPosX_Top = Box_Position.x + 8;
		float NewPosY_Top = Box_Position.y - (float)13.5;
		TopSensor->body->SetTransform({ PIXEL_TO_METERS(NewPosX_Top),PIXEL_TO_METERS(Box_Position.y) }, 0);

		float NewPosX_Bot = Box_Position.x + 8;
		float NewPosY_Bot = Box_Position.y + 27 - (float)13.5;
		BottomSensor->body->SetTransform({ PIXEL_TO_METERS(NewPosX_Bot),PIXEL_TO_METERS(NewPosY_Bot) }, 0);

		Box_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX_Bot),PIXEL_TO_METERS(NewPosY_Top) }, 0);

	}

	app->render->DrawTexture(texture, Box_Position.x, Box_Position.y);

}