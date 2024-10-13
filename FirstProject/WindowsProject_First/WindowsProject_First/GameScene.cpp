#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Monster.h"
#include "ObjectManager.h"

//Init�� ���� �ʿ��� ������Ʈ�� �ʱ�ȭ ������ ����
// �Ŀ� Update�� Render�� ���� �� ������Ʈ ����

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	// ����� ������Ʈ ����
	Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
	// ������ �������� �ʱ� ��ġ ����
	player->SetPos(Pos{400,400});
	// ������ �������� �Ŵ����� ���
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