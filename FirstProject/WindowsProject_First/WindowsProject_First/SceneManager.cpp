#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "GameScene.h"
#include "EditScene.h"

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	// ������� �޾ƿ� �� Ÿ�Կ� ���� ������Ʈ
	if (_scene)
	{
		_scene->Update();
	}
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
	{
		_scene->Render(hdc);
	}
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneManager::ChangeSdcene(SceneType sceneType)
{
	// �� ��ü

	// ��ü �� ���� ���� ��� ����
	if (_sceneType == sceneType)
	{
		return;
	}
	// ��ü�� �� �غ�
	Scene* newScene = nullptr;

	// Ÿ�Կ� �´� �� ��ü
	switch (sceneType)
	{
	case SceneType::None:
		break;
	case SceneType::DevScene:
		newScene = new DevScene();
		break;
	case SceneType::GameScene:
		newScene = new GameScene();
		break;
	case SceneType::EditScene:
		newScene = new EditScene();
		break;
	default:
		break;
	}

	// ���� �� ����
	SAFE_DELETE(_scene);

	// ���� ���� ���ο� �� ����
	_scene = newScene;
	_sceneType = sceneType;

	// ���ο� �� �ʱ�ȭ
	newScene->Init();

}