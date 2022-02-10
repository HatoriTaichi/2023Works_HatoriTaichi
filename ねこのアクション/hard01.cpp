//---------------------------
//インクルードファイル
//---------------------------
#include "hard01.h"
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
bool g_bHd01 = true;
bool g_bPlayer3 = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitHdStage01(void)
{
	g_bHd01 = true;
	g_bPlayer3 = true;

	if (g_bHd01 == true)
	{
		InitBg();
		SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		InitPlayer();
		SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

		InitBlock();
		SetBlock(D3DXVECTOR3(0.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, SCREEN_HEIGHT - 30.0f, 2.0f, 8.0f, 0);

		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 750, 100.0f, 12.8f, 2.0f, 0);
		SetBlock(D3DXVECTOR3(820.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 750, 100.0f, 12.8f, 2.0f, 0);

		SetBlock(D3DXVECTOR3(250.0f, SCREEN_HEIGHT - 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 100.0f, 12.8f, 2.0f, 0);

		SetBlock(D3DXVECTOR3(450.0f, SCREEN_HEIGHT - 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100.0f, 1.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(550.0f, SCREEN_HEIGHT - 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 100.0f, 1.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(650.0f, SCREEN_HEIGHT - 350.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 100.0f, 1.0f, 1.0f, 0);

		InitTrap();
		SetTrap(D3DXVECTOR3(550.0f, SCREEN_HEIGHT - 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 100.0f, 1.0f, 5.0f, 1);

		InitEnemy();

		InitBullet();

		InitScore();

		InitTimer();

		InitLife();

		InitPause();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitHdStage01(void)
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
void UpdateHdStage01(void)
{
	PLAYER			*pPlayer;
	static int		 nCnt;

	pPlayer = GetPlayer();

	if (GetKeyboardTrigger(DIK_E) == true || GetKeyboardTrigger(DIK_X) == true)
	{
		g_bHd01 = g_bHd01 ? false : true;
	}
	if (g_bHd01 == true)
	{
		nCnt++;

		UpdateBg();

		UpdatePlayer();

		UpdateBlock();

		UpdateTrap();

		UpdateEnemy();

		UpdateBullet();

		UpdateScore();

		UpdateTimer();

		UpdateLife();
		if (nCnt >= 600)
		{
			SetBullet(D3DXVECTOR3(200.0f, SCREEN_HEIGHT - 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 2);
			SetBullet(D3DXVECTOR3(780.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 2);
			nCnt = 0;
		}
		if (pPlayer->pos.x + pPlayer->fWidth / 2 >= 750 &&
			pPlayer->pos.x - pPlayer->fWidth / 2 <= 820 &&
			g_bPlayer3 == true)
		{
			SetEnemy(D3DXVECTOR3(780.0f, 150.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 50.0f, 50.0f, 1, 1);
			g_bPlayer3 = false;
		}
		if (pPlayer->bUse == false)
		{
			g_bPlayer3 = true;
		}
	}
	else if (g_bHd01 == false)
	{
		UpdateBg();

		g_bHd01 = UpdatePause();
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawHdStage01(void)
{
	if (g_bHd01 == true)
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
	else if (g_bHd01 == false)
	{
		DrawBg();

		DrawPause();
	}
}