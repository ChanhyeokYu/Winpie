#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Monster.h"
#include "ObjectManager.h"

//Init을 통해 필요한 오브젝트를 초기화 시점에 생성
// 후에 Update와 Render를 통해 각 오브젝트 갱신

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	// 사용할 오브젝트 생성
	Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
	// 생성된 오브젝의 초기 위치 조정
	player->SetPos(Pos{400,400});
	// 생성된 오브젝를 매니저에 등록
	GET_SINGLE(ObjectManager)->Add(player);
	for (uint32 i = 0; i < 5; i++)
	{
		Monster* monster = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster->SetPos(Pos{ static_cast<float>((i+1)*100),100});
		GET_SINGLE(ObjectManager)->Add(monster);
	}

}

void GameScene::Update()
{
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
	{
		object->Update();
	}
}

void GameScene::Render(HDC hdc)
{
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
	{
		object->Render(hdc);
	}
}
