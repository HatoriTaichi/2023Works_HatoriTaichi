//---------------------------
//インクルードファイル
//---------------------------
#include "hard02.h"
#include "bullet.h"
#include "block.h"
#include "enemy.h"
#include "input.h"
#include "player.h"
#include "bg.h"
#include "score.h"
#include "timer.h"
#include "pause.h"
#include "life.h"
#include "trap.h"

//---------------------------
//グローバル変数
//---------------------------
bool g_bHd02 = true;
bool g_bPlayer4 = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitHdStage02(void)
{
	g_bHd02 = true;
	g_bPlayer4 = true;

	if (g_bHd02 == true)
	{
		InitBg();
		SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		InitPlayer();
		SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 670.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

		InitBlock();
		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 100.0f, 1.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(0.0f, 670.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100.0f, 1.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(100.0f, 670.0f, 0.0f), D3DXVECTOR3(0.0f, -1.5f, 0.0f), 100, 25.0f, 1.0f, 1.0f, 1);

		SetBlock(D3DXVECTOR3(300.0f, 670.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100.0f, 1.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 400.0f, 1.0f, 4.0f, 0);
		SetBlock(D3DXVECTOR3(400.0f, 670.0f, 0.0f), D3DXVECTOR3(0.0f, -1.5f, 0.0f), 100, 25.0f, 1.0f, 1.0f, 1);

		SetBlock(D3DXVECTOR3(650.0f, 670.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 100, 25.0f, 1.0f, 1.0f, 1);
		SetBlock(D3DXVECTOR3(650.0f, 470.0f, 0.0f), D3DXVECTOR3(1.5f, 0.0f, 0.0f), 100, 25.0f, 1.0f, 1.0f, 1);
		SetBlock(D3DXVECTOR3(650.0f, 270.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 100, 25.0f, 1.0f, 1.0f, 1);

		SetBlock(D3DXVECTOR3(1080.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300, 200.0f, 1.0f, 0.8f, 0);

		InitTrap();
		SetTrap(D3DXVECTOR3(300.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 50.0f, 4.0f, 1.0f, 0);
		SetTrap(D3DXVECTOR3(250.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 400.0f, 1.0f, 8.0f, 2);

		InitEnemy();
		SetEnemy(D3DXVECTOR3(300.0f, 670.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 50.0f, 50.0f, 0, 1);

		InitBullet();

		InitPause();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitHdStage02(void)
{
	UninitBg();

	UninitPlayer();

	UninitBlock();

	UninitTrap();

	UninitEnemy();

	UninitBullet();

	UninitPause();
}

//---------------------------
//更新処理
//---------------------------
void UpdateHdStage02(void)
{
	PLAYER			*pPlayer;

	pPlayer = GetPlayer();
	if (GetKeyboardTrigger(DIK_E) == true || GetKeyboardTrigger(DIK_X) == true)
	{
		g_bHd02 = g_bHd02 ? false : true;
	}
	if (g_bHd02 == true)
	{
		UpdateBg();

		UpdatePlayer();

		UpdateBlock();

		UpdateTrap();

		UpdateEnemy();

		UpdateBullet();

		UpdateScore();

		UpdateTimer();

		UpdateLife();

		if (pPlayer->pos.x - pPlayer->fWidth / 2 >= 700 &&
			CollisionBlock(&pPlayer->pos, &pPlayer->posold, &pPlayer->move, pPlayer->fWidth, pPlayer->fHeight, 0) == true &&
			g_bPlayer4 == true)
		{
			SetTrap(D3DXVECTOR3(650.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 0.0f, 0.0f), 20.0f, SCREEN_HEIGHT, 1.0f, 15.0f, 1);
			g_bPlayer4 = false;
		}
		if (pPlayer->bUse == false)
		{
			g_bPlayer4 = true;
		}
	}
	else if (g_bHd02 == false)
	{
		UpdateBg();

		g_bHd02 = UpdatePause();
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawHdStage02(void)
{
	if (g_bHd02 == true)
	{
		DrawBg();

		DrawPlayer();

		DrawBlock();

		DrawTrap();

		DrawEnemy();

		DrawBullet();

		DrawScore();

		DrawTimer();

		DrawLife();
	}
	else if (g_bHd02 == false)
	{
		DrawBg();

		DrawPause();
	}
}