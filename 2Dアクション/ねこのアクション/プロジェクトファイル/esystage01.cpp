//---------------------------
//インクルードファイル
//---------------------------
#include "esystage01.h"
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
#include "pause.h"

//---------------------------
//グローバル変数
//---------------------------
bool g_bEs01 = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitEsStage01(void)
{
	g_bEs01 = true;

	if (g_bEs01 == true)
	{
		InitBg();
		SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		InitPlayer();
		SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

		InitBlock();
		SetBlock(D3DXVECTOR3(0.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, SCREEN_HEIGHT - 30.0f, 2.0f, 8.0f, 0);
		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 100.0f, 12.8f, 2.0f, 0);

		SetBlock(D3DXVECTOR3(260.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 450.0f, 2.0f, 4.0f, 0);

		SetBlock(D3DXVECTOR3(150.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 2.5, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 260, 100.0f, 4.0f, 2.0f, 0);
		SetBlock(D3DXVECTOR3(510.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 1.0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 260, 100.0f, 4.0f, 2.0f, 0);
		SetBlock(D3DXVECTOR3(850.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 1.0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400, 100.0f, 5.8f, 2.0f, 0);

		SetBlock(D3DXVECTOR3(460.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 7.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 65.0f, 25.0f, 1.0f, 0.5f, 0);
		SetBlock(D3DXVECTOR3(650.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 10.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 65.0f, 25.0f, 1.0f, 0.5f, 0);
		SetBlock(D3DXVECTOR3(850.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 12.5f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 65.0f, 25.0f, 1.0f, 0.5f, 0);
		SetBlock(D3DXVECTOR3(1020.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 17.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 70.0f, 25.0f, 1.0f, 0.5f, 0);

		SetBlock(D3DXVECTOR3(1200.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f * 2, SCREEN_HEIGHT - 30.0f, 2.0f, 8.0f, 0);

		SetBlock(D3DXVECTOR3(510.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 15.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 25.0f, 1.0f, 1.0f, 2);
		SetBlock(D3DXVECTOR3(1070.0f, 180, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 25.0f, 1.0f, 1.0f, 2);

		SetBlock(D3DXVECTOR3(155.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 3.5, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 100.0f, 20.0f, 2.0f, 1.0f, 1);

		InitEnemy();
		SetEnemy(D3DXVECTOR3(900 - ENEMY_X_SIZE, SCREEN_HEIGHT - BLOCK_Y_SIZE * 1.0, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMY_X_SIZE, ENEMY_Y_SIZE, 0, 1);
		SetEnemy(D3DXVECTOR3(600 - ENEMY_X_SIZE, SCREEN_HEIGHT - BLOCK_Y_SIZE * 1.0, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMY_X_SIZE, ENEMY_Y_SIZE, 0, 1);
		SetEnemy(D3DXVECTOR3(300 - ENEMY_X_SIZE, SCREEN_HEIGHT - BLOCK_Y_SIZE * 2.5, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMY_X_SIZE, ENEMY_Y_SIZE, 0, 1);
		SetEnemy(D3DXVECTOR3(155.0f + 50.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 3.5 - 10.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMY_X_SIZE, ENEMY_Y_SIZE, 1, 1);

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
void UninitEsStage01(void)
{
	UninitBg();

	UninitPlayer();

	UninitBlock();

	UninitEnemy();

	UninitBullet();

	UninitPause();
}

//---------------------------
//更新処理
//---------------------------
void UpdateEsStage01(void)
{
	if (GetKeyboardTrigger(DIK_E) == true || GetKeyboardTrigger(DIK_X) == true)
	{
		g_bEs01 = g_bEs01 ? false : true;
	}
	if (g_bEs01 == true)
	{
		UpdateBg();

		UpdatePlayer();

		UpdateBlock();

		UpdateEnemy();

		UpdateBullet();

		UpdateScore();

		UpdateTimer();

		UpdateLife();
	}
	else if (g_bEs01 == false)
	{
		UpdateBg();

		g_bEs01 = UpdatePause();
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawEsStage01(void)
{
	if (g_bEs01 == true)
	{
		DrawBg();

		DrawPlayer();

		DrawBlock();

		DrawEnemy();

		DrawBullet();

		DrawScore();

		DrawTimer();

		DrawLife();
	}
	else if (g_bEs01 == false)
	{
		DrawBg();

		DrawPause();
	}
}