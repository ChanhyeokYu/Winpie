#include "pch.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "InputManager.h"

TilemapActor::TilemapActor()
{
}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();
}

void TilemapActor::Tick()
{
	Super::Tick();

	TilePicking();

}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_tilemap == nullptr)
	{
		return;
	}

	if (_showDebug == false)
	{
		return;
	}

	const VectorInt mapSize = _tilemap->GetMapSize();
	const int32 tileSize = _tilemap->GetTileSize();
	vector<vector<Tile>>& tiles = _tilemap->GetTiles();

	Sprite* spriteO = GET_SINGLE(ResourceManager)->GetSprite(L"TileO");
	Sprite* spriteX = GET_SINGLE(ResourceManager)->GetSprite(L"TileX");

	Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	int32 leftX = (static_cast<int32>(cameraPos.x) - GWinSizeX / 2);
	int32 leftY = (static_cast<int32>(cameraPos.y) - GWinSizeY / 2);
	int32 rigthX = (static_cast<int32>(cameraPos.x) + GWinSizeX / 2);
	int32 rigthY = (static_cast<int32>(cameraPos.y) + GWinSizeY / 2);

	int32 startX = (leftX - _pos.x) / TILE_SIZEX;
	int32 startY = (leftY - _pos.y) / TILE_SIZEY;
	int32 endX = (rigthX - _pos.x) / TILE_SIZEX;
	int32 endY = (rigthY - _pos.y) / TILE_SIZEY;



	for (int32 y = startY; y <= endY; y++)
	{
		for (int32 x = startX; x<= endX; x++)
		{
			if (x < 0 || x >= mapSize.x)
			{
				continue;
			}
			if (y < 0 || y >= mapSize.y)
			{
				continue;
			}

			switch (tiles[y][x].value)
			{
			case 0:

				::GdiTransparentBlt(
					hdc,
					_pos.x + x * TILE_SIZEX - (static_cast<int32>(cameraPos.x - GWinSizeX /2)),
					_pos.y + y * TILE_SIZEY - (static_cast<int32>(cameraPos.y - GWinSizeY / 2)),
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetDC(),
					spriteO->GetPos().x,
					spriteO->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetTransparent()
				);

				break;
			case 1:

				::GdiTransparentBlt(
					hdc,
					_pos.x + x * TILE_SIZEX - (static_cast<int32>(cameraPos.x - GWinSizeX / 2)),
					_pos.y + y * TILE_SIZEY - (static_cast<int32>(cameraPos.y - GWinSizeY / 2)),
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetDC(),
					spriteX->GetPos().x,
					spriteX->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetTransparent()
				);
				break;

			default:
				break;
			}

		}
	}

}

void TilemapActor::TilePicking()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		Vector cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		int32 screenX = cameraPos.x - GWinSizeX / 2;
		int32 screenY = cameraPos.y - GWinSizeY / 2;

		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		int32 x = posX / TILE_SIZEX;
		int32 y = posY / TILE_SIZEY;

		Tile* tile = _tilemap->GetTileAt({ x,y });
		if (tile->value == 0)
		{
			tile->value = 1;
		}
		else
		{
			tile->value = 0;
		}

	}
}