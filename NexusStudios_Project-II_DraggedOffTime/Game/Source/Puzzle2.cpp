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

	//Box 1
	TopSensor1 = app->physics->CreateRectangleSensor(Box1_Position.x + 16, Box1_Position.y, 32, 3, bodyType::KINEMATIC, ColliderType::SENSOR_TOP_BOX1_PUZZLE2);
	BottomSensor1 = app->physics->CreateRectangleSensor(Box1_Position.x + 16, Box1_Position.y + 32, 32, 3, bodyType::KINEMATIC, ColliderType::SENSOR_BOTTOM_BOX1_PUZZLE2);

	Box1_Collider= app->physics->CreateRectangle(Box1_Position.x + 16, Box1_Position.y + 16, 32, 32, bodyType::KINEMATIC);

	//Box 2
	TopSensor2 = app->physics->CreateRectangleSensor(Box2_Position.x + 16, Box2_Position.y, 32, 3, bodyType::KINEMATIC, ColliderType::SENSOR_TOP_BOX2_PUZZLE2);
	BottomSensor2 = app->physics->CreateRectangleSensor(Box2_Position.x + 16, Box2_Position.y + 32, 32, 3, bodyType::KINEMATIC, ColliderType::SENSOR_BOTTOM_BOX2_PUZZLE2);

	Box2_Collider = app->physics->CreateRectangle(Box2_Position.x + 16, Box2_Position.y + 16, 32, 32, bodyType::KINEMATIC);

	//Box 3
	TopSensor3 = app->physics->CreateRectangleSensor(Box3_Position.x + 16, Box3_Position.y, 32, 3, bodyType::KINEMATIC, ColliderType::SENSOR_TOP_BOX3_PUZZLE2);
	BottomSensor3 = app->physics->CreateRectangleSensor(Box3_Position.x + 16, Box3_Position.y + 32, 32, 3, bodyType::KINEMATIC, ColliderType::SENSOR_BOTTOM_BOX3_PUZZLE2);

	Box3_Collider = app->physics->CreateRectangle(Box3_Position.x + 16, Box3_Position.y + 16, 32, 32, bodyType::KINEMATIC);

	//Box 4
	TopSensor4 = app->physics->CreateRectangleSensor(Box4_Position.x + 16, Box4_Position.y, 32, 3, bodyType::KINEMATIC, ColliderType::SENSOR_TOP_BOX4_PUZZLE2);
	BottomSensor4 = app->physics->CreateRectangleSensor(Box4_Position.x + 16, Box4_Position.y + 32, 32, 3, bodyType::KINEMATIC, ColliderType::SENSOR_BOTTOM_BOX4_PUZZLE2);

	Box4_Collider = app->physics->CreateRectangle(Box4_Position.x + 16, Box4_Position.y + 16, 32, 32, bodyType::KINEMATIC);

	//Box 5
	TopSensor5 = app->physics->CreateRectangleSensor(Box5_Position.x + 16, Box5_Position.y, 32, 3, bodyType::KINEMATIC, ColliderType::SENSOR_TOP_BOX5_PUZZLE2);
	BottomSensor5 = app->physics->CreateRectangleSensor(Box5_Position.x + 16, Box5_Position.y + 32, 32, 3, bodyType::KINEMATIC, ColliderType::SENSOR_BOTTOM_BOX5_PUZZLE2);

	Box5_Collider = app->physics->CreateRectangle(Box5_Position.x + 16, Box5_Position.y + 16, 32, 32, bodyType::KINEMATIC);
}

void Puzzle2::Update()
{

	//Box 1

	NewPosX1 = Box1_Position.x + 16;

	if (top_collision1) {

		Box1_Position.y = Box1_Position.y + 2;

		float NewPosY_Top = Box1_Position.y;
		TopSensor1->body->SetTransform({ PIXEL_TO_METERS(NewPosX1),PIXEL_TO_METERS(NewPosY_Top) }, 0);

		float NewPosY_Bot = Box1_Position.y + 32;
		BottomSensor1->body->SetTransform({ PIXEL_TO_METERS(NewPosX1),PIXEL_TO_METERS(NewPosY_Bot) }, 0);

		float NewPosY_Box = Box1_Position.y + 16;
		Box1_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX1),PIXEL_TO_METERS(NewPosY_Box) }, 0);

	}
	if (bottom_collision1) {

		Box1_Position.y = Box1_Position.y - 2;

		float NewPosY_Top = Box1_Position.y - 16;
		TopSensor1->body->SetTransform({ PIXEL_TO_METERS(NewPosX1),PIXEL_TO_METERS(Box1_Position.y) }, 0);

		float NewPosY_Bot = Box1_Position.y + 32;
		BottomSensor1->body->SetTransform({ PIXEL_TO_METERS(NewPosX1),PIXEL_TO_METERS(NewPosY_Bot) }, 0);

		float NewPosY_Box = Box1_Position.y + 32 - 16;
		Box1_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX1),PIXEL_TO_METERS(NewPosY_Box) }, 0);

	}

	//Box 2

	NewPosX2 = Box2_Position.x + 16;

	if (top_collision2) {

		Box2_Position.y = Box2_Position.y + 2;

		float NewPosY_Top = Box2_Position.y;
		TopSensor2->body->SetTransform({ PIXEL_TO_METERS(NewPosX2),PIXEL_TO_METERS(NewPosY_Top) }, 0);

		float NewPosY_Bot = Box2_Position.y + 32;
		BottomSensor2->body->SetTransform({ PIXEL_TO_METERS(NewPosX2),PIXEL_TO_METERS(NewPosY_Bot) }, 0);

		float NewPosY_Box = Box2_Position.y + 16;
		Box2_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX2),PIXEL_TO_METERS(NewPosY_Box) }, 0);

	}
	if (bottom_collision2) {

		Box2_Position.y = Box2_Position.y - 2;

		float NewPosY_Top = Box2_Position.y - 16;
		TopSensor1->body->SetTransform({ PIXEL_TO_METERS(NewPosX2),PIXEL_TO_METERS(Box2_Position.y) }, 0);

		float NewPosY_Bot = Box2_Position.y + 32;
		BottomSensor1->body->SetTransform({ PIXEL_TO_METERS(NewPosX2),PIXEL_TO_METERS(NewPosY_Bot) }, 0);

		float NewPosY_Box = Box2_Position.y + 32 - 16;
		Box2_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX2),PIXEL_TO_METERS(NewPosY_Box) }, 0);

	}

	//Box 3

	NewPosX3 = Box3_Position.x + 16;

	if (top_collision3) {

		Box3_Position.y = Box3_Position.y + 2;

		float NewPosY_Top = Box3_Position.y;
		TopSensor3->body->SetTransform({ PIXEL_TO_METERS(NewPosX3),PIXEL_TO_METERS(NewPosY_Top) }, 0);

		float NewPosY_Bot = Box3_Position.y + 32;
		BottomSensor3->body->SetTransform({ PIXEL_TO_METERS(NewPosX3),PIXEL_TO_METERS(NewPosY_Bot) }, 0);

		float NewPosY_Box = Box3_Position.y + 16;
		Box2_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX3),PIXEL_TO_METERS(NewPosY_Box) }, 0);

	}
	if (bottom_collision3) {

		Box3_Position.y = Box3_Position.y - 2;

		float NewPosY_Top = Box3_Position.y - 16;
		TopSensor3->body->SetTransform({ PIXEL_TO_METERS(NewPosX3),PIXEL_TO_METERS(Box3_Position.y) }, 0);

		float NewPosY_Bot = Box3_Position.y + 32;
		BottomSensor3->body->SetTransform({ PIXEL_TO_METERS(NewPosX3),PIXEL_TO_METERS(NewPosY_Bot) }, 0);

		float NewPosY_Box = Box3_Position.y + 32 - 16;
		Box3_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX3),PIXEL_TO_METERS(NewPosY_Box) }, 0);

	}

	//Box 4

	NewPosX4 = Box4_Position.x + 16;

	if (top_collision4) {

		Box4_Position.y = Box4_Position.y + 2;

		float NewPosY_Top = Box4_Position.y;
		TopSensor4->body->SetTransform({ PIXEL_TO_METERS(NewPosX4),PIXEL_TO_METERS(NewPosY_Top) }, 0);

		float NewPosY_Bot = Box4_Position.y + 32;
		BottomSensor4->body->SetTransform({ PIXEL_TO_METERS(NewPosX4),PIXEL_TO_METERS(NewPosY_Bot) }, 0);

		float NewPosY_Box = Box4_Position.y + 16;
		Box4_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX4),PIXEL_TO_METERS(NewPosY_Box) }, 0);

	}
	if (bottom_collision4) {

		Box4_Position.y = Box4_Position.y - 2;

		float NewPosY_Top = Box4_Position.y - 16;
		TopSensor4->body->SetTransform({ PIXEL_TO_METERS(NewPosX4),PIXEL_TO_METERS(Box4_Position.y) }, 0);

		float NewPosY_Bot = Box4_Position.y + 32;
		BottomSensor4->body->SetTransform({ PIXEL_TO_METERS(NewPosX4),PIXEL_TO_METERS(NewPosY_Bot) }, 0);

		float NewPosY_Box = Box4_Position.y + 32 - 16;
		Box4_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX4),PIXEL_TO_METERS(NewPosY_Box) }, 0);

	}


	//Box 5

	NewPosX5 = Box5_Position.x + 16;

	if (top_collision5) {

		Box5_Position.y = Box5_Position.y + 2;

		float NewPosY_Top = Box5_Position.y;
		TopSensor5->body->SetTransform({ PIXEL_TO_METERS(NewPosX5),PIXEL_TO_METERS(NewPosY_Top) }, 0);

		float NewPosY_Bot = Box5_Position.y + 32;
		BottomSensor5->body->SetTransform({ PIXEL_TO_METERS(NewPosX5),PIXEL_TO_METERS(NewPosY_Bot) }, 0);

		float NewPosY_Box = Box5_Position.y + 16;
		Box5_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX5),PIXEL_TO_METERS(NewPosY_Box) }, 0);

	}
	if (bottom_collision5) {

		Box5_Position.y = Box5_Position.y - 2;

		float NewPosY_Top = Box5_Position.y - 16;
		TopSensor5->body->SetTransform({ PIXEL_TO_METERS(NewPosX5),PIXEL_TO_METERS(Box5_Position.y) }, 0);

		float NewPosY_Bot = Box5_Position.y + 32;
		BottomSensor5->body->SetTransform({ PIXEL_TO_METERS(NewPosX5),PIXEL_TO_METERS(NewPosY_Bot) }, 0);

		float NewPosY_Box = Box5_Position.y + 32 - 16;
		Box5_Collider->body->SetTransform({ PIXEL_TO_METERS(NewPosX5),PIXEL_TO_METERS(NewPosY_Box) }, 0);

	}

	app->render->DrawTexture(texture, Box1_Position.x, Box1_Position.y);
	app->render->DrawTexture(texture, Box2_Position.x, Box2_Position.y);
	app->render->DrawTexture(texture, Box3_Position.x, Box3_Position.y);
	app->render->DrawTexture(texture, Box4_Position.x, Box4_Position.y);
	app->render->DrawTexture(texture, Box5_Position.x, Box5_Position.y);

}