//---------------------------
//インクルードファイル
//---------------------------
#include "herd03.h"
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
bool g_bHd03 = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitHdStage03(void)
{
	g_bHd03 = true;

	if (g_bHd03 == true)
	{
		InitBg();
		SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		InitPlayer();
		SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

		InitBlock();
		SetBlock(D3DXVECTOR3(0.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100.0f, 1.0f, 1.0f, 0);

		SetBlock(D3DXVECTOR3(100.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 100, 25.0f, 1.0f, 1.0f, 1);
		SetBlock(D3DXVECTOR3(200.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50, SCREEN_HEIGHT, 1.0f, 7.0f, 0);
		SetBlock(D3DXVECTOR3(250.0f, 75.0f, 0.0f), D3DXVECTOR3(1.5f, 0.0f, 0.0f), 100, 25.0f, 1.0f, 1.0f, 1);

		SetBlock(D3DXVECTOR3(250.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH - 600, 50.0f, 7.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300, 500, 2.0f, 4.0f, 0);

		SetBlock(D3DXVECTOR3(400, 350.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH - 600, 50.0f, 5.0f, 1.0f, 0);

		SetBlock(D3DXVECTOR3(250.0f, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 1.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(375.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25, 25, 1.0f, 1.0f, 2);
		SetBlock(D3DXVECTOR3(450.0f, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 1.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(650.0f, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 1.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 100, 1.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(975.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25, 25, 1.0f, 1.0f, 2);
		SetBlock(D3DXVECTOR3(1050.0f, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 100, 4.0f, 1.0f, 0);

		InitTrap();
		SetTrap(D3DXVECTOR3(250.0f, 115.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH - 600, 35.0f, 20.0f, 1.0f, 3);
		SetTrap(D3DXVECTOR3(250.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH - 600, 35.0f, 20.0f, 1.0f, 0);

		InitEnemy();
		SetEnemy(D3DXVECTOR3(450.0f, 345.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 50.0f, 50.0f, 1, 1);

		InitBullet();

		InitPause();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitHdStage03(void)
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
void UpdateHdStage03(void)
{
	PLAYER			*pPlayer;

	pPlayer = GetPlayer();
	if (GetKeyboardTrigger(DIK_E) == true || GetKeyboardTrigger(DIK_X) == true)
	{
		g_bHd03 = g_bHd03 ? false : true;
	}
	if (g_bHd03 == true)
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
	}
	else if (g_bHd03 == false)
	{
		UpdateBg();

		g_bHd03 = UpdatePause();
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawHdStage03(void)
{
	if (g_bHd03 == true)
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
	else if (g_bHd03 == false)
	{
		DrawBg();

		DrawPause();
	}
}